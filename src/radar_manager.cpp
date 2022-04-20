#include "radar_manager.h"
#include "cloud_data_process.h"
#include "config_setting.h"
#include "cloud_data_read_thread.h"
RadarManager::RadarManager()
{
    init();
}

RadarManager::~RadarManager()
{
    QMap<QString, OsightMeasureTread*>::iterator it;
    for (it = mDeviceMap.begin(); it != mDeviceMap.end(); ++it)
    {
        if (it.value() != NULL)
        {
            it.value()->stop();
            it.value()->getDevice()->stopMeasure();
            it.value()->getDevice()->close();
            it.value()->deleteLater();
        }
    }

    QMap<int, DataReadThread*>::iterator itdata;
    for (itdata = mDataReadMap.begin(); itdata != mDataReadMap.end(); ++itdata)
    {
        if (itdata.value() != NULL)
        {
            itdata.value()->stop();
            itdata.value()->deleteLater();
        }
    }
}

void RadarManager::init()
{
    //TODO:待完成
    mpDataProcess = new SingleRadarProcess(5);

    for (int i = 0; i < 5; ++i)
    {
        ExinovaCloudData data;
        mOutlineCloudMap[i] = data;
    }
}

bool RadarManager::addDevice(const QString& ip, const int& port, int type)
{
    if (!isDevExist(ip) && ipJudge(ip))
    {
        OsightMeasureTread* pThread = new OsightMeasureTread();
        pThread->setDevice((OsightDevice::RadarNumber)type);
        pThread->getDevice()->setIp(ip);
        pThread->getDevice()->setPort(port);
        pThread->setRadarAddr(ip, port);
        //TODO:先从配置中获取对应本地端口
        if (type == OsightDevice::RADAR_B)
        {
            pThread->setLocalAddr(
                ExinovaSettings::value("local/ip").toString(),
                ExinovaSettings::value("local/port2b").toInt());
        }
        else if (type == OsightDevice::RADAR_E)
        {
            pThread->setLocalAddr(
                ExinovaSettings::value("local/ip").toString(),
                ExinovaSettings::value("local/port2e").toInt());
        }
        else
        {
            pThread->setLocalAddr(
                ExinovaSettings::value("local/ip").toString(),
                ExinovaSettings::value("local/port2b").toInt());
        }
        mDeviceMap.insert(ip, pThread);

        QObject::connect(pThread, &OsightMeasureTread::sigCloudPointUpdated, 
            this, &RadarManager::threadCloudUpdate);

        return true;
    }
    else
    {
        return false;
    }
}

bool RadarManager::isDevExist(const QString& ip)
{
    return mDeviceMap.contains(ip);
}

void RadarManager::removeDevice(const QString& ip)
{
    QMap<QString, OsightMeasureTread*>::iterator it = mDeviceMap.find(ip);
    if (it != mDeviceMap.end())
    {
        QObject::disconnect(it.value(), &OsightMeasureTread::sigCloudPointUpdated,
            this, &RadarManager::threadCloudUpdate);
        delete it.value();
        mDeviceMap.erase(it);
    }
}

void RadarManager::connect(const QString& ip, const int& port, int type)
{
    QMap<QString, OsightMeasureTread*>::iterator it = mDeviceMap.find(ip);
    if (it != mDeviceMap.end())
    {
        //开始测量
        it.value()->getDevice()->setEnable(true);
        it.value()->resume();
        if (!it.value()->isRunning())
        {
            it.value()->start();
        }
    }
    else
    {
        if (addDevice(ip, port, type))
        {
            mDeviceMap[ip]->getDevice()->setEnable(true);
            mDeviceMap[ip]->start();
        }
        else
            return;
    }
}

void RadarManager::disconnect(const QString& ip)
{
    //TODO:目前没有删除线程，没有移出map
    QMap<QString, OsightMeasureTread*>::iterator it = mDeviceMap.find(ip);
    if (it != mDeviceMap.end())
    {
        it.value()->pause();
    }
}

