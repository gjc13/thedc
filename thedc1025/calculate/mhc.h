#ifndef _MHC_H_
#define _MHC_H_


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2806x_Device.h"         // F2806x Headerfile
#include "F2806x_Examples.h"       // F2806x Examples Headerfile
#include "F2806x_EPwm_defines.h" 	 // useful defines for initialization
#include "string.h"

#include "functions.h"
#include "math.h"





#define PLL2SRC_INTOSC1 0


/*******************************************************************************************************************************
 * I2C地址开始
 *******************************************************************************************************************************/
//#define MPU6050ADDR		0x68
//#define BMP085Addr
//
//// 定义MPU6050内部地址
//#define		SMPLRT_DIV			0x19	//陀螺仪采样率，典型值：0x07(125Hz)
//#define		CONFIG					0x1A	//低通滤波频率，典型值：0x06(5Hz)
//#define		GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
//#define		ACCEL_CONFIG		0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
//#define		PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
//#define		WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)
//#define		ACCEL_XOUT_H		0x3B
//#define		ACCEL_XOUT_L		0x3C
//#define		ACCEL_YOUT_H		0x3D
//#define		ACCEL_YOUT_L		0x3E
//#define		ACCEL_ZOUT_H		0x3F
//#define		ACCEL_ZOUT_L		0x40
//#define		TEMP_OUT_H			0x41
//#define		TEMP_OUT_L			0x42
//#define		GYRO_XOUT_H		0x43
//#define		GYRO_XOUT_L		0x44
//#define		GYRO_YOUT_H		0x45
//#define		GYRO_YOUT_L		0x46
//#define		GYRO_ZOUT_H		0x47
//#define		GYRO_ZOUT_L		0x48
//
//#define GYRO_ZH_INDEX 10
//#define GYRO_ZL_INDEX 11
//
//#define HMC58X3_ADDR	 		0x1E//3C // 7 bit address of the HMC58X3 used with the Wire library
//#define HMC_POS_BIAS 			1
//#define HMC_NEG_BIAS 			2
//// HMC58X3 register map. For details see HMC58X3 datasheet
//#define HMC58X3_R_CONFA 		0
//#define HMC58X3_R_CONFB 		1
//#define HMC58X3_R_MODE 		2
//
//#define HMC58X3_R_XM 			3
//#define HMC58X3_R_XL 			4
//#define HMC58X3_R_YM 			(7)  //!< Register address for YM.
//#define HMC58X3_R_YL 			(8)  //!< Register address for YL.
//#define HMC58X3_R_ZM 			(5)  //!< Register address for ZM.
//#define HMC58X3_R_ZL 			(6)  //!< Register address for ZL.
//
//#define HMC58X3_R_STATUS 	9
//#define HMC58X3_R_IDA 			10
//#define HMC58X3_R_IDB 			11
//#define HMC58X3_R_IDC 			12
//
//#define MG_LSB_088					 0.73
//#define MG_LSB_13					 0.92
//#define MG_LSB_19					 1.22
//#define MG_LSB_25					 1.52
//#define MG_LSB_40					 2.27
//#define MG_LSB_47					 2.56
//#define MG_LSB_56					 3.03
//#define MG_LSB_81					 4.35
/*******************************************************************************************************************************
 * I2C地址结束
 * *****************************************************************************************************************************/






/* ---- MPU6500 Reg In MPU9250 ---------------------------------------------- */
#define MPU6500_I2C_ADDR    	        	(0xD0)
#define MPU6500_Device_ID           		(0x71)  // In MPU9250


