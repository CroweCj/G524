#pragma once
#include <WINSOCK2.H>
#include <time.h>
#include <string>
#include "osight_def.h"

class OsightRadarDriver
{
public:
    OsightRadarDriver();

    ~OsightRadarDriver();

    bool connect(const char* radarIp = "192.168.1.10",
        const unsigned short radarPort = 6500,
        const char* localIp = "192.168.1.88",
        const unsigned short localPort = 5500);

    void disconnect();

    bool startMeasure();

    bool stopMeasure();

    bool paramSyncReq();

    //返回数据点数
    int paramSyncRsp();

    bool paramConfigReq(unsigned char spped,
        unsigned char intensity,
        unsigned int angleRes);

    int paramConfigRsp(unsigned char spped,
        unsigned char intensity,
        unsigned int angleRes);

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

    bool mIsBigEnd;

    int mTimeOut;
};