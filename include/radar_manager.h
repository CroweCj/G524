#ifndef EXINOVA_G524_RADAR_MANAGER_H__
#define EXINOVA_G524_RADAR_MANAGER__H__
/*****************************************************************************
* @FileName:radar_manager.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:�״��豸�����ࣺ���潻�����������ݣ�����豸����,���ݴ���
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
    //��ʼ��
    void init();

private:
    QMap<QString, OsightDevice> mDeviceMap;
};
#endif // EXINOVA_G524_RADAR_MANAGER__H__
