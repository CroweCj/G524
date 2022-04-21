#include "mainwindow.h"
#include <math.h>
#include <QFileDialog>
#include <QKeySequence>
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
    updateSettings();
    delete mpRadarManager;
    delete mpFileSelectWidget;
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
    
    mpRadarManager = new RadarManager();

    initVtkWidget();

    initUi();

    initConnect();

    initFileRead();

    initFileWrite();
}

void MainWindow::setBackgroundColor(pcl::visualization::PCLVisualizer::Ptr viewer,double r, double g, double b)
{
    viewer->setBackgroundColor(r, g, b);
}

void MainWindow::radarAConnect()
{
    QString ip = ui.lineEdit_ip_a->text();
    int port = ui.spinBox_port_a->value();
    mpRadarManager->setRadarThd(OsightDevice::RADAR_A,
        ui.doubleSpinBox_xmin_a->value(),
        ui.doubleSpinBox_xmax_a->value(),
        ui.doubleSpinBox_ymin_a->value(),
        ui.doubleSpinBox_ymax_a->value());
    mpRadarManager->connect(ip, port, OsightDevice::RADAR_A);
}

void MainWindow::radarADisconnect()
{
    mpRadarManager->disconnect(OsightDevice::RADAR_A);
}

void MainWindow::radarAXMinChange(double value)
{
    mpRadarManager->setRadarxMin(OsightDevice::RADAR_A,
        ui.doubleSpinBox_xmin_a->value());
}

void MainWindow::radarAXMaxChange(double value)
{
    mpRadarManager->setRadarxMax(OsightDevice::RADAR_A,
        ui.doubleSpinBox_xmax_a->value());
}

void MainWindow::radarAYMinChange(double value)
{
    mpRadarManager->setRadaryMin(OsightDevice::RADAR_A,
        ui.doubleSpinBox_ymin_a->value());
}

void MainWindow::radarAYMaxChange(double value)
{
    mpRadarManager->setRadaryMax(OsightDevice::RADAR_A,
        ui.doubleSpinBox_ymax_a->value());
}

void MainWindow::radarBConnect()
{
    QString ip = ui.lineEdit_ip_b->text();
    int port = ui.spinBox_port_b->value();
    mpRadarManager->setRadarThd(OsightDevice::RADAR_B,
        ui.doubleSpinBox_xmin_b->value(),
        ui.doubleSpinBox_xmax_b->value(),
        ui.doubleSpinBox_ymin_b->value(),
        ui.doubleSpinBox_ymax_b->value());
    mpRadarManager->connect(ip, port, OsightDevice::RADAR_B);
}

void MainWindow::radarBDisconnect()
{
    mpRadarManager->disconnect(OsightDevice::RADAR_B);
}

void MainWindow::radarBXMinChange(double value)
{
    mpRadarManager->setRadarxMin(OsightDevice::RADAR_B,
        ui.doubleSpinBox_xmin_b->value());
}

void MainWindow::radarBXMaxChange(double value)
{
    mpRadarManager->setRadarxMax(OsightDevice::RADAR_B,
        ui.doubleSpinBox_xmax_b->value());
}

void MainWindow::radarBYMinChange(double value)
{
    mpRadarManager->setRadaryMin(OsightDevice::RADAR_B,
        ui.doubleSpinBox_ymin_b->value());
}

void MainWindow::radarBYMaxChange(double value)
{
    mpRadarManager->setRadaryMax(OsightDevice::RADAR_B,
        ui.doubleSpinBox_ymax_b->value());
}

void MainWindow::radarCConnect()
{
    QString ip = ui.lineEdit_ip_c->text();
    int port = ui.spinBox_port_c->value();
    mpRadarManager->setRadarThd(OsightDevice::RADAR_C,
        ui.doubleSpinBox_xmin_c->value(),
        ui.doubleSpinBox_xmax_c->value(),
        ui.doubleSpinBox_ymin_c->value(),
        ui.doubleSpinBox_ymax_c->value());
    mpRadarManager->connect(ip, port,OsightDevice::RADAR_C);
}

void MainWindow::radarCDisconnect()
{
    mpRadarManager->disconnect(OsightDevice::RADAR_C);
}

void MainWindow::radarCXMinChange(double value)
{
    mpRadarManager->setRadarxMin(OsightDevice::RADAR_C,
        ui.doubleSpinBox_xmin_c->value());
}

