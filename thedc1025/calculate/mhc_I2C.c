///TODO:处理i2c错误下的isMPUavailable设置
///By gjc

#include "mhc.h"
#include "GlobalVariables.h"

void init_I2C_devices()
{
	   // 初始化MPU6050，等每条数据发完再写下一条，i2c出错重新初始化不能用这个
    while( iicWriteByte(MPU6050ADDR,PWR_MGMT_1	, 0x01) != I2C_SUCCESS);
    while( iicWriteByte(MPU6050ADDR,SMPLRT_DIV	, 0x00) != I2C_SUCCESS);
    while( iicWriteByte(MPU6050ADDR,CONFIG 			, 0x00) != I2C_SUCCESS);
    while( iicWriteByte(MPU6050ADDR,GYRO_CONFIG, 0x18) != I2C_SUCCESS);
    while( iicWriteByte(MPU6050ADDR,ACCEL_CONFIG, 0x01) != I2C_SUCCESS);

		// 初始化HMC5883
//	       while( 	iicWriteByte(HMC58X3_ADDR , HMC58X3_R_CONFA , 	0x78) 	!= 	I2C_SUCCESS);
//	       while( 	iicWriteByte(HMC58X3_ADDR , HMC58X3_R_CONFB , 	0x00) 	!= 	I2C_SUCCESS);
//	       while( 	iicWriteByte(HMC58X3_ADDR , HMC58X3_R_MODE , 	0x00) 	!= 	I2C_SUCCESS);

}

void init_I2C_devices_flying()//重新初始化I2C 飞行时I2C出错则调用 初始化不成功则调用iiC_broken
{
	init_I2C_devices();
//	   // 暂时没改,要改
//    while( iicWriteByte(MPU6050ADDR,PWR_MGMT_1	, 0x01) != I2C_SUCCESS);
//    while(i2c_Send_Complete==0);
//    while( iicWriteByte(MPU6050ADDR,SMPLRT_DIV	, 0x00) != I2C_SUCCESS);
//    while(i2c_Send_Complete==0);
//    while( iicWriteByte(MPU6050ADDR,CONFIG 			, 0x00) != I2C_SUCCESS);
//    while(i2c_Send_Complete==0);
//    while( iicWriteByte(MPU6050ADDR,GYRO_CONFIG, 0x18) != I2C_SUCCESS);
//    while(i2c_Send_Complete==0);
//    while( iicWriteByte(MPU6050ADDR,ACCEL_CONFIG, 0x01) != I2C_SUCCESS);
//    while(i2c_Send_Complete==0);
}

void iiC_broken()//I2C配置失败
{
	//处理方式太SB，要改
	while(1)//设置输出为0
	{
		setPwm(1,0);
		setPwm(2,0);
		setPwm(3,0);
		setPwm(4,0);
		setPwm(5,0);
	}
}



