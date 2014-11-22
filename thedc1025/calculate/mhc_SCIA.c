#include "mhc.h"
#include "GlobalVariables.h"

volatile Uint16 lastReciveTime = 0;

__interrupt void sciaTxFifoIsr(void)
{
	Uint16 i=0;
    for(i=0; i< 4; i++)
    {
    	if( sciASendBuffer[sciASendBufferPointer]  &&  sciASendBufferPointer<128 )//Buffer��������
    	{
    		SciaRegs.SCITXBUF = sciASendBuffer[sciASendBufferPointer];//����һ����
    		sciASendBufferPointer++;
    	}
    	else
    	{
    		SciaRegs.SCIFFTX.bit.TXFFIENA=0;//���ж�
    		break;
    	}
    }
    SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}


__interrupt void sciaRxFifoIsr(void)
{
	if(cpuTime > lastReciveTime+2 )
		sciAReadBufferPointer = 0;
	lastReciveTime=cpuTime;

	if(sciAReadBufferPointer<30)//ÿ֡����30����
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
   SciaRegs.SCIHBAUD = 0x0001;//9600 baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
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

//	strcat((char*)sciASendBuffer,"An:");
//	double_to_string(nowAngle*180/PI , (char*)sciASendBuffer);
//	strcat((char*)sciASendBuffer,"gy:");
//	double_to_string(gGyro.z*180/PI,(char*)sciASendBuffer);
//	strcat((char*)sciASendBuffer,"DAn:");
//	double_to_string(nowDataAngle*180/PI,(char*)sciASendBuffer);
//	strcat((char*)sciASendBuffer,"TarAn:");
//	double_to_string(targetAngle*180/PI,(char*)sciASendBuffer);
//	strcat((char*)sciASendBuffer,"PD:");
//	double_to_string(Padjust,(char*)sciASendBuffer);
//	double_to_string(Dadjust,(char*)sciASendBuffer);

//	strcat((char*)sciASendBuffer,"direction:");
//	double_to_string((double)direction,(char*)sciASendBuffer);
//

	strcat((char*)sciASendBuffer,"eCap");
	double_to_string((double)eCapData[0],(char*)sciASendBuffer);
	double_to_string((double)eCapData[1],(char*)sciASendBuffer);

	strcat((char*)sciASendBuffer,"sta");
	double_to_string((double)moveStatus,(char*)sciASendBuffer);

	strcat((char*)sciASendBuffer,"dir");
	double_to_string((double)direction,(char*)sciASendBuffer);

	strcat((char*)sciASendBuffer,"loc");
	double_to_string((double)nowX,(char*)sciASendBuffer);
	double_to_string((double)nowY,(char*)sciASendBuffer);

	strcat((char*)sciASendBuffer,"tag");
	double_to_string((double)targetX,(char*)sciASendBuffer);
	double_to_string((double)targetY,(char*)sciASendBuffer);
//
//	strcat((char*)sciASendBuffer,"dis");
//	double_to_string(nowDistance,(char*)sciASendBuffer);
//
//	strcat((char*)sciASendBuffer,"Ang");
//	double_to_string(nowAngle,(char*)sciASendBuffer);
//
//	strcat((char*)sciASendBuffer,"taAng");
//	double_to_string(targetAngle,(char*)sciASendBuffer);
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
