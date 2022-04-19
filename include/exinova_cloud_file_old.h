#ifndef EXINOVA_G524_EXINOVA_CLOUD_FILE_H__
#define EXINOVA_G524_EXINOVA_CLOUD_FILE__H__
/*****************************************************************************
* @FileName:exinova_cloud_file.h
* @Author: chujiajun
* @CreatTime: 2022/4/18
* @Descriptions:���ڶ�д��������
* @Version: ver 1.0
*****************************************************************************/
#include <QFile>
#include <QString>
#include <QMutex>

class QTextStream;
class ExinovaCloudData;

class ExinovaFile
{
public:
    enum OpenMode
    {
        READONLY = 0,
        WRITEONLY,
        APPEND
    };

    enum DataMode
    {
        XYZ = 0,
        XYZI,
        XYZRGB,
        XYZINormal,
        XYZRGBA,
        DataEnd
    };//δʹ��

    enum FileType
    {
        PCD = 0,
        TXT,
        BIN,
        FileTypeEnd
    };

    ExinovaFile();
    ExinovaFile(const QString& fileName);
    ~ExinovaFile();
    void setFilePath(const QString& filePath);
    bool open(OpenMode mode, FileType type);
    bool open(const QString& fileName, OpenMode mode, FileType type);
    int write(ExinovaCloudData& data);
    int write(QTextStream& out, const QString& str);
    int read(ExinovaCloudData& data);
    int close();
private:
    QString header(ExinovaCloudData& data);

private:
    //�ļ�������
    QFile mFile;
    //�ļ�·��
    QString mFilePath;
    //�򿪷�ʽ
    OpenMode mOpenMode;
    //��ǰλ��
    std::atomic_int mnCurrentPos;
    QMutex mMutex;
};
#endif // EXINOVA_G524_EXINOVA_CLOUD_FILE__H__
