#include "mhc.h"
#include "GlobalVariables.h"
#include "math.h"

//extern _Control_Loop_t my_loop;


void AHRS_AccelIIRLPFilter(void)
{
	gMPU6050LPFAccel.x = iirLPFilterSingle(gMPU6050RawAccel.x, IMU_ACC_IIR_LPF_ATT_FACTOR, &(gMPU6050RawAccelStoredFilterValues.x));
	gMPU6050LPFAccel.y = iirLPFilterSingle(gMPU6050RawAccel.y, IMU_ACC_IIR_LPF_ATT_FACTOR, &(gMPU6050RawAccelStoredFilterValues.y));
	gMPU6050LPFAccel.z = iirLPFilterSingle(gMPU6050RawAccel.z, IMU_ACC_IIR_LPF_ATT_FACTOR, &(gMPU6050RawAccelStoredFilterValues.z));
}

//void AHRS_GyroIIRLPFilter(void)
//{
//	gMPU6050LPFGyro.x = iirLPFilterSingle(gMPU6050RawGyro.x, IMU_GYRO_IIR_LPF_ATT_FACTOR, &(gMPU6050RawGyroStoredFilterValues.x));
//	gMPU6050LPFGyro.y = iirLPFilterSingle(gMPU6050RawGyro.y, IMU_GYRO_IIR_LPF_ATT_FACTOR, &(gMPU6050RawGyroStoredFilterValues.y));
//	gMPU6050LPFGyro.z = iirLPFilterSingle(gMPU6050RawGyro.z, IMU_GYRO_IIR_LPF_ATT_FACTOR, &(gMPU6050RawGyroStoredFilterValues.z));
//}

//void AHRS_GyroBiasSet(void)
//{
//	gMPU6050BiasGyro = gMPU6050LPFGyro;
//}


void AHRS_Normalize(void)
{
//	gGyroTmp.x = (gMPU6050RawGyro.x - gMPU6050BiasGyro.x) * IMU_DEG_PER_LSB_CFG * M_PI / 180;
//	gGyroTmp.y = (gMPU6050RawGyro.y - gMPU6050BiasGyro.y) * IMU_DEG_PER_LSB_CFG * M_PI / 180;
	gGyro.z = (gMPU6050RawGyro.z - gyroZDrift) * IMU_DEG_PER_LSB_CFG * M_PI / 180;
	gAccelTmp.x = (gMPU6050LPFAccel.x /*- gMPU6050BiasAccel.x*/) * MPU6050_G_PER_LSB_8 * 1.0f;
	gAccelTmp.y = (gMPU6050LPFAccel.y/* - gMPU6050BiasAccel.y*/) * MPU6050_G_PER_LSB_8 * 1.0f;
	gAccel.z = (gMPU6050LPFAccel.z/* - gMPU6050BiasAccel.z*/) * MPU6050_G_PER_LSB_8 * 1.0f;

//	gGyro.x =-gGyroTmp.y -0.014033417;
//	gGyro.y = gGyroTmp.x +0.025224293;
//	gGyro.z = gGyro.z - 0.008488423;
//	gAccel.x =-gAccelTmp.y ;
//	gAccel.y =gAccelTmp.x ;
}

void AHRS_GetEulerRPY(void)
{
//	float gx, gy, gz; // estimated gravity direction
//
//	gx = 2 * (q1*q3 - q0*q2);
//	gy = 2 * (q0*q1 + q2*q3);
//	gz = q0*q0 - q1*q1 - q2*q2 + q3*q3;
//
//
//	posture_now.yaw = atan2(2*q1*q2 - 2*q0*q3, 2*q0*q0 + 2*q1*q1 - 1) ;
//	posture_now.roll = -atan(gx / sqrt(gy*gy + gz*gz)) ;
//	posture_now.pitch = atan(gy / sqrt(gx*gx + gz*gz))  ;


}



