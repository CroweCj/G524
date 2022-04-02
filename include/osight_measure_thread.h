#ifndef OSIGHT_RADAR_OSIGHT_MEASURE_THREAD_H__
#define OSIGHT_RADAR_OSIGHT_MEASURE_THREAD__H__

#include <QThread>
#include <QMetaType>
#include "osight_driver.h"
#include "osight_def.h"

//注册
Q_DECLARE_METATYPE(PointCloudT::Ptr);

class OsightMeasureTread : public QThread
{
    Q_OBJECT

public:
    OsightMeasureTread(QObject* parent = NULL);

    ~OsightMeasureTread();

    void setRadarAddr(const QString& addr, short port);

    void setLocalAddr(const QString& addr, short port);

    void stop();

    //speed范围5-30
    void setRadarSpeed(unsigned char speed);

    //设置雷达强度
    void setRadarIntensity(unsigned char intensity);

    //设置角分辨率
    void setRadarAngleRes(double angleResUi);

    PointCloudT::Ptr getCloud();

protected:
    void run();

private:
    void processMeasureData(LidarData* pData, int pointNum);

signals:
    void sigRadarConnectFailed();

    void sigRadarConnectSuccess();

    void sigCloudPointUpdated();

private:
    //
    OsightRadarDriver* mpRadarDriver;
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

    PointCloudT::Ptr mCloud;

    //雷达转速
    unsigned char mRadarSpeed;

    //强度
    unsigned char mIntensity;

    //角分辨率
    unsigned int mAngleRes;
};
#endif // OSIGHT_RADAR_OSIGHT_MEASURE_THREAD__H__
