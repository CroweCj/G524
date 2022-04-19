#ifndef EXINOVA_G524_EXINOVA_CLOUD_CFILE_H__
#define EXINOVA_G524_EXINOVA_CLOUD_CFILE__H__
#include <string>
/*****************************************************************************
* @FileName:exinova_cloud_cfile.h
* @Author: chujiajun
* @CreatTime: 2022/4/18
* @Descriptions:保存ExinovaCloudData数据
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
    //文件路径
    std::string mFilePath;
    //文件打开模式
    OpenMode mOpenMode;
    //文件句柄
    FILE* mpFileHandle;
    //数据条数
    int mDataCount;				
};
#endif // EXINOVA_G524_EXINOVA_CLOUD_CFILE__H__
