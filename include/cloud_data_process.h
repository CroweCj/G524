#ifndef EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS_H__
#define EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS__H__
/*****************************************************************************
* @FileName:cloud_data_process.h
* @Author: �Ҽѿ�
* @CreatTime: 2022/3/21
* @Descriptions:���ڴ����������
* @Version: ver 1.0
*****************************************************************************/

#include <vector>
#include <map>
#include "param_def.h"
typedef struct OBJ
{
    //��ʼ��
    float startPoint;
    //��ֹ��
    float stopPoint;
    //����
    float distance;
}OBJ;
typedef struct DetectSpeedData
{
    double speed;
    ExinovaCloudData data;
}DetectSpeedData;

typedef struct DetectOutlineData
{
    bool enable;
    ExinovaCloudData data;
}DetectOutlineData;

class SingleRadarProcess
{
public:
    SingleRadarProcess(int nums = 0);

    ~SingleRadarProcess();

    //��ȡ����
    bool detectorOutline(int radarId, ExinovaCloudData& data);
    //��ȡ�ٶ�
    double detectorSpeed(int radarId, ExinovaCloudData& data);
    //
    void updateXYZ(ExinovaCloudData& data);

    double getSpeed(int id);

    void detectorOutliers(int num, ExinovaCloudData& data);

    ExinovaCloudData getOutlineData(int id);

private:
    void init();

    double countSpeed(int radarId, ExinovaCloudData& data, bool isReverse);

    bool coordinataTrans(int radarId, ExinovaCloudData& data);
private:
    //�״�����
    int mRadarNums;
    //��
    QMutex mMutex;
    //�ٶ�
    std::map<int, DetectSpeedData> mSpeedMap;
    //����
    std::map<int, DetectOutlineData> mOutlineMap;
    //��ʷ֡
    std::map<int, std::vector<std::vector<OBJ>>> mHistoryFramesObs;
};
#endif // EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS__H__
