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

    mpRadarDriver = new OsightRadarDriver();
}

OsightMeasureTread::~OsightMeasureTread()
{
    mpRadarDriver->stopMeasure();
    mpRadarDriver->disconnect();
    if (mpRadarDriver != NULL)
        delete mpRadarDriver;

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
    if (speed < 5)
        mRadarSpeed = 5;
    else if (speed > 30)
        mRadarSpeed = 30;
    else
        mRadarSpeed = speed;
}
void OsightMeasureTread::setRadarIntensity(unsigned char intensity)
{
    mIntensity = intensity;
}

void OsightMeasureTread::setRadarAngleRes(double angleRes)
{
    //����ֵ*10^7
    mAngleRes = angleRes * pow(10, 7);
}

PointCloudT::Ptr OsightMeasureTread::getCloud()
{
    return mCloud;
}

void OsightMeasureTread::run()
{
    mIsRun = true;

    //TODO:�����״�ͱ�����ַ
    if (mpRadarDriver->connect(mRadarAddr.toStdString().c_str(),
        mRadarPort,
        mLocalAddr.toStdString().c_str(),
        mLocalPort))
    {
        //TODO:��������
        mpRadarDriver->paramConfigRsp(mRadarSpeed, mIntensity, mAngleRes);
        //��ȡ���ݵ���
        int pointNum = mpRadarDriver->paramSyncRsp();
        if (pointNum > 0)
        {
            //�����ڴ�
            LidarData* pData = new LidarData[pointNum];
            //��ʼ�ɼ�
            mpRadarDriver->startMeasure();
            while (mIsRun)
            {
                if (mpRadarDriver->recvOneFrameData(pData))
                {
                    processMeasureData(pData, pointNum);
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
                            pointNum = mpRadarDriver->paramSyncRsp();
                            if (pointNum > 0)
                            {
                                mIsRun = true;
                                startTime = clock();
                                //���������
                                delete[] pData;
                                //�������뻺��������
                                pData = new LidarData[pointNum];
                                //������������
                                mpRadarDriver->startMeasure();
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


void OsightMeasureTread::processMeasureData(LidarData* pData, int pointNum)
{
    //TODO:cloud�����һ������
    mCloud->clear();
    PointT poi;
    for (int i = 0; i < pointNum; ++i)
    {
        //TODO:test
        //����x��y��z �޴�ֱ�Ƕ�
        poi.x = pData[i].distance * cos(pData[i].angle);
        poi.y = pData[i].distance * sin(pData[i].angle);
        poi.z = 0;
        mCloud->push_back(poi);
    }
    for (PointCloudT::iterator cloud_it = mCloud->begin(); cloud_it != mCloud->end(); ++cloud_it)
    {
        cloud_it->r = 248;
        cloud_it->g = 248;
        cloud_it->b = 255;
    }
    emit sigCloudPointUpdated();
}
