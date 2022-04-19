#include "cloud_data_read_thread.h"
#include "exinova_cloud_cfile.h"
DataReadThread::DataReadThread(QObject* parent) 
    : QThread(parent)
    , mPauseFlag(false)
    , mStopFlag(false)
{

}

DataReadThread::~DataReadThread()
{
}

void DataReadThread::setFileName(const QString& fileName)
{
    mFileName = fileName;
}

void DataReadThread::start(Priority pri)
{
    QThread::start(pri);
}

void DataReadThread::stop()
{
    if (QThread::isRunning())
    {
        mStopFlag = true;
        QThread::quit();
        QThread::wait();
    }
}

void DataReadThread::pause()
{
    if (QThread::isRunning())
    {
        mPauseFlag = true;
    }
}

void DataReadThread::resume()
{
    if (QThread::isRunning())
    {
        mPauseFlag = false;
    }
}

void DataReadThread::run()
{
    //文件类
    ExinovaDataFile file;

    if (!mFileName.isEmpty())
    {
        file.setFilePath(mFileName.toStdString().c_str());
        if (file.open(ExinovaDataFile::READONLY) == 0)
        {
            //TODO:暂停，停止未用
            while (file.read(mCloud) >= 0)
            {
                emit sigDataIsReady();
                msleep(1);
            }
        }
        file.close();
    }
}