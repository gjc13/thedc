#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

float32 GetDistance(int32 fromx,int32 fromy,int32 tox,int32 toy)
{
	int32 deltaX=fromx-tox;
	int32 deltaY=fromy-toy;
	return sqrt(deltaX*deltaX+deltaY*deltaY);
}

float32 GetAngle(int32 fromx,int32 fromy,int32 tox,int32 toy)
{
	int32 deltaX=fromx-tox;
	int32 deltaY=fromy-toy;
	int32 distance=GetDistance(fromx,fromy,tox,toy);
	if(deltaY>0)
	{
		return acos(deltaX/distance);
	}
	else
	{
		return acos(deltaX/distance)+PI;
	}
}

float32 GetDiffAngle(float32 fromAngle,float32 toAngle)
{
	float32 diffAngle=fromAngle-toAngle;
	diffAngle=diffAngle<0?-diffAngle:0;
	diffAngle=(360-diffAngle < diffAngle)?360-diffAngle:diffAngle;
	return diffAngle;//这行是马浩程10.27.16:46加的
}

int16 IsCounterClockWise(float32 fromAngle,float32 toAngle)
{
	float32 fromX=cos(fromAngle);
	float32 fromY=sin(fromAngle);
	float32 toX=cos(toAngle);
	float32 toY=cos(toAngle);
	return toY*fromX-toX*fromY>0;
}

Uint16 ShouldDecodeData()
{
	if(sciAReadBufferPointer==PLAYERDATALENGTH)
	{
		return sciAReadBuffer[PLAYERDATALENGTH-1]==0x0A && sciAReadBuffer[PLAYERDATALENGTH-2] == 0x0D ;
	}
	return 0;
}

void DecodePlayerData()
{
	int i,j;
	Uint16 playerID=sciAReadBuffer[0];
	Uint16 *iter=(void *)(&playerData);
	Uint16 *iterBuffer=sciAReadBuffer;
	(*iter)=*iterBuffer;
	iter++;
	iterBuffer++;
	for(i=1; i<=4; i++)
	{
		if(i==playerID)
		{
			playerData_headx=*(iterBuffer);
			playerData_heady=*(iterBuffer+1);
			playerData_rearx=*(iterBuffer+2);
			playerData_reary=*(iterBuffer+3);
			nowAngle=GetAngle(playerData_headx,playerData_rearx,playerData_heady,playerData_reary);
			nowX=(playerData_headx+playerData_rearx)/2;
			nowY=(playerData_heady+playerData_reary)/2;
			nowScore=*(iterBuffer+4);
		}
		for(j=0; j<5; j++)
		{
			(*iter)=(*iterBuffer);
			iter++;
			iterBuffer++;
		}
	}
	for(i=0; i<4; i++)
	{
		(*iter)=(((*iterBuffer)>>i)&(0x01));
		iter++;
	}
	iterBuffer++;
	for(i=0; i<2; i++)
	{
		(*iter)=(*iterBuffer);
		iter++;
		iterBuffer++;
	}
}

void SetEngineOutPut()
{
	float32 distanceMinBound=10,angleTolerance=PI/30,targetAngle,diffAngle;
	float32 nowDistance=GetDistance(nowX,nowY,targetX,targetY);
	if(nowDistance<distanceMinBound)
	{
		return;
	}
	angleTolerance=nowDistance>distanceMinBound?angleTolerance:angleTolerance*2;
	targetAngle=GetAngle(nowX,nowY,targetX,targetY);
	diffAngle=GetDiffAngle(nowAngle,targetAngle);
	if(GetDiffAngle(nowAngle,targetAngle)>PI/9)
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
	float32 rateP=1;
	float32 startPAngle=PI/10;
	float32 minPower=0.2;
	float32 diffAngle=GetDiffAngle(nowAngle,targetAngle);
	float32 outPower=diffAngle<startPAngle?rateP*diffAngle:0.6;
	outPower=+minPower;
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
	float32 rateP=0.05;
	float32 startPDistance=16;
	float32 minPower=0.2;
	float32 distance=GetDistance(nowX,nowY,targetX,targetY);
	float32 outPower=distance>startPDistance?rateP*distance:0.6;
	outPower+=minPower;
	setEngine(ENGINEFRONT,outPower,ENGINEFRONT,outPower);
}

