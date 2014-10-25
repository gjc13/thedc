#ifndef _FUNCTIONS
#define _FUNCTIONS

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2806x_Device.h"         // F2806x Headerfile
#include "F2806x_Examples.h"       // F2806x Examples Headerfile
#include "F2806x_EPwm_defines.h" 	 // useful defines for initialization
#include "string.h"
#include "math.h"

void int16_to_string(int16 data, char *string);
void uint32_to_string(Uint32 data, char *string);
void double_to_string(double data,char *string);
void string_to_one_double(char *string,double *data);
void string_to_one_int32(char *string,int32 *data);

void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
void InitEPwm4Example(void);
void InitEPwm5Example(void);
void setPwm(Uint16 pwmNum,float32 pwmValue);

void scia_mhc_init(void);
void scib_mhc_init(void);
__interrupt void sciaTxFifoIsr(void);
__interrupt void sciaRxFifoIsr(void);
__interrupt void scibTxFifoIsr(void);
__interrupt void scibRxFifoIsr(void);

void sciASendData();
void uint16strcpy(Uint16* dst,Uint16* rsc);

void sbusDecode();


__interrupt void ecap1_isr(void);
//__interrupt void ecap2_isr(void);
//__interrupt void ecap3_isr(void);
void InitECapture(void);


void I2CA_Init(void);
__interrupt void i2c_int1a_isr(void);
Uint16 iicWriteByte(Uint16 slaveAddr,Uint16 regAddr,Uint16 data);
//Uint16 iicReadByte(Uint16 slaveAddr,Uint16 regAddr);
void init_I2C_devices();
void init_I2C_devices_flying();//重新初始化I2C 飞行时I2C出错则调用 初始化不成功则调用iiC_broken
void iiC_broken();//I2C配置失败
Uint16 iicStartRead();
void dataConverse();


void initDSP();
void initGlobalVariables();
void sensor_calibrate(void);

__interrupt void cpu_timer0_isr(void);


void vz_ultrasonic_calculate(void);
void vz_calculate(void);
void Posture_calculate(void);
void limit_float32(float32 *num , float32 min , float32 max);
void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T);
void pid();
void setMotor();



/**************************************************
 * AHRS开始
************************************************* */
//void MadgwickAHRSupdate(float32 gx, float32 gy, float32 gz, float32 ax, float32 ay, float32 az, float32 mx, float32 my, float32 mz);
void MadgwickAHRSupdateIMU(float32 gx, float32 gy, float32 gz, float32 ax, float32 ay, float32 az);
//float32 invSqrt(float x);

void AHRS_AccelIIRLPFilter(void);
//void AHRS_GyroIIRLPFilter(void);
//void AHRS_GyroBiasSet(void);
void AHRS_Normalize(void);
void AHRS_GetEulerRPY(void);
//void BYYS_Quat2Angle(void);
//void Accl_Cali_Print(void);
//void Gyro_Cali_Print(void);
//void Running_Print(void);
float32 invSqrt(float32 x);


int16 iirLPFilterSingle(volatile int32 in,volatile int32 attenuation, volatile int32* filt);

Uint16 ShouldDecodeData();

void DecodePlayerData();

#endif
