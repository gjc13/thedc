#ifndef __GlobalVar_h__
#define __GlobalVar_h__
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2806x_Device.h"         // F2806x Headerfile
#include "F2806x_Examples.h"       // F2806x Examples Headerfile
#include "F2806x_EPwm_defines.h" 	 // useful defines for initialization

extern Uint16 sciASendBuffer[32];
extern volatile  Uint16 sciASendBufferPointer;
extern Uint16 sciAReadBuffer[32];
extern volatile Uint16 sciAReadBufferPointer;
extern Uint16 sciBSendBuffer[128];
extern volatile Uint16 sciBSendBufferPointer;
extern Uint16 sciBReadBuffer[128];
extern volatile Uint16 sciBReadBufferPointer;

extern volatile Uint16 sciBReadAByte;//S.BUS
extern volatile Uint8 sBusReadDataCopied,digitalChannel1,digitalChannel2,wireLessLost,wireLessLostCount;
extern Uint8 sBusReadData[24];
extern Uint16 channelsData2048[16];
extern float32 channelsData1000[16];
extern Uint8 channelsData4[16];

extern volatile Uint16 i2c_Send_Complete;
extern volatile Uint16 i2cDataPointer;
extern int16 i2cData[24];
extern Uint16 i2cSlaves[24];
extern Uint16 i2cRegAddr[24];
//extern float32 MPU6050Data[6];

extern Uint16 i2c_Send_Data;
extern Uint16 i2c_Slave_Addr;
extern Uint16 i2c_Reg_Addr;

extern volatile Uint16 i2cStatus;

extern volatile Uint8 doCalulate , doSCI , doSBusDecode , doUltra;
extern volatile Uint8 fly_enable;
//0 没有准备好，不能起飞
//1 保护开关关闭，不能起飞
//2 准备起飞，油为零
//3 飞
//4 脱控

extern Uint16 acceXDrift ;
extern Uint16 acceYDrift ;
extern Uint16 acceZDrift ;
extern float32 AcceXK ;
extern float32 AcceYK ;
extern float32 AcceZK ;
extern float32 Gkx , Gky , Gkz ;
extern float32 gyroXDrift;
extern float32 gyroYDrift;
extern float32 gyroZDrift;





//extern float32 tmpf;
//extern int16 tmpi;

extern volatile Uint16 cpuTime;

extern Uint32 delay;//大约10000000=7s

extern float32 G_pos_p , G_pos_r ;

extern float32 pitch_Au,roll_Av;
extern float32 pitch_Gy , roll_Gx , yaw_Gz ;

extern float32 dp,dr,dy;//p、r、y：俯仰、横滚、偏航

extern float32 speed_pitch_lp,speed_roll_lp,speed_yaw_lp;//低通滤波数据


extern struct POSTURE posture_expected;//期望值
extern struct POSTURE posture_now;
extern struct POSTURE posture_error;
extern struct POSTURE posture_adjust;
extern struct POSTURE posture_speed;
extern struct POSTURE posture_before;


extern float32 height_ultrasonic;
extern float32 height_ultrasonic_lp;
extern volatile int16 throttle_mode;//0手动 1自动




/*******************************高度融合数据开始***************************/
extern volatile float32 ultrasonic_height_data_m[30];
extern volatile int16 ultrasonic_height_data_pointer;
extern float32 g_local;
extern volatile float32 az;
extern volatile float32 az_scale,ax_scale,ay_scale;
extern volatile float32 vz_ultra,vz ;
extern float32 G_height,vz_ultrasonic_T;
/*******************************高度融合数据结束***************************/

/*******************************定高数据开始***************************/
extern volatile float32 height_ref;
extern volatile float32 throttle_ref,throttle_real;
extern float32 throttle_Kp,throttle_Kd;
/*******************************定高数据结束***************************/




extern volatile float32 MOTOR1_PULSE,MOTOR2_PULSE,MOTOR3_PULSE,MOTOR4_PULSE;


/**************************************************
 * AHRS开始
************************************************* */
extern volatile float32 beta ;								// 2 * proportional gain (Kp)
extern volatile float32 q0 , q1 , q2 , q3;	// quaternion of sensor frame relative to auxiliary frame

extern volatile Uint32 gAHRSCounter ;


extern _3Axis16i_t gMPU6050RawGyro;
extern _3Axis32i_t gMPU6050RawGyroStoredFilterValues;
//extern _3Axis16i_t gMPU6050LPFGyro;
extern _3Axis16i_t gMPU6050BiasGyro;
extern _3Axisf_t	gGyro;
extern _3Axisf_t	gGyroTmp;
extern _3Axisf_t	gAccelTmp;

extern _3Axis16i_t gMPU6050RawAccel;
extern _3Axis32i_t gMPU6050RawAccelStoredFilterValues ;
extern _3Axis16i_t gMPU6050LPFAccel;
extern _3Axis16i_t gMPU6050BiasAccel ;
extern _3Axisf_t	gAccel;

/**************************************************
 * AHRS结束
************************************************* */
extern volatile float32 eCapData[3];




extern Uint16 playerData_headx;
extern Uint16 playerData_heady;
extern Uint16 playerData_rearx;
extern Uint16 playerData_reary;
extern Uint16 nowScore;

//上位机发送的比赛信息
extern  PlayerData playerData;
#endif
