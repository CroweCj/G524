#include <QtWidgets/QApplication>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDebug>
#include "mainwindow.h"
#include "vtkoutputwindow.h"

int main(int argc, char* argv[])
{
    vtkOutputWindow::SetGlobalWarningDisplay(0);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
//int main(int argc, char* argv[])
//{
//    QApplication a(argc, argv);
//
//    ExinovaCloudData data;
//
//    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud = data.data();
//
//    cloud->width = 5;
//    cloud->height = 5;
//    cloud->points.resize(cloud->width * cloud->height);
//
//    for (auto& point : *cloud)
//    {
//        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
//        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
//        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
//    }
//
//    ExinovaCloudData data1;
//
//    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud1 = data1.data();
//
//    cloud1->width = 5;
//    cloud1->height = 5;
//    cloud1->points.resize(cloud1->width * cloud1->height);
//
//    for (auto& point : *cloud1)
//    {
//        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
//        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
//        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
//    }
//
//    ExinovaFile file("D:/Project/G524/G524/test.pcd");
//    if (!file.open(ExinovaFile::WRITEONLY, ExinovaFile::PCD))
//    {
//        return -1;
//    }
//    file.write(data);
//    file.write(data1);
//
//    file.close();
//    return a.exec();
//}
//#include "exinova_cloud_cfile.h"
//int main(int argc, char* argv[])
//{
//    QApplication a(argc, argv);
//    ExinovaDataFile file("D:/Project/G524/G524/test.dat");
//    if (file.open(ExinovaDataFile::READONLY) < 0)
//    {
//        return -1;
//    }
//    int nCount = 1000;
//    while (nCount > 0)
//    {
//        ExinovaCloudData data;
//        file.read(data);
//        QString dataStr;
//        for (int i = 0; i < data.data()->points.size(); ++i)
//        {
//            dataStr = QString::number(data.data()->points[i].x) + QString(" ")
//                + QString::number(data.data()->points[i].y) + QString(" ")
//                + QString::number(data.data()->points[i].z) + QString("\n");
//
//            qDebug() << dataStr;
//        }
//        --nCount;
//    }
//
//    file.close();
//
//    FILE* fp = fopen("D:/Project/G524/G524/test.dat", "rb");
//    ExinovaCloudData data;
//    int n = 1000;
//    while (n > 0)
//    {
//        DataHeader header[1] = {};
//        fread(header, sizeof(DataHeader), 1, fp);
//        data.data()->points.resize(header[0].size);
//        for (int i = 0; i < header[0].size; ++i)
//        {
//            PointT dataPos[1] = {};
//            int size = sizeof(PointT);
//            fread(dataPos, sizeof(PointT), 1, fp);
//            data.data()->points[i] = dataPos[0];
//        }
//        --n;
//    }
//    fclose(fp);
//    return a.exec();
//}

//#include <QtWidgets/QApplication>
//#include "osight_driver.h"
//#include "exinova_cloud_cfile.h"
//#include "exinova_point_cloud_data.h"
//
//void lidarDataToCloudTemp(LidarData* pData, int pointNum,ExinovaCloudData& data)
//{
//    data.data()->clear();
//    PointT poi;
//    for (int i = 0; i < pointNum; ++i)
//    {
//        //计算x，y，z 无垂直角度
//        poi.x = pData[i].distance * cosf(pData[i].angle * M_PI / 180);
//        poi.y = pData[i].distance * sinf(pData[i].angle * M_PI / 180);
//        poi.z = 0;
//        poi.r = 255;
//        poi.g = 255;
//        poi.b = 255;
//        poi.a = 255;
//        data.data()->push_back(poi);
//    }
//}
//
//int main(int argc, char* argv[])
//{
//    QApplication a(argc, argv);
//    OsightRadarDriver driver;
//    driver.connect("192.168.1.10",6500,"192.168.1.100",5500);
//    int nTry = 10;
//    ExinovaCloudData data;
//    ExinovaDataFile file("D:/Project/G524/G524/test.dat");
//    int nDataCount = 1000;
//
//    int num = driver.paramSyncRsp();
//    if (num > 0)
//    {
//        nTry = 10; 
//        LidarData* pData = new LidarData[num];
//        //开始采集
//        driver.startMeasure();
//        if (file.open(ExinovaDataFile::WRITEONLY) < 0)
//        {
//            return -1;
//        }
//        while (true)
//        {
//            if (driver.recvOneFrameData(pData) && nDataCount > 0)
//            {
//                lidarDataToCloudTemp(pData, num, data);
//                file.write(data);
//                Sleep(5);
//                int n = 0;
//                --nDataCount;
//            }
//            else
//            {
//                break;
//            }
//        }
//        delete[] pData;
//    }
//    file.close();
//    driver.stopMeasure();
//    driver.disconnect();
//    return a.exec();
//}

