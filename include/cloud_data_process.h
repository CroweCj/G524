#ifndef EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS_H__
#define EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS__H__
/*****************************************************************************
* @FileName:cloud_data_process.h
* @Author: 褚佳俊
* @CreatTime: 2022/3/21
* @Descriptions:用于处理点数数据
* @Version: ver 1.0
*****************************************************************************/

#include <vector>
#include <map>
#include "param_def.h"
typedef struct OBJ
{
    //起始点
    float startPoint;
    //终止点
    float stopPoint;
    //距离
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

class RadarDataProcess
{
public:
    RadarDataProcess(int nums = 0);

    ~RadarDataProcess();

    enum ObjStatus
    {
        Car_In = 0,     //车辆驶入
        Car_Out,        //车辆离开
        Car_Run,        //车辆在跑
        None            //无车辆
    };
    //获取轮廓
    bool detectorOutline(int radarId,int speedRadarId, ExinovaCloudData& data);
    //获取速度
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
    
    bool removeZeroFromCloud(ExinovaCloudData& data);
private:
    //雷达数量
    int mRadarNums;
    //锁
    QMutex mMutex;
    //速度
    std::map<int, DetectSpeedData> mSpeedMap;
    //轮廓
    std::map<int, DetectOutlineData> mOutlineMap;
    //历史帧
    std::map<int, std::vector<std::vector<OBJ>>> mHistoryFramesObs;
    //
    std::map<int, std::atomic_bool> mIsHaveObjMap;
    //目标状态
    std::map <int,ObjStatus> mStatusMap;
};
#endif // EXINOVA_G524_EXINOVA_CLOUD_DATA_PROCESS__H__
