#include "mhc.h"
#include "GlobalVariables.h"
#include "functions.h"

Uint16 ShouldDecodePlayerData()
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
		if(i==playerID /*&& (abs(*iterBuffer-playerData_headx)<10||gameFirstStart) */)
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
	isPlayerDataAvailable=!(GetDistance(playerData_rearx,playerData_reary,playerData_headx,playerData_heady)<1);
	canMove=playerData.is_running && playerData.time>1;
	if(isPlayerDataAvailable)
	{
		playerData_lastRecieveCPUTime=cpuTime;
	}
	if(playerData.time<=1)
	{
		canMove=0;
		gameFirstStart=1;
	}
}
