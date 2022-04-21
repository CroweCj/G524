#include "radar_manager.h"
#include <QDebug>
#include "cloud_data_process.h"
#include "config_setting.h"
#include "cloud_data_read_thread.h"
RadarManager::RadarManager()
{
    init();
}

RadarManager::~RadarManager()
{
    QMap<int, OsightMeasureTread*>::iterator it;
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
    mpDataProcess = new RadarDataProcess(5);

    for (int i = 0; i < 5; ++i)
    {
        ExinovaCloudData data;
        mOutlineCloudMap[i] = data;
        ExinovaCloudData datatemp;
        mShowCloudMap[i] = datatemp;
    }
}

bool RadarManager::addDevice(const QString& ip, const int& port, int type)
{
    if (!isDevExist(type) && ipJudge(ip))
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
        mDeviceMap.insert(type, pThread);

        QObject::connect(pThread, &OsightMeasureTread::sigCloudPointUpdated, 
            this, &RadarManager::threadCloudUpdate);

        return true;
    }
    else
    {
        return false;
    }
}

bool RadarManager::isDevExist(const int type)
{
    return mDeviceMap.contains(type);
}

void RadarManager::removeDevice(const int type)
{
    QMap<int, OsightMeasureTread*>::iterator it = mDeviceMap.find(type);
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
    QMap<int, OsightMeasureTread*>::iterator it = mDeviceMap.find(type);
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
            mDeviceMap[type]->getDevice()->setEnable(true);
            mDeviceMap[type]->start();
        }
        else
            return;
    }
}

void RadarManager::disconnect(const int type)
{
    //TODO:目前没有删除线程，没有移出map
    QMap<int, OsightMeasureTread*>::iterator it = mDeviceMap.find(type);
    if (it != mDeviceMap.end())
    {
        it.value()->pause();
    }
}

void RadarManager::setRadarxMin(const int type, double val)
{
    QMap<int, OsightMeasureTread*>::iterator it = mDeviceMap.find(type);
    if (it != mDeviceMap.end())
    {
        it.value()->getDevice()->setFilterXMin(val);
    }
}

void RadarManager::setRadarxMax(const int type, double val)
{
    QMap<int, OsightMeasureTread*>::iterator it = mDeviceMap.find(type);
    if (it != mDeviceMap.end())
    {
        it.value()->getDevice()->setFilterXMax(val);
    }
}

void RadarManager::setRadaryMin(const int type, double val)
{
    QMap<int, OsightMeasureTread*>::iterator it = mDeviceMap.find(type);
    if (it != mDeviceMap.end())
    {
        it.value()->getDevice()->setFilterYMin(val);
    }
}

void RadarManager::setRadaryMax(const int type, double val)
{
    QMap<int, OsightMeasureTread*>::iterator it = mDeviceMap.find(type);
    if (it != mDeviceMap.end())
    {
        it.value()->getDevice()->setFilterYMax(val);
    }
}

void RadarManager::setRadarThd(const int type,
    double xmin,
    double xmax,
    double ymin,
    double ymax)
{
    QMap<int, OsightMeasureTread*>::iterator it = mDeviceMap.find(type);
    if (it != mDeviceMap.end())
    {
        OsightDevice* pDevice = it.value()->getDevice();
        pDevice->setFilterXMin(xmin);
        pDevice->setFilterXMax(xmax);
        pDevice->setFilterYMin(ymin);
        pDevice->setFilterYMax(ymax);
    }
}

PointCloudT::Ptr RadarManager::getCloud(const int type)
{
    return mShowCloudMap[type].data();
}

PointCloudT::Ptr RadarManager::getReadCloud(const int type)
{
    return mDataReadMap[type]->getCloud().data();
}

double RadarManager::getSpeed(const int type)
{
    return mpDataProcess->getSpeed(type);
}

PointCloudT::Ptr RadarManager::getOutlineCloud(const int type)
{
    return mOutlineCloudMap[type].data();
}

