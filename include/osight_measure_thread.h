#ifndef OSIGHT_RADAR_OSIGHT_MEASURE_THREAD_H__
#define OSIGHT_RADAR_OSIGHT_MEASURE_THREAD__H__

#include <QThread>
#include <QMetaType>
#include "osight_driver.h"
#include "osight_def.h"

//ע��
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

    //speed��Χ5-30
    void setRadarSpeed(unsigned char speed);

    //�����״�ǿ��
    void setRadarIntensity(unsigned char intensity);

    //���ýǷֱ���
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

    PointCloudT::Ptr mCloud;

    //�״�ת��
    unsigned char mRadarSpeed;

    //ǿ��
    unsigned char mIntensity;

    //�Ƿֱ���
    unsigned int mAngleRes;
};
#endif // OSIGHT_RADAR_OSIGHT_MEASURE_THREAD__H__
