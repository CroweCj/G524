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

    //判断大小端
    void JudgeSysBigEndian();

    //连接雷达
    bool ConnectRadar(const char* radarIp = "192.168.1.10",
        const unsigned short radarPort = 6500,
        const char* localIp = "192.168.1.100",
        const unsigned short localPort = 5500);
    
    //关闭连接
    bool CloseRadar();

    //参数同步响应请求
    bool ParaSyncReq();

    //参数同步响应处理
    bool ProcessParaSyncRsp(char* pData,
        unsigned int& startAngle,
        unsigned int& stopAngle,
        unsigned int& pointNum,
        unsigned int& angularRes,
        unsigned char& intensity);

    //参数配置请求信息
    bool ProcessParaConfig(unsigned char speed,
        unsigned char intensity,
        unsigned int angularRes);

    //开始采集数据信息
    bool StartMeasure();

    //停止采集数据信息
    bool StopMeasure();

    //采集数据
    bool RecvData(LidarData* data);

    //获取数据总点数
    int GetPointNum();

    //获取起始角度（扩大了1000倍）
    int GetStartAngle();

    //获取终止角度（扩大了1000倍）
    int GetStopAngle();

    //获取角分辨率（扩大了10000000）
    //2500000,1250000,625000,3125000
    int GetAngularRes();


public:
    //u16主机映射到网络字节序
    void HostToNet_U16(unsigned short& val);
    //u16网络字节序到主机映射
    void NetToHost_U16(unsigned short& val);
    //u32主机映射到网络字节序
    void HostToNet_U32(unsigned int& val);
    //u32网络字节序到主机映射
    void NetToHost_U32(unsigned int& val);
    ////编码
    //void Coding_1Byte(char** pBuf, unsigned char data);
    //void Coding_2Byte(char** pBuf, unsigned short data);
    //void Coding_4Byte(char** pBuf, unsigned int data);

    ////解码
    //void Decoding_1Byte(char** pBuf, unsigned char& data);
    //void Decoding_2Byte(char** pBuf, unsigned short& data);
    //void Decoding_4Byte(char** pBuf, unsigned int& data);

    //计算CRC
    unsigned short CalCrc(unsigned char* pBuf, int len);
private:
    void ProcessRecvData(char* pBuf,
        LidarData* pData,
        int* pointNum,
        int* curPoso,
        float* stopAngle);

    unsigned int ProcessHead(char* pBuf);

private:
    //通信
    SOCKET mSocket;
    //远端地址
    sockaddr_in mRemoteAddr;
    //本端地址
    sockaddr_in mLocalAddr;
    //大小端
    bool mIsSysBigEnd;
    //时延
    int mTimeOut;

};

#endif // OSIGHT_RADAR_OSIGHT_DRIVER__H__
