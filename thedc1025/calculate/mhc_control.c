#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

void pid()
{
	float32 temp;
/*��̬���Ƴ���ʼ **************************************************************************************/


//��ң��������

	temp=channelsData1000[2];
	posture_expected.throttle= /*( (0.0000044*temp - 0.0065)*temp + 3.6273) * temp - 281.7*/temp;
	posture_expected.roll=(channelsData1000[0]-offset_roll)/500*MAX_PITCH_ROLL;
	posture_expected.pitch=(offset_pitch-channelsData1000[1])/500*MAX_PITCH_ROLL;

//���Ʒ�Χ
	 if(posture_expected.throttle<230.0)
	 {
		 posture_expected.throttle=0;
		 posture_expected.yaw=posture_now.yaw;
	 }
	 else if(posture_expected.throttle>999)
		 posture_expected.throttle=999;

		if(throttle_mode==0)//�ֶ�����
		{
			throttle_real=posture_expected.throttle;
		}
		else //�Զ�����
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



//����error
	  posture_error.pitch =posture_expected.pitch-posture_now.pitch; //������:Ŀ��ֵ��ȥ��ǰֵ
	  posture_error.roll  = posture_expected.roll-posture_now.roll;
	  posture_error.yaw   = posture_expected.yaw-posture_now.yaw;

//���ٶ�speed����
	  posture_speed.pitch=(posture_now.pitch-posture_before.pitch)/dt;
	  posture_speed.roll=(posture_now.roll-posture_before.roll)/dt;
	  posture_speed.yaw=(posture_now.yaw-posture_before.yaw)/dt;

 //�����ͨ�˲�Speed
	  low_pass(&speed_pitch_lp,posture_speed.pitch,50,dt);
	  low_pass(&speed_roll_lp,posture_speed.roll,50,dt);
	  low_pass(&speed_yaw_lp,posture_speed.yaw,50,dt);


	  temp=posture_expected.throttle*0.6;
	  limit_float32( &posture_adjust.yaw , -temp , temp );
	  limit_float32( &posture_adjust.pitch , -temp , temp );
	  limit_float32( &posture_adjust.roll , -temp , temp );

	  posture_before  = posture_now;	//������̬
//	 ********************************************************
//	 ��̬���Ƴ������
//	 ********************************************************
}

void setMotor()
{
	float32 pulse_temp=0;

	if(fly_enable!=0)//��ʼ�����
	{
		if( channelsData4[9]==0 )//��������
		{
			if(posture_expected.throttle>230 )
				fly_enable=3;
			else
				fly_enable=2;

			if(wireLessLost)//�ѿ�
			{
				if(++wireLessLostCount>20)//�ѿ�0.05s����ʧ�ر���ģʽ
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
		if(throttle_mode==0)//�л����Զ�����ģʽʱ��¼�ο����źͲο��߶�
		{
			height_ref=height_ultrasonic_lp;
			throttle_ref= posture_expected.throttle;
		}
		throttle_mode=1;//�Զ�����
	}
	else
	{
		throttle_mode=0;//�ֶ�����
	}


	pulse_temp = throttle_real+posture_adjust.pitch+posture_adjust.roll-posture_adjust.yaw;//���һ
	limit_float32(&pulse_temp,0,999);		//���Ʒ�Χ�ڵ���趨�Ľ��ܷ�Χ֮��
	MOTOR1_PULSE= pulse_temp;

	pulse_temp = throttle_real+posture_adjust.pitch-posture_adjust.roll+posture_adjust.yaw;//�����
	limit_float32(&pulse_temp,0,999);		//���Ʒ�Χ�ڵ���趨�Ľ��ܷ�Χ֮��
	MOTOR2_PULSE= pulse_temp;

	pulse_temp = throttle_real-posture_adjust.pitch-posture_adjust.roll-posture_adjust.yaw;//�����
	limit_float32(&pulse_temp,0,999);		//���Ʒ�Χ�ڵ���趨�Ľ��ܷ�Χ֮��
	MOTOR3_PULSE=pulse_temp;

	pulse_temp = throttle_real-posture_adjust.pitch+posture_adjust.roll+posture_adjust.yaw;//�����
	limit_float32(&pulse_temp,0,999);		//���Ʒ�Χ�ڵ���趨�Ľ��ܷ�Χ֮��
	MOTOR4_PULSE= pulse_temp;

	if(fly_enable==3 )  //������ɣ����򲻸�������
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
	��������������
	*************************************************************************/
}
