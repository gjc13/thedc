#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

void InitializeEngine()
{
	targetX=160;
	targetY=160;
	gameFirstStart=1;
	canMove=0;
}

//Uint16 UpdatePosture()
//{
//	float32 dataAngleWeight=0.8;
//	float32 mpuAngleWeight=0.2;
////	float32 nowDataAngle;
//	float32 dataDiffAngle;
//	float32 mpuDiffAngle;
//	float32 diffAngle;
//	Uint16 lastTime=lastUpdatePostureTime;
//	lastUpdatePostureTime=cpuTime;
//	if(abs(gGyro.z)>6*PI)
//	{
//		isMPUavailable=0;
//	}
//	if(!isPlayerDataAvailable && !isMPUavailable)
//	{
//		return 0;
//	}
//	if(isPlayerDataAvailable)
//	{
//		nowX=(playerData_headx+playerData_rearx)/2;
//		nowY=(playerData_heady+playerData_reary)/2;
//		headX=playerData_headx;
//		headY=playerData_heady;
//		rearX=playerData_rearx;
//		rearY=playerData_reary;
//	}
//	nowDataAngle=GetAngle(playerData_rearx,playerData_reary,playerData_headx,playerData_heady);
//	dataDiffAngle=nowDataAngle-nowAngle;
//	if(nowDataAngle>3*PI/2 && nowAngle<PI/2)
//	{
//		dataDiffAngle=dataDiffAngle-2*PI;
//	}
//	else if(nowDataAngle<PI/2 && nowAngle>3*PI/2)
//	{
//		dataDiffAngle=dataDiffAngle+2*PI;
//	}
//	mpuDiffAngle=-gGyro.z*GetSecondTimespan(lastTime,cpuTime);
//
//	//角度互补滤波
//	if(!isPlayerDataAvailable)
//	{
//		diffAngle=mpuDiffAngle;
//	}
//	else if(!isMPUavailable)
//	{
//		diffAngle=dataDiffAngle;
//	}
//	else
//	{
//		diffAngle=dataAngleWeight*dataDiffAngle+mpuAngleWeight*mpuDiffAngle;
//	}
//	if(diffAngle>0.5 || diffAngle<-0.5)
//	{
//		angleDiffIntergration-=diffAngle;
//	}
//	angleDiffIntergration*=0.9;
//	angleDiffIntergration+=diffAngle;
//
//	nowAngle=nowAngle+diffAngle;
//	nowAngle=nowAngle<0?nowAngle+2*PI:nowAngle;
//	nowAngle=nowAngle>2*PI?nowAngle-2*PI:nowAngle;
//
//	//错误处理可能还不完善，加完光流/码盘之后统一改
//	return isPlayerDataAvailable;
//}

Uint16 UpdatePosture()
{
	float32 dataAngleWeight=0.5;
	float32 mpuAngleWeight=0.5;
//	float32 nowDataAngle;
	float32 dataDiffAngle;
	float32 mpuDiffAngle;
	float32 diffAngle;
//	Uint16 lastTime=lastUpdatePostureTime;
	lastUpdatePostureTime=cpuTime;
	if(abs(gGyro.z)>6*PI)
	{
		isMPUavailable=0;
	}
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
	dataDiffAngle=nowDataAngle-nowAngle;
	if(nowDataAngle>3*PI/2 && nowAngle<PI/2)
	{
		dataDiffAngle=dataDiffAngle-2*PI;
	}
	else if(nowDataAngle<PI/2 && nowAngle>3*PI/2)
	{
		dataDiffAngle=dataDiffAngle+2*PI;
	}
	mpuDiffAngle=-gGyro.z*0.0025;

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
	if(diffAngle>0.5 || diffAngle<-0.5)
	{
		angleDiffIntergration-=diffAngle;
	}
	angleDiffIntergration*=0.9;
	angleDiffIntergration+=diffAngle;

	nowAngle=nowAngle+diffAngle;
	nowAngle=nowAngle<0?nowAngle+2*PI:nowAngle;
	nowAngle=nowAngle>2*PI?nowAngle-2*PI:nowAngle;

	isPlayerDataAvailable=0;
	//错误处理可能还不完善，加完光流/码盘之后统一改
	return isPlayerDataAvailable;
}


void SetEngineOutput()
{
	float32 distanceMinBound=5;
	float32 nowDistance=GetDistance(nowX,nowY,targetX,targetY);
	float32 diffAngle=0;
	float32 angleTolerance=PI/12;
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
		RunToTarget();
	}
}

void TurnEngine(float32 targetAngle)
{
	//随便写的参数
	float32 rateP=angleP;
	float32 rateD=IsCounterClockWise(nowAngle,targetAngle)?-angleD:angleD;
	float32 rateI=angleI;

	//TODO test the minPower
	float32 minPower=0.03;
	float32 maxPower=0.18;
	float32 diffAngle=GetDiffAngleAbs(nowAngle,targetAngle);
	diffAngle=diffAngle>PI?2*PI-diffAngle:diffAngle;
	Padjust=0;
	Iadjust=0;
	Dadjust=0;
	if(isMPUavailable && (gGyro.z>-10 && gGyro.z<10))
	{
		Padjust=rateP*diffAngle;
		Dadjust=rateD*gGyro.z;
	}
	else
	{
		//Better to be conservative when MPU fails
		return;
		//Padjust=(rateP*diffAngle)/2;
	}
	Padjust=Padjust<0.3?Padjust:0.3;
	Iadjust=rateI*angleDiffIntergration;
	angleOutPut=Padjust+Iadjust+Dadjust;
	angleOutPut=(angleOutPut>0 && angleOutPut>maxPower)?maxPower:angleOutPut;
	angleOutPut=(angleOutPut>0 && angleOutPut<minPower)?minPower:angleOutPut;
	angleOutPut=(angleOutPut<0 && angleOutPut>-minPower)?-minPower:angleOutPut;
	angleOutPut=(angleOutPut<0 && angleOutPut<-maxPower)?-maxPower:angleOutPut;
	if(angleOutPut>0)
	{
		if(IsCounterClockWise(nowAngle,targetAngle))
		{
			setEngine(ENGINEFRONT,angleOutPut,ENGINEBACK,angleOutPut*0.9);
		}
		else
		{
			setEngine(ENGINEBACK,angleOutPut,ENGINEFRONT,angleOutPut*0.9);
		}
	}
	else
	{
		if(IsCounterClockWise(nowAngle,targetAngle))
		{
			setEngine(ENGINEBACK,angleOutPut,ENGINEFRONT,angleOutPut);
		}
		else
		{
			setEngine(ENGINEFRONT,angleOutPut,ENGINEBACK,angleOutPut);
		}
	}
}

void RunToTarget()
{
	float32 rateP=0.1;
	float32 minPower=0.02;
	float32 distance=GetDistance(nowX,nowY,targetX,targetY);
	float32 outPower=distance*rateP;
	float32 rightOut=0;
//	outPower=outPower>0.05?outPower:0.05;
//	rightOut=outPower*0.7;
//	rightOut+=minPower;
//	outPower+=minPower;
//	setEngine(ENGINEFRONT,outPower,ENGINEFRONT,rightOut);
	outPower=outPower>0.16?0.16:outPower;
	rightOut=outPower*0.8;
	outPower+=minPower;
	rightOut+=minPower;
	setEngine(ENGINEFRONT,outPower,ENGINEFRONT,rightOut);
}

void DisableEngineOutput()
{
	setEngine(ENGINESTOP,0,ENGINESTOP,0);
}

