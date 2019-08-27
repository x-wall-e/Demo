#ifndef __MPU6050_H
#define __MPU6050_H

#include "stm32f10x.h"
#include "iic.h"
#include "delay.h"
#include <stdio.h>
//#include "fusion.h"

/* MPU6050 register */
#define	SMPLRT_DIV			0x19	// Gyro sampling rate,Typical value:0x07(125Hz)
#define	MPU6050_CONFIG		0x1A	// Low pass filter frequency,Typical value:0x06(5Hz)
#define	GYRO_CONFIG			0x1B	// Gyro self-test and measurement range,Typical value:0x18(Not self-test,2000deg/s)
#define	ACCEL_CONFIG		0x1C	// Accelerometer self-test, measurement range and high-pass filter frequency,Typical value:0x00(Not self-test,2g,5Hz)
#define MPU_FIFO_EN_REG		0X23
#define MPU_I2CMST_STA_REG	0X36
#define MPU_INTBP_CFG_REG	0X37
#define MPU_INT_EN_REG		0X38
#define MPU_INT_STA_REG		0X3A
#define	ACCEL_XOUT_H		0x3B
#define	ACCEL_XOUT_L		0x3C
#define	ACCEL_YOUT_H		0x3D
#define	ACCEL_YOUT_L		0x3E
#define	ACCEL_ZOUT_H		0x3F
#define	ACCEL_ZOUT_L		0x40
#define	TEMP_OUT_H			0x41
#define	TEMP_OUT_L			0x42
#define	GYRO_XOUT_H			0x43
#define	GYRO_XOUT_L			0x44
#define	GYRO_YOUT_H			0x45
#define	GYRO_YOUT_L			0x46
#define	GYRO_ZOUT_H			0x47
#define	GYRO_ZOUT_L			0x48
#define MPU_USER_CTRL_REG	0X6A
#define	PWR_MGMT_1			0x6B	// Power management 1,Typical value:0x00(Normally enabled)
#define PWR_MGMT_2			0X6C	// Power management 1
#define WHO_AM_I			0x75	// The default value of the register is 0x68. Bits 0 and 7 are reserved. (Hard coded to 0)


/* MPU6050 slave address·*/
#define	MPU6050_DEVICE	0xD0		// Address register when IIC is written, +1 is read, AD0 is grounded

/* Structure variable declaration */
struct MPU6050_tag	// IMU direct sampled value
{
	s16 accel_x;	// Accelerometer x
	s16 accel_y;	// Accelerometer y
	s16 accel_z;	// Accelerometer z
	s16 gyro_x;		// Gyro x
	s16 gyro_y;		// Gyro y
	s16 gyro_z;		// Gyro z
};

struct MPU6050Filter_tag	// IMU filtered value
{
	s16 accel_x_f;	// Accelerometer x filtered value
	s16 accel_y_f;	// Accelerometer y filtered value
	s16 accel_z_f;	// Accelerometer z filtered value
	s16 gyro_x_c;	// Gyro x filtered value
	s16 gyro_y_c;	// Gyro y filtered value
	s16 gyro_z_c;	// Gyro z filtered value
};

extern struct MPU6050_tag g_MPU6050Data;				// IMU direct sampled value
extern struct MPU6050Filter_tag g_MPU6050Data_Filter;	// IMU filtered structure
extern s32 g_Gyro_xoffset;								// Error after IMU calibration
extern s32 g_Gyro_yoffset;
extern s32 g_Gyro_zoffset;


//-----Operation Func-----//
extern void MPU6050_Init(void);							// Initial MPU6050
extern void MPU6050_WirteByte(u8 reg, u8 data);			// MPU6050 Single write byte
extern u8 MPU6050_ReadByte(u8 reg);						// MPU6050 Single read byte
extern void	Get_Accel_Data(u8 reg);						// Get MPU6050 Accelerometer data
extern void	Get_Gyro_Data(u8 reg);						// Get MPU6050 Gyro data
extern void IMU_Calibration(void);						// MPU6050 calibration
extern void ReadFromIMU(void);
extern void MPU6050_Check(void);						//Check MPU6050 found or not
extern short MPU_Get_Temperature(void);					//Get MPU6050 temperature
extern u8 MPU_Read_Len(u8 dev, u8 reg, u8 length, u8 *data);
extern u8 MPU_Write_Len(u8 dev, u8 reg, u8 length, u8* data);

#endif
