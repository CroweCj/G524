#ifndef EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS_H__
#define EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS__H__
/*****************************************************************************
* @FileName:cloud_data_process.h
* @Author: 褚佳俊
* @CreatTime: 2022/3/21
* @Descriptions:用于处理点数数据
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

    //获取轮廓
    bool detectorOutline(int radarId, ExinovaCloudData& data);
    //获取速度
    double detectorSpeed(int radarId, ExinovaCloudData& data);

private:
    void init();
    //TODO:测速算法
    double countSpeed(int radarId, ExinovaCloudData& data, bool isReverse);
    //TODO:轮廓算法
    bool coordinataTrans(int radarId, ExinovaCloudData& data);
    //
    void updateXYZ(ExinovaCloudData& data);
private:
    //雷达数量
    int mRadarNums;
    //锁
    QMutex mMutex;
    //速度
    QMap<int, DetectSpeedData> mSpeedMap;
    //轮廓
    QMap<int, DetectOutlineData> mOutlineMap;
    //历史帧
    QMap<int, QVector<QVector<OBJ>>> mHistoryFramesObs;
};
#endif // EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS__H__
