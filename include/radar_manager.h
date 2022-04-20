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

class SingleRadarProcess;
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
    bool isDevExist(const QString& ip);
    //移除设备
    void removeDevice(const QString& ip);
    //设备连接
    void connect(const QString& ip, const int& port, int type);
    //设备断开连接
    void disconnect(const QString& ip);
    //设置xmin
    void setRadarxMin(const QString& ip, double val);
    //设置xmax
    void setRadarxMax(const QString& ip, double val);
    //设置ymin
    void setRadaryMin(const QString& ip, double val);
    //设置ymax
    void setRadaryMax(const QString& ip, double val);
    //设置xmin,xmax,ymin,ymax
    void setRadarThd(const QString& ip,
        double xmin,
        double xmax, 
        double ymin, 
        double ymax);
    //获取cloud
    PointCloudT::Ptr getCloud(const QString& ip);
    //获取速度
    double getSpeed(const QString& ip);
    //获取轮廓数据
    PointCloudT::Ptr getOutlineCloud(const QString& ip);
    
    void setFileName(const QString& ip, const QString& fileName);
    //添加数据读取
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
    //测量线程数据刷新
    void threadCloudUpdate(const QString& ip);
    //数据读取线程数据刷新
    void readThreadCloudUpdate(int radarType);
private:
    //初始化信号与槽
    void initConnect();
    //判断ip是否合法
    bool ipJudge(const QString& ip);
private:
    //存储设备信息
    QMap<QString, OsightMeasureTread*> mDeviceMap;
    //存储轮廓数据
    std::map<int, ExinovaCloudData> mOutlineCloudMap;
    //数据处理类
    SingleRadarProcess* mpDataProcess;
    //存储线程读取
    //0-A 1-B 2-C 3-D 4-E
    QMap<int, DataReadThread*> mDataReadMap;
    //锁
    QMutex mMutex;
};
#endif // EXINOVA_G524_RADAR_MANAGER__H__
