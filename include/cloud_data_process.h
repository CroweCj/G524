#ifndef OSIGHT_RADAR_CLOUD_DATA_PROCESS_H__
#define OSIGHT_RADAR_CLOUD_DATA_PROCESS__H__
/*****************************************************************************
* @FileName:cloud_data_process.h
* @Author: 褚佳俊
* @CreatTime: 2022/3/21
* @Descriptions:用于处理点数数据
* @Version: ver 1.0
*****************************************************************************/

#include <QVector>
#include <QMap>
#include "osight_def.h"

typedef struct OBJ
{
    //起始点
    float startPoint;
    //终止点
    float stopPoint;
    //距离
    float distance;
}OBJ;

class SingleRadarProcess
{
public:
    SingleRadarProcess();

    ~SingleRadarProcess();
    /**************
    * @brief: 测速
    * @param[in]:id 区分雷达
    * @param[in]:cloudData 点云数据
    * @param[in]:isReverse 数据反转标志
    * @@return:（double）速度  
    ***************/
    double countSpeed(int id, PointCloudT::Ptr cloudData, bool isReverse);

private:
    //存储历史帧对象
    QMap<int, QVector<QVector<OBJ>>> mHistoryFramesObs;

    //门限（地面到雷达的距离）-用于计算速度
    static double mThreshold;
};
#endif // OSIGHT_RADAR_CLOUD_DATA_PROCESS__H__