void RadarManager::setRadarxMin(const QString& ip, double val)
{
    QMap<QString, OsightMeasureTread*>::iterator it = mDeviceMap.find(ip);
    if (it != mDeviceMap.end())
    {
        it.value()->getDevice()->setFilterXMin(val);
    }
}

void RadarManager::setRadarxMax(const QString& ip, double val)
{
    QMap<QString, OsightMeasureTread*>::iterator it = mDeviceMap.find(ip);
    if (it != mDeviceMap.end())
    {
        it.value()->getDevice()->setFilterXMax(val);
    }
}

void RadarManager::setRadaryMin(const QString& ip, double val)
{
    QMap<QString, OsightMeasureTread*>::iterator it = mDeviceMap.find(ip);
    if (it != mDeviceMap.end())
    {
        it.value()->getDevice()->setFilterYMin(val);
    }
}

void RadarManager::setRadaryMax(const QString& ip, double val)
{
    QMap<QString, OsightMeasureTread*>::iterator it = mDeviceMap.find(ip);
    if (it != mDeviceMap.end())
    {
        it.value()->getDevice()->setFilterYMax(val);
    }
}

void RadarManager::setRadarThd(const QString& ip,
    double xmin,
    double xmax,
    double ymin,
    double ymax)
{
    QMap<QString, OsightMeasureTread*>::iterator it = mDeviceMap.find(ip);
    if (it != mDeviceMap.end())
    {
        OsightDevice* pDevice = it.value()->getDevice();
        pDevice->setFilterXMin(xmin);
        pDevice->setFilterXMax(xmax);
        pDevice->setFilterYMin(ymin);
        pDevice->setFilterYMax(ymax);
    }
}

PointCloudT::Ptr RadarManager::getCloud(const QString& ip)
{
    return mDeviceMap[ip]->getCloud().data();
}

double RadarManager::getSpeed(const QString& ip)
{
    OsightDevice::RadarNumber type = mDeviceMap[ip]->getDevice()->getRadarNumber();
    return mpDataProcess->getSpeed(type);
}

PointCloudT::Ptr RadarManager::getOutlineCloud(const QString& ip)
{
    OsightDevice::RadarNumber type = mDeviceMap[ip]->getDevice()->getRadarNumber();
    return mOutlineCloudMap[type].data();
}

void RadarManager::setFileName(const QString& ip, const QString& fileName)
{
    if(mDeviceMap[ip] != NULL)
        mDeviceMap[ip]->setFileName(fileName,true);
}

void RadarManager::addDataRead(int radarType, const QString& filePath)
{
    QMap<int, DataReadThread*>::iterator it = mDataReadMap.find(radarType);
    if (it != mDataReadMap.end())
    {
        it.value()->setRadarType(radarType);
        it.value()->setFileName(filePath);
    }
    else
    {
        DataReadThread* pDataThread = new DataReadThread(radarType);
        pDataThread->setFileName(filePath);
        mDataReadMap.insert(radarType, pDataThread);
        QObject::connect(pDataThread, &DataReadThread::sigDataIsReady, this, &RadarManager::readThreadCloudUpdate);
    }
}

void RadarManager::startDataRead()
{
    QMap<int, DataReadThread*>::iterator it = mDataReadMap.begin();
    for (it; it != mDataReadMap.end(); ++it)
    {
        if (it.value() != NULL)
        {
            it.value()->start();
        }
    }
}

