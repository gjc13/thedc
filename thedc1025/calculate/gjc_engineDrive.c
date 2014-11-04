#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

void InitializeEngine()
{
	targetX=204;
	targetY=185;
	gameFirstStart=1;
	canMove=0;
}

Uint16 UpdatePosture()
{
	float32 dataAngleWeight=0.5;
	float32 mpuAngleWeight=0.5;
	float32 nowDataAngle;
	float32 dataDiffAngle;
	float32 mpuDiffAngle;
	float32 diffAngle;
	if(!isPlayerDataAvailable && !isMPUavailable)
	{
		return 0;
	}
	if(isPlayerDataAvailable)
	{
		nowX=(playerData_headx+playerData_rearx)/2;
		nowY=(playerData_heady+playerData_reary)/2;
		headX=playerData_headx;
		headY=playerData_heady;
		rearX=playerData_rearx;
		rearY=playerData_reary;
	}
	nowDataAngle=GetAngle(playerData_rearx,playerData_reary,playerData_headx,playerData_heady);
	dataDiffAngle=GetDiffAngle(nowAngle,nowDataAngle);
	mpuDiffAngle=gGyro.z*GetSecondTimespan(playerData_lastRecieveCPUTime,cpuTime);

	//角度互补滤波
	if(!isPlayerDataAvailable)
	{
		diffAngle=mpuDiffAngle;
	}
	else if(!isMPUavailable)
	{
		diffAngle=dataDiffAngle;
	}
	else
	{
		diffAngle=dataAngleWeight*dataDiffAngle+mpuAngleWeight*mpuDiffAngle;
	}
	angleDiffIntergration*=0.9;
	angleDiffIntergration+=diffAngle;

	nowAngle=nowAngle+diffAngle;
	nowAngle=nowAngle<0?nowAngle+2*PI:nowAngle;
	nowAngle=nowAngle>2*PI?nowAngle-2*PI:nowAngle;

	//错误处理可能还不完善，加完光流/码盘之后统一改
	return isPlayerDataAvailable;
}

void SetEngineOutput()
{
	float32 distanceMinBound=5;
	float32 nowDistance=GetDistance(nowX,nowY,targetX,targetY);
	float32 diffAngle=0;
	float32 angleTolerance=PI/25;
	if(nowDistance<distanceMinBound)
	{
		DisableEngineOutput();
		return;
	}
	targetAngle=GetAngle(nowX,nowY,targetX,targetY);
	diffAngle=GetDiffAngleAbs(nowAngle,targetAngle);
	angleTolerance=nowDistance>distanceMinBound?angleTolerance:angleTolerance*2;
	if(diffAngle>angleTolerance)
	{
		TurnEngine(targetAngle);
	}
	else
	{
		//RunToTarget();
	}
}

void TurnEngine(float32 targetAngle)
{
	//随便写的参数
	float32 rateP=angleP;
	float32 rateD=IsCounterClockWise(nowAngle,targetAngle)?-angleD:angleD;
	float32 rateI=angleI;
	float32 startPAngle=PI/3;

	//TODO test the minPower
	float32 minPower=0;
	float32 diffAngle=GetDiffAngleAbs(nowAngle,targetAngle);
	if(diffAngle<startPAngle)
	{
		if(isMPUavailable)
		{
			Padjust=rateP*diffAngle;
			Dadjust=rateD*gGyro.z;
		}
		else
		{
			//Better to be conservative when MPU fails
			Padjust=(rateP*diffAngle)/2;
		}
	}
	Padjust=Padjust<0.3?Padjust:0.3;
	Iadjust=rateI*angleDiffIntergration;
	angleOutPut=Padjust+Iadjust+Dadjust;
	angleOutPut=angleOutPut>1?1:angleOutPut;
	angleOutPut=angleOutPut<minPower?minPower:angleOutPut;
	if(IsCounterClockWise(nowAngle,targetAngle) && diffAngle<PI*0.9)
	{
		setEngine(ENGINEFRONT,angleOutPut,ENGINEBACK,angleOutPut);
	}
	else
	{
		setEngine(ENGINEBACK,angleOutPut,ENGINEFRONT,angleOutPut);
	}
}

void RunToTarget()
{
	float32 rateP=0.005;
	float32 startPDistance=30;
	float32 minPower=0.03;
	float32 distance=GetDistance(nowX,nowY,targetX,targetY);
	float32 outPower=distance>startPDistance?rateP*distance:0.2;
	outPower+=minPower;
	setEngine(ENGINEFRONT,outPower,ENGINEFRONT,outPower);
}

void DisableEngineOutput()
{
	setEngine(ENGINESTOP,0,ENGINESTOP,0);
}

