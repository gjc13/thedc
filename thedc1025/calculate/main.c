#include "mhc.h"
#include "GlobalVariables.h"
#include "functions.h"

void main(void)
{
//	Uint16 i;
	initDSP();
//	while(1)
//	{
//		setEngine(1,0.2,1,0.2);
//	}
	init_I2C_devices();



   uint16strcpy(sciASendBuffer,(Uint16*)"*****´®¿ÚAÕý³£*****");
   sciASendBufferPointer=0;
   SciaRegs.SCIFFTX.bit.TXFFIENA=1;

//   sensor_calibrate();


   InitializeEngine();
   for(;;)
   {
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

	   if(canMove && (isMPUavailable||isPlayerDataAvailable))
	   {
		   if(moveStatus==PEND)
		   {
			   SeekNextTarget();
		   }
		   SetEngineOutput();
	   }
	   else
	   {
//		   nowAngle=0;
		   gameFirstStart=1;
		   DisableEngineOutput();
	   }

	   if(doSBusDecode)
	   {
		   sbusDecode();
		   doSBusDecode=0;
	   }
	   if(doUltra)
	   {
		   vz_ultrasonic_calculate();
		   doUltra=0;
	   }

//	   if(eCapData[0]<40)
//		   setEngine(1,0.25,1,0.245);
//	   else
//		   setEngine(0,0,0,0);



//	   GpioDataRegs.GPBDAT.bit.GPIO33 = 1;
//	   for(delay=0;delay<40;delay++);
//	   GpioDataRegs.GPBDAT.bit.GPIO33 = 0;
//	   for(delay=0;delay<70000;delay++);




   }

} 
