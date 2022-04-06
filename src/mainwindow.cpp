#include "mainwindow.h"
#include <math.h>
#include "osight_def.h"
#define CLOUD_TEST
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    init();
#ifdef CLOUD_TEST
    //TODO:测试代码
    PointCloudT::Ptr cloudTest;
    cloudTest.reset(new PointCloudT);
    cloudTest->resize(50000);
    unsigned int red = 0;
    unsigned int green = 255;
    unsigned int blue = 0;
    for (auto& point : *cloudTest)
    {
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);

        point.r = red;
        point.g = green;
        point.b = blue;
    }
    viewerA->addPointCloud(cloudTest, "test");
    viewerA->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud_one");
    viewerA->updatePointCloud(cloudTest, "test");
    viewerA->resetCamera();
    ui.qvtkWidget_A->update();
#endif // CLOUD_TEST
}
MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
    ////雷达转速默认15
    //ui.lineEdit_radar_speed->setText(QString::number(15));
    ////强度默认1byte
    //ui.comboBox_intensity->setCurrentIndex(1);
    ////角分辨率默认0.25
    //ui.comboBox__angle_res->setCurrentIndex(0);
    //ui.lineEdit_local_ip->setText("192.168.1.100");
    //ui.lineEdit_local_port1->setText("5500");
    //ui.lineEdit_local_port2->setText("5500");
    //ui.lineEdit__radar_ip1->setText("192.168.1.10");
    //ui.lineEdit__radar_port1->setText("6500");

    initVtkWidget();

    initUi();
}

void MainWindow::setBackgroundColor(pcl::visualization::PCLVisualizer::Ptr viewer,double r, double g, double b)
{
    viewer->setBackgroundColor(r, g, b);
}

void MainWindow::initVtkWidget()
{
    viewerA.reset(new pcl::visualization::PCLVisualizer("viewerA"));
    viewerB.reset(new pcl::visualization::PCLVisualizer("viewerB"));
    viewerC.reset(new pcl::visualization::PCLVisualizer("viewerC"));
    viewerD.reset(new pcl::visualization::PCLVisualizer("viewerD"));
    viewerE.reset(new pcl::visualization::PCLVisualizer("viewerE"));
    viewerShow.reset(new pcl::visualization::PCLVisualizer("viewerShow"));
    ui.qvtkWidget_A->SetRenderWindow(viewerA->getRenderWindow());
    ui.qvtkWidget_B->SetRenderWindow(viewerB->getRenderWindow());
    ui.qvtkWidget_C->SetRenderWindow(viewerC->getRenderWindow());
    ui.qvtkWidget_D->SetRenderWindow(viewerD->getRenderWindow());
    ui.qvtkWidget_E->SetRenderWindow(viewerE->getRenderWindow());
    ui.qvtkWidget_show->SetRenderWindow(viewerShow->getRenderWindow());

    viewerA->resetCamera();
    ui.qvtkWidget_A->update();
    viewerB->resetCamera();
    ui.qvtkWidget_B->update();
    viewerC->resetCamera();
    ui.qvtkWidget_C->update();
    viewerD->resetCamera();
    ui.qvtkWidget_D->update();
    viewerE->resetCamera();
    ui.qvtkWidget_E->update();
    viewerShow->resetCamera();
    ui.qvtkWidget_show->update();
}

void MainWindow::initUi()
{
    //TODO:待完成
    //显示雷达设置标签页
    ui.tabWidget_radar_setting->setCurrentIndex(RADAR_SETTING);
    //显示雷达b
    ui.tabWidget_A->setCurrentIndex(RADAR_B);
    ui.tabWidget->setCurrentIndex(RADAR_B);
    //雷达端口默认6500
    ui.spinBox_port_a->setValue(6500);
    ui.spinBox_port_b->setValue(6500);
    ui.spinBox_port_c->setValue(6500);
    ui.spinBox_port_d->setValue(6500);
    ui.spinBox_port_e->setValue(6500);

}

void MainWindow::initConnect()
{
    //TODO:待完成
}