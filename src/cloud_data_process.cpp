#include "cloud_data_process.h"
#include <QMutexLocker>
#include <QPair>
#include <pcl/common/transforms.h>
#include <pcl/filters/statistical_outlier_removal.h>

//TODO:目前不知道此参数具体用意
const int POINTS_MIN_SIZE = 100;
//TODO:经验值？
const double MIN_SPEED = 5.311;

SingleRadarProcess::SingleRadarProcess(int nums)
    :mRadarNums(nums)
{
    mHistoryFramesObs.clear();

    init();
}

SingleRadarProcess::~SingleRadarProcess()
{

}

bool SingleRadarProcess::detectorOutline(int radarId, ExinovaCloudData& data)
{

    QMutexLocker locker(&mMutex);
    std::map<int, DetectOutlineData>::iterator it = mOutlineMap.find(radarId);
    if (it == mOutlineMap.end())
    {
        return false;
    }
    if (!it->second.enable)
    {
        return false;
    }
    if (it->second.data.data()->empty()
        && data.data()->empty())
    {
        return false;
    }
    else if (it->second.data.data()->empty()
        && !data.data()->empty())
    {
        it->second.data += data;
        return false;
    }
    else if (!it->second.data.data()->empty()
        && !data.data()->empty())
    {
        if (coordinataTrans(radarId, it->second.data))
        {
            it->second.data += data;
        }
        return false;
    }
    else if (!it->second.data.data()->empty()
        && data.data()->empty())
    {
        data += it->second.data;
        it->second.data.data()->clear();
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

double SingleRadarProcess::detectorSpeed(int radarId, ExinovaCloudData& data)
{
    QMutexLocker locker(&mMutex);
    std::map<int, DetectSpeedData>::iterator it = mSpeedMap.find(radarId);
    if (it == mSpeedMap.end())
    {
        return 0;
    }
    else
    {
        it->second.data = data;
        double speed = countSpeed(radarId, it->second.data, true);
        if (speed > MIN_SPEED)
        {
            it->second.speed = speed;
            return speed;
        }
        else
        {
            return 0;
        }
    }
}

void SingleRadarProcess::init()
{
    for (int i = 0; i < mRadarNums; ++i)
    {
        DetectSpeedData speedData;
        speedData.speed = 0;
        DetectOutlineData outlineData;
        std::vector<std::vector<OBJ>> frameObs;
        //mSpeedMap.insert(i, speedData);
        //mOutlineMap.insert(i, outlineData);
        //mHistoryFramesObs.insert(i, frameObs);
        mSpeedMap[i] = speedData;
        mOutlineMap[i] = outlineData;
        mHistoryFramesObs[i] = frameObs;
    }
}

double SingleRadarProcess::countSpeed(int radarId, ExinovaCloudData& data, bool isReverse)
{
    //历史数据
    std::map<int, std::vector<std::vector<OBJ>>>::iterator iter;
    iter = mHistoryFramesObs.find(radarId);
    if (iter == mHistoryFramesObs.end())
        return 0;
    PointCloudT::Ptr cloudData = data.data();
    if (isReverse)
    {
        std::reverse(cloudData->points.begin(), cloudData->points.end());
    }

    int obStartIndex = 0;
    int obEndIndex = 0;
    //当前帧目标统计
    std::vector<OBJ> currentFrameObs;
    for (int i = 1; i < cloudData->size(); ++i)
    {
        if (cloudData->at(i).y < THRESHOLD && cloudData->at(i - 1).y > THRESHOLD)
        {
            obStartIndex = i;
        }
        if (cloudData->at(i).y > THRESHOLD && cloudData->at(i - 1).y < THRESHOLD)
        {
            obEndIndex = i - 1;
            OBJ tmpOb;
            tmpOb.startPoint = cloudData->at(obStartIndex).x;
            tmpOb.stopPoint = cloudData->at(obEndIndex).x;
            tmpOb.distance = tmpOb.stopPoint - tmpOb.startPoint;
            currentFrameObs.push_back(tmpOb);
        }
    }

    //如果当前帧没有目标，则刷新历史数据，并返回0
    if (currentFrameObs.empty())
    {
        if (iter->second.size() < 10)
        {
            iter->second.push_back(currentFrameObs);
        }
        else
        {
            iter->second.erase(iter->second.begin());
            iter->second.push_back(currentFrameObs);
        }
        return 0;
    }

    //选取中间目标作为跟踪目标
    OBJ trackedOb;
    int obIndex = -1;
    double minDis = -100;
    for (int i = 0; i < currentFrameObs.size(); ++i)
    {
        if (currentFrameObs[i].startPoint < 0 && currentFrameObs[i].stopPoint > 0)
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
            if (currentFrameObs[i].stopPoint < 0 && currentFrameObs[i].stopPoint > minDis)
            {
                minDis = currentFrameObs[i].stopPoint;
                obIndex = i;
            }
        }
    }
    //如果找到可追踪对象，则确认追踪对象，否则更新历史数据并返回0
    if (obIndex != -1)
    {
        trackedOb = currentFrameObs[obIndex];
    }
    else
    {
        if (iter->second.size() < 10)
        {
            iter->second.push_back(currentFrameObs);
        }
        else
        {
            iter->second.erase(iter->second.begin());
            iter->second.push_back(currentFrameObs);
        }

        return 0;
    }
    //追溯历史帧目标
    std::vector<OBJ> trackedOBs;
    trackedOBs.push_back(trackedOb);
    OBJ tmpOb = trackedOb;
    for (int i = iter->second.size() - 1; i >= 0; --i)
    {
        double minTmpDis = 100;
        int tmpIndex = -1;
        for (int j = 0; j < iter->second[i].size(); ++j)
        {
            if (iter->second[i][j].startPoint > 0) continue;
            double endPointDis = std::abs(iter->second[i][j].stopPoint - tmpOb.stopPoint);
            double startPointDis = std::abs(iter->second[i][j].startPoint - tmpOb.startPoint);
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
            trackedOBs.push_back(iter->second[i][tmpIndex]);
            tmpOb = iter->second[i][tmpIndex];
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
    if (iter->second.size() < 10)
    {
        iter->second.push_back(currentFrameObs);
    }
    else
    {
        iter->second.erase(iter->second.begin());
        iter->second.push_back(currentFrameObs);
    }

    return averageSpeed * 50;
}

bool SingleRadarProcess::coordinataTrans(int radarId, ExinovaCloudData& data)
{
    std::map<int, DetectSpeedData>::const_iterator it = mSpeedMap.find(radarId);
    if (it == mSpeedMap.end())
    {
        return false;
    }
    else
    {
        PointCloudT transData;
        Eigen::Affine3f transForm = Eigen::Affine3f::Identity();
        transForm.translation() << 0.0, 0.0, 0.02 * it->second.speed;
        pcl::transformPointCloud(*data.data(), transData, transForm);
        data.data()->clear();
        data += transData;
        return true;
    }
}

void SingleRadarProcess::updateXYZ(ExinovaCloudData& data)
{
    double X_MIN, X_MAX, Y_MIN, Y_MAX, Z_MIN, Z_MAX;
    X_MIN = 9999;
    X_MAX = -9999;
    Y_MIN = 9999;
    Y_MAX = -9999;
    Z_MIN = 9999;
    Z_MAX = -9999;

    for (auto point : data.data()->points)
    {
        if (point.x < X_MIN)
            X_MIN = point.x;
        if (point.y < Y_MIN)
            Y_MIN = point.y;
        if (point.z < Z_MIN)
            Z_MIN = point.z;
        if (point.x > X_MAX)
            X_MAX = point.x;
        if (point.y > Y_MAX)
            Y_MAX = point.y;
        if (point.z > Z_MAX)
            Z_MAX = point.z;
    }
    double X = abs(X_MAX - X_MIN);
    double Y = abs(Y_MAX - Y_MIN);
    double Z = abs(Z_MAX - Z_MIN);
    Eigen::Affine3f transForm = Eigen::Affine3f::Identity();
    transForm.translation() << 0.0, (0 - THRESHOLD), (0 - (Z / 2));
    PointCloudT transData;
    pcl::transformPointCloud(*data.data(), transData, transForm);
    data.data()->clear();
    data += transData;
}

double SingleRadarProcess::getSpeed(int id)
{
    QMutexLocker locker(&mMutex);
    std::map<int, DetectSpeedData>::const_iterator it = mSpeedMap.find(id);
    if (it == mSpeedMap.end())
    {
        return 0;
    }
    else
    {
        return it->second.speed;
    }
}

void SingleRadarProcess::detectorOutliers(int num, ExinovaCloudData& data)
{
    pcl::PointCloud<pcl::PointXYZRGBA> outliers_data;
    pcl::StatisticalOutlierRemoval<pcl::PointXYZRGBA> sor;
    sor.setInputCloud(data.data());
    sor.setMeanK(num);
    sor.setStddevMulThresh(1.0);
    sor.filter(outliers_data);
    data.data()->clear();
    data += outliers_data;
}
