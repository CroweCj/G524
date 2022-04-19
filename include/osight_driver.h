#ifndef EXINOVA_G524_OSIGHT_DRIVER_H__
#define EXINOVA_G524_OSIGHT_DRIVER__H__
/*****************************************************************************
* @FileName:osight_driver.h
* @Author: chujiajun
* @CreatTime: 2022/4/2
* @Descriptions:osight���ݻ�ȡ
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
    //�����豸
    bool connect(const char* radarIp = "192.168.1.10",
        const unsigned short radarPort = 6500,
        const char* localIp = "192.168.1.88",
        const unsigned short localPort = 5500);
    //�ر��豸
    void disconnect();
    //��ʼ����
    bool startMeasure();
    //ֹͣ����
    bool stopMeasure();

    bool paramSyncReq();

    //�������ݵ���
    int paramSyncRsp();
    //���ò�������
    bool paramConfigReq(unsigned char spped,
        unsigned char intensity,
        unsigned int angleRes);
    //���ò�����Ӧ�����ò����ӿڣ�
    int paramConfigRsp(unsigned char spped,
        unsigned char intensity,
        unsigned int angleRes);
    //��ȡһ֡����
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
    //�����ж�Զ�˷���������mRemoteAddr��ַ�Ƿ���ͬ
    sockaddr_in mRemoteCmp;

    bool mIsBigEnd;

    int mTimeOut;
};
#endif // EXINOVA_G524_OSIGHT_DRIVER__H__