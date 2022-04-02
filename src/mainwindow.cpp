#include "mainwindow.h"
#include <math.h>
#include "osight_def.h"
#define CLOUD_TEST
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer"));
    ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setBackgroundColor(0.1, 0.1, 0.1);

    mpThreadOne = new OsightMeasureTread();
    mpThreadTwo = new OsightMeasureTread();

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
    viewer->addPointCloud(cloudTest, "test");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud_one");
    viewer->updatePointCloud(cloudTest, "test");
    viewer->resetCamera();
    ui.qvtkWidget->update();
#endif // CLOUD_TEST

    connect(mpThreadOne, &OsightMeasureTread::sigRadarConnectFailed, this, [=]() {
        //显示失败信息
        QString str = QString::fromLocal8Bit("雷达1号连接失败\n");
        ui.textBrowser->insertPlainText(str);
        });
    connect(mpThreadOne, &OsightMeasureTread::sigCloudPointUpdated, this, [=]() {
        PointCloudT::Ptr cloud = mpThreadOne->getCloud();     
        viewer->removeAllPointClouds();
        viewer->removeAllShapes();
        viewer->addPointCloud(cloud, "cloud_one");
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud_one");
        viewer->updatePointCloud(cloud, "cloud_one");
        viewer->resetCamera();
        ui.qvtkWidget->update();
        });
    connect(mpThreadTwo, &OsightMeasureTread::sigRadarConnectFailed, this, [=]() {
        //显示失败信息
        QString str = QString::fromLocal8Bit("雷达2号连接失败\n");
        ui.textBrowser->insertPlainText(str);
        });
    connect(mpThreadTwo, &OsightMeasureTread::sigCloudPointUpdated, this, [=]() {
        PointCloudT::Ptr cloud = mpThreadOne->getCloud();
        viewer->addPointCloud(cloud, "cloud_two");
        viewer->updatePointCloud(cloud, "cloud_two");
        viewer->resetCamera();
        ui.qvtkWidget->update();
        });

    connect(ui.lineEdit_local_ip, &QLineEdit::editingFinished, this, [=]() {
        mpThreadOne->setLocalAddr(ui.lineEdit_local_ip->text(), ui.lineEdit_local_port1->text().toUShort());
        mpThreadTwo->setLocalAddr(ui.lineEdit_local_ip->text(), ui.lineEdit_local_port2->text().toUShort());
        });
    connect(ui.lineEdit_local_port1, &QLineEdit::editingFinished, this, [=]() {
        mpThreadOne->setLocalAddr(ui.lineEdit_local_ip->text(), ui.lineEdit_local_port1->text().toUShort());
        });
    connect(ui.lineEdit_local_port2, &QLineEdit::editingFinished, this, [=]() {
        mpThreadTwo->setLocalAddr(ui.lineEdit_local_ip->text(), ui.lineEdit_local_port2->text().toUShort());
        });
    connect(ui.lineEdit__radar_ip1, &QLineEdit::editingFinished, this, [=]() {
        mpThreadOne->setRadarAddr(ui.lineEdit__radar_ip1->text(), ui.lineEdit__radar_port1->text().toUShort());
        });
    connect(ui.lineEdit__radar_ip2, &QLineEdit::editingFinished, this, [=]() {
        mpThreadTwo->setRadarAddr(ui.lineEdit__radar_ip2->text(), ui.lineEdit__radar_port2->text().toUShort());
        });
    connect(ui.lineEdit__radar_port1, &QLineEdit::editingFinished, this, [=]() {
        mpThreadOne->setRadarAddr(ui.lineEdit__radar_ip1->text(), ui.lineEdit__radar_port1->text().toUShort()); 
        });
    connect(ui.lineEdit__radar_port2, &QLineEdit::editingFinished, this, [=]() {
        mpThreadTwo->setRadarAddr(ui.lineEdit__radar_ip2->text(), ui.lineEdit__radar_port2->text().toUShort());
        });
    connect(ui.lineEdit_radar_speed, &QLineEdit::editingFinished, this, [=]() {
        initSetSpeed();
        });
    connect(ui.comboBox_intensity, &QComboBox::currentTextChanged, this, [=]() {
        initSetIntensity();
        });
    connect(ui.comboBox__angle_res, &QComboBox::currentTextChanged, this, [=]() {
        initSetAngleRes();
        });

    connect(ui.pushButton_start, &QPushButton::clicked, this, [=]() {
        mpThreadOne->start();
        //mpThreadTwo->start();
        QString str = QString::fromLocal8Bit("启动测量\n");
        ui.textBrowser->insertPlainText(str);
        });
    connect(ui.pushButton_stop, &QPushButton::clicked, this, [=]() {
        mpThreadOne->stop();
        mpThreadTwo->stop();
        QString str = QString::fromLocal8Bit("停止测量\n");
        ui.textBrowser->insertPlainText(str);
        });

    init();
}
MainWindow::~MainWindow()
{
    if (mpThreadOne != NULL)
        mpThreadOne->deleteLater();
    if (mpThreadTwo != NULL)
        mpThreadTwo->deleteLater();
}

