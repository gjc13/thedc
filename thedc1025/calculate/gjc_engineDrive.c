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
//	GpioDataRegs.GPBSET.bit.GPIO58=1;
	lastUpdatePostureTime=cpuTime;
	nowLeftSpeed=eQEP1PositionDifference*leftSpeedRatio;
	nowRightSpeed=eQEP2PositionDifference*rightSpeedRatio;
	if(abs(gGyro.z)>6*PI)
	{
		isMPUavailable=0;
	}
	else
	{
		isMPUavailable=1;
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

	//角度互补滤波
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
	//错误处理可能还不完善，加完光流/码盘之后统一改
	return newDataReceive;
}


void SetEngineOutput()
{
	float32 distanceMinBound=10;
	float32 diffAngle=0;
	float32 angleTolerance=PI/12;
	Uint16 i=0;
	if(moveStatus==WAITPOINT || playerData.time>239)
	{
		DisableEngineOutput();
		return;
	}
	if(moveStatus==PEND)
	{
		DisableEngineOutput();
		SeekNextTarget();
	}
	nowDistance=GetDistance(nowX,nowY,targetX,targetY);
	if(nowDistance<distanceMinBound && moveStatus==SEEK)
	{
		for(i=0; i<0xFFFE; i++)
		{
			DisableEngineOutput();
		}
		StartWaitPoint();
		return;
//		if(IsPointedLoc(nowX,nowY))
//		{
//			StartWaitPoint();
//			return;
//		}
//		else
//		{
//			DisableEngineOutput();
//			moveStatus=PEND;
//			return;
//		}
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
		TurnCar(targetHeadAngle);
	}
	else if(HasObstacle() && nowDistance>distanceMinBound)
	{
		if(HasFrontObstacle())
		{
			for(i=0; i<0x20FE; i++)
			{
				setEngine(ENGINEBACK,0.7,ENGINEBACK,0.7);
			}
			DisableEngineOutput();
			moveStatus=PEND;
			return;
		}
		else if(HasBackObstacle())
		{
			for(i=0; i<0x20FE; i++)
			{
				setEngine(ENGINEFRONT,0.7,ENGINEFRONT,0.7);
			}
			DisableEngineOutput();
			moveStatus=PEND;
			return;
		}
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

void TurnCar(float32 targetAngle)
{
//	float32 rateP=angleP;
//	float32 rateD=IsCounterClockWise(nowAngle,targetAngle)?-angleD:angleD;
//	float32 rateI=angleI;
//	float32 minPower=0.05;
//	float32 maxPower=0.18;
	float32 angleSlowThreshold=PI/6;
	float32 angleTurnQuickSpeed=0.5;
	float32 angleTurnSlowSpeed=0.2;
	float32 diffAngle=GetDiffAngleAbs(nowAngle,targetAngle);
	float32 turnSpeed=0;
	if(moveStatus==PEND)
	{
		DisableEngineOutput();
		return;
	}
	diffAngle=diffAngle>PI?2*PI-diffAngle:diffAngle;
	turnSpeed=diffAngle>angleSlowThreshold?angleTurnQuickSpeed:angleTurnSlowSpeed;
//	Padjust=0;
//	Iadjust=0;
//	Dadjust=0;
//	if(isMPUavailable && (gGyro.z>-10 && gGyro.z<10))
//	{
//		Padjust=rateP*diffAngle;
//		Dadjust=rateD*gGyro.z;
//	}
//	else
//	{
//		//Better to be conservative when MPU fails
//		DisableEngineOutput();
//		return;
//		//Padjust=(rateP*diffAngle)/2;
//	}
//	Padjust=Padjust<0.3?Padjust:0.3;
//	Iadjust=rateI*angleDiffIntergration;
//	angleOutPut=Padjust+Iadjust+Dadjust;
//	angleOutPut=(angleOutPut>0 && angleOutPut>maxPower)?maxPower:angleOutPut;
//	angleOutPut=(angleOutPut>0 && angleOutPut<minPower)?minPower:angleOutPut;
//	angleOutPut=(angleOutPut<0 && angleOutPut>-minPower)?-minPower:angleOutPut;
//	angleOutPut=(angleOutPut<0 && angleOutPut<-maxPower)?-maxPower:angleOutPut;
	direction=TURN;
	if(IsCounterClockWise(nowAngle,targetAngle))
	{
		if(HasBackObstacle())
		{
			SetEngineRunSpeed(turnSpeed,0);
		}
		if(HasFrontObstacle())
		{
			SetEngineRunSpeed(0,-turnSpeed);
		}
		else
		{
			SetEngineRunSpeed(turnSpeed,-turnSpeed);
		}
	}
	else
	{
		if(HasBackObstacle())
		{
			SetEngineRunSpeed(0,turnSpeed);
		}
		else if(HasFrontObstacle())
		{
			SetEngineRunSpeed(-turnSpeed,0);
		}
		else
		{
			SetEngineRunSpeed(-turnSpeed,turnSpeed);
		}
	}
//	if(diffAngle>angleSlowThreshold)
//	{
//		if(IsCounterClockWise(nowAngle,targetAngle))
//		{
//			if(HasBackObstacle())
//			{
//				SetEngineRunSpeed(angleTurnQuickSpeed,0);
////				setEngine(ENGINEFRONT,angleOutPut*1.2,ENGINEBACK,0);
//			}
//			if(HasFrontObstacle())
//			{
//				SetEngineRunSpeed(0,-angleTurnQuickSpeed);
//				setEngine(ENGINEFRONT,0,ENGINEBACK,angleOutPut*1.2);
//			}
//			else
//			{
//				setEngine(ENGINEFRONT,angleOutPut*1.2,ENGINEBACK,angleOutPut*1.2);
//			}
//		}
//		else
//		{
//			if(HasBackObstacle())
//			{
//				setEngine(ENGINEBACK,0,ENGINEFRONT,angleOutPut*1.2);
//			}
//			else if(HasFrontObstacle())
//			{
//				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,0);
//			}
//			else
//			{
//				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,angleOutPut*1.2);
//			}
//		}
//	}
//	else
//	{
//		angleOutPut=-angleOutPut;
//		if(IsCounterClockWise(nowAngle,targetAngle))
//		{
//			if(HasBackObstacle())
//			{
//				setEngine(ENGINEBACK,0,ENGINEFRONT,angleOutPut*1.2);
//			}
//			else if(HasFrontObstacle())
//			{
//				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,0);
//			}
//			else
//			{
//				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,angleOutPut*1.2);
//			}
//		}
//		else
//		{
//			if(HasBackObstacle())
//			{
//				setEngine(ENGINEBACK,0,ENGINEFRONT,angleOutPut*1.2);
//			}
//			else if(HasFrontObstacle())
//			{
//				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,0);
//			}
//			else
//			{
//				setEngine(ENGINEBACK,angleOutPut*1.2,ENGINEFRONT,angleOutPut*1.2);
//			}
//		}
//	}
}

void RunToTarget()
{
//	float32 rateP=0.002;
//
//	float32 minPower=0.005;
	float32 distance=GetDistance(nowX,nowY,targetX,targetY);
//	float32 outPower=distance*rateP;
//	float32 rightOut=0;
	float32 speed=distance>40?0.5:0.2;
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
//	rightOut=outPower;
//	if(distance<40)
//	{
//		outPower=outPower>0.1?0.1:outPower;
//		rightOut=rightOut>0.1?0.1:outPower;
//	}
	if(GetDiffAngleAbs(nowAngle,targetRunAngle)<PI/2)
	{
		direction=FRONT;
		if(direction!=nowDirection)
		{
			nowDirection=direction;
		}
//		outPower=outPower>0.2?0.2:outPower;
//		rightOut=rightOut>0.2?0.2:rightOut;
//		outPower=outPower<minPower?minPower:outPower;
//		rightOut=rightOut<minPower?minPower:rightOut;
//		setEngine(ENGINEFRONT,outPower,ENGINEFRONT,rightOut);
		SetEngineRunSpeed(speed,speed);
	}
	else
	{
		direction=BACK;
		if(direction!=nowDirection)
		{
			nowDirection=direction;
		}
//		outPower=outPower>0.06?0.06:outPower;
//		rightOut=rightOut>0.06?0.06:rightOut;
//		outPower=outPower<minPower?minPower:outPower;
//		rightOut=rightOut<minPower?minPower:rightOut;
//		setEngine(ENGINEBACK,outPower,ENGINEBACK,rightOut);
		SetEngineRunSpeed(-speed,-speed);
	}
}

//void RunAndTurn()
//{
//	float32 rateAngleP=angleP;
//	float32 diffAngle=GetDiffAngleAbs(nowAngle,targetHeadAngle);
//	float32 rateDistanceP=0.1;
//	float32 minPower=0.03;
//	float32 distance=GetDistance(nowX,nowY,targetX,targetY);
//	float32 outPower=0;
//	Padjust=0;
//	if(moveStatus==PEND)
//	{
//		DisableEngineOutput();
//		return;
//	}
//	if(isMPUavailable && (gGyro.z>-10 && gGyro.z<10))
//	{
//		Padjust=rateAngleP*diffAngle;
//	}
//	else
//	{
//		//Better to be conservative when MPU fails
//		DisableEngineOutput();
//		return;
//		//Padjust=(rateP*diffAngle)/2;
//	}
//	Padjust=Padjust<0.3?Padjust:0.3;
//	angleOutPut=Padjust;
//	angleOutPut=angleOutPut>0.05?0.05:angleOutPut;
//	angleOutPut=angleOutPut<0.01?0.01:angleOutPut;
//
//	outPower=distance*rateDistanceP;
//	outPower=outPower>0.16?0.16:outPower;
//	outPower+=minPower;
//	if(GetDiffAngleAbs(nowAngle,targetRunAngle)<PI/2)
//	{
//		direction=FRONT;
//		if(IsCounterClockWise(nowAngle,targetHeadAngle))
//		{
//			setEngine(ENGINEFRONT,outPower-angleOutPut,ENGINEFRONT,outPower+angleOutPut);
//		}
//		else
//		{
//			setEngine(ENGINEFRONT,outPower+angleOutPut,ENGINEFRONT,outPower-angleOutPut);
//		}
//	}
//	else
//	{
//		direction=BACK;
//		if(IsCounterClockWise(nowAngle,targetHeadAngle))
//		{
//			setEngine(ENGINEBACK,outPower+angleOutPut,ENGINEBACK,outPower-angleOutPut);
//		}
//		else
//		{
//			setEngine(ENGINEBACK,outPower-angleOutPut,ENGINEBACK,outPower+angleOutPut);
//		}
//	}
//}

void DisableEngineOutput()
{
	setEngine(ENGINESTOP,0,ENGINESTOP,0);
	direction=STOP;
	ResetSpeedControl();
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
	direction=STOP;
	nowDirection=STOP;
	DisableEngineOutput();
}


//在这里用超声判断是否有坑
Uint16 HasObstacle()
{
	//将是否前方有坑从HasObstacle返回
	//移动情况在direction枚举中找
	//有坑返回TRUE
	if(nowDistance>40 || nowDistance<5)
	{
		return 0;
	}
	return (direction==FRONT) ? (foundHeadObstacleTime>10) : (foundTailObstacleTime>10);
}

Uint16 HasFrontObstacle()
{
//	int16 frontVecX=headX-rearX;
//	int16 frontVecY=headY-rearY;
//	int16 obstacleVecX=0,obstacleVecY=0;
//	int16 i=0,j=0;
//	int16 shadowLength=0;
//	if(foundHeadObstacleTime==0)
//	{
//		return 0;
//	}
//	for(i=0; i<2; i++)
//	{
//		for(j=0; j<2; j++)
//		{
//			obstacleVecX=allTargetX[i][j]-nowX;
//			obstacleVecY=allTargetY[i][j]-nowY;
//			shadowLength=abs(Shadow(obstacleVecX,obstacleVecY,frontVecX,frontVecY));
//			if(shadowLength>0 && shadowLength<25)
//			{
//				return foundHeadObstacleTime>10;
//			}
//		}
//	}
//	return 0;
	return foundHeadObstacleTime>30 && nowDistance<40;
}

Uint16 HasBackObstacle()
{
//	int16 backVecX=rearX-headX;
//	int16 backVecY=rearY-headY;
//	int16 obstacleVecX=0,obstacleVecY=0;
//	int16 i=0,j=0;
//	int16 shadowLength=0;
//	if(foundTailObstacleTime==0)
//	{
//		return 0;
//	}
//	for(i=0; i<2; i++)
//	{
//		for(j=0; j<2; j++)
//		{
//			obstacleVecX=allTargetX[i][j]-nowX;
//			obstacleVecY=allTargetY[i][j]-nowY;
//			shadowLength=abs(Shadow(obstacleVecX,obstacleVecY,backVecX,backVecY));
//			if(shadowLength>0 && shadowLength<25)
//			{
//				return foundTailObstacleTime>10;
//			}
//		}
//	}
//	return 0;
	return foundTailObstacleTime>30 && nowDistance<40;
}


Uint16 IsPointedLoc(Uint16 locx,Uint16 locy)
{
	return GetDistance(locx,locy,targetX,targetY)<10;
}

void ResetSpeedControl()
{
	targetLeftSpeed=0;
	targetRightSpeed=0;
	leftSpeedPOutput=0;
	rightSpeedPOutput=0;
	leftSpeedIOutput=0;
	rightSpeedIOutput=0;
	startLeftSpeedControlTime=cpuTime;
	startRightSpeedControlTime=cpuTime;
}

void SpeedControlIntergration()
{
	if(direction==STOP)
	{
		ResetSpeedControl();
		return;
	}
	leftSpeedIOutput*=speedIDecay;
	rightSpeedIOutput*=speedIDecay;
	leftSpeedIOutput+=(targetLeftSpeed-nowLeftSpeed)*speedI;
	rightSpeedIOutput+=(targetRightSpeed-nowRightSpeed)*speedI;
}

void SetEngineRunSpeed(float32 leftSpeed,float32 rightSpeed)
{
	RegisterLeftTargetSpeed(leftSpeed);
	RegisterRightTargetSpeed(rightSpeed);
	leftSpeedPOutput=(targetLeftSpeed-nowLeftSpeed)*speedP;
	rightSpeedPOutput=(targetRightSpeed-nowRightSpeed)*speedP;
	setEngine(ENGINEFRONT,leftSpeedPOutput+leftSpeedIOutput,ENGINEFRONT,rightSpeedIOutput+rightSpeedPOutput);
}

void RegisterLeftTargetSpeed(float32 leftSpeed)
{
	//leftSpeedIOutput+=(leftSpeed-targetLeftSpeed)*(cpuTime-startLeftSpeedControlTime);
	if(/*fabs(nowLeftSpeed-targetLeftSpeed)<speedTolerance && */fabs(leftSpeed-targetLeftSpeed)>speedTolerance)
	{
		leftSpeedIOutput=0;
		startLeftSpeedControlTime=cpuTime;
	}
	targetLeftSpeed=leftSpeed;
}

void RegisterRightTargetSpeed(float32 rightSpeed)
{
	//rightSpeedIOutput+=(rightSpeed-targetRightSpeed)*(cpuTime-startRightSpeedControlTime);
	if(/*fabs(nowRightSpeed-targetRightSpeed)<speedTolerance && */fabs(rightSpeed-targetRightSpeed)>speedTolerance)
	{
		rightSpeedIOutput=0;
		startRightSpeedControlTime=cpuTime;
	}
	targetRightSpeed=rightSpeed;
}

void setSaw(int16 on)
{
	setPwm(3,on?SAW_POWER:0);
	setPwm(4,on?SAW_POWER:0);
}
