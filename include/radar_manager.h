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

class RadarDataProcess;
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
    bool isDevExist(const int type);
    //�Ƴ��豸
    void removeDevice(const int type);
    //�豸����
    void connect(const QString& ip, const int& port, int type);
    //�豸�Ͽ�����
    void disconnect(const int type);
    //����xmin
    void setRadarxMin(const int type, double val);
    //����xmax
    void setRadarxMax(const int type, double val);
    //����ymin
    void setRadaryMin(const int type, double val);
    //����ymax
    void setRadaryMax(const int type, double val);
    //����xmin,xmax,ymin,ymax
    void setRadarThd(const int type,
        double xmin,
        double xmax, 
        double ymin, 
        double ymax);
    //��ȡcloud
    PointCloudT::Ptr getCloud(const int type);
    //��ȡ�ļ���ȡcloud
    PointCloudT::Ptr getReadCloud(const int type);
    //��ȡ�ٶ�
    double getSpeed(const int type);
    //��ȡ��������
    PointCloudT::Ptr getOutlineCloud(const int type);
    
    void setFileName(const int type, const QString& fileName);
    //������ݶ�ȡ
    void addDataRead(int radarType, const QString& filePath);
    void startDataRead();
	void pauseDataRead();
	void resumeDataRead();
    void nextFrame();
    void stopDataWrite();
signals:
    //void sigAThreadCloudUpdated(const QString& ip);
    //void sigBThreadCloudUpdated(const QString& ip);
    //void sigCThreadCloudUpdated(const QString& ip);
    //void sigDThreadCloudUpdated(const QString& ip);
    //void sigEThreadCloudUpdated(const QString& ip);
    void sigThreadCloudUpdated(const int type);
    void sigBSpeedUpdated();
    void sigCSpeedUpdated();
    void sigDSpeedUpdated();
    void sigAOutlineUpdated();
    void sigEOutlineUpdated();
    void sigDataReadThreadCloudUpdate(const int type);
public slots:
    //�����߳�����ˢ��
    void threadCloudUpdate(const int type);
    //���ݶ�ȡ�߳�����ˢ��
    void readThreadCloudUpdate(int radarType);
private:
    //��ʼ���ź����
    void initConnect();
    //�ж�ip�Ƿ�Ϸ�
    bool ipJudge(const QString& ip);
private:
    //�洢�豸��Ϣ
    QMap<int, OsightMeasureTread*> mDeviceMap;
    //�洢��������
    std::map<int, ExinovaCloudData> mOutlineCloudMap;
    //չʾ����
    std::map<int, ExinovaCloudData> mShowCloudMap;
    //���ݴ�����
    RadarDataProcess* mpDataProcess;
    //�洢�̶߳�ȡ
    //0-A 1-B 2-C 3-D 4-E
    QMap<int, DataReadThread*> mDataReadMap;
    //��
    QMutex mMutex;
};
#endif // EXINOVA_G524_RADAR_MANAGER__H__
