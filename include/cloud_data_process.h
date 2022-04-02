#ifndef OSIGHT_RADAR_CLOUD_DATA_PROCESS_H__
#define OSIGHT_RADAR_CLOUD_DATA_PROCESS__H__
/*****************************************************************************
* @FileName:cloud_data_process.h
* @Author: �Ҽѿ�
* @CreatTime: 2022/3/21
* @Descriptions:���ڴ����������
* @Version: ver 1.0
*****************************************************************************/

#include <QVector>
#include <QMap>
#include "osight_def.h"

typedef struct OBJ
{
    //��ʼ��
    float startPoint;
    //��ֹ��
    float stopPoint;
    //����
    float distance;
}OBJ;

class SingleRadarProcess
{
public:
    SingleRadarProcess();

    ~SingleRadarProcess();
    /**************
    * @brief: ����
    * @param[in]:id �����״�
    * @param[in]:cloudData ��������
    * @param[in]:isReverse ���ݷ�ת��־
    * @@return:��double���ٶ�  
    ***************/
    double countSpeed(int id, PointCloudT::Ptr cloudData, bool isReverse);

private:
    //�洢��ʷ֡����
    QMap<int, QVector<QVector<OBJ>>> mHistoryFramesObs;

    //���ޣ����浽�״�ľ��룩-���ڼ����ٶ�
    static double mThreshold;
};
#endif // OSIGHT_RADAR_CLOUD_DATA_PROCESS__H__