#define MPU6500_XG_OFFSET_H         	(0x13)
#define MPU6500_XG_OFFSET_L         	(0x14)
#define MPU6500_YG_OFFSET_H         	(0x15)
#define MPU6500_YG_OFFSET_L       	  	(0x16)
#define MPU6500_ZG_OFFSET_H         	(0x17)
#define MPU6500_ZG_OFFSET_L        	 	(0x18)
#define MPU6500_SMPLRT_DIV          	(0x19)
#define MPU6500_CONFIG              		(0x1A)
#define MPU6500_GYRO_CONFIG         	(0x1B)
#define MPU6500_ACCEL_CONFIG        	(0x1C)
#define MPU6500_ACCEL_CONFIG_2      	(0x1D)
#define MPU6500_LP_ACCEL_ODR        	(0x1E)
#define MPU6500_MOT_THR            	 	(0x1F)
#define MPU6500_FIFO_EN             		(0x23)
#define MPU6500_I2C_MST_CTRL        	(0x24)
#define MPU6500_I2C_SLV0_ADDR       	(0x25)
#define MPU6500_I2C_SLV0_REG        	(0x26)
#define MPU6500_I2C_SLV0_CTRL       	(0x27)
#define MPU6500_I2C_SLV1_ADDR       	(0x28)
#define MPU6500_I2C_SLV1_REG        	(0x29)
#define MPU6500_I2C_SLV1_CTRL       	(0x2A)
#define MPU6500_I2C_SLV2_ADDR       	(0x2B)
#define MPU6500_I2C_SLV2_REG        	(0x2C)
#define MPU6500_I2C_SLV2_CTRL       	(0x2D)
#define MPU6500_I2C_SLV3_ADDR       	(0x2E)
#define MPU6500_I2C_SLV3_REG        	(0x2F)
#define MPU6500_I2C_SLV3_CTRL       	(0x30)
#define MPU6500_I2C_SLV4_ADDR       	(0x31)
#define MPU6500_I2C_SLV4_REG        	(0x32)
#define MPU6500_I2C_SLV4_DO         	(0x33)
#define MPU6500_I2C_SLV4_CTRL       	(0x34)
#define MPU6500_I2C_SLV4_DI         		(0x35)
#define MPU6500_I2C_MST_STATUS      	(0x36)
#define MPU6500_INT_PIN_CFG        	 	(0x37)
#define MPU6500_INT_ENABLE          	(0x38)
#define MPU6500_INT_STATUS         	 	(0x3A)
#define MPU6500_ACCEL_XOUT_H        	(0x3B)
#define MPU6500_ACCEL_XOUT_L        	(0x3C)
#define MPU6500_ACCEL_YOUT_H        	(0x3D)
#define MPU6500_ACCEL_YOUT_L        	(0x3E)
#define MPU6500_ACCEL_ZOUT_H        	(0x3F)
#define MPU6500_ACCEL_ZOUT_L        	(0x40)
#define MPU6500_TEMP_OUT_H          	(0x41)
#define MPU6500_TEMP_OUT_L          	(0x42)
#define MPU6500_GYRO_XOUT_H         	(0x43)
#define MPU6500_GYRO_XOUT_L         	(0x44)
#define MPU6500_GYRO_YOUT_H         	(0x45)
#define MPU6500_GYRO_YOUT_L         	(0x46)
#define MPU6500_GYRO_ZOUT_H         	(0x47)
#define MPU6500_GYRO_ZOUT_L         	(0x48)
#define MPU6500_EXT_SENS_DATA_00    	(0x49)
#define MPU6500_EXT_SENS_DATA_01    	(0x4A)
#define MPU6500_EXT_SENS_DATA_02    	(0x4B)
#define MPU6500_EXT_SENS_DATA_03    	(0x4C)
#define MPU6500_EXT_SENS_DATA_04    	(0x4D)
#define MPU6500_EXT_SENS_DATA_05    	(0x4E)
#define MPU6500_EXT_SENS_DATA_06    	(0x4F)
#define MPU6500_EXT_SENS_DATA_07    	(0x50)
#define MPU6500_EXT_SENS_DATA_08    	(0x51)
#define MPU6500_EXT_SENS_DATA_09    	(0x52)
#define MPU6500_EXT_SENS_DATA_10    	(0x53)
#define MPU6500_EXT_SENS_DATA_11    	(0x54)
#define MPU6500_EXT_SENS_DATA_12    	(0x55)
#define MPU6500_EXT_SENS_DATA_13    	(0x56)
#define MPU6500_EXT_SENS_DATA_14    	(0x57)
#define MPU6500_EXT_SENS_DATA_15    	(0x58)
#define MPU6500_EXT_SENS_DATA_16    	(0x59)
#define MPU6500_EXT_SENS_DATA_17    	(0x5A)
#define MPU6500_EXT_SENS_DATA_18    	(0x5B)
#define MPU6500_EXT_SENS_DATA_19    	(0x5C)
#define MPU6500_EXT_SENS_DATA_20    	(0x5D)
#define MPU6500_EXT_SENS_DATA_21    	(0x5E)
#define MPU6500_EXT_SENS_DATA_22    	(0x5F)
#define MPU6500_EXT_SENS_DATA_23    	(0x60)
#define MPU6500_I2C_SLV0_DO         		(0x63)
#define MPU6500_I2C_SLV1_DO         		(0x64)
#define MPU6500_I2C_SLV2_DO         		(0x65)
#define MPU6500_I2C_SLV3_DO         		(0x66)
#define MPU6500_I2C_MST_DELAY_CTRL  	(0x67)
#define MPU6500_SIGNAL_PATH_RESET   	(0x68)
#define MPU6500_MOT_DETECT_CTRL     	(0x69)
#define MPU6500_USER_CTRL          	 	(0x6A)
#define MPU6500_PWR_MGMT_1          	(0x6B)
#define MPU6500_PWR_MGMT_2          	(0x6C)
#define MPU6500_FIFO_COUNTH         	(0x72)
#define MPU6500_FIFO_COUNTL         	(0x73)
#define MPU6500_FIFO_R_W            		(0x74)
#define MPU6500_WHO_AM_I            	(0x75)	// ID = 0x71 In MPU9250
#define MPU6500_XA_OFFSET_H         	(0x77)
#define MPU6500_XA_OFFSET_L        	 	(0x78)
#define MPU6500_YA_OFFSET_H         	(0x7A)
#define MPU6500_YA_OFFSET_L         		(0x7B)
#define MPU6500_ZA_OFFSET_H         	(0x7D)
#define MPU6500_ZA_OFFSET_L      	   	(0x7E)

