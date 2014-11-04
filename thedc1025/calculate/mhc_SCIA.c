#include "mhc.h"
#include "GlobalVariables.h"

volatile Uint16 lastReciveTime = 0;

__interrupt void sciaTxFifoIsr(void)
{
	Uint16 i=0;
    for(i=0; i< 4; i++)
    {
    	if( sciASendBuffer[sciASendBufferPointer]  &&  sciASendBufferPointer<128 )//Buffer中有数据
    	{
    		SciaRegs.SCITXBUF = sciASendBuffer[sciASendBufferPointer];//发送一个字
    		sciASendBufferPointer++;
    	}
    	else
    	{
    		SciaRegs.SCIFFTX.bit.TXFFIENA=0;//关中断
    		break;
    	}
    }
    SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}


__interrupt void sciaRxFifoIsr(void)
{
	if(cpuTime > lastReciveTime+5 )
		sciAReadBufferPointer = 0;
	lastReciveTime=cpuTime;

	if(sciAReadBufferPointer<30)//每帧最多读30个数
	{
		sciAReadBuffer[sciAReadBufferPointer]=SciaRegs.SCIRXBUF.all;
		sciAReadBufferPointer++;
	}
	if(ShouldDecodePlayerData())
	{
		DecodePlayerData();
	}
	SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack
}

void scia_mhc_init()
{
   SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback, No parity,8 char bits,   // async mode, idle-line protocol
   SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK, // Disable RX ERR, SLEEP, TXWAKE
   SciaRegs.SCICTL2.bit.TXINTENA =1;
   SciaRegs.SCICTL2.bit.RXBKINTENA =0;
   SciaRegs.SCIHBAUD = 0x0001;//115200 baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
   SciaRegs.SCILBAUD = 0x0025;
   SciaRegs.SCICCR.bit.LOOPBKENA =0; // Disnable loop back
   SciaRegs.SCIFFTX.all=0xC000;
   SciaRegs.SCIFFRX.all=0x0021;//0x0198;
   SciaRegs.SCIFFCT.all=0x00;

   SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
}


void uint16strcpy(Uint16* dst,Uint16* rsc)
{
	while( *(dst++) = *(rsc++) );
}


void sciASendData()
{
	Uint16 i;
	for(i=0;i<128;i++)
		sciASendBuffer[i]=0;

	strcat((char*)sciASendBuffer,"Angle:");
	double_to_string(nowAngle*180/PI , (char*)sciASendBuffer);
	double_to_string(gGyro.z*100, (char*)sciASendBuffer);
//		   double_to_string(pitch_Gy*180/PI , (char*)sciASendBuffer);
//		   double_to_string(roll_Gx*180/PI , (char*)sciASendBuffer);
//
//		   strcat((char*)sciASendBuffer,"\t");
//
//		   double_to_string(  MOTOR1_PULSE , (char*)sciASendBuffer);
//		   double_to_string(  MOTOR2_PULSE , (char*)sciASendBuffer);
//		   double_to_string(  MOTOR3_PULSE , (char*)sciASendBuffer);
//		   double_to_string(  MOTOR4_PULSE , (char*)sciASendBuffer);

//	double_to_string(  height_ultrasonic , (char*)sciASendBuffer);
//	double_to_string(  height_ultrasonic_lp , (char*)sciASendBuffer);

//	double_to_string(  throttle_real , (char*)sciASendBuffer);
//	double_to_string(  throttle_ref , (char*)sciASendBuffer);

	strcat((char*)sciASendBuffer,"\r\n");

	sciASendBufferPointer=0;
	SciaRegs.SCIFFTX.bit.TXFFIENA=1;
}
