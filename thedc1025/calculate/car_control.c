#include "mhc.h"
#include "GlobalVariables.h"

void l298n_GPIO_init()//配置电机方向输出IO
{
	   EALLOW;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO12= 0; //配置GPIO12为GPout
	   GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO12 = 0;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0; //配置GPIO13为GPout
	   GpioCtrlRegs.GPADIR.bit.GPIO13= 1;
	   GpioDataRegs.GPADAT.bit.GPIO13= 0;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0; //配置GPIO14为GPout
	   GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO14 = 0;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO15= 0; //配置GPIO15为GPout
	   GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO15= 0;
	   EDIS;
}

void setEngine(int16 leftDrection,float32 leftPower,int16 rightDrection,float32 rightPower)
{
	switch(leftDrection)
	{
	case 0://刹车
		   GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;
		   GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;
		   setPwm(2,1);
		   break;
	case 1://前进
		   GpioDataRegs.GPASET.bit.GPIO14 = 1;
		   GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;
		   setPwm(2,leftPower);
		   break;
	case 2://后退
		   GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;
		   GpioDataRegs.GPASET.bit.GPIO15 = 1;
		   setPwm(2,leftPower);
		   break;
	}

	switch(rightDrection)
	{
	case 0://刹车
		   GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;
		   GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;
		   setPwm(1,1);
		   break;
	case 1://前进
		   GpioDataRegs.GPASET.bit.GPIO12 = 1;
		   GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;
		   setPwm(1,rightPower);
		   break;
	case 2://后退
		   GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;
		   GpioDataRegs.GPASET.bit.GPIO13 = 1;
		   setPwm(1,rightPower);
		   break;
	}
}