/* ---- AK8963 Reg In MPU9250 ----------------------------------------------- */
#define AK8963_I2C_ADDR             (0x18)
#define AK8963_Device_ID            	(0x48)

// Read-only Reg
#define AK8963_WIA                  	(0x00)
#define AK8963_INFO                 	(0x01)
#define AK8963_ST1                  	(0x02)
#define AK8963_HXL                  	(0x03)
#define AK8963_HXH                  	(0x04)
#define AK8963_HYL                  	(0x05)
#define AK8963_HYH                  	(0x06)
#define AK8963_HZL                  	(0x07)
#define AK8963_HZH                  	(0x08)
#define AK8963_ST2                  	(0x09)
// Write/Read Reg
#define AK8963_CNTL1                	(0x0A)
#define AK8963_CNTL2                	(0x0B)
#define AK8963_ASTC                	(0x0C)
#define AK8963_TS1                  	(0x0D)
#define AK8963_TS2                  	(0x0E)
#define AK8963_I2CDIS           		(0x0F)
// Read-only Reg ( ROM )
#define AK8963_ASAX                	(0x10)
#define AK8963_ASAY                	(0x11)
#define AK8963_ASAZ                	(0x12)
/*====================================================================================================*/





#define SEPARATE		   '\t'	   //数据之间的间隔符，目前只支持单字符
#define RECEIVE_SEPARATE   ','


#define DOUBLEERROR 0.000001
#define PI       3.14159265358979
#define g        9.806				//重力加速度
#define DEG_TO_RAD 0.017453292519943

