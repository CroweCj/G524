#include "exinova_point_cloud_data.h"
#include <QMutexLocker>

ExinovaCloudData::ExinovaCloudData()
{
    mCloud = PointCloudT::Ptr(new PointCloudT);
}
ExinovaCloudData::ExinovaCloudData(PointCloudT::Ptr cloud)
    :mCloud(cloud)
{
}

ExinovaCloudData::~ExinovaCloudData()
{
}

ExinovaCloudData ExinovaCloudData::operator+(ExinovaCloudData& data)
{
    QMutexLocker locker(&mMutex);
    PointCloudT::Ptr result(new PointCloudT);
    *result = (*mCloud) + (*data.data());
    return ExinovaCloudData(result);
}

ExinovaCloudData& ExinovaCloudData::operator+=(ExinovaCloudData& data)
{
    QMutexLocker locker(&mMutex);
    *mCloud += *data.data();
    return *this;
}

ExinovaCloudData& ExinovaCloudData::operator+=(PointCloudT& data)
{
    QMutexLocker locker(&mMutex);
    *mCloud += data;
    return *this;
}

ExinovaCloudData& ExinovaCloudData::operator=(const ExinovaCloudData& data)
{
    QMutexLocker locker(&mMutex);
    mCloud = data.data();
    return *this;
}

void ExinovaCloudData::setData(PointCloudT::Ptr cloud)
{
    QMutexLocker locker(&mMutex);
    mCloud = cloud;
}

void ExinovaCloudData::clearData()
{
    QMutexLocker locker(&mMutex);
    mCloud->clear();
}

PointCloudT::Ptr ExinovaCloudData::data()
{
    QMutexLocker locker(&mMutex);
    return mCloud;
}




