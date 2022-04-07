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
#include <QString>
#include "osight_measure_thread.h"

class RadarManager : public QObject
{
    Q_OBJECT

public:
    RadarManager();

    ~RadarManager();
    //初始化
    void init();
    //添加设备
    void addDevice(const QString& ip, int type);
    //判断设备是否存在
    bool isDevExist(const QString& ip);
    //移除设备
    void removeDevice(const QString& ip);
    //设备连接
    void connect(const QString& ip, int type);
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
signals:
    void sigThreadCloudUpdated();
public slots:
    void threadCloudUpdate();
private:
    //初始化信号与槽
    void initConnect();
    //判断ip是否合法
    bool ipJudge(const QString& ip);
private:
    //存储设备信息
    QMap<QString, OsightMeasureTread*> mDeviceMap;
};
#endif // EXINOVA_G524_RADAR_MANAGER__H__
