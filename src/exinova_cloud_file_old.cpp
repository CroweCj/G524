#include "exinova_cloud_file.h"
#include <QTextStream>
#include <QMutexLocker>
#include "exinova_point_cloud_data.h"

ExinovaFile::ExinovaFile()
    : mFilePath("")
    , mOpenMode(APPEND)
    , mnCurrentPos(0)
{
}

ExinovaFile::ExinovaFile(const QString& fileName)
    : mFilePath(fileName)
    , mOpenMode(APPEND)
    , mnCurrentPos(0)
{
}

ExinovaFile::~ExinovaFile()
{
    //TODO:
}

void ExinovaFile::setFilePath(const QString& filePath)
{
    mFilePath = filePath;
}

bool ExinovaFile::open(OpenMode mode, FileType type)
{
    QFlags<QIODevice::OpenModeFlag> flag;
    if (type == BIN && mode == READONLY)
    {
        flag = QIODevice::ReadOnly | QIODevice::Truncate;
    }
    else if (type == BIN && mode == WRITEONLY)
    {
        flag = QIODevice::WriteOnly | QIODevice::Truncate;
    }
    else if ((type == TXT || type == PCD)
        && mode == READONLY)
    {
        flag = QIODevice::ReadOnly | QIODevice::Text;
    }
    else if ((type == TXT || type == PCD)
        && mode == WRITEONLY)
    {
        flag = QIODevice::WriteOnly | QIODevice::Text;
    }
    else
    {
        flag = QIODevice::NotOpen;
    }
    mFile.setFileName(mFilePath);
    return mFile.open(flag);
}
bool ExinovaFile::open(const QString& fileName, OpenMode mode, FileType type)
{
    mFile.setFileName(mFilePath);
    open(mode, type);
    return true;
}

int ExinovaFile::write(ExinovaCloudData& data)
{
    PointCloudT::Ptr cloud = data.data();

    QTextStream out(&mFile);
    QString headerStr = header(data);
    out << headerStr << "\n";

    for (int i = 0; i < cloud->size(); ++i)
    {
        out << cloud->points[i].x
            << " "
            << cloud->points[i].y
            << " "
            << cloud->points[i].z
            << " "
            << cloud->points[i].r
            << " "
            << cloud->points[i].g
            << " "
            << cloud->points[i].b
            << " "
            << cloud->points[i].a
            << "\n";
    }
    out.flush();
    return 0;
}

int ExinovaFile::write(QTextStream& out, const QString& str)
{
    out << str;
    out.flush();

    return 0;
}

int ExinovaFile::read(ExinovaCloudData& data)
{
    PointCloudT::Ptr cloud = data.data();
    cloud->clear();
    QTextStream in(&mFile);
    in.seek(mnCurrentPos);
    //while (mnCurrentPos > 0 
    //    && mnCurrentPos != in.pos())
    //{
    //    in.readLine();
    //    if (in.atEnd())
    //        return 0;
    //}
    if (in.atEnd())
        return -1;
    QString headerStr;
    headerStr = in.readLine();
    QStringList strLst = headerStr.split(" ");
    if (strLst.size() != 8)
        return -1;
    int num = strLst[0].toInt();
    cloud->resize(num);
    QString dataStr = "";
    for (int i = 0; i < num; ++i)
    {
        strLst.clear();
        dataStr = in.readLine();
        strLst = dataStr.split(" ");
        if (strLst.size() != 7)
            continue;
        cloud->points[i].x = strLst[0].toFloat();
        cloud->points[i].y = strLst[1].toFloat();
        cloud->points[i].z = strLst[2].toFloat();
        cloud->points[i].r = strLst[3].toInt();
        cloud->points[i].g = strLst[4].toInt();
        cloud->points[i].b = strLst[5].toInt();
        cloud->points[i].a = strLst[6].toInt();
    }
    mnCurrentPos = in.pos();
    in.flush();
    return 0;
}
int ExinovaFile::close()
{
    mFile.close();
    return 0;
}
QString ExinovaFile::header(ExinovaCloudData& data)
{
    QString headerStr = QString::number(data.data()->points.size()) + QString(" ");
    headerStr += "X" + QString(" ") + "Y" + QString(" ") + "Z" + QString(" ");
    headerStr += "R" + QString(" ") + "G" + QString(" ") + "B" + QString(" ") + "A";
    return headerStr;
}