#include "osight_def.h"
#include "osight_driver.h"

unsigned char auchCRCHi[] =
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
};

unsigned char auchCRCLo[] =
{
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};

/* u16 的高低字节转换宏定义 */
#define HSPS_HTONS(x)    OsightDriver::mIsSysBigEnd ? x : ((((x) & 0x00FF) << 8) | (((x) & 0xFF00) >> 8)) // u16主机映射到网络字节序
#define HSPS_NTOHS(x)    OsightDriver::mIsSysBigEnd ? x : ((((x) & 0x00FF) << 8) | (((x) & 0xFF00) >> 8)) // u16网络映射到主机字节序

                                             /* u32 的高低字节转换宏定义 */
#define HSPS_HTONL(x)    OsightDriver::mIsSysBigEnd ? x : ((((x) & 0x000000FF) << 24)|(((x) & 0x0000FF00) << 8)|(((x) & 0x00FF0000) >> 8)|(((x) & 0xFF000000) >> 24)) // u32主机映射到网络字节序
#define HSPS_NTOHL(x)    OsightDriver::mIsSysBigEnd ? x : ((((x) & 0x000000FF) << 24)|(((x) & 0x0000FF00) << 8)|(((x) & 0x00FF0000) >> 8)|(((x) & 0xFF000000) >> 24)) // u32网络映射到主机字节序

                                             /*  编码宏 */
#define HSPS_PACK_1_BYTE(pucBuff, ucData)   {*pucBuff = ucData; pucBuff++;}
#define HSPS_PACK_2_BYTE(pucBuff, usData)   {*(UINT16*)pucBuff = HSPS_HTONS(usData); pucBuff += sizeof(UINT16);}
#define HSPS_PACK_4_BYTE(pucBuff, ulData)   {*(UINT32*)pucBuff = HSPS_HTONL(ulData); pucBuff += sizeof(UINT32);}

                                             /*  解码宏 */
#define HSPS_UNPACK_1_BYTE(pucBuff, ucData) {ucData = *pucBuff; pucBuff++;}
#define HSPS_UNPACK_2_BYTE(pucBuff, usData) {usData = HSPS_NTOHS(*(UINT16*)pucBuff); pucBuff += sizeof(UINT16);}
#define HSPS_UNPACK_4_BYTE(pucBuff, ulData) {ulData = HSPS_NTOHL(*(UINT32*)pucBuff); pucBuff += sizeof(UINT32);}


OsightDriver::OsightDriver()
: mIsSysBigEnd(false)
, mTimeOut(3000)
{
    JudgeSysBigEndian();
}

OsightDriver::~OsightDriver()
{
    CloseRadar();
}

void OsightDriver::JudgeSysBigEndian()
{
    union Test
    {
        int a;
        char b;
    };

    Test t;
    t.a = 1;
    if (t.b == 1)
        mIsSysBigEnd = false;  //"小端机器"
    else
        mIsSysBigEnd = true;   //"大端机器"
}

bool OsightDriver::ConnectRadar(const char* radarIp,
    const unsigned short radarPort,
    const char* localIp,
    const unsigned short localPort)
{
    clock_t startTime = clock();
    //初始化网络
    WSADATA wsaData;
    WORD sockVer = MAKEWORD(2,2);
    if (WSAStartup(sockVer, &wsaData) != 0)
        return false;
    //雷达端
    mRemoteAddr.sin_family = AF_INET;
    mRemoteAddr.sin_port = htons(radarPort);
    mRemoteAddr.sin_addr.s_addr = inet_addr(radarIp);
    int nAddrLen = sizeof(mRemoteAddr);

    //主机端
    mLocalAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    mLocalAddr.sin_family = AF_INET;
    mLocalAddr.sin_port = htons(localPort);
    mLocalAddr.sin_addr.s_addr = htons(INADDR_ANY);

    //socket
    mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (mSocket == INVALID_SOCKET)
    {
        WSACleanup();
        return false;
    }

    //设置非阻塞模式
    int imode = 1;
    if (ioctlsocket(mSocket, FIONBIO, (u_long FAR*)&imode) 
        == SOCKET_ERROR)
    {
        WSACleanup();
        return false;
    }

    while (bind(mSocket, (sockaddr*)&mLocalAddr, sizeof(mLocalAddr)) == SOCKET_ERROR)
    {
        if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000 >= mTimeOut)
        {
            return false;
        }
    }

    return true;
}

