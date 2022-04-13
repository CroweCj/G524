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

    enum State
    {
        Stoped,     //ֹͣ״̬��������δ��������������ֹͣ
        Running,    //����״̬
        Paused      //��ͣ״̬
    };

    void setDevice(OsightDevice::RadarNumber type);

    OsightDevice* getDevice() { return mpRadarDevice; }

    void setRadarAddr(const QString& addr, short port);

    void setLocalAddr(const QString& addr, short port);
    //����ת��
    //��Χ5-30
    void setRadarSpeed(unsigned char speed);
    //�����״�ǿ��
    void setRadarIntensity(unsigned char intensity);
    //���ýǷֱ���
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
    //�豸
    OsightDevice* mpRadarDevice;
    //�Ƿ�����
    State mStatus;
    //�״��ַ �������Ƴ�
    QString mRadarAddr;
    //�״�˿ں� �������Ƴ�
    short mRadarPort;
    //������ַ �������Ƴ�
    QString mLocalAddr;
    //�����˿ں� �������Ƴ�
    short mLocalPort;
    //��������
    ExinovaCloudData mCloud;
    //��
    QMutex mMutex;
    //��ͣ��־
    std::atomic_bool mPauseFlag;
    //��ֹ��־
    std::atomic_bool mStopFlag;
};
#endif // EXINOVA_G524_OSIGHT_MEASURE_THREAD__H__
