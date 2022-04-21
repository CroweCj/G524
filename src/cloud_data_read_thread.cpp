#include "cloud_data_read_thread.h"
#include "exinova_cloud_cfile.h"
DataReadThread::DataReadThread(QObject* parent) 
    : QThread(parent)
    , mPauseFlag(false)
    , mStopFlag(false)
    , mNextFrame(false)
{
}

DataReadThread::DataReadThread(int type, QObject* parent)
    : QThread(parent)
    , mRadarType(type)
    , mPauseFlag(false)
    , mStopFlag(false)
    , mNextFrame(false)
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
    //�ļ���
    ExinovaDataFile file;

    if (!mFileName.isEmpty())
    {
        file.setFilePath(mFileName.toStdString().c_str());
        if (file.open(ExinovaDataFile::READONLY) == 0)
        {
            //TODO:��ͣ��ֹͣδ��
            //һ֡һ֡ȡ����
            while (!mStopFlag)
            {
                while (mNextFrame 
                    &&file.read(mCloud) >= 0)
                {
                    emit sigDataIsReady(mRadarType);
                    msleep(5);
                    mNextFrame = false;
                }
            }
        }
        file.close();
    }
}