bool OsightDriver::CloseRadar()
{
    StopMeasure();
    closesocket(mSocket);
    WSACleanup();

    return true;
}

bool OsightDriver::ParaSyncReq()
{
    char temp[6] = { 0 };
    char* pTemp = temp;
    HSPS_PACK_4_BYTE(pTemp, PARA_SYNC_REQ);
    unsigned short crc = CalCrc((unsigned char*)pTemp, 4);
    HSPS_PACK_2_BYTE(pTemp, crc);

    int addrLen = sizeof(struct sockaddr_in);
    if (sendto(mSocket, temp, sizeof(temp), 0, (const struct sockaddr*)&mRemoteAddr, addrLen) < 0)
    {
        return false;
    }

    return true;
}

bool OsightDriver::ProcessParaSyncRsp(char* pData,
    unsigned int& startAngle,
    unsigned int& stopAngle,
    unsigned int& pointNum,
    unsigned int& angularRes,
    unsigned char& intensity)
{
    //跳过协议id（4字节）,设备MAC(6字节),SN序列号（4字节）,PN号（4字节）
    //主机软件版本（2字节）,FPGA软件版本（2字节）,TDC种类（1字节）
    //线数（1字节）
    pData += 24;
    HSPS_UNPACK_4_BYTE(pData, startAngle);
    HSPS_UNPACK_4_BYTE(pData, stopAngle);
    HSPS_UNPACK_4_BYTE(pData, pointNum);

    pData += 30;

    HSPS_UNPACK_1_BYTE(pData, intensity);
    HSPS_UNPACK_4_BYTE(pData, angularRes);

    int tempPointNum = ((stopAngle - startAngle) / 1000.0) / (angularRes / 10000000.0) + 1;
    if ((pointNum > 0) && (pointNum == tempPointNum))
    {
        pointNum = tempPointNum;
    }
    else
    {
        return false;
    }

    return true;
}

