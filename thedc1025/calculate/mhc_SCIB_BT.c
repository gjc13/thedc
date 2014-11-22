#include "mhc.h"
#include "GlobalVariables.h"

__interrupt void scibTxFifoIsr(void)
{
	Uint16 i=0;
    for(i=0; i< 4; i++)
    {
    	if(sciBSendBuffer[sciBSendBufferPointer]  &&  sciBSendBufferPointer<128 )//Buffer中有数据
    	{
    		ScibRegs.SCITXBUF = sciBSendBuffer[sciBSendBufferPointer];//发送一个字
    		sciBSendBufferPointer++;
    	}
    	else
    	{
    		ScibRegs.SCIFFTX.bit.TXFFIENA=0;//关中断
    		break;
    	}
    }
    ScibRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}

__interrupt void scibRxFifoIsr(void)
{
//	if(sciBReadBufferPointer<128)
//	{
//		sciBReadBuffer[sciBReadBufferPointer]=ScibRegs.SCIRXBUF.all;
//		sciBReadBufferPointer++;
//	}

//	sciBReadAByte=1;
//	sBusReadDataCopied=0;

	ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack
}

void scib_mhc_init()
{
//	ESTOP0;
   ScibRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback, No parity,8 char bits, async mode, idle-line protocol
//   ScibRegs.SCICCR.all =0x00E7;   // 2 stop bit,  No loopback, EVEN parity,8 char bits, async mode, idle-line protocol

   ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                  // Disable RX ERR, SLEEP, TXWAKE
   ScibRegs.SCICTL2.bit.TXINTENA =1;
   ScibRegs.SCICTL2.bit.RXBKINTENA =0;

   ScibRegs.SCIHBAUD = 0x0000;//100000 baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
   ScibRegs.SCILBAUD = 0x0017;

   ScibRegs.SCICCR.bit.LOOPBKENA =0; // Enable loop back
   ScibRegs.SCIFFTX.all=0xC000;
   ScibRegs.SCIFFRX.all=0x0021;
   ScibRegs.SCIFFCT.all=0x00;

   ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScibRegs.SCIFFRX.bit.RXFIFORESET=1;
}

//!sbusDecode,S.BUS解析
/*!
	\param p_origin  接受数据首地址
	\param p_result  存放结果首地址
	将p_origin每个byte高地位互换，按11位分割
	作者：郭嘉丞
	版本：1.0
*/
void sbusDecode()
{
//	Uint8 *p_origin=sBusReadData;
//	Uint16 *p_result=channelsData2048;
//	int16 countOrigin=0,countResult=0,i;
//	Uint8 filter=0x01;
//	(*p_result)=0;	//p_result置零
//	p_result--;		//p_result从int[0]开始，p_origin从char[1]开始
//	for(i=0; i<176; i++)
//	{
//		countOrigin--;countResult--;
//		if(countOrigin<0)
//		{
//			countOrigin=7;	//Origin每8位指针移动
//			p_origin++;
//		}
//		if(countResult<0)
//		{
//			countResult=10;					//Result每11位指针移动
//			(*p_result)=(*p_result)<<1;		//撤销最后一次移位
//			p_result++;
//			(*p_result)=0;
//		}
//		(*p_result)|=(((*p_origin)&(filter))<<10);
//		(*p_result)=(*p_result)>>1;
//		(*p_origin)=(*p_origin)>>1;
//	}
//
//	p_origin++;
//	wireLessLost=(*p_origin)&0x04;
//	digitalChannel2=(*p_origin)&0x02;
//	digitalChannel1=(*p_origin)&0x01;
//
//	for(countResult=0;countResult<16;countResult++)
//	{
//		channelsData1000[countResult]=channelsData2048[countResult]/2048.*1000;
//		if(channelsData2048[countResult]<360)
//			channelsData4[countResult]=0;
//		else 	if(channelsData2048[countResult]<1016)
//			channelsData4[countResult]=1;
//		else 	if(channelsData2048[countResult]<1032)
//			channelsData4[countResult]=2;
//		else 	if(channelsData2048[countResult]<1688)
//			channelsData4[countResult]=3;
//		else
//			channelsData4[countResult]=4;
//	}

}


void sciBSendData()
{
	Uint16 i;
	for(i=0;i<128;i++)
		sciBSendBuffer[i]=0;


	strcat((char*)sciBSendBuffer,"sta");
	int16_to_string((int16)moveStatus,(char*)sciBSendBuffer);

	strcat((char*)sciBSendBuffer,"dir");
	int16_to_string((int16)direction,(char*)sciBSendBuffer);

	strcat((char*)sciBSendBuffer,"loc");
	int16_to_string((int16)nowX,(char*)sciBSendBuffer);
	int16_to_string((int16)nowY,(char*)sciBSendBuffer);

	strcat((char*)sciBSendBuffer,"tag");
	int16_to_string((int16)targetX,(char*)sciBSendBuffer);
	int16_to_string((int16)targetY,(char*)sciBSendBuffer);

	strcat((char*)sciBSendBuffer,"nP");
	int16_to_string((int16)getNewPoint,(char*)sciBSendBuffer);
	strcat((char*)sciBSendBuffer,"pT");
	int16_to_string((int16)waitingTime,(char*)sciBSendBuffer);


//		   strcat((char*)sciBSendBuffer,"\t");

	strcat((char*)sciBSendBuffer,"\r\n");

	sciBSendBufferPointer=0;
	ScibRegs.SCIFFTX.bit.TXFFIENA=1;
}
