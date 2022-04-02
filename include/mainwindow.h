#ifndef OSIGHT_RADAR_PCL_MAINWINDOW_H__
#define OSIGHT_RADAR_PCL_MAINWINDOW__H__

#include <QtWidgets/QMainWindow>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vtkRenderWindow.h>
#include "ui_mainwindow.h"
#include "osight_measure_thread.h"
#include "cloud_data_process.h"

class PclMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PclMainWindow(QWidget* parent = Q_NULLPTR);

    ~PclMainWindow();

    void init();

    void setBackgroundColor(double r, double g, double b);

private:
    void initSetAngleRes();

    void initSetIntensity();

    void initSetSpeed();

private:
    Ui::QtPCLTestClass ui;

    pcl::visualization::PCLVisualizer::Ptr viewer;

    //TODO:目前控制两个雷达 先这么做 
    OsightMeasureTread* mpThreadOne;

    OsightMeasureTread* mpThreadTwo;
    //处理点云数据
    SingleRadarProcess* mpSingleRadarProcess;
    
};

#endif // OSIGHT_RADAR_PCL_MAINWINDOW__H__
