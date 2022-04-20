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
#include <map>
#include <QString>
#include "osight_measure_thread.h"

class SingleRadarProcess;
class DataReadThread;

class RadarManager : public QObject
{
    Q_OBJECT

public:
    RadarManager();

    ~RadarManager();
    //��ʼ��
    void init();
    //����豸
    bool addDevice(const QString& ip, const int& port, int type);
    //�ж��豸�Ƿ����
    bool isDevExist(const QString& ip);
    //�Ƴ��豸
    void removeDevice(const QString& ip);
    //�豸����
    void connect(const QString& ip, const int& port, int type);
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
    //����xmin,xmax,ymin,ymax
    void setRadarThd(const QString& ip,
        double xmin,
        double xmax, 
        double ymin, 
        double ymax);
    //��ȡcloud
    PointCloudT::Ptr getCloud(const QString& ip);
    //��ȡ�ٶ�
    double getSpeed(const QString& ip);
    //��ȡ��������
    PointCloudT::Ptr getOutlineCloud(const QString& ip);
    
    void setFileName(const QString& ip, const QString& fileName);
    //������ݶ�ȡ
    void addDataRead(int radarType, const QString& filePath);
    void startDataRead();
signals:
    void sigAThreadCloudUpdated(const QString& ip);
    void sigBThreadCloudUpdated(const QString& ip);
    void sigCThreadCloudUpdated(const QString& ip);
    void sigDThreadCloudUpdated(const QString& ip);
    void sigEThreadCloudUpdated(const QString& ip);
    void sigBSpeedUpdated(const QString& ip);
    void sigCSpeedUpdated(const QString& ip);
    void sigDSpeedUpdated(const QString& ip);
    void sigAOutlineUpdated(const QString& ip);
    void sigEOutlineUpdated(const QString& ip);
public slots:
    //�����߳�����ˢ��
    void threadCloudUpdate(const QString& ip);
    //���ݶ�ȡ�߳�����ˢ��
    void readThreadCloudUpdate(int radarType);
private:
    //��ʼ���ź����
    void initConnect();
    //�ж�ip�Ƿ�Ϸ�
    bool ipJudge(const QString& ip);
private:
    //�洢�豸��Ϣ
    QMap<QString, OsightMeasureTread*> mDeviceMap;
    //�洢��������
    std::map<int, ExinovaCloudData> mOutlineCloudMap;
    //���ݴ�����
    SingleRadarProcess* mpDataProcess;
    //�洢�̶߳�ȡ
    //0-A 1-B 2-C 3-D 4-E
    QMap<int, DataReadThread*> mDataReadMap;
    //��
    QMutex mMutex;
};
#endif // EXINOVA_G524_RADAR_MANAGER__H__
