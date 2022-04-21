#ifndef EXINOVA_G524_RADAR_DATA_PROCESS_H__
#define EXINOVA_G524_RADAR_DATA_PROCESS__H__
/*****************************************************************************
* @FileName:radar_data_process.h
* @Author: chujiajun
* @CreatTime: 2022/4/13
* @Descriptions: δʹ�� 
* @Version: ver 1.0
*****************************************************************************/
#include <vector>
#include <map>
#include <mutex>
#include "param_def.h"
typedef struct ObjData
{
    //��ʼ��
    float startPoint;
    //��ֹ��
    float stopPoint;
    //����
    float distance;
}ObjData;

typedef struct OutlineData
{
    //�Ƿ��������ƴ��
    bool enable;
    //ƴ�ӵ�����
    ExinovaCloudData data;
}OutlineData;

typedef struct SpeedData
{
    //�ٶ�
    double speed;
    //����
    ExinovaCloudData data;
}SpeedData;

class SingleRadarDataProcess
{
public:
    SingleRadarDataProcess();
    ~SingleRadarDataProcess();
    //��ȡ����
    bool detectorOutline(ExinovaCloudData& data);
    //��ȡ�ٶ�
    double detectorSpeed(ExinovaCloudData& data);
    //StatisticalOutlierRemoval�˲�
    void staOutlierRemovalFilter(ExinovaCloudData& data);
private:
    void init();
    //�����ٶ�
    double countSpeed(ExinovaCloudData& data, bool isReverse);
    //�����ٶ�ƴ������
    bool coordinataTrans(ExinovaCloudData& data);
    //�Ƴ���Ч��
    bool removeZeroFromCloud(ExinovaCloudData& data);
private:
    //��
    std::mutex mMutex;
    //�����ٶ�ƴ������
    OutlineData mOutlineData;
    //�ٶ�����
    SpeedData mSpeedData;
    //��ʷ֡
    std::vector<std::vector<ObjData>> mHistoryFramesObs;
};
#endif // EXINOVA_G524_RADAR_DATA_PROCESS__H__
