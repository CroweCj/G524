#ifndef EXINOVA_G524_OSIGHT_DEVICE_H__
#define EXINOVA_G524_OSIGHT_DEVICE__H__
/*****************************************************************************
* @FileName:osight_device.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:封装雷达设备：数据获取，参数设置等
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
    //设备类型
    enum RadarNumber
    {
        RADAR_A = 0, //负责扫描正下方路面三个车道，根据车辆速度进行车辆轮廓叠加
        RADAR_B,     //负责扫描车道1，用于车道1车辆测速
        RADAR_C,     //负责扫描车道2，用于车道2车辆测速
        RADAR_D,     //负责扫描车道3，用于车道3车辆测速
        RADAR_E,     //负责扫描正下方路面三个车道，根据车辆速度进行车辆轮廓叠加
        RADAR_F,
        END
    };

    OsightDevice(RadarNumber type);

    ~OsightDevice();
    //连接设备
    bool open(const QString& local, 
        const int localPort, 
        const QString& device, 
        const int devicePort,
        int timeout);
    //关闭设备
    void close();
    //开始测量
    bool startMeasure();
    //停止测量
    bool stopMeasure();
    //获取数据（一帧）
    bool getOneFrameData(LidarData* data);
    //获取点数
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
    //设置雷达转速
    //范围5-30
    void setRadarSpeed(unsigned char speed);
    //设置雷达强度
    void setRadarIntensity(unsigned char intensity);
    //设置角分辨率
    void setRadarAngleRes(double angleResUi);
    //设置转速，强度，分辨率
    void setParams();
    //获取设备类型
    RadarNumber getRadarNumber() { return mRadarNumber; }
private:
    QMutex mMutex;
    //设备是否可用
    bool mEnable;
    //设备地址
    QString mIp;
    //设备端口
    int mPort;
    //设备参数
    FilterSetting mFilterSetting;
    //转速
    unsigned char mSpeed;
    //强度
    unsigned char mIntensity;
    //角分辨率
    double mAngleRes;
    //设备驱动
    OsightRadarDriver* mpDriver;
    //设备类型
    RadarNumber mRadarNumber;
};
#endif // EXINOVA_G524_OSIGHT_DEVICE__H__
