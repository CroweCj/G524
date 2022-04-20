#ifndef EXINOVA_G524_FILE_SELECT_WIDGET_H__
#define EXINOVA_G524_FILE_SELECT_WIDGET__H__
/*****************************************************************************
* @FileName:file_select_widget.h
* @Author: chujiajun
* @CreatTime: 2022/4/19
* @Descriptions:选择历史数据界面
* @Version: ver 1.0
*****************************************************************************/
#include <QWidget>
#include <QStandardItemModel>
#include <QMap>
#include "ui_file_select_widget.h"
class FileSelectWidget : public QWidget
{
    Q_OBJECT
public:
    FileSelectWidget(QWidget* parent = NULL);
    ~FileSelectWidget();
    void init();
    QMap<int, QString>& getFilePathMap() { return mFilePathMap; }
signals:
    void sigFilePathSaved();
private:
    Ui::file_select_widget ui;
    QStandardItemModel* mpModel;
    QMap<int, QString> mFilePathMap;
};
#endif // EXINOVA_G524_FILE_SELECT_WIDGET__H__
