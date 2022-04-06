#ifndef OSIGHT_RADAR_PCL_MAINWINDOW_H__
#define OSIGHT_RADAR_PCL_MAINWINDOW__H__
/*****************************************************************************
* @FileName:mainwindow.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:主界面
* @Version: ver 1.0
*****************************************************************************/
#include <QtWidgets/QMainWindow>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vtkRenderWindow.h>
#include "ui_mainwindow.h"
#include "osight_measure_thread.h"
#include "cloud_data_process.h"
typedef enum FunctionWidgetIndex
{
    RADAR_SETTING = 0,      //雷达设置
    VEHICLE_SHOW,           //车辆轮廓
    FUNC_END
}FunctionWidgetIndex;

typedef enum RadarType
{
    RADAR_A = 0,
    RADAR_B,
    RADAR_C,
    RADAR_D,
    RADAR_E,
    INDEX_END
}RadarType;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

    ~MainWindow();

    void init();

    //设置背景色
    void setBackgroundColor(pcl::visualization::PCLVisualizer::Ptr viewer,
        double r,
        double g,
        double b);

private:
    //初始化vtk控件
    void initVtkWidget();
    //初始化界面控件
    void initUi();
    //初始化信号连接
    void initConnect();

private:
    Ui::mainwindow ui;
    //雷达ABCDE对应Visualizer
    pcl::visualization::PCLVisualizer::Ptr viewerA, viewerB, viewerC, viewerD, viewerE;
    //用于车辆轮廓点云显示
    pcl::visualization::PCLVisualizer::Ptr viewerShow;
};

#endif // OSIGHT_RADAR_PCL_MAINWINDOW__H__
