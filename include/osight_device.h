#ifndef EXINOVA_G524_OSIGHT_DEVICE_H__
#define EXINOVA_G524_OSIGHT_DEVICE__H__
/*****************************************************************************
* @FileName:osight_device.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:��װ�״��豸�����ݻ�ȡ���������õ�
* @Version: ver 1.0
*****************************************************************************/
#include <QString>
#include <QMutex>
#include "osight_driver.h"

class OsightRadarDriver;

typedef struct FilterSetting
{
    double xMin;
    double xMax;
    double yMin;
    double yMax;
}FilterSetting;


class OsightDevice
{
public:
    //�豸����
    enum RadarNumber
    {
        RADAR_A = 0, //����ɨ�����·�·���������������ݳ����ٶȽ��г�����������
        RADAR_B,     //����ɨ�賵��1�����ڳ���1��������
        RADAR_C,     //����ɨ�賵��2�����ڳ���2��������
        RADAR_D,     //����ɨ�賵��3�����ڳ���3��������
        RADAR_E,     //����ɨ�����·�·���������������ݳ����ٶȽ��г�����������
        RADAR_F,
        END
    };

    OsightDevice(RadarNumber type);

    ~OsightDevice();
    //�����豸
    bool open(const QString& local, 
        const int localPort, 
        const QString& device, 
        const int devicePort,
        int timeout);
    //�ر��豸
    void close();
    //��ʼ����
    bool startMeasure();
    //ֹͣ����
    bool stopMeasure();
    //��ȡ���ݣ�һ֡��
    bool getOneFrameData(LidarData* data);
    //��ȡ����
    int getPointNum();

    QString getIp();

    void setIp(const QString& ip);

    int getPort();

    void setPort(int port);

    bool getDevcieEnbaled();

    double getFilterXMin();

    void setFilterXMin(double xmin);

    double getFilterXMax();

    void setFilterXMax(double xmax);

    double getFilterYMin();

    void setFilterYMin(double ymin);

    double getFilterYMax();

    void setFilterYMax(double ymax);
    //�����״�ת��
    //��Χ5-30
    void setRadarSpeed(unsigned char speed);
    //�����״�ǿ��
    void setRadarIntensity(unsigned char intensity);
    //���ýǷֱ���
    void setRadarAngleRes(double angleResUi);
    //����ת�٣�ǿ�ȣ��ֱ���
    void setParams();
    //��ȡ�豸����
    RadarNumber getRadarNumber() { return mRadarNumber; }
private:
    QMutex mMutex;
    //�豸�Ƿ����
    bool mEnable;
    //�豸��ַ
    QString mIp;
    //�豸�˿�
    int mPort;
    //�豸����
    FilterSetting mFilterSetting;
    //ת��
    unsigned char mSpeed;
    //ǿ��
    unsigned char mIntensity;
    //�Ƿֱ���
    double mAngleRes;
    //�豸����
    OsightRadarDriver* mpDriver;
    //�豸����
    RadarNumber mRadarNumber;
};
#endif // EXINOVA_G524_OSIGHT_DEVICE__H__
