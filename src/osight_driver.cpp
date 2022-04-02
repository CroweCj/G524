#include <WINSOCK2.H>
#include <time.h>
#include <string>
#include "osight_driver.h"
unsigned char auchCRCHi1[] =
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

unsigned char auchCRCLo1[] =
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

UINT16   N_CRC16(unsigned char* updata, UINT32 len)
{
    unsigned char uchCRCHi = 0xFF;
    unsigned char uchCRCLo = 0xFF;
    UINT32  uindex;
    while (len--)
    {
        uindex = uchCRCHi ^ *updata++;
        uchCRCHi = uchCRCLo ^ auchCRCHi1[uindex];
        uchCRCLo = auchCRCLo1[uindex];
    }
    return (uchCRCHi << 8 | uchCRCLo);
}

OsightRadarDriver::OsightRadarDriver()
    :mTimeOut(3000)
    ,mIsBigEnd(false)

{
    JudgeBigEnd();
}

OsightRadarDriver::~OsightRadarDriver()
{
    
}

bool OsightRadarDriver::connect(const char* radarIp,
    const unsigned short radarPort,
    const char* localIp,
    const unsigned short localPort)
{
    WSADATA  wsaData;
    WORD  sockVersion = MAKEWORD(2, 2);
    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        return false;
    }
    mRemoteAddr.sin_family = AF_INET;
    mRemoteAddr.sin_port = htons(radarPort);
    mRemoteAddr.sin_addr.s_addr = inet_addr(radarIp);

    mHostAddr.sin_family = AF_INET;
    mHostAddr.sin_port = htons(localPort);
    mHostAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    mHostAddr.sin_addr.s_addr = htons(INADDR_ANY);

    mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int mode = 1;
    ioctlsocket(mSocket, FIONBIO, (u_long FAR*)& mode);
    if(mSocket == INVALID_SOCKET)
    {
        return false;
    }
    clock_t startTime = clock();
    while (bind(mSocket, (sockaddr*)&mHostAddr, sizeof(mHostAddr)) == SOCKET_ERROR)
    {
        if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000 
            >= mTimeOut)
        {
            return false;
        }
    }

    return true;
}

void OsightRadarDriver::disconnect()
{
    stopMeasure();
    closesocket(mSocket);
    WSACleanup();
}

