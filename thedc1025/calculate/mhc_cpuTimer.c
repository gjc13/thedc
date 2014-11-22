#include "mhc.h"
#include "GlobalVariables.h"

__interrupt void cpu_timer0_isr(void)
{
//	Uint16 i;

	//更新光电门输入
	if(GpioDataRegs.GPADAT.bit.GPIO31)
	{
		foundHeadObstacleTime++;
		foundHeadObstacleTime=foundHeadObstacleTime>400?400:foundHeadObstacleTime;
	}
	else
	{
		foundHeadObstacleTime=0;
	}
	if(GpioDataRegs.GPADAT.bit.GPIO30)
	{
		foundTailObstacleTime++;
		foundTailObstacleTime=foundTailObstacleTime>400?400:foundTailObstacleTime;
	}
	else
	{
		foundTailObstacleTime=0;
	}


	if(cpuTime++>60000)
		cpuTime=0;

	if(SciaRegs.SCIRXST.bit.RXERROR || SciaRegs.SCIFFRX.bit.RXFFOVF)//如果串口接收出错就重新初始化串口
	{
		isPlayerDataAvailable=0;
		SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;
		SciaRegs.SCIFFRX.bit.RXFIFORESET=0;
		SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
		SciaRegs.SCICTL1.bit.SWRESET=0;
		SciaRegs.SCICTL1.bit.SWRESET=1;
	}


	doCalulate=1;


//	if(cpuTime%100==0)

	if(moveStatus==WAITPOINT)
	{
		waitingTime++;
	}
	if(waitingTime>waitTimeLimit)
	{
		DisableEngineOutput();
		moveStatus=PEND;
		SeekNextTarget();
		waitingTime=0;
		getNewPoint=0;
	}
	lockTurnTime--;
	lockTurnTime=lockTurnTime<0?0:lockTurnTime;

	UpdatePosture();

	if(cpuTime%80==0)
		doSCIA=1;

	if(cpuTime%50==0)
		doSCIB=1;


//	if(cpuTime%10==0)
//		doUltra=1;

//	GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;
//	GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
//	if(cpuTime%12==0)
//	{
//		GpioDataRegs.GPASET.bit.GPIO30 = 1;//给超声波打个脉冲
//		GpioDataRegs.GPASET.bit.GPIO31= 1;//给超声波打个脉冲
//	}

//	if(sciBReadAByte==0 && sBusReadDataCopied==0)//读完一帧
//	{
//		{
//			for(i=0;i<24;i++)
//				sBusReadData[i]=sciBReadBuffer[i];//复制24字节到sBusReadData
//
//			for(i=0;i<25;i++)
//				sciBReadBuffer[i]=0;//清零
//			sciBReadBufferPointer=0;//接收下一帧
//
//			sBusReadDataCopied=1;
//			doSBusDecode=1;
//		}
//	}
//	else
//		sciBReadAByte=0;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
