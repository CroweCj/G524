#ifndef EXINOVA_G524_CLOUD_DATA_READ_THREAD_H__
#define EXINOVA_G524_CLOUD_DATA_READ_THREAD__H__
/*****************************************************************************
* @FileName:cloud_data_read_thread.h
* @Author: chujiajun
* @CreatTime: 2022/4/18
* @Descriptions:
* @Version: ver 1.0
*****************************************************************************/
#include <QThread>
#include <QMutex>
#include "param_def.h"
class DataReadThread : public QThread
{
    Q_OBJECT
public:
    DataReadThread(QObject* parent = NULL);
    ~DataReadThread();

    void setFileName(const QString& fileName);

    ExinovaCloudData& getCloud() {return mCloud;}
signals:
    void sigDataIsReady();

public slots:
    void start(Priority pri = InheritPriority);

    void stop();

    void pause();

    void resume();

protected:
    void run();
private:
    //点云数据
    ExinovaCloudData mCloud;
    //锁
    QMutex mMutex;
    //暂停标志
    std::atomic_bool mPauseFlag;
    //终止标志
    std::atomic_bool mStopFlag;
    //文件地址
    QString mFileName;
};
#endif // EXINOVA_G524_CLOUD_DATA_READ_THREAD__H__
