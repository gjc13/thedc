#include "mhc.h"
#include "GlobalVariables.h"
#include "functions.h"

//

void main(void)
{
	Uint16 i;

	initDSP();

	nowAngle=0;

	//init_I2C_devices();
	GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
	spiPointer=0;
	SpiaRegs.SPITXBUF=spiASendData[spiPointer];
//	init_I2C_devices();

    uint16strcpy(sciASendBuffer,(Uint16*)"*****串口A正常*****");
    sciASendBufferPointer=0;
    SciaRegs.SCIFFTX.bit.TXFFIENA=1;
    uint16strcpy(sciBSendBuffer,(Uint16*)"*****串口B正常*****");
    sciBSendBufferPointer=0;
    ScibRegs.SCIFFTX.bit.TXFFIENA=1;
    setSaw(1);



   InitializeEngine();

//   while(1)
//   {
//	   if(foundHeadObstacleTime>10 || foundTailObstacleTime>10)
//	   {
//			for(i=0; i<0x20FE; i++)
//			{
//				setEngine(ENGINEFRONT,0.25,ENGINEFRONT,0.25);
//			}
//	   }
//	   else
//	   {
//		   setEngine(ENGINEBACK,0.1,ENGINEBACK,0.1);
//	   }
//   }

   for(;;)
   {
	   //TODO: 检查时间（开赛后1s启动）
	   //<Disabled in speed control>
	   if(gameFirstStart)
	   {
		   DisableEngineOutput();
	   }
	   //</Disabled in speed control>


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
		   if(moveStatus!=WAITPOINT)
		   {
			   SetEngineOutput();
		   }
		   else
		   {
			   DisableEngineOutput();
		   }
	   }
	   else
	   {
//		   nowAngle=0;
		   gameFirstStart=1;
		   moveStatus=PEND;
		   targetIterator=0;
		   DisableEngineOutput();
	   }

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




   }

} 
