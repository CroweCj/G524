#pragma once
//雷达信息定义文件
// 
//Error Code
//成功
const unsigned int SUCCESS = 0x0000;

//角分辨率不支持配置
const  unsigned int ANGULAR_NONSUP = 0x0001;
//转速不支持配置
const  unsigned int RSPEED_NONSUP = 0x0002;
//强度不支持配置
const  unsigned int intENSITY_NONSUP = 0x0003;

//角分辨率不合法
const  unsigned int ANGULAR_ERROR = 0x0101;
//转速范围不合法
const  unsigned int RSPEED_ERROR = 0x0102;
//强度参数不合法
const  unsigned int intENSITY_ERROR = 0x0103;
//告警ID不合法
const  unsigned int WARN_ID_ERROR = 0x0104;
//告警类型不合法
const  unsigned int WANR_TYPE_ERROR = 0x0105;
//告警参数不合法
const  unsigned int WANR_PARA_ERROR = 0x0106;
//离群点参数不合法
const  unsigned int OUTLIER_PARA_ERROR = 0x0107;
//回波参数不合法
const  unsigned int ECHO_PARA_ERROR = 0x0108;
//网络模式参数不合法
const  unsigned int NET_PARA_ERROR = 0x0109;
//IP参数不合法
const  unsigned int IP_PARA_ERROR = 0x010A;

//参数同步请求消息id
const  unsigned int PARA_SYNC_REQ = 0x02000001;
//参数同步响应消息
const  unsigned int PARA_SYNC_RSP = 0x02000002;
//参数变更指示消息
const  unsigned int PARA_CHANGED_IND_RSP = 0x02000102;
//参数配置请求消息
const  unsigned int PARA_DEVICE_CONFIGURATION_REQ = 0x02000201;
//参数配置响应消息
const  unsigned int PARA_DEVICE_CONFIGURATION_RSP = 0x02000202;
//告警参数请求消息
const  unsigned int PARA_ALARM_CONFIGURATION_REQ = 0x02000301;
//告警参数配置响应消息
const  unsigned int PARA_ALARM_CONFIGURATION_RSQ = 0x02000302;
//开始测量数据请求消息
const  unsigned int START_MEASURE_TRANSMISSION_REQ = 0x02000401;
//测量数据响应消息
const  unsigned int MEAS_DATA_PACKAGE_RSP = 0x02000402;
//日志提取请求消息
const  unsigned int LOG_GET_REQ = 0x02000501;
//日志提取响应消息
const  unsigned int LOG_GET_RSP = 0x02000502;
//定时报告响应消息
const  unsigned int TIME_REPORT_INF = 0x02000602;
//算法请求消息
const  unsigned int ACTIVE_FILTER_REQ = 0x02000701;
//算法选择响应消息
const  unsigned int ACTIVE_FILTER_RSP = 0x02000702;
//校准模式请求消息
const  unsigned int SET_CALIBRATION_MODE_REQ = 0x02000801;
//校准模式响应消息
const  unsigned int SET_CALIBRATION_MODE_RSP = 0x02000802;
//设置网络模式请求消息
const  unsigned int SET_NET_MODE_REQ = 0x02000901;
//设置网络模式请求消息
const  unsigned int SET_NET_MODE_RSP = 0x02000902;
//设置设备IP请求消息
const  unsigned int SET_STATIC_IP_REQ = 0x02000A01;
//设置设备IP响应消息
const  unsigned int SET_STATIC_IP_RSP = 0x02000A02;

//连接不成功
const  unsigned int CONNECT_FAILED = -1;

//雷达转速最小值
const unsigned char MIN_RADAR_SPEED = 5;
//雷达转速最大值
const unsigned char MAX_RADAR_SPEED = 30;
//角分辨率0.25
const double ANGLE_RES_2500000 = 0.25;
//角分辨率0.125
const double ANGLE_RES_1250000 = 0.125;
//角分辨率0.0625
const double ANGLE_RES_625000 = 0.0625;
//角分辨率0.03125
const double ANGLE_RES_312500 = 0.03125;

const unsigned short CONFIG_FAILED = 0x1111;

const unsigned short CONFIG_SUCCESS = 0x0000;

const unsigned short CONFIG_ANGLE_RES_NONE = 0x0001;

const unsigned short CONFIG_SPEED_NONE = 0x0002;

const unsigned short CONFIG_INTENSITY_NONE = 0x0003;

const unsigned short CONFIG_ANGLE_RES_INVALID = 0x0101;

const unsigned short CONFIG_SPEED_INVALID = 0x0102;

const unsigned short CONFIG_INTENSITY_INVALID = 0x0103;

const unsigned char RADAR_SPEED_MIN = 5;

const unsigned char RADAR_SPEED_MAX = 30;

typedef struct LidarData
{
    float  angle;//角度
    float  distance;//距离
    unsigned short intensity;//强度
}LidarData;