bool OsightRadarDriver::startMeasure()
{
    char temp[7] = { 0 };
    char* pBuf = temp;
    Pack4Byte(&pBuf, START_MEASURE_TRANSMISSION_REQ);
    Pack1Byte(&pBuf, 1);
    UINT16 intCrc = N_CRC16((unsigned char*)temp, 5);
    Pack2Byte(&pBuf, intCrc);
    int remoteAddrLen = sizeof(sockaddr_in);
    if(sendto(mSocket, temp, sizeof(temp), 0, (const struct sockaddr*)&mRemoteAddr, remoteAddrLen) < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool OsightRadarDriver::stopMeasure()
{
    char temp[7] = { 0 };
    char* pBuf = temp;
    Pack4Byte(&pBuf, START_MEASURE_TRANSMISSION_REQ);
    Pack1Byte(&pBuf, 2);
    UINT16 intCrc = N_CRC16((unsigned char*)temp, 5);
    Pack2Byte(&pBuf, intCrc);
    int remoteAddrLen = sizeof(sockaddr_in);
    if (sendto(mSocket, temp, sizeof(temp), 0, (const struct sockaddr*)&mRemoteAddr, remoteAddrLen) < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool OsightRadarDriver::paramSyncReq()
{
    char temp[6] = { 0 };
    char* pBuf = temp;
    Pack4Byte(&pBuf, PARA_SYNC_REQ);
    UINT16 intCrc = N_CRC16((unsigned char*)temp, 4);
    Pack2Byte(&pBuf, intCrc);
    int remoteAddrLen = sizeof(sockaddr_in);
    if (sendto(mSocket, temp, sizeof(temp), 0, (const struct sockaddr*)&mRemoteAddr, remoteAddrLen) < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int OsightRadarDriver::paramSyncRsp()
{
    if(paramSyncReq())
    {
        clock_t  startTime = clock();
        while(true)
        {
            if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000
                >= mTimeOut)
            {
                return -1;
            }
            char recvBuf[1462];
            memset(recvBuf, 0, sizeof(recvBuf));
            int remoteAddrLen = sizeof(mRemoteAddr);
            if(recvfrom(mSocket,recvBuf,1462,0,(sockaddr*)&mRemoteAddr,&remoteAddrLen) > 0)
            {
                char* pBuf = recvBuf;
                unsigned int messageId;
                UnPack4Byte(&pBuf, messageId);
                if(messageId == PARA_SYNC_RSP)
                {
                    int totalPointNum = -1;
                    processSync(recvBuf, totalPointNum);
                    return totalPointNum;
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
    else
    {
        return -1;
    }

}

bool OsightRadarDriver::paramConfigReq(unsigned char spped,
    unsigned char intensity,
    unsigned int angleRes)
{
    char temp[12] = { 0 };
    char* pBuf = temp;
    Pack4Byte(&pBuf, PARA_DEVICE_CONFIGURATION_REQ);
    Pack1Byte(&pBuf, spped);
    Pack1Byte(&pBuf, intensity);
    Pack4Byte(&pBuf, angleRes);

    UINT16 intCrc = N_CRC16((unsigned char*)temp, 10);
    Pack2Byte(&pBuf, intCrc);
    int remoteAddrLen = sizeof(sockaddr_in);
    if (sendto(mSocket, temp, sizeof(temp), 0, (const struct sockaddr*)&mRemoteAddr, remoteAddrLen) < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int OsightRadarDriver::paramConfigRsp(unsigned char spped,
    unsigned char intensity,
    unsigned int angleRes)
{
    if (paramConfigReq(spped,intensity,angleRes))
    {
        clock_t  startTime = clock();
        while (true)
        {
            if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000
                >= mTimeOut)
            {
                return CONFIG_FAILED;
            }
            char recvBuf[1462];
            memset(recvBuf, 0, sizeof(recvBuf));
            int remoteAddrLen = sizeof(mRemoteAddr);
            if (recvfrom(mSocket, recvBuf, 1462, 0, (sockaddr*)&mRemoteAddr, &remoteAddrLen) > 0)
            {
                char* pBuf = recvBuf;
                unsigned int messageId;
                UnPack4Byte(&pBuf, messageId);
                if (messageId == PARA_DEVICE_CONFIGURATION_RSP)
                {
                    unsigned short errCode = CONFIG_FAILED;
                    UnPack2Byte(&pBuf, errCode);
                    return errCode;
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
    else
    {
        return CONFIG_FAILED;
    }
}

bool OsightRadarDriver::recvOneFrameData(LidarData* data)
{
    int curPos = 0;
    clock_t  startTime = clock();
    while (true)
    {
        if (((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000 >= mTimeOut)
        {
            return false;
        }

        LidarData datebufer[500];
        int nsize = 0;
        UINT32 Message;
        float stopAngle = 225.0;
        char           recData[1460];
        memset(recData, 0, sizeof(recData));
        int nAddrLen = sizeof(mRemoteAddr);
        int receiveSize = recvfrom(mSocket, recData, 1460, 0, (sockaddr*)&mRemoteAddr, &nAddrLen);
        if (receiveSize > 6)
        {
            UINT16 crc;
            memcpy(&crc, recData + receiveSize - 2, 2);
            if (N_CRC16((UINT8*)recData, receiveSize - 2) == NtoHS(crc))
            {
                unsigned int messageId;
                char* pBuf = recData;
                UnPack4Byte(&pBuf, messageId);
                switch (messageId)
                {
                case MEAS_DATA_PACKAGE_RSP:
                    processOneFrameData(recData, datebufer, &nsize, &curPos, &stopAngle);
                    break;
                default:
                    continue;
                }
            }
        }
        else
        {
            continue;
        }
        for (int i = 0; i < nsize; i++)
        {
            data[curPos + i].angle = datebufer[i].angle;
            data[curPos + i].distance = datebufer[i].distance;
            data[curPos + i].intensity = datebufer[i].intensity;
        }
        if (datebufer[nsize - 1].angle == stopAngle)
        {
            return true;
        }
    }
}

unsigned short OsightRadarDriver::HtoNS(unsigned short data)
{
    if(mIsBigEnd)
    {
        return data;
    }
    else
    {
        return (((data) & 0x00FF) << 8) | (((data) & 0xFF00) >> 8);
    }
}

unsigned short OsightRadarDriver::NtoHS(unsigned short data)
{
    if (mIsBigEnd)
    {
        return data;
    }
    else
    {
        return (((data) & 0x00FF) << 8) | (((data) & 0xFF00) >> 8);
    }
}

unsigned int OsightRadarDriver::HtoNL(unsigned int data)
{
    if (mIsBigEnd)
    {
        return data;
    }
    else
    {
        return ((((data) & 0x000000FF) << 24) |
            (((data) & 0x0000FF00) << 8) |
            (((data) & 0x00FF0000) >> 8) |
            (((data) & 0xFF000000) >> 24));
    }
}

unsigned int OsightRadarDriver::NtoHL(unsigned int data)
{
    if (mIsBigEnd)
    {
        return data;
    }
    else
    {
        return ((((data) & 0x000000FF) << 24) |
            (((data) & 0x0000FF00) << 8) |
            (((data) & 0x00FF0000) >> 8) |
            (((data) & 0xFF000000) >> 24));
    }
}

void OsightRadarDriver::Pack1Byte(char** pBuf, unsigned char data)
{
    *(*pBuf) = data;
    (*pBuf) += sizeof(char);
}

void OsightRadarDriver::Pack2Byte(char** pBuf, unsigned short data)
{
    *((unsigned short*)*pBuf) = HtoNS(data);
    (*pBuf) += sizeof(char) * 2;
}

void OsightRadarDriver::Pack4Byte(char** pBuf, unsigned int data)
{
    *((unsigned int*)*pBuf) = HtoNL(data);
    (*pBuf) += sizeof(char) * 4;
}

void OsightRadarDriver::UnPack1Byte(char** pBuf, unsigned char& data)
{
    data = *(*pBuf);
    (*pBuf) += sizeof(char);
}

void OsightRadarDriver::UnPack2Byte(char** pBuf, unsigned short& data)
{
    data = NtoHS(*((unsigned short*)*pBuf));
    (*pBuf) += sizeof(char) * 2;
}

void OsightRadarDriver::UnPack4Byte(char** pBuf, unsigned int& data)
{
    data = NtoHL(*((unsigned int*)*pBuf));
    (*pBuf) += sizeof(char) * 4;
}

void OsightRadarDriver::JudgeBigEnd()
{
    union Test
    {
        int a;
        char b;
    };
    Test test;
    test.a = 1;
    if (test.b == 1)
        mIsBigEnd = false;
    else
        mIsBigEnd = true;
}

void OsightRadarDriver::processSync(char* pRecvBuf, int& totalPointNum)
{
    unsigned int startAngel = 0;
    unsigned int stopAngle = 0;
    unsigned int pointNum = 0;
    unsigned int angularRes = 0;

    pRecvBuf += 24;

    UnPack4Byte(&pRecvBuf, startAngel);
    UnPack4Byte(&pRecvBuf, stopAngle);
    UnPack4Byte(&pRecvBuf, pointNum);

    pRecvBuf += 31;

    UnPack4Byte(&pRecvBuf, angularRes);

    int tmpPointNum = ((stopAngle - startAngel) / 1000.0) / (angularRes / 10000000.0) + 1;
    if(pointNum > 0 
        && pointNum == tmpPointNum)
    {
        totalPointNum = pointNum;
    }
    else
    {
        return;
    }
}

void OsightRadarDriver::processOneFrameData(char* pRecvBuf,
    LidarData* pDataBuf,
    int* count,
    int* curPos,
    float* stopAngle)
{
    unsigned char lineNum = 0;
    unsigned char intensity = 0;
    unsigned char deviceStatus = 0;
    unsigned int startAngle = 0;
    unsigned int tempStopAngle = 0;
    unsigned int hAngularRes = 0;
    unsigned short maxPointCount = 0;
    unsigned char packetNo = 0;
    unsigned short pointCount = 0;

    pRecvBuf += 4;

    UnPack1Byte(&pRecvBuf, lineNum);

    pRecvBuf += 9;

    UnPack1Byte(&pRecvBuf, intensity);
    UnPack1Byte(&pRecvBuf, deviceStatus);
    if (deviceStatus > 0)
        return;

    pRecvBuf += 12;

    UnPack4Byte(&pRecvBuf, startAngle);
    UnPack4Byte(&pRecvBuf, tempStopAngle);

    pRecvBuf += 42;

    UnPack4Byte(&pRecvBuf, hAngularRes);

    pRecvBuf += 3;

    UnPack2Byte(&pRecvBuf, maxPointCount);
    UnPack1Byte(&pRecvBuf, packetNo);
    UnPack2Byte(&pRecvBuf, pointCount);

    *stopAngle = tempStopAngle / 1000.0;
    *count = pointCount;
    *curPos = maxPointCount * packetNo;
    unsigned int tempDistance = 0;
    unsigned char temp = 0;
    for(int i = 0; i < pointCount; ++i)
    {
        float fangle = (*curPos) *((float)hAngularRes / 10000000.0) + i * ((float)hAngularRes / 10000000.0) + startAngle / 1000.0;
        pDataBuf[i].angle = fangle;
        for (int j = 0; j < lineNum; j++)
        {
            UnPack4Byte(&pRecvBuf, tempDistance);
            pDataBuf[i].distance = (float)tempDistance / 10000.0;
            switch (intensity) {
            case 0:
                break;
            case 1:
                UnPack1Byte(&pRecvBuf, temp);
                pDataBuf[i].intensity = temp;
                break;
            case 2:
                UnPack2Byte(&pRecvBuf, pDataBuf[i].intensity);
                break;
            default:
                break;
            }
        }
    }
}