int16 iirLPFilterSingle(volatile int32 in,volatile int32 attenuation, volatile int32* filt)
{
  int32 inScaled;
  int32 filttmp = *filt;
  int16 out;

  if (attenuation > (1<<IIR_SHIFT))
  {
    attenuation = (1<<IIR_SHIFT);
  }
  else if (attenuation < 1)
  {
    attenuation = 1;
  }

  // Shift to keep accuracy
  inScaled = in << IIR_SHIFT;
  // Calculate IIR filter
  filttmp = filttmp + (((inScaled-filttmp) >> IIR_SHIFT) * attenuation);
  // Scale and round
  out = (filttmp >> 8) + ((filttmp & (1 << (IIR_SHIFT - 1))) >> (IIR_SHIFT - 1));
  *filt = filttmp;

  return out;
}



//=====================================================================================================
// MadgwickAHRS.c
//=====================================================================================================
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
// 19/02/2012	SOH Madgwick	Magnetometer measurement is normalised
//=====================================================================================================


// AHRS algorithm update
//void MadgwickAHRSupdate(float32 gx, float32 gy, float32 gz, float32 ax, float32 ay, float32 az, float32 mx, float32 my, float32 mz) {
//	float32 recipNorm;
//	float32 s0, s1, s2, s3;
//	float32 qDot1, qDot2, qDot3, qDot4;
//	float32 hx, hy;
//	float32 _2q0mx, _2q0my, _2q0mz, _2q1mx, _2bx, _2bz, _4bx, _4bz, _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3, q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
//
//	// Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
//	if((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f)) {
//		MadgwickAHRSupdateIMU(gx, gy, gz, ax, ay, az);
//		return;
//	}
//
//	// Rate of change of quaternion from gyroscope
//	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
//	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
//	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
//	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);
//
//	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
//	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
//
//		// Normalise accelerometer measurement
//		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
//		ax *= recipNorm;
//		ay *= recipNorm;
//		az *= recipNorm;
//
//		// Normalise magnetometer measurement
//		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
//		mx *= recipNorm;
//		my *= recipNorm;
//		mz *= recipNorm;
//
//		// Auxiliary variables to avoid repeated arithmetic
//		_2q0mx = 2.0f * q0 * mx;
//		_2q0my = 2.0f * q0 * my;
//		_2q0mz = 2.0f * q0 * mz;
//		_2q1mx = 2.0f * q1 * mx;
//		_2q0 = 2.0f * q0;
//		_2q1 = 2.0f * q1;
//		_2q2 = 2.0f * q2;
//		_2q3 = 2.0f * q3;
//		_2q0q2 = 2.0f * q0 * q2;
//		_2q2q3 = 2.0f * q2 * q3;
//		q0q0 = q0 * q0;
//		q0q1 = q0 * q1;
//		q0q2 = q0 * q2;
//		q0q3 = q0 * q3;
//		q1q1 = q1 * q1;
//		q1q2 = q1 * q2;
//		q1q3 = q1 * q3;
//		q2q2 = q2 * q2;
//		q2q3 = q2 * q3;
//		q3q3 = q3 * q3;
//
//		// Reference direction of Earth's magnetic field
//		hx = mx * q0q0 - _2q0my * q3 + _2q0mz * q2 + mx * q1q1 + _2q1 * my * q2 + _2q1 * mz * q3 - mx * q2q2 - mx * q3q3;
//		hy = _2q0mx * q3 + my * q0q0 - _2q0mz * q1 + _2q1mx * q2 - my * q1q1 + my * q2q2 + _2q2 * mz * q3 - my * q3q3;
//		_2bx = sqrt(hx * hx + hy * hy);
//		_2bz = -_2q0mx * q2 + _2q0my * q1 + mz * q0q0 + _2q1mx * q3 - mz * q1q1 + _2q2 * my * q3 - mz * q2q2 + mz * q3q3;
//		_4bx = 2.0f * _2bx;
//		_4bz = 2.0f * _2bz;
//
//		// Gradient decent algorithm corrective step
//		s0 = -_2q2 * (2.0f * q1q3 - _2q0q2 - ax) + _2q1 * (2.0f * q0q1 + _2q2q3 - ay) - _2bz * q2 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q3 + _2bz * q1) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q2 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
//		s1 = _2q3 * (2.0f * q1q3 - _2q0q2 - ax) + _2q0 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q1 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + _2bz * q3 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q2 + _2bz * q0) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q3 - _4bz * q1) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
//		s2 = -_2q0 * (2.0f * q1q3 - _2q0q2 - ax) + _2q3 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q2 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + (-_4bx * q2 - _2bz * q0) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q1 + _2bz * q3) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q0 - _4bz * q2) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
//		s3 = _2q1 * (2.0f * q1q3 - _2q0q2 - ax) + _2q2 * (2.0f * q0q1 + _2q2q3 - ay) + (-_4bx * q3 + _2bz * q1) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q0 + _2bz * q2) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q1 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
//		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
//		s0 *= recipNorm;
//		s1 *= recipNorm;
//		s2 *= recipNorm;
//		s3 *= recipNorm;
//
//		// Apply feedback step
//		qDot1 -= beta * s0;
//		qDot2 -= beta * s1;
//		qDot3 -= beta * s2;
//		qDot4 -= beta * s3;
//	}
//
//	// Integrate rate of change of quaternion to yield quaternion
//	q0 += qDot1 * (1.0f / sampleFreq);
//	q1 += qDot2 * (1.0f / sampleFreq);
//	q2 += qDot3 * (1.0f / sampleFreq);
//	q3 += qDot4 * (1.0f / sampleFreq);
//
//	// Normalise quaternion
//	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
//	q0 *= recipNorm;
//	q1 *= recipNorm;
//	q2 *= recipNorm;
//	q3 *= recipNorm;
//}




