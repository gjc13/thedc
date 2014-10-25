#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

void pid()
{
	float32 temp;
/*姿态控制程序开始 **************************************************************************************/


//从遥控器读数

	temp=channelsData1000[2];
	posture_expected.throttle= /*( (0.0000044*temp - 0.0065)*temp + 3.6273) * temp - 281.7*/temp;
	posture_expected.roll=(channelsData1000[0]-offset_roll)/500*MAX_PITCH_ROLL;
	posture_expected.pitch=(offset_pitch-channelsData1000[1])/500*MAX_PITCH_ROLL;

//限制范围
	 if(posture_expected.throttle<230.0)
	 {
		 posture_expected.throttle=0;
		 posture_expected.yaw=posture_now.yaw;
	 }
	 else if(posture_expected.throttle>999)
		 posture_expected.throttle=999;

		if(throttle_mode==0)//手动油门
		{
			throttle_real=posture_expected.throttle;
		}
		else //自动定高
		{
			throttle_Kp = throttle_Kp_STD * ( 0.00095*channelsData2048[10]+0.0272 );
			throttle_Kd = throttle_Kd_STD * ( 0.00095*channelsData2048[11]+0.0272 );
			throttle_real=(height_ref-height_ultrasonic_lp)*throttle_Kp-vz*throttle_Kd+throttle_ref;
			if(throttle_real>(posture_expected.throttle+250))
				throttle_real=posture_expected.throttle+250;
			if(throttle_real<(posture_expected.throttle-250))
				throttle_real=posture_expected.throttle-250;
	//		limit_float32(&throttle_real,posture_expected.throttle-100,posture_expected.throttle+100);
		}



//计算error
	  posture_error.pitch =posture_expected.pitch-posture_now.pitch; //误差计算:目标值减去当前值
	  posture_error.roll  = posture_expected.roll-posture_now.roll;
	  posture_error.yaw   = posture_expected.yaw-posture_now.yaw;

//角速度speed计算
	  posture_speed.pitch=(posture_now.pitch-posture_before.pitch)/dt;
	  posture_speed.roll=(posture_now.roll-posture_before.roll)/dt;
	  posture_speed.yaw=(posture_now.yaw-posture_before.yaw)/dt;

 //计算低通滤波Speed
	  low_pass(&speed_pitch_lp,posture_speed.pitch,50,dt);
	  low_pass(&speed_roll_lp,posture_speed.roll,50,dt);
	  low_pass(&speed_yaw_lp,posture_speed.yaw,50,dt);


	  temp=posture_expected.throttle*0.6;
	  limit_float32( &posture_adjust.yaw , -temp , temp );
	  limit_float32( &posture_adjust.pitch , -temp , temp );
	  limit_float32( &posture_adjust.roll , -temp , temp );

	  posture_before  = posture_now;	//更新姿态
//	 ********************************************************
//	 姿态控制程序结束
//	 ********************************************************
}

void setMotor()
{
	float32 pulse_temp=0;

	if(fly_enable!=0)//初始化完成
	{
		if( channelsData4[9]==0 )//油门锁打开
		{
			if(posture_expected.throttle>230 )
				fly_enable=3;
			else
				fly_enable=2;

			if(wireLessLost)//脱控
			{
				if(++wireLessLostCount>20)//脱控0.05s进入失控保护模式
					fly_enable = 4 ;
			}
			else
				wireLessLostCount = 0 ;
		}
		else
			fly_enable=1;
	}


	if( channelsData4[4]==4)
	{
		if(throttle_mode==0)//切换到自动定高模式时记录参考油门和参考高度
		{
			height_ref=height_ultrasonic_lp;
			throttle_ref= posture_expected.throttle;
		}
		throttle_mode=1;//自动定高
	}
	else
	{
		throttle_mode=0;//手动油门
	}


	pulse_temp = throttle_real+posture_adjust.pitch+posture_adjust.roll-posture_adjust.yaw;//电机一
	limit_float32(&pulse_temp,0,999);		//限制范围在电调设定的接受范围之内
	MOTOR1_PULSE= pulse_temp;

	pulse_temp = throttle_real+posture_adjust.pitch-posture_adjust.roll+posture_adjust.yaw;//电机二
	limit_float32(&pulse_temp,0,999);		//限制范围在电调设定的接受范围之内
	MOTOR2_PULSE= pulse_temp;

	pulse_temp = throttle_real-posture_adjust.pitch-posture_adjust.roll-posture_adjust.yaw;//电机三
	limit_float32(&pulse_temp,0,999);		//限制范围在电调设定的接受范围之内
	MOTOR3_PULSE=pulse_temp;

	pulse_temp = throttle_real-posture_adjust.pitch+posture_adjust.roll+posture_adjust.yaw;//电机四
	limit_float32(&pulse_temp,0,999);		//限制范围在电调设定的接受范围之内
	MOTOR4_PULSE= pulse_temp;

	if(fly_enable==3 )  //可以起飞，否则不给马达输出
	{
		setPwm(1,MOTOR1_PULSE) ;
		setPwm(2,MOTOR2_PULSE) ;
		setPwm(3,MOTOR3_PULSE) ;
		setPwm(4,MOTOR4_PULSE) ;
	 }
	else
	{
		setPwm(1,0) ;
		setPwm(2,0) ;
		setPwm(3,0) ;
		setPwm(4,0) ;
	}
	/************************************************************************
	电机操作程序结束
	*************************************************************************/
}
