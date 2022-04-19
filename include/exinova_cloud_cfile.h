#ifndef EXINOVA_G524_EXINOVA_CLOUD_CFILE_H__
#define EXINOVA_G524_EXINOVA_CLOUD_CFILE__H__
#include <string>
/*****************************************************************************
* @FileName:exinova_cloud_cfile.h
* @Author: chujiajun
* @CreatTime: 2022/4/18
* @Descriptions:����ExinovaCloudData����
* @Version: ver 1.0
*****************************************************************************/
class ExinovaCloudData;

struct DataHeader
{
    int size;
    char x;
    char y;
    char z;
    char r;
    char g;
    char b;
    char a;
    char space;
};

class ExinovaDataFile
{
public:
    ExinovaDataFile(const char* pFileName);
    ExinovaDataFile();
    virtual  ~ExinovaDataFile();

    enum OpenMode
    {
        READONLY = 0,
        WRITEONLY,
        APPEND
    };

    int open(OpenMode mode);
    int open(const char* pFile, OpenMode mode);
    int write(ExinovaCloudData& data);
    int read(ExinovaCloudData& data);
    int close();
    bool isOpen() { return NULL != mpFileHandle; };
    const char* filePath() const { return mFilePath.c_str(); };
    void setFilePath(const char* name) { mFilePath = name; }
private:
    void writeHeader(int pointNums);

    int readHeader();
private:
    //�ļ�·��
    std::string mFilePath;
    //�ļ���ģʽ
    OpenMode mOpenMode;
    //�ļ����
    FILE* mpFileHandle;
    //��������
    int mDataCount;				
};
#endif // EXINOVA_G524_EXINOVA_CLOUD_CFILE__H__