void MainWindow::radarCXMaxChange(double value)
{
    mpRadarManager->setRadarxMax(OsightDevice::RADAR_C,
        ui.doubleSpinBox_xmax_c->value());
}

void MainWindow::radarCYMinChange(double value)
{
    mpRadarManager->setRadaryMin(OsightDevice::RADAR_C,
        ui.doubleSpinBox_ymin_c->value());
}

void MainWindow::radarCYMaxChange(double value)
{
    mpRadarManager->setRadaryMax(OsightDevice::RADAR_C,
        ui.doubleSpinBox_ymax_c->value());
}

void MainWindow::radarDConnect()
{
    QString ip = ui.lineEdit_ip_d->text();
    int port = ui.spinBox_port_d->value();
    mpRadarManager->setRadarThd(OsightDevice::RADAR_D,
        ui.doubleSpinBox_xmin_d->value(),
        ui.doubleSpinBox_xmax_d->value(),
        ui.doubleSpinBox_ymin_d->value(),
        ui.doubleSpinBox_ymax_d->value());
    mpRadarManager->connect(ip, port,OsightDevice::RADAR_D);
}

void MainWindow::radarDDisconnect()
{
    mpRadarManager->disconnect(OsightDevice::RADAR_D);
}

void MainWindow::radarDXMinChange(double value)
{
    mpRadarManager->setRadarxMin(OsightDevice::RADAR_D,
        ui.doubleSpinBox_xmin_d->value());
}

void MainWindow::radarDXMaxChange(double value)
{
    mpRadarManager->setRadarxMax(OsightDevice::RADAR_D,
        ui.doubleSpinBox_xmax_d->value());
}

void MainWindow::radarDYMinChange(double value)
{
    mpRadarManager->setRadaryMin(OsightDevice::RADAR_D,
        ui.doubleSpinBox_ymin_d->value());
}

void MainWindow::radarDYMaxChange(double value)
{
    mpRadarManager->setRadaryMax(OsightDevice::RADAR_D,
        ui.doubleSpinBox_ymax_d->value());
}

void MainWindow::radarEConnect()
{
    QString ip = ui.lineEdit_ip_e->text();
    int port = ui.spinBox_port_e->value();
    mpRadarManager->setRadarThd(OsightDevice::RADAR_E,
        ui.doubleSpinBox_xmin_e->value(),
        ui.doubleSpinBox_xmax_e->value(),
        ui.doubleSpinBox_ymin_e->value(),
        ui.doubleSpinBox_ymax_e->value());
    mpRadarManager->connect(ip, port, OsightDevice::RADAR_E);
}

void MainWindow::radarEDisconnect()
{
    mpRadarManager->disconnect(OsightDevice::RADAR_E);
}

void MainWindow::radarEXMinChange(double value)
{
    mpRadarManager->setRadarxMin(OsightDevice::RADAR_E,
        ui.doubleSpinBox_xmin_e->value());
}

void MainWindow::radarEXMaxChange(double value)
{
    mpRadarManager->setRadarxMax(OsightDevice::RADAR_E,
        ui.doubleSpinBox_xmax_e->value());
}

void MainWindow::radarEYMinChange(double value)
{
    mpRadarManager->setRadaryMin(OsightDevice::RADAR_E,
        ui.doubleSpinBox_ymin_e->value());
}

void MainWindow::radarEYMaxChange(double value)
{
    mpRadarManager->setRadaryMax(OsightDevice::RADAR_E,
        ui.doubleSpinBox_ymax_e->value());
}

void MainWindow::initVtkWidget()
{
    viewerA.reset(new pcl::visualization::PCLVisualizer("viewerA",false));
    viewerA->addCoordinateSystem();
    viewerA->setupInteractor(ui.qvtkWidget_A->GetInteractor(), ui.qvtkWidget_A->GetRenderWindow());
    viewerB.reset(new pcl::visualization::PCLVisualizer("viewerB", false));
    viewerB->addCoordinateSystem();
    viewerB->setupInteractor(ui.qvtkWidget_B->GetInteractor(), ui.qvtkWidget_B->GetRenderWindow());
    viewerC.reset(new pcl::visualization::PCLVisualizer("viewerC", false));
    viewerC->addCoordinateSystem();
    viewerC->setupInteractor(ui.qvtkWidget_C->GetInteractor(), ui.qvtkWidget_C->GetRenderWindow());
    viewerD.reset(new pcl::visualization::PCLVisualizer("viewerD", false));
    viewerD->addCoordinateSystem();
    viewerD->setupInteractor(ui.qvtkWidget_D->GetInteractor(), ui.qvtkWidget_D->GetRenderWindow());
    viewerE.reset(new pcl::visualization::PCLVisualizer("viewerE", false));
    viewerE->addCoordinateSystem();
    viewerE->setupInteractor(ui.qvtkWidget_E->GetInteractor(), ui.qvtkWidget_E->GetRenderWindow());
    viewerShow.reset(new pcl::visualization::PCLVisualizer("viewerShow", false));
    viewerShow->addCoordinateSystem();
    viewerShow->setupInteractor(ui.qvtkWidget_show->GetInteractor(), ui.qvtkWidget_show->GetRenderWindow());

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

    while (!viewerA->wasStopped())
    {
        viewerA->spinOnce();
    }
}

