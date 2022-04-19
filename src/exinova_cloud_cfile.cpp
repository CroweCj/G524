#include "exinova_cloud_cfile.h"
#include "exinova_point_cloud_data.h"

ExinovaDataFile::ExinovaDataFile(const char* pFileName)
    : mFilePath(pFileName)
    , mDataCount(0)
{
}

ExinovaDataFile::ExinovaDataFile()
    : mFilePath("")
    , mDataCount(0)
{
}

ExinovaDataFile::~ExinovaDataFile()
{
}

int ExinovaDataFile::open(OpenMode mode)
{
    std::string modeStr = "";
    if (mode == READONLY)
    {
        modeStr = "rb";
    }
    else if (mode == WRITEONLY)
    {
        modeStr = "wb";
    }
    else if (mode == APPEND)
    {
        modeStr = "a+";
    }
    else
    {
    }
    mpFileHandle = fopen(mFilePath.c_str(), modeStr.c_str());

    if (mpFileHandle == NULL)
        return -1;
    else
        return 0;
}

int ExinovaDataFile::open(const char* pFile, OpenMode mode)
{
    std::string modeStr = "";
    if (mode == READONLY)
    {
        modeStr = "rb";
    }
    else if (mode == WRITEONLY)
    {
        modeStr = "wb";
    }
    else if (mode == APPEND)
    {
        modeStr = "a+";
    }
    else
    {
    }
    mpFileHandle = fopen(pFile, modeStr.c_str());
    if (mpFileHandle == NULL)
        return -1;
    else
        return 0;
}

int ExinovaDataFile::write(ExinovaCloudData& data)
{
    PointCloudT::Ptr cloud = data.data();
    int nPointSize = cloud->points.size();
    if (nPointSize <= 0)
        return -1;
    if (mpFileHandle == NULL)
        return -1;
    writeHeader(nPointSize);
    for(int i = 0; i < nPointSize; ++i)
    {
        //PointData data[1] = {};
        //data[0].x = cloud->points[i].x;
        //data[0].y = cloud->points[i].y;
        //data[0].z = cloud->points[i].z;
        //data[0].r = cloud->points[i].r;
        //data[0].g = cloud->points[i].g;
        //data[0].b = cloud->points[i].b;
        //data[0].a = cloud->points[i].a;
        //fwrite(data, sizeof(PointData), 1, mpFileHandle);
        pcl::PointXYZRGBA data[1] = {};
        data[0] = cloud->points[i];
        fwrite(data, sizeof(pcl::PointXYZRGBA), 1, mpFileHandle);
    }
    //Ë¢ÐÂ
    fflush(mpFileHandle);
    ++mDataCount;
    return 0;
}

int ExinovaDataFile::read(ExinovaCloudData& data)
{
    if (mpFileHandle == NULL)
        return -1;
    int nCount = readHeader();
    if (nCount == 0)
        return -1;
    PointCloudT::Ptr cloud = data.data();
    cloud->points.resize(nCount);

    for (int i = 0; i < nCount; ++i)
    {
        //pcl::PointXYZRGBA data[1] = {};
        //PointData data[1] = {};
        //fread(data, sizeof(PointData), 1, mpFileHandle);
        //cloud->points[0].x = data[0].x;
        //cloud->points[0].y = data[0].y;
        //cloud->points[0].z = data[0].z;
        //cloud->points[0].r = data[0].r;
        //cloud->points[0].g = data[0].g;
        //cloud->points[0].b = data[0].b;
        //cloud->points[0].a = data[0].a;
        pcl::PointXYZRGBA data[1] = {};
        fread(data, sizeof(pcl::PointXYZRGBA), 1, mpFileHandle);
        cloud->points[i] = data[0];
    }
    ++mDataCount;
    return 0;
}

int ExinovaDataFile::close()
{
    if (mpFileHandle != NULL)
        fclose(mpFileHandle);
    mDataCount = 0;

    return 0;
}

void ExinovaDataFile::writeHeader(int pointNums)
{
    DataHeader header[1] = {};
    header[0].size = pointNums;
    header[0].x = 'X';
    header[0].y = 'Y';
    header[0].z = 'Z';
    header[0].r = 'R';
    header[0].g = 'G';
    header[0].b = 'B';
    header[0].a = 'A';
    fwrite(header, sizeof(DataHeader), 1, mpFileHandle);
    fflush(mpFileHandle);
}

int ExinovaDataFile::readHeader()
{
    DataHeader header[1] = {};
    fread(header, sizeof(DataHeader), 1, mpFileHandle);

    return header[0].size;
}
