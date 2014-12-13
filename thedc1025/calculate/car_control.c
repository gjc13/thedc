#include "mhc.h"
#include "GlobalVariables.h"

void l298n_GPIO_init()//���õ���������IO
{
	   EALLOW;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO41= 0; //����GPIO12ΪGPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;
	   GpioDataRegs.GPBDAT.bit.GPIO41 = 0;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0; //����GPIO13ΪGPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO42= 1;
	   GpioDataRegs.GPBDAT.bit.GPIO42= 0;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0; //����GPIO14ΪGPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO43 = 1;
	   GpioDataRegs.GPBDAT.bit.GPIO43 = 0;
	   GpioCtrlRegs.GPBMUX1.bit.GPIO44= 0; //����GPIO15ΪGPout
	   GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;
	   GpioDataRegs.GPBDAT.bit.GPIO44= 0;
	   EDIS;
}


void aux_GPIO_init()//���õ���������IO
{
	   EALLOW;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO20= 0; //����GPIO20ΪGPout
	   GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO20 = 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0; //����GPIO21ΪGPout
	   GpioCtrlRegs.GPADIR.bit.GPIO21= 1;
	   GpioDataRegs.GPADAT.bit.GPIO21= 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0; //����GPIO30ΪGPout
	   GpioCtrlRegs.GPADIR.bit.GPIO30 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO30 = 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO31= 0; //����GPIO31ΪGPout
	   GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO31= 0;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO58= 0; //����GPIO58ΪGPout,������
	   GpioCtrlRegs.GPBDIR.bit.GPIO58 = 1;
	   GpioDataRegs.GPBDAT.bit.GPIO58= 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO30= 0; //����GPIO30ΪGPin
	   GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;
	   GpioCtrlRegs.GPAMUX2.bit.GPIO31= 0; //����GPIO31ΪGPin
	   GpioCtrlRegs.GPADIR.bit.GPIO31 = 0;
	   EDIS;
}

void setEngine(int16 leftDirection,float32 leftPower,int16 rightDirection,float32 rightPower)
{
//	leftPower*=2;
//	rightPower*=2;
	if(leftPower<0)
	{
		leftPower=-leftPower;
		if(leftDirection==ENGINEBACK)
		{
			leftDirection=ENGINEFRONT;
		}
		else if(leftDirection==ENGINEFRONT)
		{
			leftDirection=ENGINEBACK;
		}
	}
	if(rightPower<0)
	{
		rightPower=-rightPower;
		if(rightDirection==ENGINEBACK)
		{
			rightDirection=ENGINEFRONT;
		}
		else if(rightDirection==ENGINEFRONT)
		{
			rightDirection=ENGINEBACK;
		}
	}

//	if(leftDirection==ENGINEBACK)
//	{
//		leftPower=leftPower<0.7?leftPower:0.7;
//	}
//	else if(leftDirection==ENGINEFRONT)
//	{
//		leftPower=leftPower<0.3?leftPower:0.3;
//	}
//	if(rightDirection==ENGINEBACK)
//	{
//		rightPower=rightPower<0.7?rightPower:0.7;
//	}
//	else if(rightDirection==ENGINEFRONT)
//	{
//		rightPower=rightPower<0.3?rightPower:0.3;
//	}

	leftPower=leftPower<0?0:leftPower;
	leftPower=leftPower>1?1:leftPower;
	rightPower=rightPower<0?0:rightPower;
	rightPower=rightPower>1?1:rightPower;

	leftPower=0+0.95*leftPower;
	rightPower=0+0.95*rightPower;

	switch(leftDirection)
	{
	case 0://ɲ��
		   GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
		   GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;
		   setPwm(1,1);
		   break;
	case 1://ǰ��
		   GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
		   GpioDataRegs.GPBSET.bit.GPIO42 = 1;
		   setPwm(1,leftPower);
		   break;
	case 2://����
		   GpioDataRegs.GPBSET.bit.GPIO41 = 1;
		   GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;
		   setPwm(1,leftPower);
		   break;
	}

	switch(rightDirection)
	{
	case 0://ɲ��
		   GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;
		   GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
		   setPwm(2,1);
		   break;
	case 1://ǰ��
		   GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;
		   GpioDataRegs.GPBSET.bit.GPIO44 = 1;
		   setPwm(2,rightPower);
		   break;
	case 2://����
		   GpioDataRegs.GPBSET.bit.GPIO43 = 1;
		   GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
		   setPwm(2,rightPower);
		   break;
	}
}