bool OsightDriver::ProcessParaConfig(unsigned char speed,
    unsigned char intensity,
    unsigned int angularRes)
{
    //下发参数所需信息
    char temp[12] = { 0 };
    char* start = temp;
    HSPS_PACK_4_BYTE(start, PARA_DEVICE_CONFIGURATION_REQ);
    HSPS_PACK_1_BYTE(start, speed);
    HSPS_PACK_1_BYTE(start, intensity);
    HSPS_PACK_4_BYTE(start, angularRes);

    unsigned short crc = CalCrc((unsigned char*)temp, 10);
    HSPS_PACK_2_BYTE(start, crc);

    int addrLen = sizeof(struct sockaddr_in);
    if (sendto(mSocket, temp, sizeof(temp), 0, (const struct sockaddr*)&mRemoteAddr, addrLen) < 0)
    {
        return false;
    }

    clock_t startTime = clock();
    while (true)
    {
        if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000 >= mTimeOut)
        {
            return false;
        }
        //message id
        unsigned int mes;
        //响应消息
        char recvData[1462];
        //数组清零
        memset(recvData, 0, sizeof(recvData));
        int nRemoteAdrLen = sizeof(mRemoteAddr);
        if (recvfrom(mSocket,recvData, 1462,0,
            (sockaddr*)&mRemoteAddr, &nRemoteAdrLen) > 0)
        {
            char* pTemp = recvData;
            HSPS_UNPACK_4_BYTE(pTemp, mes);
            if (mes == PARA_DEVICE_CONFIGURATION_RSP)
            {
                unsigned short returnMsg;
                HSPS_UNPACK_2_BYTE(pTemp, returnMsg);
                if (returnMsg == SUCCESS)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
    }
}

bool OsightDriver::StartMeasure()
{
    //开始测量请求信息块
    char temp[7];
    char* pMsg = temp;
    HSPS_PACK_4_BYTE(pMsg, START_MEASURE_TRANSMISSION_REQ);
    //1-开始发送数据 2-停止发送数据
    HSPS_PACK_1_BYTE(pMsg, 1);
    unsigned short crc = CalCrc((unsigned char*)pMsg, 5);
    HSPS_PACK_2_BYTE(pMsg, crc);

    int addrLen = sizeof(struct sockaddr_in);
    if (sendto(mSocket, temp, sizeof(temp), 0, (const struct sockaddr*)&mRemoteAddr, addrLen) < 0)
    {
        return false;
    }

    return true;
}

bool OsightDriver::StopMeasure()
{
    //开始测量请求信息块
    char temp[7];
    char* pMsg = temp;
    HSPS_PACK_4_BYTE(pMsg, START_MEASURE_TRANSMISSION_REQ);
    //1-开始发送数据 2-停止发送数据
    HSPS_PACK_1_BYTE(pMsg, 2);
    unsigned short crc = CalCrc((unsigned char*)pMsg, 5);
    HSPS_PACK_2_BYTE(pMsg, crc);

    int addrLen = sizeof(struct sockaddr_in);
    if (sendto(mSocket, temp, sizeof(temp), 0, (const struct sockaddr*)&mRemoteAddr, addrLen) < 0)
    {
        return false;
    }

    return true;
}

bool OsightDriver::RecvData(LidarData* data)
{
    clock_t startTime = clock();
    int curPos = 0;
    int pointCount = 0;
    while (true)
    {
        if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000
            >= mTimeOut)
        {
            return false;
        }
        float stopAngle = 225.0;
        LidarData pointData[500];
        //测量数据响应消息最大为1462byte
        char recvData[1462];
        memset(recvData, 0, sizeof(recvData));
        int nAddrLen = sizeof(mRemoteAddr);
        char* start = recvData;
        int recvSize = recvfrom(mSocket, recvData, 1462, 0, (sockaddr*)&mRemoteAddr, &nAddrLen);
        //每包数据应包含Message ID（4byte）与CRC字段（2byte）
        if (recvSize > 6)
        {
            //CRC校验
            UINT16 crc;
            memcpy(&crc, recvData + recvSize - 2, 2);
            if (CalCrc((UINT8*)recvData, recvSize - 2) == ntohs(crc))
            {
                unsigned int messageId = ProcessHead(recvData);
                if (messageId == MEAS_DATA_PACKAGE_RSP)
                {
                    ProcessRecvData(recvData, 
                        pointData,
                        &pointCount,
                        &curPos, 
                        &stopAngle);
                }
                else
                {
                    continue;
                }
            }
        }
        else
        {
            continue;
        }

        for (int i = 0; i < pointCount; ++i)
        {
            data[curPos + i].angle = pointData[i].angle;
            data[curPos + i].distance = pointData[i].distance;
            data[curPos + i].intensity = pointData[i].intensity;
        }

        //判断是否读完数据
        if (pointData[pointCount - 1].angle == stopAngle)
            return true;
    }
}