__interrupt void i2c_int1a_isr(void)     // I2C-A
{
   Uint16 IntSource = I2caRegs.I2CISRC.all;   // Read interrupt source

   if(IntSource == I2C_SCD_ISRC)   // 有停止位 Interrupt source = stop condition detected
   {
	   switch(i2cStatus)
	   {
	   case 21:// 发送完成If completed message was writing data, reset msg to inactive state
		   i2c_Send_Complete=1;
		   i2cStatus=0;
		   break;

	   case 31:  // If a message receives a NACK during the address setup portion of the
		   // EEPROM read, the code further below included in the register access ready
		   // interrupt source code will generate a stop condition. After the stop
		   // condition is received (here), set the message status to try again.
		   // User may want to limit the number of retries before generating an error.
		   iicStartRead();
		   break;

	   case 32:  // If a message receives a NACK during the address setup portion of the
		   // EEPROM read, the code further below included in the register access ready
		   // interrupt source code will generate a stop condition. After the stop
		   // condition is received (here), set the message status to try again.
		   // User may want to limit the number of retries before generating an error.
//ESTOP0;
		   init_I2C_devices_flying();//可能要改，确实要改
		   break;


	   case 13://收到从设备发来的数据
//	       	  i2cStatus=0;
	       	  i2cData[i2cDataPointer]=I2caRegs.I2CDRR;//把数据从寄存器放到i2c数据数组
	       	  if( (++i2cDataPointer)>13)//如果读完最后一个数，指针回到第一个，加别的设备要改这里和地址，不科学，要改！
	       	  {
	       		  i2cDataPointer=0;
	       	  }
	          I2caRegs.I2CSAR = i2cSlaves[i2cDataPointer];
	          i2cStatus=12;
	          I2caRegs.I2CCNT = 1;
	          I2caRegs.I2CDXR = i2cRegAddr[i2cDataPointer];
	          I2caRegs.I2CMDR.all = 0x2620;			// Send data to setup EEPROM address
	       	  break;
	   }



   }  // end of stop condition detected


   // Interrupt source = Register Access Ready
   // This interrupt is used to determine when the EEPROM address setup portion of the
   // read data communication is complete. Since no stop bit is commanded, this flag
   // tells us when the message has been sent instead of the SCD flag. If a NACK is
   // received, clear the NACK bit and command a stop. Otherwise, move on to the read
   // data portion of the communication.
   else if(IntSource == I2C_ARDY_ISRC)
   {
      if(I2caRegs.I2CSTR.bit.NACK == 1)//处理非应答
      {
//    	  ESTOP0;
         I2caRegs.I2CMDR.bit.STP = 1;
         I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
         if(i2cStatus==12)
        	 i2cStatus=31;
         if(i2cStatus==21)
        	 i2cStatus=32;

      }

      else if(i2cStatus==12)//地址发完了，接收一个数据
      {
    	  I2caRegs.I2CSAR = i2cSlaves[i2cDataPointer];
    	  I2caRegs.I2CCNT = 1;	// Setup how many bytes to expect
    	  I2caRegs.I2CMDR.all = 0x2C20;			// Send restart as master receiver
    	  i2cStatus=13;//正在收数据
      }

   }  // end of register access ready

   PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}


void I2CA_Init(void)
{
   I2caRegs.I2CSAR = MPU6050ADDR	;		// Slave address - EEPROM control code

   I2caRegs.I2CPSC.all = 6;		    // Prescaler - need 7-12 Mhz on module clk
   I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
   I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero
   I2caRegs.I2CIER.all = 0x24;		// Enable SCD & ARDY interrupts

   I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset  // Stop I2C when suspended
   I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,

   return;
}



Uint16 iicWriteByte(Uint16 slaveAddr,Uint16 regAddr,Uint16 data)
{
   // Wait until the STP bit is cleared from any previous master communication. Clearing of this bit by the module is delayed
   //until after the SCD bit is set. If this bit is not checked prior to initiating a new message, the I2C could get confused.
   if (I2caRegs.I2CMDR.bit.STP == 1)
   {
      return I2C_STP_NOT_READY_ERROR;
   }

   if (I2caRegs.I2CSTR.bit.BB == 1)   // Check if bus busy
   {
      return I2C_BUS_BUSY_ERROR;
   }

   I2caRegs.I2CSAR = slaveAddr;   // Setup slave address
   I2caRegs.I2CCNT = 2;// Setup number of bytes to send   // MsgBuffer + Address
   I2caRegs.I2CDXR = regAddr;   // Setup data to send
   I2caRegs.I2CDXR = data;

   i2c_Send_Complete=0;
   i2cStatus=21;
   I2caRegs.I2CMDR.all = 0x6E20;   // Send start as master transmitter
   return I2C_SUCCESS;
}


Uint16 iicStartRead()
{
   if (I2caRegs.I2CMDR.bit.STP == 1)   // Wait until the STP bit is cleared from any previous master communication. Clearing of this bit by the module is delayed until after the SCD bit is set. If this bit is not checked prior to initiating a new message, the I2C could get confused.
   {
      return I2C_STP_NOT_READY_ERROR;
   }
   if (I2caRegs.I2CSTR.bit.BB == 1) // Check if bus busy
   {
      return I2C_BUS_BUSY_ERROR;
   }

   i2cDataPointer=0;
   I2caRegs.I2CSAR = i2cSlaves[i2cDataPointer];
   i2cStatus=12;
   I2caRegs.I2CCNT = 1;
   I2caRegs.I2CDXR = i2cRegAddr[i2cDataPointer];
   I2caRegs.I2CMDR.all = 0x2620;			// Send data to setup EEPROM address
   return I2C_SUCCESS;
}


/***********************************************************************
 no more
 **********************************************************************/
