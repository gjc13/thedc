#include "mhc.h"
#include "GlobalVariables.h"


void InitEPwm1Example()
{

   EPwm1Regs.TBPRD = PWM_PERIOD;                        // Set timer period
   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm1Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;

   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   EPwm1Regs.CMPA.half.CMPA = 2880;

   // Set actions
   EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on CAU
   EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;			  // Clear PWM1A on CAD


   EPwm1Regs.AQCTLB.bit.CAU = AQ_SET;           // Clear PWM1B on CAU
   EPwm1Regs.AQCTLB.bit.CAD = AQ_CLEAR;             // Set PWM1B on CAD

   // Active Low PWMs - Setup Deadband
   EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
   EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
}


void InitEPwm2Example()
{

   EPwm2Regs.TBPRD = PWM_PERIOD;                        // Set timer period
   EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;

   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   EPwm2Regs.CMPA.half.CMPA = 2880;

   // Set actions
   EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;             // Set Pwm2A on CAU
   EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;			  // Clear Pwm2A on CAD


   EPwm2Regs.AQCTLB.bit.CAU = AQ_SET;           // Clear Pwm2B on CAU
   EPwm2Regs.AQCTLB.bit.CAD = AQ_CLEAR;             // Set Pwm2B on CAD

   // Active Low PWMs - Setup Deadband
   EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
   EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;

}

void InitEPwm3Example()
{

   EPwm3Regs.TBPRD = PWM_PERIOD;                        // Set timer period
   EPwm3Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm3Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV4;

   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   EPwm3Regs.CMPA.half.CMPA = 2880;

   // Set actions
   EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;             // Set Pwm3A on CAU
   EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;			  // Clear Pwm3A on CAD


   EPwm3Regs.AQCTLB.bit.CAU = AQ_SET;           // Clear Pwm3B on CAU
   EPwm3Regs.AQCTLB.bit.CAD = AQ_CLEAR;             // Set Pwm3B on CAD

   // Active Low PWMs - Setup Deadband
   EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
   EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;

}

void InitEPwm4Example()
{

   EPwm4Regs.TBPRD = PWM_PERIOD;                        // Set timer period
   EPwm4Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm4Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
   EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV4;

   EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   EPwm4Regs.CMPA.half.CMPA = 2880;

   // Set actions
   EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;             // Set Pwm4A on CAU
   EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;			  // Clear Pwm4A on CAD


   EPwm4Regs.AQCTLB.bit.CAU = AQ_SET;           // Clear Pwm4B on CAU
   EPwm4Regs.AQCTLB.bit.CAD = AQ_CLEAR;             // Set Pwm4B on CAD

   // Active Low PWMs - Setup Deadband
   EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
   EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;

}


void InitEPwm5Example()
{

   EPwm5Regs.TBPRD = PWM_PERIOD;                        // Set timer period
   EPwm5Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm5Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
   EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV4;

   EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   EPwm5Regs.CMPA.half.CMPA = 2880;

   // Set actions
   EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;             // Set Pwm5A on CAU
   EPwm5Regs.AQCTLA.bit.CAD = AQ_CLEAR;			  // Clear Pwm5A on CAD


   EPwm5Regs.AQCTLB.bit.CAU = AQ_SET;           // Clear Pwm5B on CAU
   EPwm5Regs.AQCTLB.bit.CAD = AQ_CLEAR;             // Set Pwm5B on CAD

   // Active Low PWMs - Setup Deadband
   EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
   EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;
}


void setPwm(Uint16 pwmNum,float32 pwmValue)
{
	switch(pwmNum)
	{
	case 1:   EPwm1Regs.CMPA.half.CMPA = (Uint16)(PWM_PERIOD*pwmValue);break;
	case 2:   EPwm2Regs.CMPA.half.CMPA = (Uint16)(PWM_PERIOD*pwmValue);break;
	case 3:   EPwm3Regs.CMPA.half.CMPA = (Uint16)(PWM_PERIOD*pwmValue);break;
	case 4:   EPwm4Regs.CMPA.half.CMPA = (Uint16)(PWM_PERIOD*pwmValue);break;
	case 5:   EPwm5Regs.CMPA.half.CMPA = (Uint16)(PWM_PERIOD*pwmValue);break;
	}
}



