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



//volatile Uint16 i2c_Send_Complete=0;
//volatile Uint16 i2cDataPointer=0;
//int16 i2cData[24]={0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0};
//Uint16 i2cSlaves[24]={0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68,
//		0x68,0x68,0x68,0x68, 0x1E,0x1E,0x68,0x68,  0x68,0x68,0x68,0x68};
//Uint16 i2cRegAddr[24]={ACCEL_XOUT_H , ACCEL_XOUT_L , ACCEL_YOUT_H , ACCEL_YOUT_L ,
//		ACCEL_ZOUT_H , ACCEL_ZOUT_L , GYRO_XOUT_H , GYRO_XOUT_L ,
//		GYRO_YOUT_H , GYRO_YOUT_L ,	GYRO_ZOUT_H , GYRO_ZOUT_L,
//		0, 0, 0, 0,
//		0, 0, 0, 0,
//		0, 0, 0, 0};
////float32 MPU6050Data[6];
//
//Uint16 i2c_Send_Data=0;
//Uint16 i2c_Slave_Addr=0;
//Uint16 i2c_Reg_Addr=0;



volatile Uint16 i2cStatus=0;
// 0 什么都不做
// 12 I2C正在发送地址，之后要接收一个数据
// 13 I2C发完了Reg地址，正在接收一个数据
// 21 命令I2C正在发送地址和数据

// 31 读数据时从器件非应答
// 32 写数据时从器件非应答






volatile Uint8 doCalulate=0 , doSCIA=0 ,doSCIB=0, doSBusDecode=0,doUltra=0; //应该计算  应该发串口  S.Bus收完一帧且已复制,应该计算 应该采集超声波数据

volatile Uint8 fly_enable=0;
//0 没有准备好，不能起飞
//1 保护开关关闭，不能起飞
//2 准备起飞，油为零
//3 飞
//4 脱控
//Uint16 cpuTimerInterruptsWithoutSBusDecode;


int16 acceXDrift = 285;//加速度零点偏移
int16 acceYDrift = (16300-16620)/2;
int16 acceZDrift = (16580-17200)/2-295;
float32 AcceXK = ((float32)200.0)/(16050l+16090l)/1.02/100;//加速度系数
float32 AcceYK = ((float32)200.0)/(16300l+16620l)/100;
float32 AcceZK = ((float32)200.0)/(16580l+17200l)*1.018/100;
float32 gyroXDrift;//陀螺仪零点偏移
float32 gyroYDrift;
float32 gyroZDrift;
float32 Gkx=930.0 , Gky=930.0 , Gkz=930.0 ;//陀螺仪系数




//float32 tmpf;
//int16 tmpi;

volatile Uint32 cpuTime=0;

Uint32 delay;//大约10000000=7s

float32 G_pos_p=0.05 , G_pos_r=0.05 ;

float32 pitch_Au,roll_Av;
float32 pitch_Gy = 0 , roll_Gx = 0 , yaw_Gz = 0 ;
float32 dp = 0 , dr =  0 , dy = 0;//p、r、y：俯仰、横滚、偏航

float32 speed_pitch_lp=0,speed_roll_lp=0,speed_yaw_lp=0;



struct POSTURE posture_expected={0,0,0,0};
struct POSTURE posture_now={0,0,0,0};
struct POSTURE posture_error={0,0,0,0};
struct POSTURE posture_adjust={0,0,0,0};
struct POSTURE posture_speed={0,0,0,0};
struct POSTURE posture_before={0,0,0,0};


float32 height_ultrasonic=0;
float32 height_ultrasonic_lp=0;
volatile int16 throttle_mode=0;//0手动 1自动

/*******************************高度融合数据开始***************************/
//volatile float32 ultrasonic_height_data_m[30]={0};
//volatile int16 ultrasonic_height_data_pointer=0;
//float32 g_local=9.800000;	//最好改改
//volatile float32 az_scale=10,ax_scale=10,ay_scale=10;//gAcce=>m/s2
//volatile float32 az=0;
//volatile float32 vz_ultra=0,vz=0;
//float32 G_height=1, vz_ultrasonic_T=0.5;
/*******************************高度融合数据结束***************************/

