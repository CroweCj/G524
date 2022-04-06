#include "osight_device.h"

OsightDevice::OsightDevice(RadarNumber type)
    :mRadarNumber(type)
    ,mEnable(false)
    ,mIp("")
    ,mPort(6500)
{
    mpDriver = new OsightRadarDriver();
}

OsightDevice::~OsightDevice()
{

}

bool OsightDevice::open(const QString& local,
    const int localPort,
    const QString& device,
    const int devicePort,
    int timeout)
{
    QMutexLocker locker(&mMutex);
    bool status = mpDriver->connect(local.toStdString().c_str(),
                    localPort,
                    device.toStdString().c_str(),
                    devicePort);
    mEnable = status;

    return status;
}

void OsightDevice::close()
{
    mEnable = false;
    mpDriver->disconnect();
}

bool OsightDevice::startMeasure()
{
    QMutexLocker locker(&mMutex);

    return mpDriver->startMeasure();
}

bool OsightDevice::stopMeasure()
{
    QMutexLocker locker(&mMutex);

    return mpDriver->stopMeasure();
}

bool OsightDevice::getOneFrameData(LidarData* data)
{
    QMutexLocker locker(&mMutex);
    bool status = mpDriver->recvOneFrameData(data);

    return status;
}

int OsightDevice::getPointNum()
{
    QMutexLocker locker(&mMutex);

    return mpDriver->paramSyncRsp();
}

QString OsightDevice::getIp()
{
    return mIp;
}

void OsightDevice::setIp(const QString& ip)
{
    QMutexLocker locker(&mMutex);
    mIp = ip;
}

int OsightDevice::getPort()
{
    return mPort;
}

void OsightDevice::setPort(int port)
{
    QMutexLocker locker(&mMutex);
    mPort = port;
}

bool OsightDevice::getDevcieEnbaled()
{
    return mEnable;
}

double OsightDevice::getFilterXMin()
{
    return mFilterSetting.xMin;
}

void OsightDevice::setFilterXMin(double xmin)
{
    QMutexLocker locker(&mMutex);
    mFilterSetting.xMin = xmin;
}

double OsightDevice::getFilterXMax()
{
    return mFilterSetting.xMax;
}

void OsightDevice::setFilterXMax(double xmax)
{
    QMutexLocker locker(&mMutex);
    mFilterSetting.xMax = xmax;
}

double OsightDevice::getFilterYMin()
{
    return mFilterSetting.yMin;
}

void OsightDevice::setFilterYMin(double ymin)
{
    QMutexLocker locker(&mMutex);
    mFilterSetting.yMin = ymin;
}

double OsightDevice::getFilterYMax()
{
    return mFilterSetting.yMax;
}

void OsightDevice::setFilterYMax(double ymax)
{
    QMutexLocker locker(&mMutex);
    mFilterSetting.yMax = ymax;
}

void OsightDevice::setRadarSpeed(unsigned char speed)
{
    if (speed < RADAR_SPEED_MIN)
        mSpeed = RADAR_SPEED_MIN;
    else if (speed > RADAR_SPEED_MAX)
        mSpeed = RADAR_SPEED_MAX;
    else
        mSpeed = speed;
}

void OsightDevice::setRadarIntensity(unsigned char intensity)
{
    QMutexLocker locker(&mMutex);
    mIntensity = intensity;
}

void OsightDevice::setRadarAngleRes(double angleResUi)
{
    QMutexLocker locker(&mMutex);
    //½çÃæÖµ*10^7
    mAngleRes = angleResUi * pow(10, 7);
}

void OsightDevice::setParams()
{
    QMutexLocker locker(&mMutex);
    mpDriver->paramConfigRsp(mSpeed, mIntensity, mAngleRes);
}


