#ifndef OSIGHT_RADAR_PCL_MAINWINDOW_H__
#define OSIGHT_RADAR_PCL_MAINWINDOW__H__
/*****************************************************************************
* @FileName:mainwindow.h
* @Author: chujiajun
* @CreatTime: 2022/4/6
* @Descriptions:������
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
    RADAR_SETTING = 0,      //�״�����
    VEHICLE_SHOW,           //��������
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

    //���ñ���ɫ
    void setBackgroundColor(pcl::visualization::PCLVisualizer::Ptr viewer,
        double r,
        double g,
        double b);

private:
    //��ʼ��vtk�ؼ�
    void initVtkWidget();
    //��ʼ������ؼ�
    void initUi();
    //��ʼ���ź�����
    void initConnect();

private:
    Ui::mainwindow ui;
    //�״�ABCDE��ӦVisualizer
    pcl::visualization::PCLVisualizer::Ptr viewerA, viewerB, viewerC, viewerD, viewerE;
    //���ڳ�������������ʾ
    pcl::visualization::PCLVisualizer::Ptr viewerShow;
};

#endif // OSIGHT_RADAR_PCL_MAINWINDOW__H__