int OsightDriver::GetPointNum()
{
    bool bTemp = false;
    char SsmReq[6] = { 0 };//参数同步请求消息
    char* start = SsmReq;
    HSPS_PACK_4_BYTE(start, PARA_SYNC_REQ);
    UINT16 intCrc = CalCrc((unsigned char*)SsmReq, 4);
    HSPS_PACK_2_BYTE(start, intCrc);
    int addr_len = sizeof(struct sockaddr_in);
    if (sendto(mSocket, SsmReq, sizeof(SsmReq), 0, (const struct sockaddr*)&mRemoteAddr, addr_len) < 0)
    {
        bTemp = false;
    }
    bTemp = true;

    if (bTemp)
    {
        clock_t startTime = clock();
        int pointNum = -1;
        while (true)
        {
            if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000
                >= mTimeOut)
            {
                return -1;
            }
            char recvData[1462];
            memset(recvData, 0, sizeof(recvData));
            int nAddrLen = sizeof(mRemoteAddr);
            char* start = recvData;
            //接受的消息应包含message id和crc
            if (recvfrom(mSocket,
                recvData,
                1462, 0,
                (sockaddr*)&mRemoteAddr,
                &nAddrLen) >= 6)
            {
                char* temp = recvData;
                unsigned int messageId;
                HSPS_UNPACK_4_BYTE(start, messageId);
                if (messageId == PARA_SYNC_RSP)
                {
                    unsigned int startAngle;
                    unsigned int stopAngle;
                    unsigned int pointNum;
                    unsigned int angularRes;
                    unsigned char intensity;
                    ProcessParaSyncRsp(recvData,
                        startAngle,
                        stopAngle,
                        pointNum,
                        angularRes,
                        intensity);
                    return pointNum;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    return -1;
}

int OsightDriver::GetStartAngle()
{
    if (ParaSyncReq())
    {
        clock_t startTime = clock();
        int pointNum = -1;
        while (true)
        {
            if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000
                >= mTimeOut)
            {
                return -1;
            }
            unsigned int messageId;
            char recvData[1462];
            memset(recvData, 0, sizeof(recvData));
            int nAddrLen = sizeof(mRemoteAddr);
            char* start = recvData;
            //接受的消息应包含message id和crc
            if (recvfrom(mSocket,
                recvData,
                1462, 0,
                (sockaddr*)&mRemoteAddr,
                &nAddrLen) >= 6)
            {
                HSPS_UNPACK_4_BYTE(start, messageId);
                if (messageId == PARA_SYNC_RSP)
                {
                    unsigned int startAngle;
                    unsigned int stopAngle;
                    unsigned int pointNum;
                    unsigned int angularRes;
                    unsigned char intensity;
                    ProcessParaSyncRsp(recvData,
                        startAngle,
                        stopAngle, 
                        pointNum, 
                        angularRes,
                        intensity);
                    return startAngle;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    return 0;
}

int OsightDriver::GetStopAngle()
{
    if (ParaSyncReq())
    {
        clock_t startTime = clock();
        int pointNum = -1;
        while (true)
        {
            if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000
                >= mTimeOut)
            {
                return -1;
            }
            unsigned int messageId;
            char recvData[1462];
            memset(recvData, 0, sizeof(recvData));
            int nAddrLen = sizeof(mRemoteAddr);
            char* start = recvData;
            //接受的消息应包含message id和crc
            if (recvfrom(mSocket,
                recvData,
                1462, 0,
                (sockaddr*)&mRemoteAddr,
                &nAddrLen) >= 6)
            {
                HSPS_UNPACK_4_BYTE(start, messageId);
                if (messageId == PARA_SYNC_RSP)
                {
                    unsigned int startAngle;
                    unsigned int stopAngle;
                    unsigned int pointNum;
                    unsigned int angularRes;
                    unsigned char intensity;
                    ProcessParaSyncRsp(recvData,
                        startAngle,
                        stopAngle,
                        pointNum,
                        angularRes,
                        intensity);
                    return stopAngle;
                }
                else
                {
                    continue;
                }
            }
        }
    }

    return 0;
}

int OsightDriver::GetAngularRes()
{
    if (ParaSyncReq())
    {
        clock_t startTime = clock();
        int pointNum = -1;
        while (true)
        {
            if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000
                >= mTimeOut)
            {
                return -1;
            }
            unsigned int messageId;
            char recvData[1462];
            memset(recvData, 0, sizeof(recvData));
            int nAddrLen = sizeof(mRemoteAddr);
            //接受的消息应包含message id和crc
            if (recvfrom(mSocket,
                recvData,
                1462, 0,
                (sockaddr*)&mRemoteAddr,
                &nAddrLen) >= 6)
            {
                char* start = recvData;
                HSPS_UNPACK_4_BYTE(start, messageId);
                if (messageId == PARA_SYNC_RSP)
                {
                    unsigned int startAngle;
                    unsigned int stopAngle;
                    unsigned int pointNum;
                    unsigned int angularRes;
                    unsigned char intensity;
                    ProcessParaSyncRsp(recvData,
                        startAngle,
                        stopAngle, 
                        pointNum, 
                        angularRes,
                        intensity);
                    return angularRes;
                }
                else
                {
                    continue;
                }
            }
        }
    }

    return 0;
}

void OsightDriver::HostToNet_U16(unsigned short& val)
{
    if(!mIsSysBigEnd)
    {
        val = htons(val);
    }
}

void OsightDriver::NetToHost_U16(unsigned short& val)
{
    if (!mIsSysBigEnd)
    {
        val = ntohs(val);
    }
}

void OsightDriver::HostToNet_U32(unsigned int& val)
{
    if (!mIsSysBigEnd)
    {
        val = htonl(val);
    }
}

void OsightDriver::NetToHost_U32(unsigned int& val)
{
    if (!mIsSysBigEnd)
    {
        val = ntohl(val);
    }
}

unsigned short OsightDriver::CalCrc(unsigned char* pBuf, int len)
{
    unsigned char uchCRCHi = 0xFF;
    unsigned char uchCRCLo = 0xFF;
    unsigned int uindex;
    while (len--)
    {
        uindex = uchCRCHi ^ *pBuf++;
        uchCRCHi = uchCRCLo ^ auchCRCHi[uindex];
        uchCRCLo = auchCRCLo[uindex];
    }
    return (uchCRCHi << 8 | uchCRCLo);
}

void OsightDriver::ProcessRecvData(char* pBuf,
    LidarData* pData,
    int* pointNum,
    int* curPoso,
    float* stopAngle)
{
    pBuf += 4;
    //线数
    unsigned char lineNum;
    //强度信息0-无 1-1byte 2-2byte
    unsigned char intensityStatus;
    //设备状态
    unsigned char devStaus;
    //起始角度
    unsigned int startAngle;
    //终止角度
    unsigned int stopAng;
    //角分辨率
    unsigned int angularRes;
    //包总数
    unsigned char totalPak;
    //包序列号
    unsigned char packNo;
    //最大点数
    unsigned short maxPointNum;
    //当前包点数
    unsigned short curPointNum;
    
    HSPS_UNPACK_1_BYTE(pBuf, lineNum);
    //跳过echo，sn序列号,pn序列号
    pBuf += sizeof(unsigned char);
    pBuf += sizeof(unsigned int) * 2;
    HSPS_UNPACK_1_BYTE(pBuf, intensityStatus);
    HSPS_UNPACK_1_BYTE(pBuf, devStaus);
    //设备状态异常
    if (devStaus > 0)
        return;
    //跳过Time Stamp，Inputs status，Outputs Stuaus
    pBuf += sizeof(unsigned int) * 3;
    HSPS_UNPACK_4_BYTE(pBuf, startAngle);
    HSPS_UNPACK_4_BYTE(pBuf, stopAng);
    //跳过时间字段
    pBuf += sizeof(unsigned char) * 10;
    //跳过预留字段
    pBuf += sizeof(unsigned char) * 32;
    HSPS_UNPACK_4_BYTE(pBuf, angularRes);
    //TODO:未考虑垂直角度分辨率 跳过
    pBuf += sizeof(unsigned char) * 2;
    HSPS_UNPACK_1_BYTE(pBuf, totalPak);
    HSPS_UNPACK_2_BYTE(pBuf, maxPointNum);
    HSPS_UNPACK_1_BYTE(pBuf, packNo);
    HSPS_UNPACK_2_BYTE(pBuf, curPointNum);
    //包序列号大于总包数
    if (packNo > totalPak)
        return;
    *stopAngle = stopAng / 1000.0;
    *pointNum = curPointNum;
    *curPoso = maxPointNum * packNo;

    unsigned int temp32;
    unsigned short temp16;
    unsigned char temp8;
    for (int i = 0; i < curPointNum; ++i)
    {
        float curPointAng = maxPointNum * packNo * ((float)angularRes / 10000000.0) + i * ((float)angularRes / 10000000.0) + startAngle / 1000.0;
        pData[i].angle = curPointAng;
        for (int j = 0; j < lineNum; ++j)
        {
            HSPS_UNPACK_4_BYTE(pBuf, temp32);
            pData[i].distance = temp32 / 10000.0;
            if (intensityStatus == 1)
            {
                HSPS_UNPACK_1_BYTE(pBuf, temp8);
                pData[i].intensity = temp8;
            }
            else if (intensityStatus == 2)
            {
                HSPS_UNPACK_2_BYTE(pBuf, temp16);
                pData[i].intensity = temp16;
            }
            else
            {
                continue;
            }
        }
    }
}

unsigned int OsightDriver::ProcessHead(char* pBuf)
{
    unsigned int messageId;
    HSPS_UNPACK_4_BYTE(pBuf, messageId);
    return messageId;
}
