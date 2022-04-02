#pragma once
#include "exinova_point_cloud_data.h"
//系统参数定义
//数据结构定义

//param-----------------------
//门限值 雷达距离地面高度 用于测速
static double THRESHOLD = 6.5;
//-----------------------param

//struct----------------------
typedef struct OBJ
{
    //起始点
    float startPoint;
    //终止点
    float stopPoint;
    //距离
    float distance;
}OBJ;

typedef struct DetectSpeedData
{
    double speed;
    ExinovaCloudData data;
}DetectSpeedData;

typedef struct DetectOutlineData
{
    bool enable;
    ExinovaCloudData data;
}DetectOutlineData;


//----------------------struct