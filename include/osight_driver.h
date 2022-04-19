#ifndef EXINOVA_G524_OSIGHT_DRIVER_H__
#define EXINOVA_G524_OSIGHT_DRIVER__H__
/*****************************************************************************
* @FileName:osight_driver.h
* @Author: chujiajun
* @CreatTime: 2022/4/2
* @Descriptions:osight数据获取
* @Version: ver 1.0
*****************************************************************************/
#include <WINSOCK2.H>
#include <time.h>
#include <string>
#include "osight_def.h"
class OsightRadarDriver
{
public:
    OsightRadarDriver();

    ~OsightRadarDriver();
    //连接设备
    bool connect(const char* radarIp = "192.168.1.10",
        const unsigned short radarPort = 6500,
        const char* localIp = "192.168.1.88",
        const unsigned short localPort = 5500);
    //关闭设备
    void disconnect();
    //开始测量
    bool startMeasure();
    //停止测量
    bool stopMeasure();

    bool paramSyncReq();

    //返回数据点数
    int paramSyncRsp();
    //设置参数请求
    bool paramConfigReq(unsigned char spped,
        unsigned char intensity,
        unsigned int angleRes);
    //设置参数回应（设置参数接口）
    int paramConfigRsp(unsigned char spped,
        unsigned char intensity,
        unsigned int angleRes);
    //获取一帧数据
    bool recvOneFrameData(LidarData* data);

public:
    unsigned short HtoNS(unsigned short data);

    unsigned short NtoHS(unsigned short data);

    unsigned int HtoNL(unsigned int data);

    unsigned int NtoHL(unsigned int data);

    void Pack1Byte(char** pBuf, unsigned char data);

    void Pack2Byte(char** pBuf, unsigned short data);

    void Pack4Byte(char** pBuf, unsigned int data);

    void UnPack1Byte(char** pBuf, unsigned char &data);

    void UnPack2Byte(char** pBuf, unsigned short &data);

    void UnPack4Byte(char** pBuf, unsigned int& data);

    void JudgeBigEnd();

private:
    void processSync(char* pRecvBuf, int& totalPointNum);

    void processOneFrameData(char* pRecvBuf,
        LidarData* pDataBuf,
        int* count,
        int* curPos, 
        float* stopAngle);

private:
    SOCKET mSocket;

    sockaddr_in mRemoteAddr;

    sockaddr_in mHostAddr;
    //用来判断远端返回数据与mRemoteAddr地址是否相同
    sockaddr_in mRemoteCmp;

    bool mIsBigEnd;

    int mTimeOut;
};
#endif // EXINOVA_G524_OSIGHT_DRIVER__H__