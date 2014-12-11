#include "mhc.h"
#include "GlobalVariables.h"

void l298n_GPIO_init()//配置电机方向输出IO
{
	   EALLOW;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO41= 0; //配置GPIO12为GPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;
	   GpioDataRegs.GPBDAT.bit.GPIO41 = 0;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0; //配置GPIO13为GPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO42= 1;
	   GpioDataRegs.GPBDAT.bit.GPIO42= 0;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0; //配置GPIO14为GPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO43 = 1;
	   GpioDataRegs.GPBDAT.bit.GPIO43 = 0;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO44= 0; //配置GPIO15为GPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;
	   GpioDataRegs.GPBDAT.bit.GPIO44= 0;
	   EDIS;
}


void aux_GPIO_init()//配置电机方向输出IO
{
	   EALLOW;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO20= 0; //配置GPIO20为GPout
	   GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO20 = 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0; //配置GPIO21为GPout
	   GpioCtrlRegs.GPADIR.bit.GPIO21= 1;
	   GpioDataRegs.GPADAT.bit.GPIO21= 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0; //配置GPIO30为GPout
	   GpioCtrlRegs.GPADIR.bit.GPIO30 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO30 = 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO31= 0; //配置GPIO31为GPout
	   GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO31= 0;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO58= 0; //配置GPIO58为GPout,蜂鸣器
	   GpioCtrlRegs.GPBDIR.bit.GPIO58 = 1;
	   GpioDataRegs.GPBDAT.bit.GPIO58= 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO30= 0; //配置GPIO30为GPin
	   GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO31= 0; //配置GPIO31为GPin
	   GpioCtrlRegs.GPADIR.bit.GPIO31 = 0;
	   EDIS;
}

void setEngine(int16 leftDirection,float32 leftPower,int16 rightDirection,float32 rightPower)
{
	leftPower*=2;
	rightPower*=2;
	if(leftPower<0)
	{
		if(leftDirection==ENGINEBACK)
		{
			leftDirection=ENGINEFRONT;
		}
		else if(leftDirection==ENGINEFRONT)
		{
			rightDirection=ENGINEBACK;
		}
	}
	if(rightPower<0)
	{
		if(rightDirection==ENGINEBACK)
		{
			rightDirection=ENGINEFRONT;
		}
		else if(rightDirection==ENGINEFRONT)
		{
			rightDirection=ENGINEBACK;
		}
	}

	if(leftDirection==ENGINEBACK)
	{
		leftPower=leftPower<0.7?leftPower:0.7;
	}
	else if(leftDirection==ENGINEFRONT)
	{
		leftPower=leftPower<0.3?leftPower:0.3;
	}
	if(rightDirection==ENGINEBACK)
	{
		rightPower=rightPower<0.7?rightPower:0.7;
	}
	else if(rightDirection==ENGINEFRONT)
	{
		rightPower=rightPower<0.3?rightPower:0.3;
	}

	switch(leftDirection)
	{
	case 0://刹车
		   GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
		   GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;
		   setPwm(2,1);
		   break;
	case 1://前进
		   GpioDataRegs.GPBSET.bit.GPIO41 = 1;
		   GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;
		   setPwm(2,leftPower);
		   break;
	case 2://后退
		   GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
		   GpioDataRegs.GPBSET.bit.GPIO42 = 1;
		   setPwm(2,leftPower);
		   break;
	}

	switch(rightDirection)
	{
	case 0://刹车
		   GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;
		   GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
		   setPwm(1,1);
		   break;
	case 1://前进
		   GpioDataRegs.GPBSET.bit.GPIO43 = 1;
		   GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
		   setPwm(1,rightPower);
		   break;
	case 2://后退
		   GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;
		   GpioDataRegs.GPBSET.bit.GPIO44 = 1;
		   setPwm(1,rightPower);
		   break;
	}
}
