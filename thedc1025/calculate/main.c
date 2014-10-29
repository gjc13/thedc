#include "mhc.h"
#include "GlobalVariables.h"

void main(void)
{
//	Uint16 i;
	initDSP();
	init_I2C_devices();

	while( iicStartRead() != I2C_SUCCESS );

   uint16strcpy(sciASendBuffer,(Uint16*)"*****����A����*****");
   sciASendBufferPointer=0;
   SciaRegs.SCIFFTX.bit.TXFFIENA=1;

//   sensor_calibrate();

//   fly_enable=2;

   InitializeEngine();

   for(;;)
   {
//	   fly_enable=0;
	   if(doCalulate)
	   {
		 dataConverse();
		 Posture_calculate();
//		 pid();
//		 setMotor();
//		 doCalulate=0;
	   }
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

//	   if(eCapData[0]<40)
//		   setEngine(1,0.25,1,0.245);
//	   else
//		   setEngine(0,0,0,0);

	   if(UpdatePosture() && canMove)
	   {
		   SetEngineOutput();
	   }
	   else if(!canMove)
	   {
		   DisableEngineOutput();
	   }



//	   GpioDataRegs.GPBDAT.bit.GPIO33 = 1;
//	   for(delay=0;delay<40;delay++);
//	   GpioDataRegs.GPBDAT.bit.GPIO33 = 0;
//	   for(delay=0;delay<70000;delay++);




   }

} 
