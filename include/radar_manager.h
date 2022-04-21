#ifndef EXINOVA_G524_RADAR_MANAGER_H__
#define EXINOVA_G524_RADAR_MANAGER__H__
/*****************************************************************************
* @FileName:radar_manager.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:雷达设备管理类：界面交互，参数传递，多个设备管理,数据处理
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
    //初始化
    void init();
    //添加设备
    bool addDevice(const QString& ip, const int& port, int type);
    //判断设备是否存在
    bool isDevExist(const int type);
    //移除设备
    void removeDevice(const int type);
    //设备连接
    void connect(const QString& ip, const int& port, int type);
    //设备断开连接
    void disconnect(const int type);
    //设置xmin
    void setRadarxMin(const int type, double val);
    //设置xmax
    void setRadarxMax(const int type, double val);
    //设置ymin
    void setRadaryMin(const int type, double val);
    //设置ymax
    void setRadaryMax(const int type, double val);
    //设置xmin,xmax,ymin,ymax
    void setRadarThd(const int type,
        double xmin,
        double xmax, 
        double ymin, 
        double ymax);
    //获取cloud
    PointCloudT::Ptr getCloud(const int type);
    //获取文件读取cloud
    PointCloudT::Ptr getReadCloud(const int type);
    //获取速度
    double getSpeed(const int type);
    //获取轮廓数据
    PointCloudT::Ptr getOutlineCloud(const int type);
    
    void setFileName(const int type, const QString& fileName);
    //添加数据读取
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
    //测量线程数据刷新
    void threadCloudUpdate(const int type);
    //数据读取线程数据刷新
    void readThreadCloudUpdate(int radarType);
private:
    //初始化信号与槽
    void initConnect();
    //判断ip是否合法
    bool ipJudge(const QString& ip);
private:
    //存储设备信息
    QMap<int, OsightMeasureTread*> mDeviceMap;
    //存储轮廓数据
    std::map<int, ExinovaCloudData> mOutlineCloudMap;
    //展示数据
    std::map<int, ExinovaCloudData> mShowCloudMap;
    //数据处理类
    RadarDataProcess* mpDataProcess;
    //存储线程读取
    //0-A 1-B 2-C 3-D 4-E
    QMap<int, DataReadThread*> mDataReadMap;
    //锁
    QMutex mMutex;
};
#endif // EXINOVA_G524_RADAR_MANAGER__H__
