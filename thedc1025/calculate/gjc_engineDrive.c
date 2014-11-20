#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

void InitializeEngine()
{
	DisableEngineOutput();
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
//	//�ǶȻ����˲�
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
//	//��������ܻ������ƣ��������/����֮��ͳһ��
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
	if(!newDataReceive && !isMPUavailable)
	{
		return 0;
	}
	if(newDataReceive)
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

	//�ǶȻ����˲�
	if(!newDataReceive)
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

	newDataReceive=0;
	//��������ܻ������ƣ��������/����֮��ͳһ��
	return newDataReceive;
}


void SetEngineOutput()
{
	float32 distanceMinBound=5;
	float32 diffAngle=0;
	float32 angleTolerance=PI/12;
	if(moveStatus==PEND)
	{
		DisableEngineOutput();
		SeekNextTarget();
	}
	else if(moveStatus==WAITPOINT || playerData.time>239)
	{
		DisableEngineOutput();
		return;
	}
	nowDistance=GetDistance(nowX,nowY,targetX,targetY);
	if(nowDistance<distanceMinBound && moveStatus==SEEK)
	{
		DisableEngineOutput();
		if(IsPointedLoc(nowX,nowY))
		{
			StartWaitPoint();
			return;
		}
		else
		{
			DisableEngineOutput();
			moveStatus=PEND;
		}
		return;
	}
	targetRunAngle=GetAngle(nowX,nowY,targetX,targetY);
	if(ShouldReverseTurn(nowAngle,targetRunAngle))
	{
		targetHeadAngle=targetRunAngle+PI;
		targetHeadAngle=targetHeadAngle>2*PI?targetHeadAngle-2*PI:targetHeadAngle;
	}
	else
	{
		targetHeadAngle=targetRunAngle;
	}
	diffAngle=GetDiffAngleAbs(nowAngle,targetHeadAngle);
	angleTolerance=nowDistance>distanceMinBound?angleTolerance:angleTolerance*2;
	if(diffAngle>angleTolerance && abs(PI-diffAngle)>angleTolerance)
	{
		TurnEngine(targetHeadAngle);
	}
	else if(HasObstacle())
	{
		DisableEngineOutput();
		moveStatus=PEND;
		return;
	}
	else
	{
//		if(diffAngle>angleTolerance && abs(PI-diffAngle)>angleTolerance)
//		{
//			RunAndTurn();
//		}
//		else
//		{
//			RunToTarget();
//		}
		RunToTarget();
	}
}

void TurnEngine(float32 targetAngle)
{
	float32 rateP=angleP;
	float32 rateD=IsCounterClockWise(nowAngle,targetAngle)?-angleD:angleD;
	float32 rateI=angleI;
	float32 minPower=0.05;
	float32 maxPower=0.18;
	float32 diffAngle=GetDiffAngleAbs(nowAngle,targetAngle);
	if(moveStatus==PEND)
	{
		DisableEngineOutput();
		return;
	}
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
		DisableEngineOutput();
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
	direction=TURN;
	if(angleOutPut>0)
	{
		if(IsCounterClockWise(nowAngle,targetAngle))
		{
			if(HasBackObstacle())
			{
				setEngine(ENGINEFRONT,angleOutPut*1.2,ENGINEBACK,0);
			}
			if(HasFrontObstacle())
			{
				setEngine(ENGINEFRONT,0,ENGINEBACK,angleOutPut*1.2);
			}
			else
			{
				setEngine(ENGINEFRONT,angleOutPut*1.2,ENGINEBACK,angleOutPut*1.2);
			}
		}
		else
		{
			if(HasBackObstacle())
			{
				setEngine(ENGINEBACK,0,ENGINEFRONT,angleOutPut*1.2);
			}
			else if(HasFrontObstacle())
			{
				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,0);
			}
			else
			{
				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,angleOutPut*1.2);
			}
		}
	}
	else
	{
		angleOutPut=-angleOutPut;
		if(IsCounterClockWise(nowAngle,targetAngle))
		{
			if(HasBackObstacle())
			{
				setEngine(ENGINEBACK,0,ENGINEFRONT,angleOutPut*1.2);
			}
			else if(HasFrontObstacle())
			{
				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,0);
			}
			else
			{
				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,angleOutPut*1.2);
			}
		}
		else
		{
			if(HasBackObstacle())
			{
				setEngine(ENGINEBACK,0,ENGINEFRONT,angleOutPut*1.2);
			}
			else if(HasFrontObstacle())
			{
				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,0);
			}
			else
			{
				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,angleOutPut*1.2);
			}
		}
	}
}

