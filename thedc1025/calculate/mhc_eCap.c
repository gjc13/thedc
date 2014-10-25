#include "mhc.h"
#include "GlobalVariables.h"

/*****************************************************************
 *！！！！！！！！！！！！！！各通道输出定义不同！！！！！！！！！！！！！！！！！！
 */

void InitECapture()
{
	//ECAP1
   ECap1Regs.ECEINT.all = 0x0000;             // Disable all capture interrupts
   ECap1Regs.ECCLR.all = 0xFFFF;              // Clear all CAP interrupt flags
   ECap1Regs.ECCTL1.bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped
   // Configure peripheral registers
   ECap1Regs.ECCTL2.bit.CONT_ONESHT = 1;      // One-shot
   ECap1Regs.ECCTL2.bit.STOP_WRAP = 3;        // Stop at 4 events
   ECap1Regs.ECCTL1.bit.CAP1POL = 0;          // Rising edge
   ECap1Regs.ECCTL1.bit.CAP2POL = 1;          // Falling edge
   ECap1Regs.ECCTL1.bit.CTRRST1 = 1;          // Difference operation
   ECap1Regs.ECCTL1.bit.CTRRST2 = 1;          // Difference operation
   ECap1Regs.ECCTL2.bit.SYNCI_EN = 1;         // Enable sync in
   ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;        // Pass through
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable capture units

   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;        // Start Counter
   ECap1Regs.ECCTL2.bit.REARM = 1;            // arm one-shot
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
   ECap1Regs.ECEINT.bit.CEVT2 = 1;            // 2 events = interrupt

//
//   //ECAP2
//   ECap2Regs.ECEINT.all = 0x0000;
//   ECap2Regs.ECCLR.all = 0xFFFF;
//   ECap2Regs.ECCTL1.bit.CAPLDEN = 0;
//   ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0;
//
//   ECap2Regs.ECCTL2.bit.CONT_ONESHT = 1;
//   ECap2Regs.ECCTL2.bit.STOP_WRAP = 3;
//   ECap2Regs.ECCTL1.bit.CAP1POL = 1;
//   ECap2Regs.ECCTL1.bit.CAP2POL = 0;
//   ECap2Regs.ECCTL1.bit.CTRRST1 = 1;
//   ECap2Regs.ECCTL1.bit.CTRRST2 = 1;
//   ECap2Regs.ECCTL2.bit.SYNCI_EN = 1;
//   ECap2Regs.ECCTL2.bit.SYNCO_SEL = 0;
//   ECap2Regs.ECCTL1.bit.CAPLDEN = 1;
//
//   ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;
//   ECap2Regs.ECCTL2.bit.REARM = 1;
//   ECap2Regs.ECCTL1.bit.CAPLDEN = 1;
//   ECap2Regs.ECEINT.bit.CEVT2 = 1;
//
//
//   //ECAP3
//   ECap3Regs.ECEINT.all = 0x0000;
//   ECap3Regs.ECCLR.all = 0xFFFF;
//   ECap3Regs.ECCTL1.bit.CAPLDEN = 0;
//   ECap3Regs.ECCTL2.bit.TSCTRSTOP = 0;
//
//   ECap3Regs.ECCTL2.bit.CONT_ONESHT = 1;
//   ECap3Regs.ECCTL2.bit.STOP_WRAP = 3;
//   ECap3Regs.ECCTL1.bit.CAP1POL = 1;
//   ECap3Regs.ECCTL1.bit.CAP2POL = 0;
//   ECap3Regs.ECCTL1.bit.CTRRST1 = 1;
//   ECap3Regs.ECCTL1.bit.CTRRST2 = 1;
//   ECap3Regs.ECCTL2.bit.SYNCI_EN = 1;
//   ECap3Regs.ECCTL2.bit.SYNCO_SEL = 0;
//   ECap3Regs.ECCTL1.bit.CAPLDEN = 1;
//
//   ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1;
//   ECap3Regs.ECCTL2.bit.REARM = 1;
//   ECap3Regs.ECCTL1.bit.CAPLDEN = 1;
//   ECap3Regs.ECEINT.bit.CEVT2 = 1;
}

__interrupt void ecap1_isr(void)//油门
{
//	float32 t = ECap1Regs.CAP1/4521.7;
//	if( t > 3 && t < 500 )
//	{
//		height_ultrasonic = t ;
//		low_pass(&height_ultrasonic_lp , t , G_height_ultrasonic_lp , 0.05);
//	}
	float32  t = ECap1Regs.CAP2/1000;
//	if( t < 4000000 )
	{
		eCapData[0]=t ;
	}

	ECap1Regs.ECCLR.bit.CEVT2 = 1;
	ECap1Regs.ECCLR.bit.INT = 1;
	ECap1Regs.ECCTL2.bit.REARM = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
}

//__interrupt void ecap2_isr(void)//横滚
//{
//	Uint32 t = ECap2Regs.CAP1;
//		if( t < 72500 )
//			ecapData[1] = -100 ;
//		else if( t > 208580 )
//			ecapData[1] = -200 ;
//		else
//		{
//			if( t < 90687 )
//				t = 90687 ;
//			if( t >181375 )
//				t = 181375 ;
//			ecapData[1] =1999.9-0.011026938811517 * t  ;
//
//		}
//	ECap2Regs.ECCLR.bit.CEVT2 = 1;
//	ECap2Regs.ECCLR.bit.INT = 1;
//	ECap2Regs.ECCTL2.bit.REARM = 1;
//	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
//}
//
//__interrupt void ecap3_isr(void)//俯仰
//{
//	Uint32 t = ECap3Regs.CAP1;
//		if( t < 72500 )
//			ecapData[2] = -100 ;
//		else if( t > 208580 )
//			ecapData[2] = -200 ;
//		else
//		{
//			if( t < 90687 )
//				t = 90687 ;
//			if( t >181375 )
//				t = 181375 ;
//			ecapData[2] = 1999.9-0.011026938811517 * t  ;
//
//		}
//
//	ECap3Regs.ECCLR.bit.CEVT2 = 1;
//	ECap3Regs.ECCLR.bit.INT = 1;
//	ECap3Regs.ECCTL2.bit.REARM = 1;
//	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
//}


