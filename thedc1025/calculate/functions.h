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
void sciBSendData();
void uint16strcpy(Uint16* dst,Uint16* rsc);

void sbusDecode();


__interrupt void ecap1_isr(void);
__interrupt void ecap2_isr(void);
//__interrupt void ecap3_isr(void);
void InitECapture(void);


void I2CA_Init(void);
__interrupt void i2c_int1a_isr(void);
Uint16 iicWriteByte(Uint16 slaveAddr,Uint16 regAddr,Uint16 data);
//Uint16 iicReadByte(Uint16 slaveAddr,Uint16 regAddr);
void init_I2C_devices();
void init_I2C_devices_flying();//���³�ʼ��I2C ����ʱI2C��������� ��ʼ�����ɹ������iiC_broken
void iiC_broken();//I2C����ʧ��
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


void l298n_GPIO_init(void);
void setEngine(int16 leftDrection,float32 leftPower,int16 rightDrection,float32 rightPower);


/**************************************************
 * AHRS��ʼ
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


Uint16 ShouldDecodePlayerData();
void DecodePlayerData();

void InitializeEngine();
void SetEngineOutput();
void DisableEngineOutput();
void TurnEngine(float32 targetAngle);
void RunToTarget();
void RunAndTurn();
Uint16 UpdatePosture();
Uint16 IsPointedLoc(Uint16 locx,Uint16 locy);

float32 GetDistance(int32 fromx,int32 fromy,int32 tox,int32 toy);
float32 GetAngle(int32 fromx,int32 fromy,int32 tox,int32 toy);
float32 GetDiffAngleAbs(float32 fromAngle,float32 toAngle);
float32 GetDiffAngle(float32 fromAngle,float32 toAngle);
int16 IsCounterClockWise(float32 fromAngle,float32 toAngle);
float32 GetSecondTimespan(Uint16 cpuTimeFrom,Uint16 cpuTimeTo);
Uint16 ShouldReverseTurn(float32 fromAngle,float32 toAngle);

//����(vecX,vecY)��(shadowX,shadowY)�ϵ�ͶӰ
float32 Shadow(int16 vecX,int16 vecY,int16 shadowX,int16 shadowY);

//��������һ������
void SeekNextTarget();

//��ʼ�ȴ��÷�
void StartWaitPoint();

//TODO ���Ƿ�ǰ���пӴ�HasObstacle����
//�ƶ������directionö������
//TURN��������鷵��FALSE
Uint16 HasObstacle();
Uint16 HasFrontObstacle();
Uint16 HasBackObstacle();


#endif
