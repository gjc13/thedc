#include "mhc.h"
#include "GlobalVariables.h"
#include "functions.h"

//正交编码器初始化
void eQEP1Initialize(void)
{
    EQep1Regs.QUPRD=3000000;         		// Unit Timer for 30Hz at 90 MHz SYSCLKOUT
    EQep1Regs.QPOSINIT=EQEP_POS_PRELOAD;	//Set the intitialization preload

    EQep1Regs.QDECCTL.bit.QSRC=00;      // QEP quadrature count mode

    EQep1Regs.QEPCTL.bit.FREE_SOFT=2;
    EQep1Regs.QEPCTL.bit.PCRM=00;       // PCRM=00 mode - QPOSCNT reset on index event
    EQep1Regs.QEPCTL.bit.UTE=1;         // Unit Timeout Enable
    EQep1Regs.QEPCTL.bit.QCLM=1;        // Latch on unit time out
    EQep1Regs.QEPCTL.bit.SWI=1;			// Enable software initialize the position counter
    									// Also initialize the position counter
    EQep1Regs.QEPCTL.bit.SWI=0;
    EQep1Regs.QPOSMAX=0xffffffff;
    EQep1Regs.QEPCTL.bit.QPEN=1;        // QEP enable

    //delete?
    EQep1Regs.QCAPCTL.bit.UPPS=5;       // 1/32 for unit position
    EQep1Regs.QCAPCTL.bit.CCPS=6;       // 1/64 for CAP clock
    EQep1Regs.QCAPCTL.bit.CEN=1;        // QEP Capture Enable


}

void eQEP2Initialize(void)
{
    EQep2Regs.QUPRD=3000000;         // Unit Timer for 30Hz at 90 MHz SYSCLKOUT
    EQep2Regs.QPOSINIT=EQEP_POS_PRELOAD;	//Set the intitialization preload

    EQep2Regs.QDECCTL.bit.QSRC=00;      // QEP quadrature count mode

    EQep2Regs.QEPCTL.bit.FREE_SOFT=2;
    EQep2Regs.QEPCTL.bit.PCRM=00;       // PCRM=00 mode - QPOSCNT reset on index event
    EQep2Regs.QEPCTL.bit.UTE=1;         // Unit Timeout Enable
    EQep2Regs.QEPCTL.bit.QCLM=1;        // Latch on unit time out
    EQep2Regs.QEPCTL.bit.SWI=1;			// Enable software initialize the position counter
    									// Also initialize the position counter
    EQep2Regs.QEPCTL.bit.SWI=0;
    EQep2Regs.QPOSMAX=0xffffffff;
    EQep2Regs.QEPCTL.bit.QPEN=1;        // QEP enable

    //delete?
    EQep2Regs.QCAPCTL.bit.UPPS=5;       // 1/32 for unit position
    EQep2Regs.QCAPCTL.bit.CCPS=6;       // 1/64 for CAP clock
    EQep2Regs.QCAPCTL.bit.CEN=1;        // QEP Capture Enable
}

//正交编码器解析
void eQEP1TickCalculate(void)
{
	if(EQep1Regs.QFLG.bit.UTO==1)
	{
		eQEP1PositionDifference=EQep1Regs.QPOSCNT-EQEP_POS_PRELOAD;
		EQep1Regs.QEPCTL.bit.SWI=1;		//ReIntialize the position counter
		EQep1Regs.QEPCTL.bit.SWI=0;
		EQep1Regs.QCLR.bit.UTO=1;        // Clear interrupt flag
	}
}

void eQEP2TickCalculate(void)
{
	if(EQep2Regs.QFLG.bit.UTO==1)
	{
		eQEP2PositionDifference=EQep2Regs.QPOSCNT-EQEP_POS_PRELOAD;
		EQep2Regs.QEPCTL.bit.SWI=1;		//ReIntialize the position counter
		EQep2Regs.QEPCTL.bit.SWI=0;
		EQep2Regs.QCLR.bit.UTO=1;        // Clear interrupt flag
	}
}
