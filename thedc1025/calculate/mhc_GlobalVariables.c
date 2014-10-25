#include "mhc.h"     // Device Headerfile and Examples Include File

Uint16 sciASendBuffer[32]={0};
volatile Uint16 sciASendBufferPointer=0;
Uint16 sciAReadBuffer[32]={0};
volatile Uint16 sciAReadBufferPointer=0;
Uint16 sciBSendBuffer[128]={0};
volatile Uint16 sciBSendBufferPointer=0;
Uint16 sciBReadBuffer[128]={0};
volatile Uint16 sciBReadBufferPointer=0;

volatile Uint16 sciBReadAByte=0;//S.BUS
volatile Uint8 sBusReadDataCopied=1;

volatile Uint8 digitalChannel1=0,digitalChannel2=0,wireLessLost=0,wireLessLostCount=0;
Uint8 sBusReadData[24];
Uint16 channelsData2048[16]={0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
float32 channelsData1000[16]={0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
Uint8 channelsData4[16]={0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};



volatile Uint16 i2c_Send_Complete=0;
volatile Uint16 i2cDataPointer=0;
int16 i2cData[24]={0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0};
Uint16 i2cSlaves[24]={0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68,
		0x1E,0x1E,0x1E,0x1E, 0x1E,0x1E,0x68,0x68,  0x68,0x68,0x68,0x68};
Uint16 i2cRegAddr[24]={ACCEL_XOUT_H , ACCEL_XOUT_L , ACCEL_YOUT_H , ACCEL_YOUT_L ,
		ACCEL_ZOUT_H , ACCEL_ZOUT_L , GYRO_XOUT_H , GYRO_XOUT_L ,
		GYRO_YOUT_H , GYRO_YOUT_L ,	GYRO_ZOUT_H , GYRO_ZOUT_L,
		HMC58X3_R_XM, HMC58X3_R_XL,HMC58X3_R_YM , HMC58X3_R_YL ,
		HMC58X3_R_ZM , HMC58X3_R_ZL,0,0,		0,0,0,0};
//float32 MPU6050Data[6];

Uint16 i2c_Send_Data=0;
Uint16 i2c_Slave_Addr=0;
Uint16 i2c_Reg_Addr=0;



volatile Uint16 i2cStatus=0;
// 0 ʲô������
// 12 I2C���ڷ��͵�ַ��֮��Ҫ����һ������
// 13 I2C������Reg��ַ�����ڽ���һ������
// 21 ����I2C���ڷ��͵�ַ������

// 31 ������ʱ��������Ӧ��
// 32 д����ʱ��������Ӧ��






volatile Uint8 doCalulate=0 , doSCI=0 , doSBusDecode=0,doUltra=0; //Ӧ�ü���  Ӧ�÷�����  S.Bus����һ֡���Ѹ���,Ӧ�ü��� Ӧ�òɼ�����������

volatile Uint8 fly_enable=0;
//0 û��׼���ã��������
//1 �������عرգ��������
//2 ׼����ɣ���Ϊ��
//3 ��
//4 �ѿ�
//Uint16 cpuTimerInterruptsWithoutSBusDecode;


int16 acceXDrift = 285;//���ٶ����ƫ��
int16 acceYDrift = (16300-16620)/2;
int16 acceZDrift = (16580-17200)/2-295;
float32 AcceXK = ((float32)200.0)/(16050l+16090l)/1.02/100;//���ٶ�ϵ��
float32 AcceYK = ((float32)200.0)/(16300l+16620l)/100;
float32 AcceZK = ((float32)200.0)/(16580l+17200l)*1.018/100;
float32 gyroXDrift;//���������ƫ��
float32 gyroYDrift;
float32 gyroZDrift;
float32 Gkx=930.0 , Gky=930.0 , Gkz=930.0 ;//������ϵ��




//float32 tmpf;
//int16 tmpi;

volatile Uint16 cpuTime=0;

Uint32 delay;//��Լ10000000=7s

float32 G_pos_p=0.05 , G_pos_r=0.05 ;

float32 pitch_Au,roll_Av;
float32 pitch_Gy = 0 , roll_Gx = 0 , yaw_Gz = 0 ;
float32 dp = 0 , dr =  0 , dy = 0;//p��r��y�������������ƫ��

float32 speed_pitch_lp=0,speed_roll_lp=0,speed_yaw_lp=0;



struct POSTURE posture_expected={0,0,0,0};
struct POSTURE posture_now={0,0,0,0};
struct POSTURE posture_error={0,0,0,0};
struct POSTURE posture_adjust={0,0,0,0};
struct POSTURE posture_speed={0,0,0,0};
struct POSTURE posture_before={0,0,0,0};


float32 height_ultrasonic=0;
float32 height_ultrasonic_lp=0;
volatile int16 throttle_mode=0;//0�ֶ� 1�Զ�

/*******************************�߶��ں����ݿ�ʼ***************************/
volatile float32 ultrasonic_height_data_m[30]={0};
volatile int16 ultrasonic_height_data_pointer=0;
float32 g_local=9.800000;	//��øĸ�
volatile float32 az_scale=10,ax_scale=10,ay_scale=10;//gAcce=>m/s2
volatile float32 az=0;
volatile float32 vz_ultra=0,vz=0;
float32 G_height=1, vz_ultrasonic_T=0.5;
/*******************************�߶��ں����ݽ���***************************/

/*******************************�������ݿ�ʼ***************************/
volatile float32 height_ref=80;
volatile float32 throttle_ref=400,throttle_real=400;
float32 throttle_Kp=0.07,throttle_Kd=150;
/*******************************�������ݽ���***************************/


volatile float32 MOTOR1_PULSE=0,MOTOR2_PULSE=0,MOTOR3_PULSE=0,MOTOR4_PULSE=0;



/**************************************************
 * AHRS��ʼ
************************************************* */
volatile float32 beta = betaDef;								// 2 * proportional gain (Kp)
volatile float32 q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;	// quaternion of sensor frame relative to auxiliary frame

volatile Uint32 gAHRSCounter = 0;


_3Axis16i_t gMPU6050RawGyro;
_3Axis32i_t gMPU6050RawGyroStoredFilterValues;
//_3Axis16i_t gMPU6050LPFGyro;
_3Axis16i_t gMPU6050BiasGyro;
_3Axisf_t	gGyro;
_3Axisf_t	gGyroTmp;
_3Axisf_t	gAccelTmp;

_3Axis16i_t gMPU6050RawAccel;
_3Axis32i_t gMPU6050RawAccelStoredFilterValues = {0,0,0};
_3Axis16i_t gMPU6050LPFAccel;
_3Axis16i_t gMPU6050BiasAccel = {0,0,0};
_3Axisf_t	gAccel;

/**************************************************
 * AHRS����
************************************************* */


volatile float32 eCapData[3]={0,0,0};
Uint16 playerData_headx;
Uint16 playerData_heady;
Uint16 playerData_rearx;
Uint16 playerData_reary;
Uint16 nowScore;

//��λ�����͵ı�����Ϣ
PlayerData playerData;
