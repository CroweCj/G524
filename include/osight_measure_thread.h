#ifndef EXINOVA_G524_OSIGHT_MEASURE_THREAD_H__
#define EXINOVA_G524_OSIGHT_MEASURE_THREAD__H__
/*****************************************************************************
* @FileName:osight_measure_thread.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:���ݲɼ��߳�
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
    //����ת��
    //��Χ5-30
    void setRadarSpeed(unsigned char speed);
    //�����״�ǿ��
    void setRadarIntensity(unsigned char intensity);
    //���ýǷֱ���
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
    //�豸
    OsightDevice* mpRadarDevice;
    //�Ƿ�����
    bool mIsRun;
    //�״��ַ
    QString mRadarAddr;
    //�״�˿ں�
    short mRadarPort;
    //������ַ
    QString mLocalAddr;
    //�����˿ں�
    short mLocalPort;
    //��������
    PointCloudT::Ptr mCloud;
    //��
    QMutex mMutex;
};
#endif // EXINOVA_G524_OSIGHT_MEASURE_THREAD__H__
