#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"


void dataConverse()//i2c数据转为-1~1
{

//	HMC5883Data[0]=( (int16)(((i2cData[12]  <<8) | i2cData[13]  )- 0.0 ) ) / 1.0;
//	HMC5883Data[1]=( (int16)(((i2cData[14]  <<8) | i2cData[15]  )- 0.0 ) ) / 1.0;
//	HMC5883Data[2]=( (int16)(((i2cData[16]  <<8) | i2cData[17]  )- 0.0 ) ) / 1.0;
//


//	gMPU6050RawAccel.x=(int16)((i2cData[0]<<8) | i2cData[1] );
//	gMPU6050RawAccel.y=(int16)((i2cData[2]<<8) | i2cData[3] );
//	gMPU6050RawAccel.z=(int16)((i2cData[4]<<8) | i2cData[5] );
//
//	gMPU6050RawGyro.x=(int16)((i2cData[6]<<8) | i2cData[7] );
//	gMPU6050RawGyro.y=(int16)((i2cData[8]<<8) | i2cData[9] );
//	gMPU6050RawGyro.z=(int16)((i2cData[10]<<8) | i2cData[11] );
	spi_zGyro=spiAReadData[61]<<8|spiAReadData[63];
}


/***************************************************************************************
函数原型：void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T)
功    能：低通滤波函数
参    数：float32 *lp_data：指向滤波后的数据的指针
		  float32 source_data  ：源数据
		  float32 G			  ：滤波系数
		  float32 T			  ：调用周期
返    回：无
作    者: 肖熙吉
版	  本：1.0
时    间：2013—12-5
****************************************************************************************/
void low_pass(float32 *lp_data,float32 source_data,float32 G,float32 T)
{
 *lp_data=(*lp_data+G*source_data*T)/(1+T*G);
}


void Posture_calculate(void)
{
//	AHRS_AccelIIRLPFilter();//加速度低通滤波
	AHRS_Normalize();//数据归一化
//	MadgwickAHRSupdateIMU(gGyro.x,gGyro.y,gGyro.z,gAccel.x,gAccel.y,gAccel.z);//更新四元数
//	AHRS_GetEulerRPY();//转换为欧拉角
//	vz_calculate();//计算高度融合数据
}

///***************************************************************************************
//函数原型：Posture_calculate
//功    能：由传感器数据计算姿态
//****************************************************************************************/
//void Posture_calculate(void)
//{
//
//	float32 Au_lp=MPU6050Data[0] , Av_lp=MPU6050Data[1] , Aw_lp=MPU6050Data[2]  ;//暂时未加低通滤波
//
// 	limit_float32( &Au_lp , -0.999 , 0.999 );//限制范围，防止计算结果出现溢出
//	limit_float32( &Av_lp , -0.999 , 0.999 );
//
//	if(Aw_lp<0.001&&Aw_lp>-0.001)//限制范围，防止出现除0
//	  Aw_lp=0.001;
//
//	pitch_Au=-atan(Au_lp/sqrt(Av_lp*Av_lp+Aw_lp*Aw_lp));//俯仰正向，机头抬高
//	if(Aw_lp>0) 	   			//将范围扩展到-180°到180°
//		roll_Av=atan(Av_lp/Aw_lp);//横滚横滚正向，机身右倾
//	if((Aw_lp<0)&&(Av_lp>0))
//		 roll_Av=PI+atan(Av_lp/Aw_lp);
//	if((Aw_lp<0)&&(Av_lp<0))
//		 roll_Av=-PI+atan(Av_lp/Aw_lp);
//
//	 //俯仰横滚计算
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
//		posture_now.pitch=(posture_now.pitch+dp*dt+G_pos_p*pitch_Au*dt)/(1+dt*G_pos_p); //互补滤波
//		posture_now.roll=(posture_now.roll+dr*dt+G_pos_r*roll_Av*dt)/(1+dt*G_pos_r);    //互补滤波
//		posture_now.yaw=yaw_Gz ; //暂时用陀螺仪积分
//
//
//		limit_float32( &posture_now.pitch , -PI/2 , PI/2 );//限制范围到-90°到90°
//		limit_float32( &posture_now.roll , -PI , PI );//限制范围到-PI°到PI°
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
函数原型：vz_ultrasonic_calculate
功    能：由超声波传感器数据计算z轴速度
****************************************************************************************/
void vz_ultrasonic_calculate(void)
{
//	int16 old_pointer ;
//	if(++ultrasonic_height_data_pointer>29)
//		ultrasonic_height_data_pointer=0;
//	ultrasonic_height_data_m[ultrasonic_height_data_pointer] = height_ultrasonic/100;//统一单位m
//
//	old_pointer = ultrasonic_height_data_pointer-20;//0.5s前的高度，修改时要改vz_ultrasonic_T
//	if(old_pointer<0)
//		old_pointer+=30;
//
//	vz_ultra=( ultrasonic_height_data_m[ultrasonic_height_data_pointer] - ultrasonic_height_data_m[old_pointer] ) / vz_ultrasonic_T ;
}

/***************************************************************************************
函数原型：vz_calculate
功    能：由加速度和超声波融合计算z轴速度
****************************************************************************************/
void vz_calculate(void)
{
//	az = gAccel.z * az_scale  ;
//	az=(gAccel.y*ay_scale*sin(posture_now.pitch)-gAccel.x*ax_scale*sin(posture_now.roll)*cos(posture_now.pitch)+gAccel.z*az_scale*cos(posture_now.roll)*cos(posture_now.pitch));//可能有问题
//	vz = (vz+(az-g_local)*dt+G_height*vz_ultra*dt)/(1+dt*G_height); //高度互补滤波
//
//	if(vz>20)
//		vz=20;
//	if(vz<-20)
//		vz=-20;

}