/*******************************定高数据开始***************************/
//volatile float32 height_ref=80;
//volatile float32 throttle_ref=400,throttle_real=400;
//float32 throttle_Kp=0.07,throttle_Kd=150;
/*******************************定高数据结束***************************/


volatile float32 MOTOR1_PULSE=0,MOTOR2_PULSE=0,MOTOR3_PULSE=0,MOTOR4_PULSE=0;



/**************************************************
 * AHRS开始
************************************************* */
//volatile float32 beta = betaDef;								// 2 * proportional gain (Kp)
//volatile float32 q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;	// quaternion of sensor frame relative to auxiliary frame

volatile Uint32 gAHRSCounter = 0;


_3Axis16i_t gMPU6050RawGyro;
_3Axis32i_t gMPU6050RawGyroStoredFilterValues;
//_3Axis16i_t gMPU6050LPFGyro;
//_3Axis16i_t gMPU6050BiasGyro;
_3Axisf_t	gGyro;
_3Axisf_t	gGyroTmp;
//_3Axisf_t	gAccelTmp;

//_3Axis16i_t gMPU6050RawAccel;
//_3Axis32i_t gMPU6050RawAccelStoredFilterValues = {0,0,0};
//_3Axis16i_t gMPU6050LPFAccel;
//_3Axis16i_t gMPU6050BiasAccel = {0,0,0};
//_3Axisf_t	gAccel;

/**************************************************
 * AHRS结束
************************************************* */



volatile float32 eCapData[3]={0,0,0};



volatile Uint16 playerData_headx=0;
volatile Uint16 playerData_heady=0;
volatile Uint16 playerData_rearx=0;
volatile Uint16 playerData_reary=0;
volatile Uint16 nowScore=0;
volatile Uint16 nowX=0;
volatile Uint16 nowY=0;
volatile Uint16 headX=0;
volatile Uint16 headY=0;
volatile Uint16 rearX=0;
volatile Uint16 rearY=0;
volatile float32 nowAngle=0;
volatile Uint16 targetX=0;
volatile Uint16 targetY=0;

//上位机发送的比赛信息
PlayerData playerData;
//volatile Uint16 playerData_lastRecieveCPUTime=0;
volatile Uint16 canMove=0;
volatile Uint16 gameFirstStart=0;
volatile Uint16 isPlayerDataAvailable=1;

//MPU_6050提供的姿态信息
volatile Uint16 isMPUavailable=0;

Uint32 lastUpdatePostureTime;

//角度PID
float32 angleOutPut;
float32 targetRunAngle;
float32 targetHeadAngle;

float32 angleP;
float32 angleI;
float32 angleD;
float32 Padjust;
float32 Iadjust;
float32 Dadjust;
float32 angleDiffIntergration;

float32 nowDataAngle;

volatile Uint16 foundHeadObstacleTime;

volatile Uint16 foundTailObstacleTime;

volatile enum MoveDirection direction;

volatile enum MoveStatus moveStatus;

Uint16 allTargetX[2][2];
Uint16 allTargetY[2][2];
Uint16 lowerXLimit;
Uint16 lowerYLimit;

volatile Uint16 targetIterator;
Uint16 numTargets;

Uint16 pointedLocX[4];
Uint16 pointedLocY[4];

volatile Uint32 waitingTime;
Uint32 waitTimeLimit;

float32 nowDistance;

Uint16 newDataReceive;

//nowDirection在转向过程中不会变化，用于记录整体方向
Uint16 nowDirection;
int16 lockTurnTime;

volatile Uint16 getNewPoint;


//正交编码器捕获数据
volatile int32 eQEP1PositionDifference;
volatile int32 eQEP2PositionDifference;

