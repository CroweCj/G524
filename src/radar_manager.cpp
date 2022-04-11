#include "radar_manager.h"
#include "cloud_data_process.h"
RadarManager::RadarManager()
{
    init();
}

RadarManager::~RadarManager()
{
    QMap<QString, OsightMeasureTread*>::iterator it;
    for (it = mDeviceMap.begin(); it != mDeviceMap.end(); ++it)
    {
        QObject::disconnect(it.value(), &OsightMeasureTread::sigCloudPointUpdated,
            this, &RadarManager::threadCloudUpdate);
        it.value()->deleteLater();
    }
}

void RadarManager::init()
{
    //TODO:待完成
    mpDataProcess = new SingleRadarProcess(5);
}

bool RadarManager::addDevice(const QString& ip, int type)
{
    if (!isDevExist(ip) && ipJudge(ip))
    {
        OsightMeasureTread* pThread = new OsightMeasureTread();
        pThread->setDevice((OsightDevice::RadarNumber)type);
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

void RadarManager::connect(const QString& ip, int type)
{
    QMap<QString, OsightMeasureTread*>::iterator it = mDeviceMap.find(ip);
    if (it != mDeviceMap.end())
    {
        //开始测量
        it.value()->getDevice()->setEnable(true);
        it.value()->start();
    }
    else
    {
        if (addDevice(ip, type))
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
        it.value()->stop();
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
        emit sigAThreadCloudUpdated(ip);
        if (mpDataProcess->detectorOutline(type, mDeviceMap[ip]->getCloud()))
        {
            emit sigAOutlineUpdated(ip);
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
        emit sigEThreadCloudUpdated(ip);
        if (mpDataProcess->detectorOutline(type, mDeviceMap[ip]->getCloud()))
        {
            emit sigEOutlineUpdated(ip);
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