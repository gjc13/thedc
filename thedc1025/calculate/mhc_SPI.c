#include "mhc.h"
#include "GlobalVariables.h"




void initSPI()
{
// Initialize SPI FIFO registers

   SpiaRegs.SPICCR.bit.SPISWRESET=0; // Reset SPI

   SpiaRegs.SPICCR.all=0x47;       //reset�������ز����½��������8-bit character, non-Loopback mode
   SpiaRegs.SPICTL.all=0x07;       //Interrupt enabled, Masterģʽ����ֹ����ж�
   SpiaRegs.SPIBRR = 0x15;           // Baud rate
   SpiaRegs.SPIFFTX.all=0xA000;      // Disable FIFO's,
   SpiaRegs.SPIFFRX.all=0x201F;
   SpiaRegs.SPIFFCT.all=0x00;
   SpiaRegs.SPIPRI.all=0x0010;

   SpiaRegs.SPICCR.bit.SPISWRESET=1;  // Enable SPI

   spiPointer=0;
}


__interrupt void spiaRxIsr(void)//��ʹ��FIFOʱ�������ݣ�������ɣ�����������ô��ж�
{
	if(spiPointer%2==1)
	{
		GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
	}

	SpiaRegs.SPIFFRX.bit.RXFFINTCLR=1;  // Clear Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x20;       // Issue PIE ack
    spiAReadData[spiPointer] = SpiaRegs.SPIRXBUF & 0x00FF;     // Read data

    spiPointer++;
    if(spiPointer==65)
    	spiPointer=40;

  	GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
  	SpiaRegs.SPITXBUF = spiASendData[spiPointer]<<8;     // Send data
}


/***********************************************************************
 no more
 **********************************************************************/