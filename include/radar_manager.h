#ifndef EXINOVA_G524_RADAR_MANAGER_H__
#define EXINOVA_G524_RADAR_MANAGER__H__
/*****************************************************************************
* @FileName:radar_manager.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:雷达设备管理类：界面交互，参数传递，多个设备管理,数据处理
* @Version: ver 1.0
*****************************************************************************/
#include <QMap>
#include <QString>
#include "osight_device.h"

class RadarManager
{
public:
    RadarManager();

    ~RadarManager();
    //初始化
    void init();

private:
    QMap<QString, OsightDevice> mDeviceMap;
};
#endif // EXINOVA_G524_RADAR_MANAGER__H__