#define PWM_PERIOD 56608 //PWM周期7086 400HZ        56608 50HZ

#define G_pa     5.0			    //气压计低通滤波
#define G_v1     0.5					//速度高通滤波
#define G_v2     0.002			  //速度高通滤波(积分)
#define G_alt1	 3.0					//超声高度融合
#define G_alt2   0.2					//气压高度融合
#define G_posi	 0.5					//位置融合
#define dt       0.0025			  //积分周期，暂时使用的是400Hz
#define Light_flux_K  0.02
#define G_height_ultrasonic_lp 2 //超声波传感器低通滤波




#define offset_roll 500.
#define offset_pitch 500.
#define MAX_PITCH_ROLL 0.90 //弧度

#define Au MPU6050Data[0]//加速度前
#define Av MPU6050Data[1]//加速度右
#define Aw MPU6050Data[2]//加速度下
#define Gu MPU6050Data[3]//陀螺仪
#define Gv MPU6050Data[4]
#define Gw MPU6050Data[5]

#define posture_D_STD 92//默认姿态控制D参数
#define posture_P_STD 280//默认姿态控制P参数
#define throttle_Kp_STD 1.8//默认姿态控制P参数
#define throttle_Kd_STD 180//默认姿态控制D参数


/**************************************************
 * AHRS开始
************************************************* */
#define sampleFreq	400.0f//512.0f		// sample frequency in Hz
#define betaDef		0.01f		// 2 * proportional gain


//#include "global.h"


#define IMU_UPDATE_FREQ   MPU6050ScanFreq
#define IMU_UPDATE_DT     (float)(1.0/IMU_UPDATE_FREQ)

/**
 * Set ACC_WANTED_LPF1_CUTOFF_HZ to the wanted cut-off freq in Hz.
 * The highest cut-off freq that will have any affect is fs /(2*pi).
 * E.g. fs = 350 Hz -> highest cut-off = 350/(2*pi) = 55.7 Hz -> 55 Hz
 */
#define IMU_ACC_WANTED_LPF_CUTOFF_HZ  10
/**
 * Attenuation should be between 1 to 256.
 *
 * f0 = fs / 2*pi*attenuation ->
 * attenuation = fs / 2*pi*f0
 */
#define IMU_ACC_IIR_LPF_ATTENUATION (IMU_UPDATE_FREQ / (2 * 3.1415 * IMU_ACC_WANTED_LPF_CUTOFF_HZ))
#define IMU_ACC_IIR_LPF_ATT_FACTOR  (int32)(((1<<IIR_SHIFT) / IMU_ACC_IIR_LPF_ATTENUATION) + 0.5)

#define MPU6050ScanFreq		400
#define IMU_UPDATE_FREQ     MPU6050ScanFreq


#define IMU_GYRO_WANTED_LPF_CUTOFF_HZ  1

#define IMU_GYRO_IIR_LPF_ATTENUATION (IMU_UPDATE_FREQ / (2 * 3.1415 * IMU_GYRO_WANTED_LPF_CUTOFF_HZ))
#define IMU_GYRO_IIR_LPF_ATT_FACTOR  (int32)(((1<<IIR_SHIFT) / IMU_GYRO_IIR_LPF_ATTENUATION) + 0.5)

#define IMU_GYRO_CALIBRATION_COUNTMAX	((IMU_UPDATE_FREQ / IMU_GYRO_WANTED_LPF_CUTOFF_HZ) * 3)

#define MPU6050_DEG_PER_LSB_250  (float)((2 * 250.0) / 65536.0)
#define MPU6050_DEG_PER_LSB_500  (float)((2 * 500.0) / 65536.0)
#define MPU6050_DEG_PER_LSB_1000 (float)((2 * 1000.0) / 65536.0)
#define MPU6050_DEG_PER_LSB_2000 (float)((2 * 2000.0) / 65536.0)

