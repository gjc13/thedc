#include "GlobalVariables.h"
#include "functions.h"
#include "mhc.h"

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
