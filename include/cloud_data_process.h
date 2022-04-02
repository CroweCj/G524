#ifndef EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS_H__
#define EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS__H__
/*****************************************************************************
* @FileName:cloud_data_process.h
* @Author: �Ҽѿ�
* @CreatTime: 2022/3/21
* @Descriptions:���ڴ����������
* @Version: ver 1.0
*****************************************************************************/

#include <QVector>
#include <QMap>
#include "param_def.h"

class SingleRadarProcess
{
public:
    SingleRadarProcess();

    ~SingleRadarProcess();

    //��ȡ����
    bool detectorOutline(int radarId, ExinovaCloudData& data);
    //��ȡ�ٶ�
    double detectorSpeed(int radarId, ExinovaCloudData& data);

private:
    void init();
    //TODO:�����㷨
    double countSpeed(int radarId, ExinovaCloudData& data, bool isReverse);
    //TODO:�����㷨
    bool coordinataTrans(int radarId, ExinovaCloudData& data);
    //
    void updateXYZ(ExinovaCloudData& data);
private:
    //�״�����
    int mRadarNums;
    //��
    QMutex mMutex;
    //�ٶ�
    QMap<int, DetectSpeedData> mSpeedMap;
    //����
    QMap<int, DetectOutlineData> mOutlineMap;
    //��ʷ֡
    QMap<int, QVector<QVector<OBJ>>> mHistoryFramesObs;
};
#endif // EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS__H__
