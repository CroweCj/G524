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
}

void MainWindow::radarADisconnect()
{
    //TODO:
}

void MainWindow::radarAXMinChange(double value)
{
    //TODO:
}

void MainWindow::radarAXMaxChange(double value)
{
    //TODO:
}

void MainWindow::radarAYMinChange(double value)
{
    //TODO:
}

void MainWindow::radarAYMaxChange(double value)
{
    //TODO:
}

void MainWindow::radarBConnect()
{
    //TODO:
}

void MainWindow::radarBDisconnect()
{
    //TODO:
}

void MainWindow::radarBXMinChange(double value)
{
    //TODO:
}

void MainWindow::radarBXMaxChange(double value)
{
    //TODO:
}

void MainWindow::radarBYMinChange(double value)
{
    //TODO:
}

void MainWindow::radarBYMaxChange(double value)
{
    //TODO:
}

void MainWindow::radarCConnect()
{
    //TODO:
}

void MainWindow::radarCDisconnect()
{
    //TODO:
}

void MainWindow::radarCXMinChange(double value)
{
    //TODO:
}

void MainWindow::radarCXMaxChange(double value)
{
    //TODO:
}

void MainWindow::radarCYMinChange(double value)
{
    //TODO:
}

void MainWindow::radarCYMaxChange(double value)
{
    //TODO:
}

void MainWindow::radarDConnect()
{
    //TODO:
}

void MainWindow::radarDDisconnect()
{
    //TODO:
}

void MainWindow::radarDXMinChange(double value)
{
    //TODO:
}

void MainWindow::radarDXMaxChange(double value)
{
    //TODO:
}

void MainWindow::radarDYMinChange(double value)
{
    //TODO:
}

void MainWindow::radarDYMaxChange(double value)
{
    //TODO:
}

void MainWindow::radarEConnect()
{
    //TODO:
}

void MainWindow::radarEDisconnect()
{
    //TODO:
}

void MainWindow::radarEXMinChange(double value)
{
    //TODO:
}

void MainWindow::radarEXMaxChange(double value)
{
    //TODO:
}

void MainWindow::radarEYMinChange(double value)
{
    //TODO:
}

void MainWindow::radarEYMaxChange(double value)
{
    //TODO:
}

void MainWindow::initVtkWidget()
{
    viewerA.reset(new pcl::visualization::PCLVisualizer("viewerA"));
    viewerA->addCoordinateSystem();
    viewerB.reset(new pcl::visualization::PCLVisualizer("viewerB"));
    viewerB->addCoordinateSystem();
    viewerC.reset(new pcl::visualization::PCLVisualizer("viewerC"));
    viewerC->addCoordinateSystem();
    viewerD.reset(new pcl::visualization::PCLVisualizer("viewerD"));
    viewerD->addCoordinateSystem();
    viewerE.reset(new pcl::visualization::PCLVisualizer("viewerE"));
    viewerE->addCoordinateSystem();
    viewerShow.reset(new pcl::visualization::PCLVisualizer("viewerShow"));
    viewerShow->addCoordinateSystem();
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

    connect(ui.tabWidget_A, &QTabWidget::currentChanged, this, [=](int index) {
        ui.tabWidget->setCurrentIndex(index);
        });
    connect(ui.tabWidget, &QTabWidget::currentChanged, this, [=](int index) {
        ui.tabWidget_A->setCurrentIndex(index);
        });
}