void RadarManager::setFileName(const int type, const QString& fileName)
{
    if(mDeviceMap[type] != NULL)
        mDeviceMap[type]->setFileName(fileName,true);
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
void RadarManager::pauseDataRead()//暂停数据读取
{
    QMap<int, DataReadThread*>::iterator it = mDataReadMap.begin();
    for (it; it != mDataReadMap.end(); ++it)
    {
        if (it.value() != NULL)
        {
            it.value()->pause();
        }
    }
}
void RadarManager::resumeDataRead()//继续数据读取
{
	QMap<int, DataReadThread*>::iterator it = mDataReadMap.begin();
	for (it; it != mDataReadMap.end(); ++it)
	{
		if (it.value() != NULL)
		{
			it.value()->resume();
		}
	}
}
void RadarManager::stopDataWrite() //停止数据写入
{
	for (QMap<int, OsightMeasureTread*>::iterator iter = mDeviceMap.begin(); iter != mDeviceMap.end(); iter++) {
        if (iter.value()->isRunning()) {
            iter.value()->GetFile().close();
            qDebug() << "stopDataWrite" << "\n";
        }
        else {
            qDebug() << "no thread is running!" << "\n";
        }
	}
}
void RadarManager::nextFrame()
{
    QMap<int, DataReadThread*>::iterator it = mDataReadMap.begin();
    for (it; it != mDataReadMap.end(); ++it)
    {
        if (it.value() != NULL)
        {
            it.value()->nextFrame(true);
        }
    }
}

void RadarManager::threadCloudUpdate(const int type)
{
    mShowCloudMap[type].clearData();
    mShowCloudMap[type] += mDeviceMap[type]->getCloud();
    emit sigThreadCloudUpdated(type);
    if (type == OsightDevice::RADAR_A)
    {
        mOutlineCloudMap[type].clearData();
        ExinovaCloudData data;
        data += mDeviceMap[type]->getCloud();
        if (mpDataProcess->detectorOutline(type, OsightDevice::RADAR_B, data))
        {
            mpDataProcess->detectorOutliers(type, data);
            mpDataProcess->updateXYZ(data);
            mOutlineCloudMap[type] += data;
            emit sigAOutlineUpdated();
        }
    }
    else if (type == OsightDevice::RADAR_B)
    {
        if (mpDataProcess->detectorSpeed(type, mDeviceMap[type]->getCloud()) > 0)
        {
            emit sigBSpeedUpdated();
        }
    }
    else if (type == OsightDevice::RADAR_C)
    {
        if (mpDataProcess->detectorSpeed(type, mDeviceMap[type]->getCloud()) > 0)
        {
            emit sigCSpeedUpdated();
        }
    }
    else if (type == OsightDevice::RADAR_D)
    {
        if (mpDataProcess->detectorSpeed(type, mDeviceMap[type]->getCloud()) > 0)
        {
            emit sigDSpeedUpdated();
        }
    }
    else if (type == OsightDevice::RADAR_E)
    {
        mOutlineCloudMap[type].clearData();
        ExinovaCloudData data;
        data += mDeviceMap[type]->getCloud();
        if (mpDataProcess->detectorOutline(type, OsightDevice::RADAR_B, data))
        {
            mpDataProcess->detectorOutliers(type, data);
            mpDataProcess->updateXYZ(data);
            mOutlineCloudMap[type] += data;
            emit sigEOutlineUpdated();
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
        mOutlineCloudMap[radarType].clearData();
        if (mpDataProcess->detectorOutline(radarType, OsightDevice::RADAR_B, mDataReadMap[radarType]->getCloud()))
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
        mOutlineCloudMap[radarType].clearData();
        ExinovaCloudData data;
        data += mDataReadMap[radarType]->getCloud();
        if (mpDataProcess->detectorOutline(radarType, OsightDevice::RADAR_B, data))
        {
            mpDataProcess->detectorOutliers(radarType, data);
            mpDataProcess->updateXYZ(data);
            mOutlineCloudMap[radarType] += data;
            emit sigEOutlineUpdated();
        }
    }
    else
    {
    }

    emit sigDataReadThreadCloudUpdate(radarType);
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