void RunToTarget()
{
	float32 rateP=0.1;
	float32 minPower=0.03;
	float32 distance=GetDistance(nowX,nowY,targetX,targetY);
	float32 outPower=distance*rateP;
	float32 rightOut=0;
//	outPower=outPower>0.05?outPower:0.05;
//	rightOut=outPower*0.7;
//	rightOut+=minPower;
//	outPower+=minPower;
//	setEngine(ENGINEFRONT,outPower,ENGINEFRONT,rightOut);
	if(moveStatus==PEND)
	{
		DisableEngineOutput();
		return;
	}
	outPower=outPower>0.16?0.16:outPower;
	rightOut=outPower;
	outPower+=minPower;
	rightOut+=minPower;
	if(GetDiffAngleAbs(nowAngle,targetRunAngle)<PI/2)
	{
		direction=FRONT;
		if(direction!=nowDirection)
		{
			nowDirection=direction;
		}
		outPower=outPower>0.05?0.05:outPower;
		rightOut=rightOut>0.05?0.05:rightOut;
		setEngine(ENGINEFRONT,outPower,ENGINEFRONT,rightOut);
	}
	else
	{
		direction=BACK;
		if(direction!=nowDirection)
		{
			nowDirection=direction;
		}
		outPower+=0.04;
		rightOut+=0.04;
		setEngine(ENGINEBACK,outPower,ENGINEBACK,rightOut);
	}
}

void RunAndTurn()
{
	float32 rateAngleP=angleP;
	float32 diffAngle=GetDiffAngleAbs(nowAngle,targetHeadAngle);
	float32 rateDistanceP=0.1;
	float32 minPower=0.03;
	float32 distance=GetDistance(nowX,nowY,targetX,targetY);
	float32 outPower=0;
	Padjust=0;
	if(moveStatus==PEND)
	{
		DisableEngineOutput();
		return;
	}
	if(isMPUavailable && (gGyro.z>-10 && gGyro.z<10))
	{
		Padjust=rateAngleP*diffAngle;
	}
	else
	{
		//Better to be conservative when MPU fails
		DisableEngineOutput();
		return;
		//Padjust=(rateP*diffAngle)/2;
	}
	Padjust=Padjust<0.3?Padjust:0.3;
	angleOutPut=Padjust;
	angleOutPut=angleOutPut>0.05?0.05:angleOutPut;
	angleOutPut=angleOutPut<0.01?0.01:angleOutPut;

	outPower=distance*rateDistanceP;
	outPower=outPower>0.16?0.16:outPower;
	outPower+=minPower;
	if(GetDiffAngleAbs(nowAngle,targetRunAngle)<PI/2)
	{
		direction=FRONT;
		if(IsCounterClockWise(nowAngle,targetHeadAngle))
		{
			setEngine(ENGINEFRONT,outPower-angleOutPut,ENGINEFRONT,outPower+angleOutPut);
		}
		else
		{
			setEngine(ENGINEFRONT,outPower+angleOutPut,ENGINEFRONT,outPower-angleOutPut);
		}
	}
	else
	{
		direction=BACK;
		if(IsCounterClockWise(nowAngle,targetHeadAngle))
		{
			setEngine(ENGINEBACK,outPower+angleOutPut,ENGINEBACK,outPower-angleOutPut);
		}
		else
		{
			setEngine(ENGINEBACK,outPower-angleOutPut,ENGINEBACK,outPower+angleOutPut);
		}
	}
}

void DisableEngineOutput()
{
	setEngine(ENGINESTOP,0,ENGINESTOP,0);
	direction=STOP;
}

void SeekNextTarget()
{
	Uint16 xIndex=nowX<lowerXLimit?0:1;
	Uint16 yIndex=nowY<lowerYLimit?0:1;
	if(lockTurnTime>0)
	{
		return;
	}
	targetX=allTargetX[xIndex][yIndex];
	targetY=allTargetY[xIndex][yIndex];
	moveStatus=SEEK;
	lockTurnTime=500;
}

void StartWaitPoint()
{
	waitingTime=0;
	moveStatus=WAITPOINT;
	nowDirection=STOP;
	DisableEngineOutput();
}


//�������ó����ж��Ƿ��п�
Uint16 HasObstacle()
{
	//���Ƿ�ǰ���пӴ�HasObstacle����
	//�ƶ������directionö������
	//�пӷ���TRUE
	if(lockTurnTime>0)
	{
		return 0;
	}
	return (direction==FRONT) ? (foundHeadObstacleTime>3) : (foundTailObstacleTime>3);
}

Uint16 HasFrontObstacle()
{
	return foundHeadObstacleTime>3;
}

Uint16 HasBackObstacle()
{
	return foundTailObstacleTime>3;
}


Uint16 IsPointedLoc(Uint16 locx,Uint16 locy)
{
	return GetDistance(locx,locy,targetX,targetY)<5;
}
