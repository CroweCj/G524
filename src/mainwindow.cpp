#include "mainwindow.h"
#include <math.h>
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
}

void MainWindow::setBackgroundColor(pcl::visualization::PCLVisualizer::Ptr viewer,double r, double g, double b)
{
    viewer->setBackgroundColor(r, g, b);
}

void MainWindow::radarAConnect()
{
    //TODO:
    QString ip = ui.lineEdit_ip_a->text();
    mpRadarManager->setRadarThd(ip,
        ui.doubleSpinBox_xmin_a->value(),
        ui.doubleSpinBox_xmax_a->value(),
        ui.doubleSpinBox_ymin_a->value(),
        ui.doubleSpinBox_ymax_a->value());
    mpRadarManager->connect(ip, OsightDevice::RADAR_A);
}

void MainWindow::radarADisconnect()
{
    //TODO:
    mpRadarManager->disconnect(ui.lineEdit_ip_a->text());
}

void MainWindow::radarAXMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMin(ui.lineEdit_ip_a->text(),
        ui.doubleSpinBox_xmin_a->value());
}

void MainWindow::radarAXMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMax(ui.lineEdit_ip_a->text(),
        ui.doubleSpinBox_xmax_a->value());
}

void MainWindow::radarAYMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMin(ui.lineEdit_ip_a->text(),
        ui.doubleSpinBox_ymin_a->value());
}

void MainWindow::radarAYMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMax(ui.lineEdit_ip_a->text(),
        ui.doubleSpinBox_ymax_a->value());
}

void MainWindow::radarBConnect()
{
    //TODO:
    QString ip = ui.lineEdit_ip_b->text();
    mpRadarManager->setRadarThd(ip,
        ui.doubleSpinBox_xmin_b->value(),
        ui.doubleSpinBox_xmax_b->value(),
        ui.doubleSpinBox_ymin_b->value(),
        ui.doubleSpinBox_ymax_b->value());
    mpRadarManager->connect(ip, OsightDevice::RADAR_B);
}

void MainWindow::radarBDisconnect()
{
    //TODO:
    mpRadarManager->disconnect(ui.lineEdit_ip_b->text());
}

void MainWindow::radarBXMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMin(ui.lineEdit_ip_b->text(),
        ui.doubleSpinBox_xmin_b->value());
}

void MainWindow::radarBXMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMax(ui.lineEdit_ip_b->text(),
        ui.doubleSpinBox_xmax_b->value());
}

void MainWindow::radarBYMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMin(ui.lineEdit_ip_b->text(),
        ui.doubleSpinBox_ymin_b->value());
}

void MainWindow::radarBYMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMax(ui.lineEdit_ip_b->text(),
        ui.doubleSpinBox_ymax_b->value());
}

void MainWindow::radarCConnect()
{
    //TODO:
    QString ip = ui.lineEdit_ip_c->text();
    mpRadarManager->setRadarThd(ip,
        ui.doubleSpinBox_xmin_c->value(),
        ui.doubleSpinBox_xmax_c->value(),
        ui.doubleSpinBox_ymin_c->value(),
        ui.doubleSpinBox_ymax_c->value());
    mpRadarManager->connect(ip, OsightDevice::RADAR_C);
}

void MainWindow::radarCDisconnect()
{
    //TODO:
    mpRadarManager->disconnect(ui.lineEdit_ip_c->text());
}

void MainWindow::radarCXMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMin(ui.lineEdit_ip_c->text(),
        ui.doubleSpinBox_xmin_c->value());
}

void MainWindow::radarCXMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMax(ui.lineEdit_ip_c->text(),
        ui.doubleSpinBox_xmax_c->value());
}

void MainWindow::radarCYMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMin(ui.lineEdit_ip_c->text(),
        ui.doubleSpinBox_ymin_c->value());
}

void MainWindow::radarCYMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMax(ui.lineEdit_ip_c->text(),
        ui.doubleSpinBox_ymax_c->value());
}