void MainWindow::initUi()
{
    //显示雷达设置标签页
    ui.tabWidget_radar_setting->setCurrentIndex(RADAR_SETTING);
    //显示雷达b
    ui.tabWidget_A->setCurrentIndex(RADAR_B);
    ////雷达端口默认6500
    //ui.spinBox_port_a->setValue(6500);
    //ui.spinBox_port_b->setValue(6500);
    //ui.spinBox_port_c->setValue(6500);
    //ui.spinBox_port_d->setValue(6500);
    //ui.spinBox_port_e->setValue(6500);
    ui.doubleSpinBox_xmin_a->setMinimum(-10);
    ui.doubleSpinBox_xmin_b->setMinimum(-10);
    ui.doubleSpinBox_xmin_c->setMinimum(-10);
    ui.doubleSpinBox_xmin_d->setMinimum(-10);
    ui.doubleSpinBox_xmin_e->setMinimum(-10);
    ui.spinBox_port_a->setMaximum(65535);
    ui.spinBox_port_b->setMaximum(65535);
    ui.spinBox_port_c->setMaximum(65535);
    ui.spinBox_port_d->setMaximum(65535);
    ui.spinBox_port_e->setMaximum(65535);
    //雷达A参数默认设置
    ui.lineEdit_ip_a->setText(ExinovaSettings::value("radar_a/ip").toString());
    ui.spinBox_port_a->setValue(ExinovaSettings::value("radar_a/port","6500").toInt());
    ui.doubleSpinBox_xmin_a->setValue(ExinovaSettings::value("radar_a/xmin", "-10").toDouble());
    ui.doubleSpinBox_xmax_a->setValue(ExinovaSettings::value("radar_a/xmax", "10").toDouble());
    ui.doubleSpinBox_ymin_a->setValue(ExinovaSettings::value("radar_a/ymin", "0").toDouble());
    ui.doubleSpinBox_ymax_a->setValue(ExinovaSettings::value("radar_a/ymax", "10").toDouble());

    //雷达B参数默认设置
    ui.lineEdit_ip_b->setText(ExinovaSettings::value("radar_b/ip").toString());
    ui.spinBox_port_b->setValue(ExinovaSettings::value("radar_b/port", "6500").toInt());
    ui.doubleSpinBox_xmin_b->setValue(ExinovaSettings::value("radar_b/xmin","-10").toDouble());
    ui.doubleSpinBox_xmax_b->setValue(ExinovaSettings::value("radar_b/xmax","10").toDouble());
    ui.doubleSpinBox_ymin_b->setValue(ExinovaSettings::value("radar_b/ymin","0").toDouble());
    ui.doubleSpinBox_ymax_b->setValue(ExinovaSettings::value("radar_b/ymax","10").toDouble());

    //雷达C参数默认设置
    ui.lineEdit_ip_c->setText(ExinovaSettings::value("radar_c/ip").toString());
    ui.spinBox_port_c->setValue(ExinovaSettings::value("radar_c/port", "6500").toInt());
    ui.doubleSpinBox_xmin_c->setValue(ExinovaSettings::value("radar_c/xmin", "-10").toDouble());
    ui.doubleSpinBox_xmax_c->setValue(ExinovaSettings::value("radar_c/xmax", "10").toDouble());
    ui.doubleSpinBox_ymin_c->setValue(ExinovaSettings::value("radar_c/ymin", "0").toDouble());
    ui.doubleSpinBox_ymax_c->setValue(ExinovaSettings::value("radar_c/ymax", "10").toDouble());

    //雷达D参数默认设置
    ui.lineEdit_ip_d->setText(ExinovaSettings::value("radar_d/ip").toString());
    ui.spinBox_port_d->setValue(ExinovaSettings::value("radar_d/port", "6500").toInt());
    ui.doubleSpinBox_xmin_d->setValue(ExinovaSettings::value("radar_d/xmin", "-10").toDouble());
    ui.doubleSpinBox_xmax_d->setValue(ExinovaSettings::value("radar_d/xmax", "10").toDouble());
    ui.doubleSpinBox_ymin_d->setValue(ExinovaSettings::value("radar_d/ymin", "0").toDouble());
    ui.doubleSpinBox_ymax_d->setValue(ExinovaSettings::value("radar_d/ymax", "10").toDouble());

    //雷达E参数默认设置
    ui.lineEdit_ip_e->setText(ExinovaSettings::value("radar_e/ip").toString());
    ui.spinBox_port_e->setValue(ExinovaSettings::value("radar_e/port", "6500").toInt());
    ui.doubleSpinBox_xmin_e->setValue(ExinovaSettings::value("radar_e/xmin", "-10").toDouble());
    ui.doubleSpinBox_xmax_e->setValue(ExinovaSettings::value("radar_e/xmax", "10").toDouble());
    ui.doubleSpinBox_ymin_e->setValue(ExinovaSettings::value("radar_e/ymin", "0").toDouble());
    ui.doubleSpinBox_ymax_e->setValue(ExinovaSettings::value("radar_e/ymax", "10").toDouble());
}

