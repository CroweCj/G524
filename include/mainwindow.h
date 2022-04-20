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
#include <QMutex>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vtkRenderWindow.h>
#include "ui_mainwindow.h"
#include "cloud_data_process.h"
#include "config_setting.h"
#include "radar_manager.h"
#include "file_select_widget.h"

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
signals:
public slots:
    void radarAConnect();
    void radarADisconnect();
    void radarAXMinChange(double value);
    void radarAXMaxChange(double value);
    void radarAYMinChange(double value);
    void radarAYMaxChange(double value);

    void radarBConnect();
    void radarBDisconnect();
    void radarBXMinChange(double value);
    void radarBXMaxChange(double value);
    void radarBYMinChange(double value);
    void radarBYMaxChange(double value);

    void radarCConnect();
    void radarCDisconnect();
    void radarCXMinChange(double value);
    void radarCXMaxChange(double value);
    void radarCYMinChange(double value);
    void radarCYMaxChange(double value);

    void radarDConnect();
    void radarDDisconnect();
    void radarDXMinChange(double value);
    void radarDXMaxChange(double value);
    void radarDYMinChange(double value);
    void radarDYMaxChange(double value);

    void radarEConnect();
    void radarEDisconnect();
    void radarEXMinChange(double value);
    void radarEXMaxChange(double value);
    void radarEYMinChange(double value);
    void radarEYMaxChange(double value);

private:
    //初始化vtk控件
    void initVtkWidget();
    //初始化界面控件
    void initUi();
    //初始化信号连接
    void initConnect();
    //更新ini文件
    void updateSettings();

    void updateShow(pcl::visualization::PCLVisualizer::Ptr viewer,
        const QString& ip,
        const QString& cloudId);

    void initFileRead();

    void initFileWrite();

private:
    Ui::mainwindow ui;
    //雷达ABCDE对应Visualizer
    pcl::visualization::PCLVisualizer::Ptr viewerA, viewerB, viewerC, viewerD, viewerE;
    //用于车辆轮廓点云显示
    pcl::visualization::PCLVisualizer::Ptr viewerShow;
    RadarManager* mpRadarManager;
    //锁
    QMutex mMutex;
    //文件路径选择界面
    FileSelectWidget* mpFileSelectWidget;
};

#endif // OSIGHT_RADAR_PCL_MAINWINDOW__H__
