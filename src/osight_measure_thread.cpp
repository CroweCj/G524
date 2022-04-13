#include "osight_measure_thread.h"
#include <time.h>
OsightMeasureTread::OsightMeasureTread(QObject* parent)
    :QThread(parent)
    ,mRadarAddr("192.168.1.10")
    ,mRadarPort(6500)
    ,mLocalAddr("192.168.1.88")
    ,mLocalPort(5500)
    ,mPauseFlag(false)
    ,mStopFlag(false)
{
}

OsightMeasureTread::~OsightMeasureTread()
{
    stop();
    mpRadarDevice->stopMeasure();
    mpRadarDevice->close();
    if (mpRadarDevice != NULL)
        delete mpRadarDevice;
}

void OsightMeasureTread::setDevice(OsightDevice::RadarNumber type)
{
    mpRadarDevice = new OsightDevice(type);
    mpRadarDevice->setIp(mRadarAddr);
    mpRadarDevice->setPort(mRadarPort);
}

void OsightMeasureTread::setRadarAddr(const QString& addr, short port)
{
    mRadarAddr = addr;
    mRadarPort = port;
}

void OsightMeasureTread::setLocalAddr(const QString& addr, short port)
{
    mLocalAddr = addr;
    mLocalPort = port;
}

void OsightMeasureTread::setRadarSpeed(unsigned char speed)
{
    mpRadarDevice->setRadarSpeed(speed);
}
void OsightMeasureTread::setRadarIntensity(unsigned char intensity)
{
    mpRadarDevice->setRadarIntensity(intensity);
}

void OsightMeasureTread::setRadarAngleRes(double angleRes)
{
    //此值为界面传入值，未放大
    mpRadarDevice->setRadarAngleRes(angleRes);
}

ExinovaCloudData& OsightMeasureTread::getCloud()
{
    return mCloud;
}

OsightMeasureTread::State OsightMeasureTread::state() const
{
    State sta = Stoped;
    if (!QThread::isRunning())
    {
        sta = Stoped;
    }
    else if (QThread::isRunning() && mPauseFlag)
    {
        sta = Paused;
    }
    else if (QThread::isRunning() && (!mPauseFlag))
    {
        sta = Running;
    }

    return sta;
}

void OsightMeasureTread::start(Priority pri)
{
    QThread::start(pri);
}

void OsightMeasureTread::stop()
{
    if (QThread::isRunning())
    {
        mStopFlag = true;
        QThread::quit();
        QThread::wait();
    }
}

void OsightMeasureTread::pause()
{
    if (QThread::isRunning())
    {
        mPauseFlag = true;
    }
}

void OsightMeasureTread::resume()
{
    if (QThread::isRunning())
    {
        mPauseFlag = false;
    }
}

void OsightMeasureTread::run()
{
    if (mpRadarDevice->open(mRadarAddr.toStdString().c_str(),
        mRadarPort,
        mLocalAddr.toStdString().c_str(),
        mLocalPort,
        3000))
    {
        //TODO:参数配置
        mpRadarDevice->setParams();
        int nTry = 10;
        while (nTry > 0 && !mStopFlag)
        {
            if (!mPauseFlag)
            {
                //获取数据点数
                int pointNum = mpRadarDevice->getPointNum();
                if (pointNum > 0)
                {
                    nTry = 10;
                    //申请内存
                    LidarData* pData = new LidarData[pointNum];
                    //开始采集
                    mpRadarDevice->startMeasure();
                    while (!mStopFlag && !mPauseFlag)
                    {
                        if (mpRadarDevice->getOneFrameData(pData))
                        {
                            lidarDataToCloud(pData, pointNum);
                        }
                        else
                        {
                            clock_t startTime = clock();
                            State sta = state();
                            while (sta == Running)
                            {
                                //TODO:重连30分钟
                                if (((double)(clock() - startTime) / CLOCKS_PER_SEC) >= 1800)
                                {
                                    stop();
                                    emit sigRadarConnectFailed(mpRadarDevice->getIp());
                                    return;
                                }
                                else
                                {
                                    pointNum = mpRadarDevice->getPointNum();
                                    if (pointNum > 0)
                                    {
                                        resume();
                                        startTime = clock();
                                        //清除缓存区
                                        delete[] pData;
                                        //重新申请缓存区数据
                                        pData = new LidarData[pointNum];
                                        //重新启动测量
                                        mpRadarDevice->startMeasure();
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    delete[] pData;
                }
                --nTry;
            }
        }
    }
    else
    {
        emit sigRadarConnectFailed(mpRadarDevice->getIp());
        return;
    }
}


void OsightMeasureTread::lidarDataToCloud(LidarData* pData, int pointNum)
{
    QMutexLocker locker(&mMutex);
    mCloud.data()->clear();
    PointT poi;
    for (int i = 0; i < pointNum; ++i)
    {
        //计算x，y，z 无垂直角度
        poi.x = pData[i].distance * cosf(pData[i].angle * M_PI / 180);
        poi.y = pData[i].distance * sinf(pData[i].angle * M_PI / 180);
        poi.z = 0;
        poi.r = 255;
        poi.g = 255;
        poi.b = 255;
        poi.a = 255;
        mCloud.data()->push_back(poi);
    }

    emit sigCloudPointUpdated(mpRadarDevice->getIp());
}
