#include "mhc.h"
#include "GlobalVariables.h"

void initDSP()
{
	Uint16 i;

	// Step 1. Initialize System Control: PLL, WatchDog, enable Peripheral Clocks, This example function is found in the F2806x_SysCtrl.c file.
	   InitSysCtrl();
	   InitPll2(PLL2SRC_INTOSC1, 1, PLL2_SYSCLK2DIV2DIS);

	   initGlobalVariables();

	// Step 2. Initalize GPIO:  This example function is found in the F2806x_Gpio.c file and
	   InitI2CGpio();
	   InitECap1Gpio();
//	   InitECap2Gpio();
//	   InitECap3Gpio();
	   InitSciaGpio();
	   InitScibGpio();
	   InitEPwm1Gpio();
	   InitEPwm2Gpio();
	   InitEPwm3Gpio();
	   InitEPwm4Gpio();
	   InitEPwm5Gpio();
	   l298n_GPIO_init();

	   EALLOW;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO33= 0; //配置GPIO34为GPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;
	   GpioDataRegs.GPBDAT.bit.GPIO33= 1;
	   EDIS;


	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	   DINT;

	// Initialize the PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags are cleared.
	// This function is found in the F2806x_PieCtrl.c file.
	   InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
	   IER = 0x0000;
	   IFR = 0x0000;

	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in F2806x_DefaultIsr.c.
	// This function is found in F2806x_PieVect.c.
	   InitPieVectTable();

	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	   EALLOW;  // This is needed to write to EALLOW protected registers
	   PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
	   PieVectTable.SCITXINTA = &sciaTxFifoIsr;
	   PieVectTable.SCIRXINTB = &scibRxFifoIsr;
	   PieVectTable.SCITXINTB = &scibTxFifoIsr;
	   PieVectTable.ECAP1_INT = &ecap1_isr;
//	   PieVectTable.ECAP2_INT = &ecap2_isr;
//	   PieVectTable.ECAP3_INT = &ecap3_isr;
	   PieVectTable.I2CINT1A = &i2c_int1a_isr;
	   PieVectTable.TINT0 = &cpu_timer0_isr;
	//   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	   EDIS;    // This is needed to disable write to EALLOW protected registers

	// Step 4. Initialize all the Device Peripherals:
	// This function is found in F2806x_InitPeripherals.c
	// InitPeripherals();  // Not required for this example
	   InitCpuTimers();
	   ConfigCpuTimer(&CpuTimer0, 90, 2500);
	   CpuTimer0Regs.TCR.all = 0x4000;

	   I2CA_Init();
	   scia_mhc_init();
	   scib_mhc_init();
	   InitECapture();
	   InitEPwm1Example();
	   InitEPwm2Example();
	   InitEPwm3Example();
	   InitEPwm4Example();
	   InitEPwm5Example();



	   EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	   EDIS;


	// Enable global Interrupts and higher priority real-time debug events:
	   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	   PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, INT1 SCIA
	   PieCtrlRegs.PIEIER9.bit.INTx2=1;     // PIE Group 9, INT2
	   PieCtrlRegs.PIEIER9.bit.INTx3=1;//SCIB
	   PieCtrlRegs.PIEIER9.bit.INTx4=1;
	   PieCtrlRegs.PIEIER4.bit.INTx1 = 1;//ecap1
//	   PieCtrlRegs.PIEIER4.bit.INTx2 = 1;//ecap2
//	   PieCtrlRegs.PIEIER4.bit.INTx3 = 1;//ecap3
	   PieCtrlRegs.PIEIER8.bit.INTx1 = 1;//I2C
	   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;//CPUtimer0


	   IER = 0x100; // Enable CPU INT 可能是SCI的
	   IER |= M_INT8;		//I2C
	   IER |= M_INT4;    // Enable CPU INT4,  ecap1 2 3
	   IER |= M_INT1;				//CPUtimer0
	   EINT;   // Enable Global interrupt INTM
	   ERTM;   // Enable Global realtime interrupt DBGM


	   setPwm(1,0);//设置输出为0
	   setPwm(2,0);
	   setPwm(3,0);
	   setPwm(4,0);
	   setPwm(5,0);


	   for(i=0;i<128;i++)
		   sciBReadBuffer[i]=0;
	   for(i=0;i<16;i++)
		   channelsData2048[i]=0;
	   for(i=0;i<16;i++)
		   channelsData1000[i]=0;


//	   for(delay=1200000;delay>0;delay--);//延时
}




