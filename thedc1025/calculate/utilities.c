#include "functions.h"
#include "mhc.h"

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
	if(deltaY>=0)
	{
		return acos(deltaX/distance);
	}
	else
	{
		return 2*PI-acos(deltaX/distance);
	}
}

float32 GetDiffAngleAbs(float32 fromAngle,float32 toAngle)
{
	float32 diffAngle=toAngle-fromAngle;
	diffAngle=diffAngle<0?diffAngle+2*PI:diffAngle;
	diffAngle=diffAngle>2*PI?diffAngle-2*PI:diffAngle;
	diffAngle=(2*PI-diffAngle < diffAngle)?2*PI-diffAngle:diffAngle;
	return diffAngle;
}

float32 GetDiffAngle(float32 fromAngle,float32 toAngle)
{
	float32 diffAngle=GetDiffAngleAbs(fromAngle,toAngle);
	return IsCounterClockWise(fromAngle,toAngle)?-diffAngle:diffAngle;
}

int16 IsCounterClockWise(float32 fromAngle,float32 toAngle)
{
	float32 fromX=cos(fromAngle);
	float32 fromY=sin(fromAngle);
	float32 toX=cos(toAngle);
	float32 toY=cos(toAngle);
	return toY*fromX-toX*fromY>0;
}


float32 GetSecondTimespan(Uint16 cpuTimeFrom,Uint16 cpuTimeTo)
{
	int32 timeFrom=cpuTimeFrom;
	int32 timeTo=cpuTimeTo;
	int32 cpuSpan=timeFrom<=timeTo?timeTo-timeFrom:timeTo+60000-timeFrom;
	return (float32)cpuSpan*2.5/1000;
}

Uint16 ShouldReverseTurn(float32 fromAngle,float32 toAngle)
{
	return GetDiffAngleAbs(fromAngle,toAngle)>PI/2;
}
