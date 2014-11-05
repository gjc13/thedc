#include "mhc.h"
#include "GlobalVariables.h"

__interrupt void cpu_timer0_isr(void)
{
	Uint16 i;

	if(cpuTime++>60000)
		cpuTime=0;

	if(SciaRegs.SCIRXST.bit.RXERROR || SciaRegs.SCIFFRX.bit.RXFFOVF)//������ڽ��ճ�������³�ʼ������
	{
		SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;
		SciaRegs.SCIFFRX.bit.RXFIFORESET=0;
		SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
		SciaRegs.SCICTL1.bit.SWRESET=0;
		SciaRegs.SCICTL1.bit.SWRESET=1;
	}


	doCalulate=1;


	if(cpuTime%100==0)
	{
		UpdatePosture();
	}

	if(cpuTime%80==0)
		doSCI=1;

	if(cpuTime%10==0)
		doUltra=1;

	GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;
	if(cpuTime%12==0)
		GpioDataRegs.GPASET.bit.GPIO30 = 1;//���������������

	if(sciBReadAByte==0 && sBusReadDataCopied==0)//����һ֡
	{
		{
			for(i=0;i<24;i++)
				sBusReadData[i]=sciBReadBuffer[i];//����24�ֽڵ�sBusReadData

			for(i=0;i<25;i++)
				sciBReadBuffer[i]=0;//����
			sciBReadBufferPointer=0;//������һ֡

			sBusReadDataCopied=1;
			doSBusDecode=1;
		}
	}
	else
		sciBReadAByte=0;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
