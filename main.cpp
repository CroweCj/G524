#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "vtkoutputwindow.h"

int main(int argc, char* argv[])
{
    vtkOutputWindow::SetGlobalWarningDisplay(0);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


//#include <QtWidgets/QApplication>
//#include "osight_driver.h"
//
//int main(int argc, char* argv[])
//{
//    QApplication a(argc, argv);
//    OsightRadarDriver driver;
//    driver.connect();
//    int nTry = 10;
//    while (nTry > 0)
//    {
//        int num = driver.paramSyncRsp();
//        if (num > 0)
//        {
//            nTry = 10; 
//            LidarData* pData = new LidarData[num];
//            //开始采集
//            driver.startMeasure();
//            while (true)
//            {
//                if (driver.recvOneFrameData(pData))
//                {
//                    //lidarDataToCloud(pData, pointNum);
//                    int n = 0;
//                }
//                else
//                {
//                    clock_t startTime = clock();
//                    while (true)
//                    {
//                        //TODO:重连30分钟
//                        if (((double)(clock() - startTime) / CLOCKS_PER_SEC) >= 1800)
//                        {
//                            return 0;
//                        }
//                        else
//                        {
//                            //pointNum = mpRadarDevice->getPointNum();
//                            //if (pointNum > 0)
//                            //{
//                            //    mIsRun = true;
//                            //    startTime = clock();
//                            //    //清除缓存区
//                            //    delete[] pData;
//                            //    //重新申请缓存区数据
//                            //    pData = new LidarData[pointNum];
//                            //    //重新启动测量
//                            //    mpRadarDevice->startMeasure();
//                            //    break;
//                            //}
//                        }
//                    }
//                }
//            }
//            delete[] pData;
//        }
//        --nTry;
//    }
//
//    return a.exec();
//}