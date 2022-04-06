#pragma once
//�״���Ϣ�����ļ�
// 
//Error Code
//�ɹ�
const unsigned int SUCCESS = 0x0000;

//�Ƿֱ��ʲ�֧������
const  unsigned int ANGULAR_NONSUP = 0x0001;
//ת�ٲ�֧������
const  unsigned int RSPEED_NONSUP = 0x0002;
//ǿ�Ȳ�֧������
const  unsigned int intENSITY_NONSUP = 0x0003;

//�Ƿֱ��ʲ��Ϸ�
const  unsigned int ANGULAR_ERROR = 0x0101;
//ת�ٷ�Χ���Ϸ�
const  unsigned int RSPEED_ERROR = 0x0102;
//ǿ�Ȳ������Ϸ�
const  unsigned int intENSITY_ERROR = 0x0103;
//�澯ID���Ϸ�
const  unsigned int WARN_ID_ERROR = 0x0104;
//�澯���Ͳ��Ϸ�
const  unsigned int WANR_TYPE_ERROR = 0x0105;
//�澯�������Ϸ�
const  unsigned int WANR_PARA_ERROR = 0x0106;
//��Ⱥ��������Ϸ�
const  unsigned int OUTLIER_PARA_ERROR = 0x0107;
//�ز��������Ϸ�
const  unsigned int ECHO_PARA_ERROR = 0x0108;
//����ģʽ�������Ϸ�
const  unsigned int NET_PARA_ERROR = 0x0109;
//IP�������Ϸ�
const  unsigned int IP_PARA_ERROR = 0x010A;

//����ͬ��������Ϣid
const  unsigned int PARA_SYNC_REQ = 0x02000001;
//����ͬ����Ӧ��Ϣ
const  unsigned int PARA_SYNC_RSP = 0x02000002;
//�������ָʾ��Ϣ
const  unsigned int PARA_CHANGED_IND_RSP = 0x02000102;
//��������������Ϣ
const  unsigned int PARA_DEVICE_CONFIGURATION_REQ = 0x02000201;
//����������Ӧ��Ϣ
const  unsigned int PARA_DEVICE_CONFIGURATION_RSP = 0x02000202;
//�澯����������Ϣ
const  unsigned int PARA_ALARM_CONFIGURATION_REQ = 0x02000301;
//�澯����������Ӧ��Ϣ
const  unsigned int PARA_ALARM_CONFIGURATION_RSQ = 0x02000302;
//��ʼ��������������Ϣ
const  unsigned int START_MEASURE_TRANSMISSION_REQ = 0x02000401;
//����������Ӧ��Ϣ
const  unsigned int MEAS_DATA_PACKAGE_RSP = 0x02000402;
//��־��ȡ������Ϣ
const  unsigned int LOG_GET_REQ = 0x02000501;
//��־��ȡ��Ӧ��Ϣ
const  unsigned int LOG_GET_RSP = 0x02000502;
//��ʱ������Ӧ��Ϣ
const  unsigned int TIME_REPORT_INF = 0x02000602;
//�㷨������Ϣ
const  unsigned int ACTIVE_FILTER_REQ = 0x02000701;
//�㷨ѡ����Ӧ��Ϣ
const  unsigned int ACTIVE_FILTER_RSP = 0x02000702;
//У׼ģʽ������Ϣ
const  unsigned int SET_CALIBRATION_MODE_REQ = 0x02000801;
//У׼ģʽ��Ӧ��Ϣ
const  unsigned int SET_CALIBRATION_MODE_RSP = 0x02000802;
//��������ģʽ������Ϣ
const  unsigned int SET_NET_MODE_REQ = 0x02000901;
//��������ģʽ������Ϣ
const  unsigned int SET_NET_MODE_RSP = 0x02000902;
//�����豸IP������Ϣ
const  unsigned int SET_STATIC_IP_REQ = 0x02000A01;
//�����豸IP��Ӧ��Ϣ
const  unsigned int SET_STATIC_IP_RSP = 0x02000A02;

//���Ӳ��ɹ�
const  unsigned int CONNECT_FAILED = -1;

//�״�ת����Сֵ
const unsigned char MIN_RADAR_SPEED = 5;
//�״�ת�����ֵ
const unsigned char MAX_RADAR_SPEED = 30;
//�Ƿֱ���0.25
const double ANGLE_RES_2500000 = 0.25;
//�Ƿֱ���0.125
const double ANGLE_RES_1250000 = 0.125;
//�Ƿֱ���0.0625
const double ANGLE_RES_625000 = 0.0625;
//�Ƿֱ���0.03125
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
    float  angle;//�Ƕ�
    float  distance;//����
    unsigned short intensity;//ǿ��
}LidarData;

