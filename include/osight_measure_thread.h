#ifndef EXINOVA_G524_OSIGHT_MEASURE_THREAD_H__
#define EXINOVA_G524_OSIGHT_MEASURE_THREAD__H__
/*****************************************************************************
* @FileName:osight_measure_thread.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:数据采集线程
* @Version: ver 1.0
*****************************************************************************/
#include <QThread>
#include <QMetaType>
#include <QMutex>
#include "osight_device.h"
#include "param_def.h"
class OsightMeasureTread : public QThread
{
    Q_OBJECT

public:
    OsightMeasureTread(QObject* parent = NULL);

    ~OsightMeasureTread();

    void setDevice(OsightDevice::RadarNumber type);

    OsightDevice* getDevice() { return mpRadarDevice; }

    void setRadarAddr(const QString& addr, short port);

    void setLocalAddr(const QString& addr, short port);

    void stop();
    //设置转速
    //范围5-30
    void setRadarSpeed(unsigned char speed);
    //设置雷达强度
    void setRadarIntensity(unsigned char intensity);
    //设置角分辨率
    void setRadarAngleRes(double angleResUi);

    PointCloudT::Ptr getCloud();

protected:
    void run();

private:
    void lidarDataToCloud(LidarData* pData, int pointNum);

signals:
    void sigRadarConnectFailed();

    void sigRadarConnectSuccess();

    void sigCloudPointUpdated();

private:
    //设备
    OsightDevice* mpRadarDevice;
    //是否运行
    bool mIsRun;
    //雷达地址
    QString mRadarAddr;
    //雷达端口号
    short mRadarPort;
    //主机地址
    QString mLocalAddr;
    //主机端口号
    short mLocalPort;
    //点云数据
    PointCloudT::Ptr mCloud;
    //锁
    QMutex mMutex;
};
#endif // EXINOVA_G524_OSIGHT_MEASURE_THREAD__H__
