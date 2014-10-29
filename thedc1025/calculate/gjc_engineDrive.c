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

float32 GetDistance(int32 fromx,int32 fromy,int32 tox,int32 toy)
{
	int32 deltaX=fromx-tox;
	int32 deltaY=fromy-toy;
	return sqrt(deltaX*deltaX+deltaY*deltaY);
}

float32 GetAngle(int32 fromx,int32 fromy,int32 tox,int32 toy)
{
	int32 deltaX=tox-fromx;
	int32 deltaY=toy-fromy;
	float32 distance=GetDistance(fromx,fromy,tox,toy);
	if(deltaY>0)
	{
		return acos(deltaX/distance);
	}
	else
	{
		return acos(deltaX/distance)+2*PI;
	}
}

float32 GetDiffAngle(float32 fromAngle,float32 toAngle)
{
	float32 diffAngle=toAngle-fromAngle;
	diffAngle=diffAngle<0?diffAngle+2*PI:diffAngle;
	diffAngle=(2*PI-diffAngle < diffAngle)?2*PI-diffAngle:diffAngle;
	return diffAngle;
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
	int32 i,j;
	Uint16 playerID=sciAReadBuffer[0];
	Uint16 *iter=(void *)(&playerData);
	Uint16 *iterBuffer=sciAReadBuffer;
	(*iter)=*iterBuffer;
	iter++;
	iterBuffer++;
	for(i=0; i<4; i++)
	{
		if(i==playerID && (abs(*iterBuffer-playerData_headx)<10||gameFirstStart))
		{
			gameFirstStart=0;
			playerData_headx=*(iterBuffer);
			playerData_heady=*(iterBuffer+1);
			playerData_rearx=*(iterBuffer+2);
			playerData_reary=*(iterBuffer+3);
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
	for(i=0; i<26; i++)
	{
		sciAReadBuffer[i]=0;
	}
	canMove=playerData.is_running && playerData.time>5;
	if(playerData.time<=1)
	{
		canMove=0;
		gameFirstStart=1;
	}
}

Uint16 UpdatePosture()
{
	Uint16 isSuccess=1;
	nowX=(playerData_headx+playerData_rearx)/2;
	nowY=(playerData_heady+playerData_reary)/2;
	headX=playerData_headx;
	headY=playerData_heady;
	rearX=playerData_rearx;
	rearY=playerData_reary;
	if(GetDistance(rearX,rearY,headX,headY)>=1)
	{
		nowAngle=GetAngle(rearX,rearY,headX,headY);
	}
	else
	{
		isSuccess=0;
	}
	return isSuccess;
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
	diffAngle=GetDiffAngle(nowAngle,targetAngle);
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
	float32 rateP=0.6;
	float32 startPAngle=PI/10;
	float32 minPower=0.1;
	float32 diffAngle=GetDiffAngle(nowAngle,targetAngle);
	float32 outPower=diffAngle<startPAngle?rateP*diffAngle:0.2;
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
