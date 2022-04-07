#ifndef EXINOVA_G524_EXINOVA_POINT_CLOUD_DATA_H__
#define EXINOVA_G524_EXINOVA_POINT_CLOUD_DATA__H__
/*****************************************************************************
* @FileName:exinova_point_cloud_data.h
* @Author: chujiajun
* @CreatTime: 2022/4/5
* @Descriptions:·â×°cloudÊý¾Ý
* @Version: ver 1.0
*****************************************************************************/
#include <QMutex>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

class ExinovaCloudData
{
public:
    ExinovaCloudData();

    ExinovaCloudData(PointCloudT::Ptr cloud);

    ExinovaCloudData(const ExinovaCloudData& data);

    ~ExinovaCloudData();

    ExinovaCloudData operator+(ExinovaCloudData& data);

    ExinovaCloudData& operator+=(ExinovaCloudData& data);

    ExinovaCloudData& operator+=(PointCloudT& data);

    ExinovaCloudData& operator=(ExinovaCloudData& data);

    void setData(PointCloudT::Ptr cloud);

    void clearData();

    PointCloudT::Ptr data();

    PointCloudT::Ptr data() const;

    ExinovaCloudData& getThis();

private:
    PointCloudT::Ptr mCloud;

    QMutex mMutex;
};

#endif // EXINOVA_G524_EXINOVA_POINT_CLOUD_DATA__H__