void initGlobalVariables()
{
	Uint16 i;

	vz_ultra=0;
	vz=0;

	for(i=0;i<128;i++)
	{
//		sciASendBuffer[i]=0;
//		sciAReadBuffer[i]=0;
//		sciBSendBuffer[i]=0;
//		sciBReadBuffer[i]=0;
	}


	sciBReadAByte=0;//S.BUS
	sBusReadDataCopied=1;
	digitalChannel1=0;
	digitalChannel2=0;
	wireLessLost=0;

	for(i=0;i<16;i++)
	{
		channelsData2048[i]=0;
		channelsData1000[i]=0;
		channelsData4[i]=0;
	}
	for(i=0;i<24;i++)
		sBusReadData[i]=0;

	i2c_Send_Complete=0;
	i2cDataPointer=0;
//	int16 i2cData[32]={0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0};//懒得改了 要改！！！
//	Uint16 i2cSlaves[32]={0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68,	0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68,
//									0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68, 	0x68,0x68,0x68,0x68};
//	Uint16 i2cRegAddr[32]={ACCEL_XOUT_H , ACCEL_XOUT_L , ACCEL_YOUT_H , ACCEL_YOUT_L , ACCEL_ZOUT_H , ACCEL_ZOUT_L , TEMP_OUT_H , TEMP_OUT_L ,
//										GYRO_XOUT_H , GYRO_XOUT_L , GYRO_YOUT_H , GYRO_YOUT_L , GYRO_ZOUT_H , GYRO_ZOUT_L,0,0,0,0,0,0,0,0,0,0,
//										0,0,0,0,0,0,0,0};
//	float32 MPU6050Data[7];
	i2c_Send_Data=0;
	i2c_Slave_Addr=0;
	i2c_Reg_Addr=0;

	i2cStatus=0;
	// 0 什么都不做
	// 12 I2C正在发送地址，之后要接收一个数据
	// 13 I2C发完了Reg地址，正在接收一个数据
	// 21 命令I2C正在发送地址和数据

	// 31 读数据时从器件非应答
	// 32 写数据时从器件非应答



	doCalulate=0 ;//应该计算  应该发串口  S.Bus收完一帧且已复制,应该计算
	doSCI=0;
	doSBusDecode=0;

	fly_enable=0; //3可以起飞



	acceXDrift = 285;//加速度零点偏移
//	acceYDrift = (16300-16620)/2;
//	acceZDrift = (16580-17200)/2-295;
	AcceXK = ((float32)200.0)/(16050l+16090l)/1.02/100;//加速度系数
	AcceYK = ((float32)200.0)/(16300l+16620l)/100;
	AcceZK = ((float32)200.0)/(16580l+17200l)*1.018/100;
	gyroXDrift=-24.6623;//陀螺仪零点偏移
	gyroYDrift=-13.71428571;
	gyroZDrift=5.25974026;
	Gkx=930.0;//陀螺仪系数
	Gky=930.0;
	Gkz=930.0;


	cpuTime=0;

	G_pos_p=0.1;
	G_pos_r=0.1 ;

//	float32 pitch_Au,roll_Av;
	pitch_Gy = 0;
	roll_Gx = 0 ;
	yaw_Gz = 0 ;
	dp = 0;
	dr =  0 ;
	dy = 0;//p、r、y：俯仰、横滚、偏航

	speed_pitch_lp=0;
	speed_roll_lp=0;
	speed_yaw_lp=0;



//	posture_expected={0,0,0,0};
//	posture_now={0,0,0,0};
//	posture_error={0,0,0,0};
//	posture_adjust={0,0,0,0};
//	posture_speed={0,0,0,0};
//	posture_before={0,0,0,0};

	MOTOR1_PULSE=0;
	MOTOR2_PULSE=0;
	MOTOR3_PULSE=0;
	MOTOR4_PULSE=0;
//	pulse_temp;
}

void sensor_calibrate(void)
{
	volatile  int16 count=0;
	volatile  float32 gAcce_z_avr=0;
	count=0;
	gAcce_z_avr=0;
	for(delay=0;delay<2000000;delay++);

	for(count=0;count<40;count++)
	{
		for(delay=0;delay<20000;delay++);
		gAcce_z_avr+=gAccel.z;
	}

	az_scale = g_local/(gAcce_z_avr/40);

}

