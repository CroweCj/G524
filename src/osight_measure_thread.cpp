#include "osight_measure_thread.h"
#include <time.h>
OsightMeasureTread::OsightMeasureTread(QObject* parent)
    :QThread(parent)
    ,mIsRun(false)
    ,mRadarAddr("192.168.1.10")
    ,mRadarPort(6500)
    ,mLocalAddr("192.168.1.88")
    ,mLocalPort(6000)
{
    mCloud.reset(new PointCloudT);
}

OsightMeasureTread::~OsightMeasureTread()
{
    mpRadarDevice->stopMeasure();
    mpRadarDevice->close();
    if (mpRadarDevice != NULL)
        delete mpRadarDevice;

}

void OsightMeasureTread::setDevice(OsightDevice::RadarNumber type)
{
    mpRadarDevice = new OsightDevice(type);
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

void OsightMeasureTread::stop()
{
    mIsRun = false;
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
    //��ֵΪ���洫��ֵ��δ�Ŵ�
    mpRadarDevice->setRadarAngleRes(angleRes);
}

PointCloudT::Ptr OsightMeasureTread::getCloud()
{
    return mCloud;
}

void OsightMeasureTread::run()
{
    mIsRun = true;

    //TODO:�����״�ͱ�����ַ
    if (mpRadarDevice->open(mRadarAddr.toStdString().c_str(),
        mRadarPort,
        mLocalAddr.toStdString().c_str(),
        mLocalPort,
        3000))
    {
        //TODO:��������
        mpRadarDevice->setParams();
        //��ȡ���ݵ���
        int pointNum = mpRadarDevice->getPointNum();
        if (pointNum > 0)
        {
            //�����ڴ�
            LidarData* pData = new LidarData[pointNum];
            //��ʼ�ɼ�
            mpRadarDevice->startMeasure();
            while (mIsRun)
            {
                if (mpRadarDevice->getOneFrameData(pData))
                {
                    lidarDataToCloud(pData, pointNum);
                }
                else
                {
                    clock_t startTime = clock();
                    while (mIsRun)
                    {
                        //TODO:����30����
                        if (((double)(clock() - startTime) / CLOCKS_PER_SEC) >= 1800)
                        {
                            mIsRun = false;
                            emit sigRadarConnectFailed();
                            return;
                        }
                        else
                        {
                            pointNum = mpRadarDevice->getPointNum();
                            if (pointNum > 0)
                            {
                                mIsRun = true;
                                startTime = clock();
                                //���������
                                delete[] pData;
                                //�������뻺��������
                                pData = new LidarData[pointNum];
                                //������������
                                mpRadarDevice->startMeasure();
                                break;
                            }
                        }
                    }
                }
            }
            delete[] pData;
        }
    }
    else
    {
        emit sigRadarConnectFailed();
        return;
    }
}


void OsightMeasureTread::lidarDataToCloud(LidarData* pData, int pointNum)
{
    QMutexLocker locker(&mMutex);
    mCloud->clear();
    PointT poi;
    for (int i = 0; i < pointNum; ++i)
    {
        //����x��y��z �޴�ֱ�Ƕ�
        poi.x = pData[i].distance * cosf(pData[i].angle * M_PI / 180);
        poi.y = pData[i].distance * sinf(pData[i].angle * M_PI / 180);
        poi.z = 0;
        poi.r = 255;
        poi.g = 255;
        poi.b = 255;
        poi.a = 255;
        mCloud->push_back(poi);
    }

    emit sigCloudPointUpdated();
}