#define MPU6050_G_PER_LSB_2      (float)((2 * 2) / 65536.0)
#define MPU6050_G_PER_LSB_4      (float)((2 * 4) / 65536.0)
#define MPU6050_G_PER_LSB_8      (float)((2 * 8) / 65536.0)
#define MPU6050_G_PER_LSB_16     (float)((2 * 16) / 65536.0)

#define IMU_DEG_PER_LSB_CFG   MPU6050_DEG_PER_LSB_1000
#define IMU_G_PER_LSB_CFG     MPU6050_G_PER_LSB_8

#define GYRO_LPF_TRESH	((IMU_UPDATE_FREQ / IMU_GYRO_WANTED_LPF_CUTOFF_HZ) * 3)
#define ACCEL_LPF_TRESH	((IMU_UPDATE_FREQ / IMU_ACC_WANTED_LPF_CUTOFF_HZ) * 10)

#ifndef M_PI
/** The constant \a pi.	*/
#define M_PI		3.14159265358979323846	/* pi */
#endif

typedef struct{volatile int16 x;volatile int16 y;volatile int16 z;} _3Axis16i_t;
typedef struct{volatile int32 x;volatile int32 y;volatile int32 z;} _3Axis32i_t;
typedef struct{volatile float x;volatile float y;volatile float z;} _3Axisf_t;

enum AHRS_STATE{AHRS_WaitInit=0,AHRS_Cali_Gyro,AHRS_Cali_Accel,AHRS_Running};


#define IIR_SHIFT         8







struct POSTURE
{
	float32 throttle;
	float32 pitch;
	float32 roll;
	float32 yaw;
};


//上位机提供的比赛信息
typedef struct
{
	//小车的编号(1——4之间的某一个)
	Uint16 player_loc;

	//小车1头尾坐标及分数(若是对手，则头尾的坐标一样)
	volatile Uint16 player1_head_x;
	volatile Uint16 player1_head_y;
	volatile Uint16 player1_rear_x;
	volatile Uint16 player1_rear_y;
	volatile Uint16 player1_score;

	//小车2头尾坐标及分数(若是对手，则头尾的坐标一样)
	volatile Uint16 player2_head_x;
	volatile Uint16 player2_head_y;
	volatile Uint16 player2_rear_x;
	volatile Uint16 player2_rear_y;
	volatile Uint16 player2_score;

	//小车3（若存在，否则发0）头尾坐标及分数,(若是对手，则头尾的坐标一样)
	volatile Uint16 player3_head_x;
	volatile Uint16 player3_head_y;
	volatile Uint16 player3_rear_x;
	volatile Uint16 player3_rear_y;
	volatile Uint16 player3_score;


	//小车4（若存在，否则发0）头尾坐标及分数,(若是对手，则头尾的坐标一样)

	volatile Uint16 player4_head_x;
	volatile Uint16 player4_head_y;
	volatile Uint16 player4_rear_x;
	volatile Uint16 player4_rear_y;
	volatile Uint16 player4_score;


	//坑的占用情况
	volatile Uint16 zone1available;
	volatile Uint16 zone2available;
	volatile Uint16 zone3available;
	volatile Uint16 zone4available;

	//比赛剩余时间
	volatile Uint16 time;

	//比赛结束信号，1表示开始，0结束
	volatile Uint16 is_running;
} PlayerData;

//策略状态机
//SEEK:前往现在的目标点
//WAITPOINT：等待得分
//PEND:挂起，这一状态下电机不会驱动
//注意每次新的SEEK都由把状态设置到PEND触发主循环中的SeekNextTarget()，不要试图直接改变目标
enum MoveStatus
{
	SEEK,WAITPOINT,PEND
};


//电机驱动状态
enum MoveDirection
{
	TURN,FRONT,BACK,STOP
};

#define PLAYERDATALENGTH 26

#define ENGINEBACK 2
#define ENGINEFRONT 1
#define ENGINESTOP 0

#define ULTRA_FRONT_THRESHOLD  38
#define ULTRA_BACK_THRESHOLD 34

#endif
