#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

void InitializeEngine()
{
	targetX=120;
	targetY=120;
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
	mpuDiffAngle=angleRatez*GetSecondTimespan(playerData_lastRecieveCPUTime,cpuTime);

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
	nowAngle=nowAngle+diffAngle;
	nowAngle=nowAngle<0?nowAngle+2*PI:nowAngle;
	nowAngle=nowAngle>2*PI?nowAngle-2*PI:nowAngle;

	//错误处理可能还不完善，加完光流/码盘之后统一改
	return isPlayerDataAvailable;
}

void SetEngineOutput()
{
	float32 distanceMinBound=10;
	float32 nowDistance=GetDistance(nowX,nowY,targetX,targetY);
	float32 targetAngle=0;
	float32 diffAngle=0;
	float32 angleTolerance=PI/30;
	if(nowDistance<distanceMinBound)
	{
		return;
	}
	targetAngle=GetAngle(nowX,nowY,targetX,targetY);
	diffAngle=GetDiffAngleAbs(nowAngle,targetAngle);
	angleTolerance=nowDistance>distanceMinBound?angleTolerance:angleTolerance*2;
	if(diffAngle>PI/9)
	{
		TurnEngine(targetAngle);
	}
	else
	{
		RunToTarget();
	}
}

void TurnEngine(float32 targetAngle)
{
	//随便写的参数
	float32 rateP=0.3;
	float32 rateD=0.2;
	float32 startPAngle=PI/10;

	//TODO test the minPower
	float32 minPower=0.01;
	float32 diffAngle=GetDiffAngleAbs(nowAngle,targetAngle);
	float32 outPower=0.1;
	if(diffAngle<startPAngle)
	{
		if(isMPUavailable)
		{
			outPower=rateP*diffAngle+rateD*angleRatez;
		}
		else
		{
			//Better to be conservative when MPU fails
			outPower=(rateP*diffAngle)/2;
		}
	}
	outPower+=minPower;
	if(IsCounterClockWise(nowAngle,targetAngle))
	{
		setEngine(ENGINEBACK,outPower,ENGINEFRONT,outPower);
	}
	else
	{
		setEngine(ENGINEFRONT,outPower,ENGINEBACK,outPower);
	}
}

void RunToTarget()
{
	float32 rateP=0.0125;
	float32 startPDistance=16;
	float32 minPower=0.1;
	float32 distance=GetDistance(nowX,nowY,targetX,targetY);
	float32 outPower=distance>startPDistance?rateP*distance:0.2;
	outPower+=minPower;
	setEngine(ENGINEFRONT,outPower,ENGINEFRONT,outPower);
}

void DisableEngineOutput()
{
	setEngine(ENGINESTOP,0,ENGINESTOP,0);
}