//---------------------------------------------------------------------------------------------------
// IMU algorithm update
//void MadgwickAHRSupdateIMU(float32 gx, float32 gy, float32 gz, float32 ax, float32 ay, float32 az) {
//	float32 recipNorm;
//	float32 s0, s1, s2, s3;
//	float32 qDot1, qDot2, qDot3, qDot4;
//	float32 _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;
//
//	// Rate of change of quaternion from gyroscope
//	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
//	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
//	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
//	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);
//
//	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
//	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
//
//		// Normalise accelerometer measurement
//		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
//		ax *= recipNorm;
//		ay *= recipNorm;
//		az *= recipNorm;
//
//		// Auxiliary variables to avoid repeated arithmetic
//		_2q0 = 2.0f * q0;
//		_2q1 = 2.0f * q1;
//		_2q2 = 2.0f * q2;
//		_2q3 = 2.0f * q3;
//		_4q0 = 4.0f * q0;
//		_4q1 = 4.0f * q1;
//		_4q2 = 4.0f * q2;
//		_8q1 = 8.0f * q1;
//		_8q2 = 8.0f * q2;
//		q0q0 = q0 * q0;
//		q1q1 = q1 * q1;
//		q2q2 = q2 * q2;
//		q3q3 = q3 * q3;
//
//		// Gradient decent algorithm corrective step
//		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
//		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
//		s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
//		s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
//		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
//		s0 *= recipNorm;
//		s1 *= recipNorm;
//		s2 *= recipNorm;
//		s3 *= recipNorm;
//
//		// Apply feedback step
//		qDot1 -= beta * s0;
//		qDot2 -= beta * s1;
//		qDot3 -= beta * s2;
//		qDot4 -= beta * s3;
//	}
//
//	// Integrate rate of change of quaternion to yield quaternion
//	q0 += qDot1 * (1.0f / sampleFreq);
//	q1 += qDot2 * (1.0f / sampleFreq);
//	q2 += qDot3 * (1.0f / sampleFreq);
//	q3 += qDot4 * (1.0f / sampleFreq);
//
//	// Normalise quaternion
//	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
//	q0 *= recipNorm;
//	q1 *= recipNorm;
//	q2 *= recipNorm;
//	q3 *= recipNorm;
//}

//---------------------------------------------------------------------------------------------------
// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root

float32 invSqrt(float32 x) {
	float32 halfx = 0.5f * x;
	float32 y = x;
	int32 i = *(int32 *)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float32*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

//====================================================================================================
// END OF CODE
//====================================================================================================