void MainWindow::radarDConnect()
{
    //TODO:
    QString ip = ui.lineEdit_ip_d->text();
    mpRadarManager->setRadarThd(ip,
        ui.doubleSpinBox_xmin_d->value(),
        ui.doubleSpinBox_xmax_d->value(),
        ui.doubleSpinBox_ymin_d->value(),
        ui.doubleSpinBox_ymax_d->value());
    mpRadarManager->connect(ip, OsightDevice::RADAR_D);
}

void MainWindow::radarDDisconnect()
{
    //TODO:
    mpRadarManager->disconnect(ui.lineEdit_ip_d->text());
}

void MainWindow::radarDXMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMin(ui.lineEdit_ip_d->text(),
        ui.doubleSpinBox_xmin_d->value());
}

void MainWindow::radarDXMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMax(ui.lineEdit_ip_d->text(),
        ui.doubleSpinBox_xmax_d->value());
}

void MainWindow::radarDYMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMin(ui.lineEdit_ip_d->text(),
        ui.doubleSpinBox_ymin_d->value());
}

void MainWindow::radarDYMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMax(ui.lineEdit_ip_d->text(),
        ui.doubleSpinBox_ymax_d->value());
}

void MainWindow::radarEConnect()
{
    //TODO:
    QString ip = ui.lineEdit_ip_e->text();
    mpRadarManager->setRadarThd(ip,
        ui.doubleSpinBox_xmin_e->value(),
        ui.doubleSpinBox_xmax_e->value(),
        ui.doubleSpinBox_ymin_e->value(),
        ui.doubleSpinBox_ymax_e->value());
    mpRadarManager->connect(ip, OsightDevice::RADAR_C);
}

void MainWindow::radarEDisconnect()
{
    //TODO:
    mpRadarManager->disconnect(ui.lineEdit_ip_e->text());
}

void MainWindow::radarEXMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMin(ui.lineEdit_ip_e->text(),
        ui.doubleSpinBox_xmin_e->value());
}

void MainWindow::radarEXMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadarxMax(ui.lineEdit_ip_e->text(),
        ui.doubleSpinBox_xmax_e->value());
}

void MainWindow::radarEYMinChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMin(ui.lineEdit_ip_e->text(),
        ui.doubleSpinBox_ymin_e->value());
}

void MainWindow::radarEYMaxChange(double value)
{
    //TODO:
    mpRadarManager->setRadaryMax(ui.lineEdit_ip_e->text(),
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
    //TODO:待完成
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
    //TODO:待完成
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


    connect(mpRadarManager, &RadarManager::sigAThreadCloudUpdated, this, [=](const QString& ip) {
        updateShow(viewerA, ip, "radar_a");
        ui.qvtkWidget_A->update();
        });
    connect(mpRadarManager, &RadarManager::sigBThreadCloudUpdated, this, [=](const QString& ip) {
        updateShow(viewerB, ip, "radar_b");
        ui.qvtkWidget_B->update();
        });
    connect(mpRadarManager, &RadarManager::sigCThreadCloudUpdated, this, [=](const QString& ip) {
        updateShow(viewerC, ip, "radar_c");
        ui.qvtkWidget_C->update();
        });
    connect(mpRadarManager, &RadarManager::sigDThreadCloudUpdated, this, [=](const QString& ip) {
        updateShow(viewerD, ip, "radar_d");
        ui.qvtkWidget_D->update();
        });
    connect(mpRadarManager, &RadarManager::sigEThreadCloudUpdated, this, [=](const QString& ip) {
        updateShow(viewerE, ip, "radar_e");
        ui.qvtkWidget_E->update();
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

void MainWindow::updateShow(pcl::visualization::PCLVisualizer::Ptr viewer, const QString& ip, const QString& cloudId)
{
    PointCloudT::Ptr cloud = mpRadarManager->getCloud(ip);
    std::string str = cloudId.toStdString();
    viewer->removeAllPointClouds();
    viewer->removeAllShapes();
    viewer->addPointCloud(cloud, str);
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, str);
    viewer->updatePointCloud(cloud, str);
}


