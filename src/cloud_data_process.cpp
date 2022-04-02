#include "cloud_data_process.h"

//TODO:��������ֵδȷ��
double SingleRadarProcess::mThreshold = 12.5;

SingleRadarProcess::SingleRadarProcess()
{
    mHistoryFramesObs.clear();
}

SingleRadarProcess::~SingleRadarProcess()
{

}

double SingleRadarProcess::countSpeed(int id, PointCloudT::Ptr cloudData, bool isReverse)
{
    //��ʷ����
    QMap<int,QVector<QVector<OBJ>>>::iterator iter;
    iter = mHistoryFramesObs.find(id);
    if (iter == mHistoryFramesObs.end())
        return 0;

    if (isReverse) 
    {
        std::reverse(cloudData->points.begin(), cloudData->points.end());
    }

    int obStartIndex = 0;
    int obEndIndex = 0;
    //��ǰ֡Ŀ��ͳ��
    QVector<OBJ> currentFrameObs;
    for (int i = 1; i < cloudData->size(); ++i)
    {
        if (cloudData->at(i).y < mThreshold && cloudData->at(i - 1).y > mThreshold) 
        {
            obStartIndex = i;
        }
        if (cloudData->at(i).y > mThreshold && cloudData->at(i - 1).y < mThreshold) 
        {
            obEndIndex = i - 1;
            OBJ tmpOb;
            tmpOb.startPoint = cloudData->at(obStartIndex).x;
            tmpOb.stopPoint = cloudData->at(obEndIndex).x;
            tmpOb.distance = tmpOb.stopPoint - tmpOb.startPoint;
            currentFrameObs.push_back(tmpOb);
        }
    }

    //�����ǰ֡û��Ŀ�꣬��ˢ����ʷ���ݣ�������0
    if (currentFrameObs.empty()) 
    {
        if (iter.value().size()< 10) 
        {
            iter.value().push_back(currentFrameObs);
        }
        else
        {
            iter.value().erase(iter.value().begin());
            iter.value().push_back(currentFrameObs);
        }
        return 0;
    }

    //ѡȡ�м�Ŀ����Ϊ����Ŀ��
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
    //����ҵ���׷�ٶ�����ȷ��׷�ٶ��󣬷��������ʷ���ݲ�����0
    if (obIndex != -1) 
    {
        trackedOb = currentFrameObs[obIndex];
    }
    else 
    {
        if (iter.value().size() < 10)
        {
            iter.value().push_back(currentFrameObs);
        }
        else
        {
            iter.value().erase(iter.value().begin());
            iter.value().push_back(currentFrameObs);
        }

        return 0;
    }
    //׷����ʷ֡Ŀ��
    std::vector<OBJ> trackedOBs;
    trackedOBs.push_back(trackedOb);
    OBJ tmpOb = trackedOb;
    for (int i = iter.value().size() - 1; i >= 0; --i)
    {
        double minTmpDis = 100;
        int tmpIndex = -1;
        for (int j = 0; j < iter.value()[i].size(); ++j) 
        {
            if (iter.value()[i][j].startPoint > 0) continue;
            double endPointDis = std::abs(iter.value()[i][j].stopPoint - tmpOb.stopPoint);
            double startPointDis = std::abs(iter.value()[i][j].startPoint - tmpOb.startPoint);
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
            trackedOBs.push_back(iter.value()[i][tmpIndex]);
            tmpOb = iter.value()[i][tmpIndex];
        }
    }

    //����ƽ���ٶ�
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

    //������ʷ����
    if (iter.value().size() < 10)
    {
        iter.value().push_back(currentFrameObs);
    }
    else
    {
        iter.value().erase(iter.value().begin());
        iter.value().push_back(currentFrameObs);
    }

    return averageSpeed * 50;
}
