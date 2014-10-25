#include "mhc.h"
#include "GlobalVariables.h"

void main(void)
{
//	Uint16 i;
	initDSP();
//	init_I2C_devices();

//	while( iicStartRead() != I2C_SUCCESS );

   uint16strcpy(sciASendBuffer,(Uint16*)"*****´®¿ÚAÕý³£*****");
   sciASendBufferPointer=0;
   SciaRegs.SCIFFTX.bit.TXFFIENA=1;

//   sensor_calibrate();

//   fly_enable=2;


   for(;;)
   {
//	   fly_enable=0;
//	   if(doCalulate)
//	   {
//		 dataConverse();
//		 Posture_calculate();
//		 pid();
//		 setMotor();
//		 doCalulate=0;
//	   }
//
	   if( doSCI && SciaRegs.SCIFFTX.bit.TXFFIENA==0)
	   {
		   sciASendData();
		   doSCI =0;
		   sciASendBufferPointer=0;
	   }
//
//	   if(doSBusDecode)
//	   {
//		   sbusDecode();
//		   doSBusDecode=0;
//	   }
//	   if(doUltra)
//	   {
//		   vz_ultrasonic_calculate();
//		   doUltra=0;
//	   }

	   GpioDataRegs.GPADAT.bit.GPIO12 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO13 = 0;
	   GpioDataRegs.GPADAT.bit.GPIO14 = 1;
	   GpioDataRegs.GPADAT.bit.GPIO15 = 0;

	   if(eCapData[0]<40)
	   {
		   setPwm(1,0.7);
		   setPwm(2,0.7);
	   }
	   else
	   {
		   setPwm(1,0);
		   setPwm(2,0);
	   }



	   GpioDataRegs.GPBDAT.bit.GPIO33 = 1;
	   for(delay=0;delay<40;delay++);
	   GpioDataRegs.GPBDAT.bit.GPIO33 = 0;
	   for(delay=0;delay<70000;delay++);

   }

} 
