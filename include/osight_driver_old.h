#ifndef OSIGHT_RADAR_OSIGHT_DRIVER_H__
#define OSIGHT_RADAR_OSIGHT_DRIVER__H__
#include <WINSOCK2.H>
#include <time.h>
#include "osight_def.h"

class OsightDriver
{
public:
    OsightDriver();
    ~OsightDriver();

    //�жϴ�С��
    void JudgeSysBigEndian();

    //�����״�
    bool ConnectRadar(const char* radarIp = "192.168.1.10",
        const unsigned short radarPort = 6500,
        const char* localIp = "192.168.1.100",
        const unsigned short localPort = 5500);
    
    //�ر�����
    bool CloseRadar();

    //����ͬ����Ӧ����
    bool ParaSyncReq();

    //����ͬ����Ӧ����
    bool ProcessParaSyncRsp(char* pData,
        unsigned int& startAngle,
        unsigned int& stopAngle,
        unsigned int& pointNum,
        unsigned int& angularRes,
        unsigned char& intensity);

    //��������������Ϣ
    bool ProcessParaConfig(unsigned char speed,
        unsigned char intensity,
        unsigned int angularRes);

    //��ʼ�ɼ�������Ϣ
    bool StartMeasure();

    //ֹͣ�ɼ�������Ϣ
    bool StopMeasure();

    //�ɼ�����
    bool RecvData(LidarData* data);

    //��ȡ�����ܵ���
    int GetPointNum();

    //��ȡ��ʼ�Ƕȣ�������1000����
    int GetStartAngle();

    //��ȡ��ֹ�Ƕȣ�������1000����
    int GetStopAngle();

    //��ȡ�Ƿֱ��ʣ�������10000000��
    //2500000,1250000,625000,3125000
    int GetAngularRes();


public:
    //u16����ӳ�䵽�����ֽ���
    void HostToNet_U16(unsigned short& val);
    //u16�����ֽ�������ӳ��
    void NetToHost_U16(unsigned short& val);
    //u32����ӳ�䵽�����ֽ���
    void HostToNet_U32(unsigned int& val);
    //u32�����ֽ�������ӳ��
    void NetToHost_U32(unsigned int& val);
    ////����
    //void Coding_1Byte(char** pBuf, unsigned char data);
    //void Coding_2Byte(char** pBuf, unsigned short data);
    //void Coding_4Byte(char** pBuf, unsigned int data);

    ////����
    //void Decoding_1Byte(char** pBuf, unsigned char& data);
    //void Decoding_2Byte(char** pBuf, unsigned short& data);
    //void Decoding_4Byte(char** pBuf, unsigned int& data);

    //����CRC
    unsigned short CalCrc(unsigned char* pBuf, int len);
private:
    void ProcessRecvData(char* pBuf,
        LidarData* pData,
        int* pointNum,
        int* curPoso,
        float* stopAngle);

    unsigned int ProcessHead(char* pBuf);

private:
    //ͨ��
    SOCKET mSocket;
    //Զ�˵�ַ
    sockaddr_in mRemoteAddr;
    //���˵�ַ
    sockaddr_in mLocalAddr;
    //��С��
    bool mIsSysBigEnd;
    //ʱ��
    int mTimeOut;

};

#endif // OSIGHT_RADAR_OSIGHT_DRIVER__H__
