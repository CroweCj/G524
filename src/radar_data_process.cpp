#include "radar_data_process.h"
#include <pcl/common/transforms.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/extract_indices.h>

//TODO:目前不知道此参数具体用意
const int POINTS_MIN_SIZE = 100;
//TODO:经验值？
const double MIN_SPEED = 5.311;

SingleRadarDataProcess::SingleRadarDataProcess()
{
    mHistoryFramesObs.clear();
    init();
}

SingleRadarDataProcess::~SingleRadarDataProcess()
{
}

bool SingleRadarDataProcess::detectorOutline(ExinovaCloudData& data)
{
    std::lock_guard<std::mutex> lock(mMutex);
    if (!mOutlineData.enable)
    {
        return false;
    }
    bool isOutlineDataEmpty = mOutlineData.data.data()->empty();
    staOutlierRemovalFilter(data);
    bool isDataEmpty = data.data()->empty();
    //无车辆
    if (isOutlineDataEmpty && isDataEmpty)
    {
        return false;
    }
    //车辆进入
    else if (isOutlineDataEmpty && !isDataEmpty)
    {
        mOutlineData.data += data;
        return false;
    }
    //车辆在监测范围内行驶
    else if (!isOutlineDataEmpty && !isDataEmpty)
    {
        if (coordinataTrans(mOutlineData.data))
        {
            mOutlineData.data += data;
        }
        return false;
    }
    //TODO:车辆驶离(判断条件需要更新)
    else if (!isOutlineDataEmpty && isDataEmpty)
    {
        data += mOutlineData.data;
        mOutlineData.data.data()->clear();
        if (data.data()->points.size() <= POINTS_MIN_SIZE)
        {
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }

    return true;
}

double SingleRadarDataProcess::detectorSpeed(ExinovaCloudData& data)
{
    std::lock_guard<std::mutex> lock(mMutex);
    mSpeedData.data.clearData();
    mSpeedData.data += data;
    //离群点移除
    staOutlierRemovalFilter(mSpeedData.data);
    //无效点移除
    removeZeroFromCloud(mSpeedData.data);
    double speed = countSpeed(mSpeedData.data, true);
    if (speed > MIN_SPEED)
    {
        mSpeedData.speed = speed;
        return speed;
    }
    else
    {
        return 0;
    }
}

void SingleRadarDataProcess::staOutlierRemovalFilter(ExinovaCloudData& data)
{
    pcl::PointCloud<pcl::PointXYZRGBA> outliers_data;
    pcl::StatisticalOutlierRemoval<pcl::PointXYZRGBA> sor;
    sor.setInputCloud(data.data());
    sor.setMeanK(1);
    sor.setStddevMulThresh(1.0);
    sor.filter(outliers_data);
    data.data()->clear();
    data += outliers_data;
}

void SingleRadarDataProcess::init()
{
    //TODO
}

double SingleRadarDataProcess::countSpeed(ExinovaCloudData& data, bool isReverse)
{
    PointCloudT::Ptr cloudData = data.data();
    if (isReverse)
    {
        std::reverse(cloudData->points.begin(), cloudData->points.end());
    }
    int obStartIndex = 0;
    int obEndIndex = 0;
    //当前帧目标统计
    std::vector<ObjData> currentFrameObs;
    for (int i = 1; i < cloudData->size(); ++i)
    {
        if (cloudData->at(i).y < THRESHOLD && cloudData->at(i - 1).y > THRESHOLD)
        {
            obStartIndex = i;
        }
        if (cloudData->at(i).y > THRESHOLD && cloudData->at(i - 1).y < THRESHOLD)
        {
            obEndIndex = i - 1;
            ObjData tmpOb;
            tmpOb.startPoint = cloudData->at(obStartIndex).x;
            tmpOb.stopPoint = cloudData->at(obEndIndex).x;
            tmpOb.distance = tmpOb.stopPoint - tmpOb.startPoint;
            currentFrameObs.push_back(tmpOb);
        }
    }

    //如果当前帧没有目标，则刷新历史数据，并返回0
    if (currentFrameObs.empty())
    {
        if (mHistoryFramesObs.size() < 10)
        {
            mHistoryFramesObs.push_back(currentFrameObs);
        }
        else
        {
            mHistoryFramesObs.erase(mHistoryFramesObs.begin());
            mHistoryFramesObs.push_back(currentFrameObs);
        }
        return 0;
    }

    //选取中间目标作为跟踪目标
    ObjData trackedOb;
    int obIndex = -1;
    double minDis = -100;
    for (int i = 0; i < currentFrameObs.size(); ++i)
    {
        if (currentFrameObs[i].startPoint < 0 
            && currentFrameObs[i].stopPoint > 0)
        {
            obIndex = i;
            break;
        }
        else if (currentFrameObs[i].startPoint > 0)
        {
            continue;
        }
        else
        {
            if (currentFrameObs[i].stopPoint < 0 
                && currentFrameObs[i].stopPoint > minDis)
            {
                minDis = currentFrameObs[i].stopPoint;
                obIndex = i;
            }
        }
    }

    //如果找到可追踪对象，则确认追踪对象，否则更新历史数据并返回0
        //如果找到可追踪对象，则确认追踪对象，否则更新历史数据并返回0
    if (obIndex != -1)
    {
        trackedOb = currentFrameObs[obIndex];
    }
    else
    {
        if (mHistoryFramesObs.size() < 10)
        {
            mHistoryFramesObs.push_back(currentFrameObs);
        }
        else
        {
            mHistoryFramesObs.erase(mHistoryFramesObs.begin());
            mHistoryFramesObs.push_back(currentFrameObs);
        }

        return 0;
    }
    //追溯历史帧目标
    std::vector<ObjData> trackedOBs;
    trackedOBs.push_back(trackedOb);
    ObjData tmpOb = trackedOb;
    for (int i = mHistoryFramesObs.size() - 1; i >= 0; --i)
    {
        double minTmpDis = 100;
        int tmpIndex = -1;
        for (int j = 0; j < mHistoryFramesObs[i].size(); ++j)
        {
            if (mHistoryFramesObs[i][j].startPoint > 0) continue;
            double endPointDis = std::abs(mHistoryFramesObs[i][j].stopPoint - tmpOb.stopPoint);
            double startPointDis = std::abs(mHistoryFramesObs[i][j].startPoint - tmpOb.startPoint);
            double dis = (endPointDis + startPointDis) / 2;
            if (dis < minTmpDis)
            {
                minTmpDis = dis;
                tmpIndex = j;
            }
        }
        if (tmpIndex == -1)
        {
            break;
        }
        else
        {
            trackedOBs.push_back(mHistoryFramesObs[i][tmpIndex]);
            tmpOb = mHistoryFramesObs[i][tmpIndex];
        }
    }

    //计算平均速度
    double endPointSpeed = 0;
    double startPointSpeed = 0;
    for (int i = 0; i < trackedOBs.size() - 1; ++i)
    {
        endPointSpeed += trackedOBs[i].stopPoint - trackedOBs[i + 1].stopPoint;
        startPointSpeed += trackedOBs[i].startPoint - trackedOBs[i + 1].startPoint;
    }
    startPointSpeed = startPointSpeed / (trackedOBs.size() - 1);
    endPointSpeed = endPointSpeed / (trackedOBs.size() - 1);
    double averageSpeed = (startPointSpeed + endPointSpeed) / 2;

    //更新历史数据
    if (mHistoryFramesObs.size() < 10)
    {
        mHistoryFramesObs.push_back(currentFrameObs);
    }
    else
    {
        mHistoryFramesObs.erase(mHistoryFramesObs.begin());
        mHistoryFramesObs.push_back(currentFrameObs);
    }

    return averageSpeed * 50;
}

bool SingleRadarDataProcess::coordinataTrans(ExinovaCloudData& data)
{
    PointCloudT transData;
    Eigen::Affine3f transForm = Eigen::Affine3f::Identity();
    transForm.translation() << 0.0, 0.0, 0.02 * mSpeedData.speed;
    pcl::transformPointCloud(*data.data(), transData, transForm);
    data.data()->clear();
    data += transData;
    return true;
}

bool SingleRadarDataProcess::removeZeroFromCloud(ExinovaCloudData& data)
{
    PointCloudT::Ptr cloud = data.data();
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices());
    pcl::ExtractIndices<PointT> extract;
    for (int i = 0; i < cloud->size(); ++i)
    {
        if (cloud->points[i].x == 0.0
            && cloud->points[i].y == 0.0
            && cloud->points[i].z == 0.0)
        {
            inliers->indices.push_back(i);
        }
    }
    extract.setInputCloud(cloud);
    extract.setIndices(inliers);
    extract.setNegative(true);
    extract.filter(*cloud);

    return true;
}