void MainWindow::init()
{
    //雷达转速默认15
    ui.lineEdit_radar_speed->setText(QString::number(15));
    //强度默认1byte
    ui.comboBox_intensity->setCurrentIndex(1);
    //角分辨率默认0.25
    ui.comboBox__angle_res->setCurrentIndex(0);
    ui.lineEdit_local_ip->setText("192.168.1.100");
    ui.lineEdit_local_port1->setText("5500");
    ui.lineEdit_local_port2->setText("5500");
    ui.lineEdit__radar_ip1->setText("192.168.1.10");
    ui.lineEdit__radar_port1->setText("6500");

    initSetAngleRes();

    initSetIntensity();

    initSetSpeed();

    viewer->resetCamera();
    ui.qvtkWidget->update();
}

void MainWindow::setBackgroundColor(double r, double g, double b)
{
    viewer->setBackgroundColor(r, g, b);
}

void MainWindow::initSetAngleRes()
{
    QString str = ui.comboBox__angle_res->currentText();
    double res = 0;
    if (str.contains(QString::number(ANGLE_RES_2500000)))
    {
        res = ANGLE_RES_2500000;
    }
    else if (str.contains(QString::number(ANGLE_RES_2500000)))
    {
        res = ANGLE_RES_2500000;
    }
    else if (str.contains(QString::number(ANGLE_RES_625000)))
    {
        res = ANGLE_RES_625000;
    }
    else if (str.contains(QString::number(ANGLE_RES_312500)))
    {
        res = ANGLE_RES_312500;
    }
    else
    {
        res = ANGLE_RES_2500000;
    }
    mpThreadOne->setRadarAngleRes(res);
    mpThreadTwo->setRadarAngleRes(res);
}

void MainWindow::initSetIntensity()
{
    unsigned char speed = ui.lineEdit_radar_speed->text().toUShort();
    if (speed < MIN_RADAR_SPEED)
    {
        speed = MIN_RADAR_SPEED;
        ui.lineEdit_radar_speed->setText(QString::number(MIN_RADAR_SPEED));
    }
    else if (speed > MAX_RADAR_SPEED)
    {
        speed = MAX_RADAR_SPEED;
        ui.lineEdit_radar_speed->setText(QString::number(MAX_RADAR_SPEED));
    }
    else
    {
    }
    mpThreadOne->setRadarSpeed(speed);
    mpThreadTwo->setRadarSpeed(speed);
}

void MainWindow::initSetSpeed()
{
    mpThreadOne->setRadarIntensity(ui.comboBox_intensity->currentText().toShort());
    mpThreadTwo->setRadarIntensity(ui.comboBox_intensity->currentText().toShort());
}