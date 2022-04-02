#pragma once
#include "exinova_point_cloud_data.h"
//ϵͳ��������
//���ݽṹ����

//param-----------------------
//����ֵ �״�������߶� ���ڲ���
static double THRESHOLD = 6.5;
//-----------------------param

//struct----------------------
typedef struct OBJ
{
    //��ʼ��
    float startPoint;
    //��ֹ��
    float stopPoint;
    //����
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