#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"


void dataConverse()//i2c����תΪ-1~1
{

//	HMC5883Data[0]=( (int16)(((i2cData[12]  <<8) | i2cData[13]  )- 0.0 ) ) / 1.0;
//	HMC5883Data[1]=( (int16)(((i2cData[14]  <<8) | i2cData[15]  )- 0.0 ) ) / 1.0;
//	HMC5883Data[2]=( (int16)(((i2cData[16]  <<8) | i2cData[17]  )- 0.0 ) ) / 1.0;
//


	gMPU6050RawAccel.x=(int16)((i2cData[0]<<8) | i2cData[1] );
	gMPU6050RawAccel.y=(int16)((i2cData[2]<<8) | i2cData[3] );
	gMPU6050RawAccel.z=(int16)((i2cData[4]<<8) | i2cData[5] );

	gMPU6050RawGyro.x=(int16)((i2cData[6]<<8) | i2cData[7] );
	gMPU6050RawGyro.y=(int16)((i2cData[8]<<8) | i2cData[9] );
	gMPU6050RawGyro.z=(int16)((i2cData[10]<<8) | i2cData[11] );
}


/***************************************************************************************
����ԭ�ͣ�void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T)
��    �ܣ���ͨ�˲�����
��    ����float32 *lp_data��ָ���˲�������ݵ�ָ��
		  float32 source_data  ��Դ����
		  float32 G			  ���˲�ϵ��
		  float32 T			  ����������
��    �أ���
��    ��: Ф����
��	  ����1.0
ʱ    �䣺2013��12-5
****************************************************************************************/
void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T)
{
 *lp_data=(*lp_data+G*source_data*T)/(1+T*G);
}


void Posture_calculate(void)
{
	AHRS_AccelIIRLPFilter();//���ٶȵ�ͨ�˲�
	AHRS_Normalize();//���ݹ�һ��
	MadgwickAHRSupdateIMU(gGyro.x,gGyro.y,gGyro.z,gAccel.x,gAccel.y,gAccel.z);//������Ԫ��
	AHRS_GetEulerRPY();//ת��Ϊŷ����
	vz_calculate();//����߶��ں�����
}

///***************************************************************************************
//����ԭ�ͣ�Posture_calculate
//��    �ܣ��ɴ��������ݼ�����̬
//****************************************************************************************/
//void Posture_calculate(void)
//{
//
//	float32 Au_lp=MPU6050Data[0] , Av_lp=MPU6050Data[1] , Aw_lp=MPU6050Data[2]  ;//��ʱδ�ӵ�ͨ�˲�
//
// 	limit_float32( &Au_lp , -0.999 , 0.999 );//���Ʒ�Χ����ֹ�������������
//	limit_float32( &Av_lp , -0.999 , 0.999 );
//
//	if(Aw_lp<0.001&&Aw_lp>-0.001)//���Ʒ�Χ����ֹ���ֳ�0
//	  Aw_lp=0.001;
//
//	pitch_Au=-atan(Au_lp/sqrt(Av_lp*Av_lp+Aw_lp*Aw_lp));//�������򣬻�ͷ̧��
//	if(Aw_lp>0) 	   			//����Χ��չ��-180�㵽180��
//		roll_Av=atan(Av_lp/Aw_lp);//���������򣬻�������
//	if((Aw_lp<0)&&(Av_lp>0))
//		 roll_Av=PI+atan(Av_lp/Aw_lp);
//	if((Aw_lp<0)&&(Av_lp<0))
//		 roll_Av=-PI+atan(Av_lp/Aw_lp);
//
//	 //�����������
////	    low_pass(&Au_lp,Au,100,dt);//30
////	    low_pass(&Av_lp,Av,100,dt);
////	    low_pass(&Aw_lp,Aw,100,dt);
//
//		dp=Gv*cos(posture_now.roll)-Gw*sin(posture_now.roll);
//		dr=Gu+(Gv*sin(posture_now.roll)+Gw*cos(posture_now.roll))*tan(posture_now.pitch);
//		dy=(Gv*sin(posture_now.roll)+Gw*cos(posture_now.roll))/cos(posture_now.pitch);
//
////		G_pos_p=0.1;
////		G_pos_r=0.1;
//
//		posture_now.pitch=(posture_now.pitch+dp*dt+G_pos_p*pitch_Au*dt)/(1+dt*G_pos_p); //�����˲�
//		posture_now.roll=(posture_now.roll+dr*dt+G_pos_r*roll_Av*dt)/(1+dt*G_pos_r);    //�����˲�
//		posture_now.yaw=yaw_Gz ; //��ʱ�������ǻ���
//
//
//		limit_float32( &posture_now.pitch , -PI/2 , PI/2 );//���Ʒ�Χ��-90�㵽90��
//		limit_float32( &posture_now.roll , -PI , PI );//���Ʒ�Χ��-PI�㵽PI��
//
//}

void limit_float32(float32 *num , float32 min , float32 max)
{
	if ( (*num) < min )
		*num = min;
	else if ( (*num) > max )
		*num = max;
}

/***************************************************************************************
����ԭ�ͣ�vz_ultrasonic_calculate
��    �ܣ��ɳ��������������ݼ���z���ٶ�
****************************************************************************************/
void vz_ultrasonic_calculate(void)
{
	int16 old_pointer ;
	if(++ultrasonic_height_data_pointer>29)
		ultrasonic_height_data_pointer=0;
	ultrasonic_height_data_m[ultrasonic_height_data_pointer] = height_ultrasonic/100;//ͳһ��λm

	old_pointer = ultrasonic_height_data_pointer-20;//0.5sǰ�ĸ߶ȣ��޸�ʱҪ��vz_ultrasonic_T
	if(old_pointer<0)
		old_pointer+=30;

	vz_ultra=( ultrasonic_height_data_m[ultrasonic_height_data_pointer] - ultrasonic_height_data_m[old_pointer] ) / vz_ultrasonic_T ;
}

/***************************************************************************************
����ԭ�ͣ�vz_calculate
��    �ܣ��ɼ��ٶȺͳ������ںϼ���z���ٶ�
****************************************************************************************/
void vz_calculate(void)
{
//	az = gAccel.z * az_scale  ;
	az=(gAccel.y*ay_scale*sin(posture_now.pitch)-gAccel.x*ax_scale*sin(posture_now.roll)*cos(posture_now.pitch)+gAccel.z*az_scale*cos(posture_now.roll)*cos(posture_now.pitch));//����������
	vz = (vz+(az-g_local)*dt+G_height*vz_ultra*dt)/(1+dt*G_height); //�߶Ȼ����˲�

	if(vz>20)
		vz=20;
	if(vz<-20)
		vz=-20;

}

