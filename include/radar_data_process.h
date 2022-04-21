#ifndef EXINOVA_G524_RADAR_DATA_PROCESS_H__
#define EXINOVA_G524_RADAR_DATA_PROCESS__H__
/*****************************************************************************
* @FileName:radar_data_process.h
* @Author: chujiajun
* @CreatTime: 2022/4/13
* @Descriptions: 未使用 
* @Version: ver 1.0
*****************************************************************************/
#include <vector>
#include <map>
#include <mutex>
#include "param_def.h"
typedef struct ObjData
{
    //起始点
    float startPoint;
    //终止点
    float stopPoint;
    //距离
    float distance;
}ObjData;

typedef struct OutlineData
{
    //是否可以数据拼接
    bool enable;
    //拼接的数据
    ExinovaCloudData data;
}OutlineData;

typedef struct SpeedData
{
    //速度
    double speed;
    //数据
    ExinovaCloudData data;
}SpeedData;

class SingleRadarDataProcess
{
public:
    SingleRadarDataProcess();
    ~SingleRadarDataProcess();
    //获取轮廓
    bool detectorOutline(ExinovaCloudData& data);
    //获取速度
    double detectorSpeed(ExinovaCloudData& data);
    //StatisticalOutlierRemoval滤波
    void staOutlierRemovalFilter(ExinovaCloudData& data);
private:
    void init();
    //计算速度
    double countSpeed(ExinovaCloudData& data, bool isReverse);
    //根据速度拼接数据
    bool coordinataTrans(ExinovaCloudData& data);
    //移除无效点
    bool removeZeroFromCloud(ExinovaCloudData& data);
private:
    //锁
    std::mutex mMutex;
    //基于速度拼接数据
    OutlineData mOutlineData;
    //速度数据
    SpeedData mSpeedData;
    //历史帧
    std::vector<std::vector<ObjData>> mHistoryFramesObs;
};
#endif // EXINOVA_G524_RADAR_DATA_PROCESS__H__
