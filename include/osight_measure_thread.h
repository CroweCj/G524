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

    enum State
    {
        Stoped,     //停止状态，包括从未启动过和启动后被停止
        Running,    //运行状态
        Paused      //暂停状态
    };

    void setDevice(OsightDevice::RadarNumber type);

    OsightDevice* getDevice() { return mpRadarDevice; }

    void setRadarAddr(const QString& addr, short port);

    void setLocalAddr(const QString& addr, short port);
    //设置转速
    //范围5-30
    void setRadarSpeed(unsigned char speed);
    //设置雷达强度
    void setRadarIntensity(unsigned char intensity);
    //设置角分辨率
    void setRadarAngleRes(double angleResUi);

    ExinovaCloudData& getCloud();

    State state() const;
public slots:
    void start(Priority pri = InheritPriority);

    void stop();

    void pause();

    void resume();

protected:
    void run();

private:
    void lidarDataToCloud(LidarData* pData, int pointNum);

signals:
    void sigRadarConnectFailed(const QString& ip);

    void sigRadarConnectSuccess(const QString& ip);

    void sigCloudPointUpdated(const QString& ip);

private:
    //设备
    OsightDevice* mpRadarDevice;
    //是否运行
    State mStatus;
    //雷达地址 后续可移除
    QString mRadarAddr;
    //雷达端口号 后续可移除
    short mRadarPort;
    //主机地址 后续可移除
    QString mLocalAddr;
    //主机端口号 后续可移除
    short mLocalPort;
    //点云数据
    ExinovaCloudData mCloud;
    //锁
    QMutex mMutex;
    //暂停标志
    std::atomic_bool mPauseFlag;
    //终止标志
    std::atomic_bool mStopFlag;
};
#endif // EXINOVA_G524_OSIGHT_MEASURE_THREAD__H__