//速度PID
float32 speedTolerance;
float32 speedP;
float32 speedI;
float32 speedIDecay;
Uint32 startLeftSpeedControlTime;
Uint32 startRightSpeedControlTime;
volatile float32 nowLeftSpeed;
volatile float32 nowRightSpeed;
volatile float32 targetLeftSpeed;
volatile float32 targetRightSpeed;
volatile float32 leftSpeedPOutput;
volatile float32 rightSpeedPOutput;
volatile float32 leftSpeedIOutput;
volatile float32 rightSpeedIOutput;



/****************spi开始****************/
Uint16 spiPointer=0;

//如有必要，可以把check去掉
Uint16 spiASendData[64]=/*{0x37 ,0xbc, 0x37|0x80, 0xff,0xf5, 0xff,0xbb,0xff,0xff,0xff,0xFf, 0xff,0xff,0xff,0xFf, 0xFf,0xFf,0xFf,0xFf,0xFf*/
{
/*0*/	MPU6500_PWR_MGMT_1,				0x01/*80*/,      	// Reset Device
		0x80 | MPU6500_WHO_AM_I,					0xFF,      	// check Device ID
		MPU6500_PWR_MGMT_1,				0x01,      	// Clock Source
		0x80 | MPU6500_PWR_MGMT_1,				0xFF,      	// check Clock Source
		MPU6500_PWR_MGMT_2, 				0x00,     	// Enable Acc & Gyro
		0x80 | MPU6500_PWR_MGMT_2, 				0xFF,     	// check Enable Acc & Gyro
		MPU6500_CONFIG, 						0x07,     	//
		0x80 | MPU6500_CONFIG, 						0xFF,     	// check
		MPU6500_GYRO_CONFIG, 				0x10,    		// +-1000dps
		0x80 | MPU6500_GYRO_CONFIG, 			0xFF,    		// check +-2000dps
/*20*/MPU6500_ACCEL_CONFIG, 				0x08,   		// +-4G
		0x80 | MPU6500_ACCEL_CONFIG, 			0xFF,   		// check +-4G
		MPU6500_ACCEL_CONFIG_2,			0x00, 		// Set Acc Data Rates
		0x80 | MPU6500_ACCEL_CONFIG_2,			0xFF, 		// check Set Acc Data Rates
		MPU6500_INT_PIN_CFG,					0x30,     	//
		0x80 | MPU6500_INT_PIN_CFG,				0xFF,     	// check
		MPU6500_I2C_MST_CTRL, 				0x40,  		// I2C Speed 348 kHz
		0x80 | MPU6500_I2C_MST_CTRL, 				0xFF,  		// check I2C Speed 348 kHz
		MPU6500_USER_CTRL, 					0x20,   	 	// Enable AUX
		0x80 | MPU6500_USER_CTRL, 					0xFF,   	 	// check Enable AUX

/*40*/0x80 | MPU6500_ACCEL_XOUT_H        	,0xff,
		0x80 | MPU6500_ACCEL_XOUT_L        	,0xff,
		0x80 | MPU6500_ACCEL_YOUT_H        	,0xff,
		0x80 | MPU6500_ACCEL_YOUT_L        	,0xff,
		0x80 | MPU6500_ACCEL_ZOUT_H        	,0xff,
/*50*/0x80 | MPU6500_ACCEL_ZOUT_L        	,0xff,
		0x80 | MPU6500_GYRO_XOUT_H         	,0xff,
		0x80 | MPU6500_GYRO_XOUT_L         	,0xff,
		0x80 | MPU6500_GYRO_YOUT_H         	,0xff,
		0x80 | MPU6500_GYRO_YOUT_L         	,0xff,
/*60*/0x80 | MPU6500_GYRO_ZOUT_H         	,0xff,
		0x80 | MPU6500_GYRO_ZOUT_L         	,0xff

};
Uint16 spiAReadData[64]=	{0};
Uint16 spiAStop[64]=       	{0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0,   1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0,   1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,  0,1,0,1,0,  1,0,1};

volatile int16 spi_zGyro=0;
/***************************spi结束******************/

//正交编码器捕获数据
volatile int32 eQEP1PositionDifference;
volatile int32 eQEP2PositionDifference;
float32 leftSpeedRatio;
float32 rightSpeedRatio;
