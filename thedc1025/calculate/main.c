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



   uint16strcpy(sciASendBuffer,(Uint16*)"*****串口A正常*****");
   sciASendBufferPointer=0;
   SciaRegs.SCIFFTX.bit.TXFFIENA=1;
   uint16strcpy(sciBSendBuffer,(Uint16*)"*****串口B正常*****");
   sciBSendBufferPointer=0;
   ScibRegs.SCIFFTX.bit.TXFFIENA=1;

//   sensor_calibrate();


   InitializeEngine();


   for(;;)
   {
	   if(gameFirstStart)
	   {
		   DisableEngineOutput();
	   }
	   if(doCalulate)
	   {
		 dataConverse();
		 Posture_calculate();
//		 pid();
//		 setMotor();
//		 doCalulate=0;
	   }
//
	   if( doSCIA && SciaRegs.SCIFFTX.bit.TXFFIENA==0)
	   {
		   sciASendData();
		   doSCIA =0;
		   sciASendBufferPointer=0;
	   }

	   if( doSCIB && ScibRegs.SCIFFTX.bit.TXFFIENA==0)
	   {
		   sciBSendData();
		   doSCIB =0;
		   sciBSendBufferPointer=0;
	   }

	   if(canMove && (isPlayerDataAvailable || isMPUavailable))
	   {
		   SetEngineOutput();
	   }
	   else
	   {
//		   nowAngle=0;
		   gameFirstStart=1;
		   moveStatus=PEND;
		   targetIterator=0;
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
