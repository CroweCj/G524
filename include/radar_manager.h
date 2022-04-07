#ifndef EXINOVA_G524_RADAR_MANAGER_H__
#define EXINOVA_G524_RADAR_MANAGER__H__
/*****************************************************************************
* @FileName:radar_manager.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:�״��豸�����ࣺ���潻�����������ݣ�����豸����,���ݴ���
* @Version: ver 1.0
*****************************************************************************/
#include <QObject>
#include <QMap>
#include <QString>
#include "osight_measure_thread.h"

class RadarManager : public QObject
{
    Q_OBJECT

public:
    RadarManager();

    ~RadarManager();
    //��ʼ��
    void init();
    //����豸
    void addDevice(const QString& ip, int type);
    //�ж��豸�Ƿ����
    bool isDevExist(const QString& ip);
    //�Ƴ��豸
    void removeDevice(const QString& ip);
    //�豸����
    void connect(const QString& ip, int type);
    //�豸�Ͽ�����
    void disconnect(const QString& ip);
    //����xmin
    void setRadarxMin(const QString& ip, double val);
    //����xmax
    void setRadarxMax(const QString& ip, double val);
    //����ymin
    void setRadaryMin(const QString& ip, double val);
    //����ymax
    void setRadaryMax(const QString& ip, double val);
signals:
    void sigThreadCloudUpdated();
public slots:
    void threadCloudUpdate();
private:
    //��ʼ���ź����
    void initConnect();
    //�ж�ip�Ƿ�Ϸ�
    bool ipJudge(const QString& ip);
private:
    //�洢�豸��Ϣ
    QMap<QString, OsightMeasureTread*> mDeviceMap;
};
#endif // EXINOVA_G524_RADAR_MANAGER__H__
