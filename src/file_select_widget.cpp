#include "file_select_widget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
const int ROW_COUNT = 5;
FileSelectWidget::FileSelectWidget(QWidget* parent) : QWidget(parent)
{
    ui.setupUi(this);
    mpModel = new QStandardItemModel(this);
    mpModel->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("雷达")
        << QString::fromLocal8Bit("IP") 
        << QString::fromLocal8Bit("文件地址") 
        << QString::fromLocal8Bit("文件导入"));
    ui.tableView->setModel(mpModel);
    ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    init();
}

FileSelectWidget::~FileSelectWidget()
{
}

void FileSelectWidget::init()
{
    QString text;
    for (int i = 0; i < ROW_COUNT; ++i)
    {
        QList<QStandardItem*> lst;
        if (i == 0)
        {
            text = QString::fromLocal8Bit("雷达A");
        }
        else if (i == 1)
        {
            text = QString::fromLocal8Bit("雷达B");
        }
        else if (i == 2)
        {
            text = QString::fromLocal8Bit("雷达C");
        }
        else if (i == 3)
        {
            text = QString::fromLocal8Bit("雷达D");
        }
        else if (i == 4)
        {
            text = QString::fromLocal8Bit("雷达E");
        }
        else
        {
            text = "";
        }
        QStandardItem* pNameItem = new QStandardItem(text);
        QStandardItem* pIpItem = new QStandardItem();
        QStandardItem* pPathItem = new QStandardItem();
        QStandardItem* pImportItem = new QStandardItem();
        lst << pNameItem << pIpItem << pPathItem << pImportItem;
        mpModel->appendRow(lst);
    }
    for (int i = 0; i < ROW_COUNT; ++i)
    {
        QLineEdit* pLineEdit = new QLineEdit(ui.tableView);
        pLineEdit->setEnabled(false);
        ui.tableView->setIndexWidget(mpModel->index(i, 2), pLineEdit);
        QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("导入"),ui.tableView);
        pBtn->setMaximumWidth(100);
        ui.tableView->setIndexWidget(mpModel->index(i, 3), pBtn);
        connect(pBtn, &QPushButton::clicked, this, [=]() {
            QString path = QFileDialog::getOpenFileName(this,
                tr("Open Data File"),
                tr("%1").arg(QApplication::applicationFilePath()),
                tr("Data File(*.dat *.pcd *.txt)"));
            if (!path.isEmpty())
                pLineEdit->setText(path);
            });
    }

    connect(ui.pushButton_cancel, &QPushButton::clicked, this, [=]() {
        this->close();
        });

    connect(ui.pushButton_apply, &QPushButton::clicked, this, [=]() {
        for (int i = 0; i < mpModel->rowCount(); ++i)
        {
            QLineEdit* pLine = static_cast<QLineEdit*>(ui.tableView->indexWidget(mpModel->item(i, 2)->index()));
            mFilePathMap[i] = pLine->text();
        }
        emit sigFilePathSaved();
        this->close();
        });
}