void MainWindow::initConnect()
{
    connect(ui.pushButton_con_a, &QPushButton::clicked, this, &MainWindow::radarAConnect);
    connect(ui.pushButton_con_b, &QPushButton::clicked, this, &MainWindow::radarBConnect);
    connect(ui.pushButton_con_c, &QPushButton::clicked, this, &MainWindow::radarCConnect);
    connect(ui.pushButton_con_d, &QPushButton::clicked, this, &MainWindow::radarDConnect);
    connect(ui.pushButton_con_e, &QPushButton::clicked, this, &MainWindow::radarEConnect);

    connect(ui.pushButton_discon_a, &QPushButton::clicked, this, &MainWindow::radarADisconnect);
    connect(ui.pushButton_discon_b, &QPushButton::clicked, this, &MainWindow::radarBDisconnect);
    connect(ui.pushButton_discon_c, &QPushButton::clicked, this, &MainWindow::radarCDisconnect);
    connect(ui.pushButton_discon_d, &QPushButton::clicked, this, &MainWindow::radarDDisconnect);
    connect(ui.pushButton_discon_e, &QPushButton::clicked, this, &MainWindow::radarEDisconnect);

    connect(ui.doubleSpinBox_xmin_a, QOverload<double>::of (&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarAXMinChange);
    connect(ui.doubleSpinBox_xmin_b, QOverload<double>::of (&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarBXMinChange);
    connect(ui.doubleSpinBox_xmin_c, QOverload<double>::of (&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarCXMinChange);
    connect(ui.doubleSpinBox_xmin_d, QOverload<double>::of (&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarDXMinChange);
    connect(ui.doubleSpinBox_xmin_e, QOverload<double>::of (&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarEXMinChange);

    connect(ui.doubleSpinBox_xmax_a, QOverload<double>::of (&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarAXMaxChange);
    connect(ui.doubleSpinBox_xmax_b, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarBXMaxChange);
    connect(ui.doubleSpinBox_xmax_c, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarCXMaxChange);
    connect(ui.doubleSpinBox_xmax_d, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarDXMaxChange);
    connect(ui.doubleSpinBox_xmax_e, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarEXMaxChange);

    connect(ui.doubleSpinBox_ymin_a, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarAYMinChange);
    connect(ui.doubleSpinBox_ymin_b, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarBYMinChange);
    connect(ui.doubleSpinBox_ymin_c, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarCYMinChange);
    connect(ui.doubleSpinBox_ymin_d, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarDYMinChange);
    connect(ui.doubleSpinBox_ymin_e, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarEYMinChange);

    connect(ui.doubleSpinBox_ymax_a, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarAYMaxChange);
    connect(ui.doubleSpinBox_ymax_b, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarBYMaxChange);
    connect(ui.doubleSpinBox_ymax_c, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarCYMaxChange);
    connect(ui.doubleSpinBox_ymax_d, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarDYMaxChange);
    connect(ui.doubleSpinBox_ymax_e, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &MainWindow::radarEYMaxChange);


    //connect(mpRadarManager, &RadarManager::sigAThreadCloudUpdated, this, [=](const QString& ip) {
    //    updateShow(viewerA, ip, "radar_a");
    //    ui.qvtkWidget_A->update();
    //    });
    //connect(mpRadarManager, &RadarManager::sigBThreadCloudUpdated, this, [=](const QString& ip) {
    //    updateShow(viewerB, ip, "radar_b");
    //    ui.qvtkWidget_B->update();
    //    });
    //connect(mpRadarManager, &RadarManager::sigCThreadCloudUpdated, this, [=](const QString& ip) {
    //    updateShow(viewerC, ip, "radar_c");
    //    ui.qvtkWidget_C->update();
    //    });
    //connect(mpRadarManager, &RadarManager::sigDThreadCloudUpdated, this, [=](const QString& ip) {
    //    updateShow(viewerD, ip, "radar_d");
    //    ui.qvtkWidget_D->update();
    //    });
    //connect(mpRadarManager, &RadarManager::sigEThreadCloudUpdated, this, [=](const QString& ip) {
    //    updateShow(viewerE, ip, "radar_e");
    //    ui.qvtkWidget_E->update();
    //    });
    connect(mpRadarManager, &RadarManager::sigThreadCloudUpdated, this, [=](const int type) {
        updateShow(type, false);
        });
    connect(mpRadarManager, &RadarManager::sigEOutlineUpdated, this, [=]() {
        //ui.lcdNumber_speed->display(mpRadarManager->getSpeed(ip));
        //TODO:暂时用4 仅用于测试
        PointCloudT::Ptr cloud = mpRadarManager->getOutlineCloud(OsightDevice::RADAR_E);
        std::string str = "outline";
        viewerShow->removeAllPointClouds();
        viewerShow->removeAllShapes();
        viewerShow->addPointCloud(cloud, str);
        viewerShow->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, str);
        viewerShow->updatePointCloud(cloud, str);
        ui.qvtkWidget_show->update();
        });

    //TODO:端口变动 数据未更新

    //暂时添加下一帧，方便测试
    ui.actionNextFrame->setShortcut(tr("Ctrl+X"));
    connect(ui.actionNextFrame, &QAction::triggered, mpRadarManager, &RadarManager::nextFrame);

    //
    connect(mpRadarManager, &RadarManager::sigDataReadThreadCloudUpdate, this, [=](const int type) {
        updateShow(type,true);
        });
}

void MainWindow::updateSettings()
{
    ExinovaSettings::setValue("radar_a/ip", ui.lineEdit_ip_a->text());
    ExinovaSettings::setValue("radar_a/port", ui.spinBox_port_a->value());
    ExinovaSettings::setValue("radar_a/xmin", ui.doubleSpinBox_xmin_a->value());
    ExinovaSettings::setValue("radar_a/xmax", ui.doubleSpinBox_xmax_a->value());
    ExinovaSettings::setValue("radar_a/ymin", ui.doubleSpinBox_ymin_a->value());
    ExinovaSettings::setValue("radar_a/ymax", ui.doubleSpinBox_ymax_a->value());

    ExinovaSettings::setValue("radar_b/ip", ui.lineEdit_ip_b->text());
    ExinovaSettings::setValue("radar_b/port", ui.spinBox_port_b->value());
    ExinovaSettings::setValue("radar_b/xmin", ui.doubleSpinBox_xmin_b->value());
    ExinovaSettings::setValue("radar_b/xmax", ui.doubleSpinBox_xmax_b->value());
    ExinovaSettings::setValue("radar_b/ymin", ui.doubleSpinBox_ymin_b->value());
    ExinovaSettings::setValue("radar_b/ymax", ui.doubleSpinBox_ymax_b->value());

    ExinovaSettings::setValue("radar_c/ip", ui.lineEdit_ip_c->text());
    ExinovaSettings::setValue("radar_c/port", ui.spinBox_port_c->value());
    ExinovaSettings::setValue("radar_c/xmin", ui.doubleSpinBox_xmin_c->value());
    ExinovaSettings::setValue("radar_c/xmax", ui.doubleSpinBox_xmax_c->value());
    ExinovaSettings::setValue("radar_c/ymin", ui.doubleSpinBox_ymin_c->value());
    ExinovaSettings::setValue("radar_c/ymax", ui.doubleSpinBox_ymax_c->value());

    ExinovaSettings::setValue("radar_d/ip", ui.lineEdit_ip_d->text());
    ExinovaSettings::setValue("radar_d/port", ui.spinBox_port_d->value());
    ExinovaSettings::setValue("radar_d/xmin", ui.doubleSpinBox_xmin_d->value());
    ExinovaSettings::setValue("radar_d/xmax", ui.doubleSpinBox_xmax_d->value());
    ExinovaSettings::setValue("radar_d/ymin", ui.doubleSpinBox_ymin_d->value());
    ExinovaSettings::setValue("radar_d/ymax", ui.doubleSpinBox_ymax_d->value());

    ExinovaSettings::setValue("radar_e/ip", ui.lineEdit_ip_e->text());
    ExinovaSettings::setValue("radar_e/port", ui.spinBox_port_e->value());
    ExinovaSettings::setValue("radar_e/xmin", ui.doubleSpinBox_xmin_e->value());
    ExinovaSettings::setValue("radar_e/xmax", ui.doubleSpinBox_xmax_e->value());
    ExinovaSettings::setValue("radar_e/ymin", ui.doubleSpinBox_ymin_e->value());
    ExinovaSettings::setValue("radar_e/ymax", ui.doubleSpinBox_ymax_e->value());
}

void MainWindow::updateShow(const int type, bool isRead)
{
    pcl::visualization::PCLVisualizer::Ptr viewer;
    PointCloudT::Ptr cloud = !isRead ? mpRadarManager->getCloud(type): mpRadarManager->getReadCloud(type);
    std::string str;
    QVTKWidget* pVtk;
    if (type == RADAR_A)
    {
        viewer = viewerA;
        str = "CLOUD_A";
        pVtk = ui.qvtkWidget_A;
    }
    else if (type == RADAR_B)
    {
        viewer = viewerB;
        str = "CLOUD_B";
        pVtk = ui.qvtkWidget_B;
    }
    else if (type == RADAR_C)
    {
        viewer = viewerC;
        str = "CLOUD_C";
        pVtk = ui.qvtkWidget_C;
    }
    else if (type == RADAR_D)
    {
        viewer = viewerD;
        str = "CLOUD_D";
        pVtk = ui.qvtkWidget_D;
    }
    else if (type == RADAR_E)
    {
        viewer = viewerE;
        str = "CLOUD_E";
        pVtk = ui.qvtkWidget_E;
    }
    viewer->removeAllPointClouds();
    viewer->removeAllShapes();
    viewer->addPointCloud(cloud, str);
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, str);
    viewer->updatePointCloud(cloud, str);
    pVtk->update();
}

void MainWindow::initFileRead()
{
    mpFileSelectWidget = new FileSelectWidget();
    connect(ui.actionOpenDir, &QAction::triggered, this, [=](bool togged) {
        mpFileSelectWidget->showNormal();
        });
    connect(ui.actionPlay, &QAction::triggered, this, [=](bool togged) {
        mpRadarManager->startDataRead();
        });


	connect(ui.actionDataStop, &QAction::triggered, mpRadarManager, &RadarManager::stopDataWrite);//文本停止写入


    connect(ui.actionPause, &QAction::triggered, mpRadarManager, [=]() {
        QString currentState = ui.actionPause->text();
        if (currentState == pause) {
            ui.actionPause->setText(resume);
            mpRadarManager->pauseDataRead();
        }
        else {
            ui.actionPause->setText(pause);
            mpRadarManager->resumeDataRead();
        }
        });//暂停、继续文本读取

    //connect(ui.actionLastFrame, &QAction::triggered, );//跳转到上一帧
    //connect(ui.actionNextFrame, &QAction::triggered, );//跳转到下一帧


    connect(mpFileSelectWidget, &FileSelectWidget::sigFilePathSaved, this, [=]() {
        QMap<int, QString> filePathMap = mpFileSelectWidget->getFilePathMap();
        for (int i = 0; i < filePathMap.size(); ++i)
        {
            //TODO:未判断文件是否存在
            if (!filePathMap[i].isEmpty())
            {
                mpRadarManager->addDataRead(i, filePathMap[i]);
            }
        }
        });
}

void MainWindow::initFileWrite()
{
    connect(ui.actionDataCol, &QAction::triggered, this, [=]() {
        QString filePath = QFileDialog::getExistingDirectory(this,
            tr("Select Data Folder"),
            tr("%1").arg(QApplication::applicationFilePath()));
        int index = ui.tabWidget_A->currentIndex();
        mpRadarManager->setFileName(index, filePath);
        });
}