void RadarManager::threadCloudUpdate(const QString& ip)
{
    OsightDevice::RadarNumber type = mDeviceMap[ip]->getDevice()->getRadarNumber();
    //switch (type)
    //{
    //case OsightDevice::RADAR_A:

    //case OsightDevice::RADAR_B:
    //    if (mpDataProcess->detectorSpeed(type, mDeviceMap[ip]->getCloud()) > 0)
    //    {
    //        emit sigBSpeedUpdated();
    //    }
    //    break;
    //case OsightDevice::RADAR_C:
    //    emit sigCSpeedUpdated();
    //    break;
    //case OsightDevice::RADAR_D:
    //    emit sigDSpeedUpdated();
    //    break;
    //case OsightDevice::RADAR_E:

    //default:
    //    break;
    //}

    if (type == OsightDevice::RADAR_A)
    {
        QMutexLocker locker(&mMutex);
        emit sigAThreadCloudUpdated(ip);
        if (mpDataProcess->detectorOutline(type, mDeviceMap[ip]->getCloud()))
        {
            emit sigAOutlineUpdated(ip);
            mOutlineCloudMap[type] += mDeviceMap[ip]->getCloud();
        }     
    }
    else if (type == OsightDevice::RADAR_B)
    {
        emit sigBThreadCloudUpdated(ip);
        if (mpDataProcess->detectorSpeed(type, mDeviceMap[ip]->getCloud()) > 0)
        {
            emit sigBSpeedUpdated(ip);
        }
    }
    else if (type == OsightDevice::RADAR_C)
    {
        emit sigCThreadCloudUpdated(ip);
        if (mpDataProcess->detectorSpeed(type, mDeviceMap[ip]->getCloud()) > 0)
        {
            emit sigCSpeedUpdated(ip);
        }
    }
    else if (type == OsightDevice::RADAR_D)
    {
        emit sigDThreadCloudUpdated(ip);
        if (mpDataProcess->detectorSpeed(type, mDeviceMap[ip]->getCloud()) > 0)
        {
            emit sigDSpeedUpdated(ip);
        }
    }
    else if (type == OsightDevice::RADAR_E)
    {
        QMutexLocker locker(&mMutex);
        emit sigEThreadCloudUpdated(ip);

        //TODO:暂时用b雷达测得速度
        if (mpDataProcess->getSpeed(OsightDevice::RADAR_B) > 0
            &&mpDataProcess->detectorOutline(type, mDeviceMap[ip]->getCloud()))
        {
            emit sigEOutlineUpdated(ip);
            mOutlineCloudMap[type] += mDeviceMap[ip]->getCloud();
        }
    }
    else
    {
    }
}

void RadarManager::readThreadCloudUpdate(int radarType)
{
    if (radarType == OsightDevice::RADAR_A)
    {
        if (mpDataProcess->detectorOutline(radarType, mDataReadMap[radarType]->getCloud()))
        {
            mOutlineCloudMap[radarType] += mDataReadMap[radarType]->getCloud();
        }
    }
    else if (radarType == OsightDevice::RADAR_B)
    {
        if (mpDataProcess->detectorSpeed(radarType, mDataReadMap[radarType]->getCloud()) > 0)
        {
            //TODO：待处理
            double speed = mpDataProcess->getSpeed(OsightDevice::RADAR_B);
            return;
        }
    }
    else if (radarType == OsightDevice::RADAR_C)
    {
        if (mpDataProcess->detectorSpeed(radarType, mDataReadMap[radarType]->getCloud()) > 0)
        {
            //TODO：待处理
        }
    }
    else if (radarType == OsightDevice::RADAR_D)
    {
        if (mpDataProcess->detectorSpeed(radarType, mDataReadMap[radarType]->getCloud()) > 0)
        {
            //TODO：待处理
        }
    }
    else if (radarType == OsightDevice::RADAR_E)
    {
        //TODO:暂时用b雷达测得速度
        if (mpDataProcess->getSpeed(OsightDevice::RADAR_B) > 0
            && mpDataProcess->detectorOutline(radarType, mDataReadMap[radarType]->getCloud()))
        {
            mOutlineCloudMap[radarType] += mDataReadMap[radarType]->getCloud();
        }
    }
    else
    {
    }
}

bool RadarManager::ipJudge(const QString& ip)
{
    if (ip.isEmpty())
        return false;
    QStringList strLst = ip.split(".");
    if (strLst.size() != 4)
    {
        return false;
    }
    else
    {
        int num = -1;
        for (int i = 0; i < strLst.size(); ++i)
        {
            num = strLst[i].toInt();
            if (num > 255 || num < 0)
            {
                return false;
            }
        }

        return true;
    }
}