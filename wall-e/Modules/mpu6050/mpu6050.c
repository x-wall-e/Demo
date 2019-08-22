#include "mpu6050.h"

/* IMUֱ direct sampled data structure */
extern struct MPU6050_tag g_MPU6050Data;
/* IMU filtered, calibrated data structure */
struct MPU6050Filter_tag g_MPU6050Data_Filter;
/* IMU calibration parameter */
s32 g_Gyro_xoffset = 0, g_Gyro_yoffset = 0, g_Gyro_zoffset = 0;
s32 g_Acc_xoffset = 0, g_Acc_yoffset = 0, g_Acc_zoffset = 0;



/*************************************
Function：void MPU6050_WirteByte(u8 reg, u8 data)
Description：MPU6050 single-byte write
Input:
	u8 reg：Register address
	u8 data：Bytes to be written
Return:None
Others:None
*************************************/
void MPU6050_WirteByte(u8 reg, u8 data)
{
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);      // Transmit device address + write signal
    IIC_Send_Byte(reg);                 // Register address
    IIC_Send_Byte(data);                // Bytes to be written
    IIC_Stop();
}

/*************************************
Function：u8 MPU6050_ReadByte(u8 reg)
Description：MPU6050 single-byte read
Input:
	u8 reg：Register address
Return:
	u8 data：Byte read
Others:None
*************************************/
u8 MPU6050_ReadByte(u8 reg)
{
    u8 tmp;

    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);          // Transmit device address + write signal
    IIC_Send_Byte(reg);                     // Register address to be read
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE + 1);      // Transmit device address + read signal
    tmp = IIC_Read_Byte(0);                 // Reading data and generate nACK
    IIC_Stop();

    return tmp;
}

/*************************************
Function：void MPU6050_Init(void)
Description：Initial MPU6050
Input:None
Return:None
Others:None
*************************************/

void MPU6050_Init(void)
{
    MPU6050_WirteByte(PWR_MGMT_1, 0x80);
    delay_ms(100);
	/*
		- Release the sleep state
		- Enable the temperature sensor
	*/
    MPU6050_WirteByte(PWR_MGMT_1, 0x00);
	/*
		- Gyro and accelerometer sampling rates
		- Related to the gyroscope output frequency
		- Related to DLPF
		- The larger the bandwidth, the more sensitive, the louder the noise, the larger the output frequency required, and the larger the sampling rate
	*/
    MPU6050_WirteByte(SMPLRT_DIV, 0x01);
	/*
		- The bandwidth in DLPF is set to a minimum of 5 Hz
		- Although it is not sensitive, but the noise is small
	*/
    MPU6050_WirteByte(MPU6050_CONFIG, 0x06);
	/*
		- The range is 500°/s
		- Sampling frequency: (SMPLRT_DIV + 1) / 1KHz = 500Hz
		- Gyroscope output frequency: 1KHz
	*/
    MPU6050_WirteByte(GYRO_CONFIG, 0x08);
	/*
		- The range is +/-4g
	*/
    MPU6050_WirteByte(ACCEL_CONFIG, 0x08);
	
	#if 0
	MPU6050_WirteByte(PWR_MGMT_1, 0x80); 	//0x6B: Resets all internal registers to their default values.										
											//		The bit automatically clears to 0 once the reset is done.
    delay_ms(100);
	
    MPU6050_WirteByte(PWR_MGMT_1, 0x00);	//0x6B: Release the sleep state and enable the temperature sensor.
	MPU6050_WirteByte(GYRO_CONFIG, 0x08);	//0x1B: ±2000dps
	MPU6050_WirteByte(ACCEL_CONFIG, 0x00);	//0x1C: ±2g
	/* 采样频率大于被采样信号最高频率的两倍 */
	MPU6050_WirteByte(SMPLRT_DIV, 0x01);	//0x19: Sample Rate Divider: 50Hz
	MPU6050_WirteByte(MPU6050_CONFIG, 0x02);//0x1A: DLPF = rate / 2
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//0x38: Disable all interrupt
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//0x6A: Disable I2C master mode
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//0x23: Disable FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//0x37: The logic level for the INT pin is active low.
	
	if(MPU6050_testConnection())
	{
		MPU_Write_Byte(PWR_MGMT_1,0X01);		//0x6B：CLKSEL：PLL with X axis gyroscope reference
		MPU_Write_Byte(PWR_MGMT_2,0X00);		//0x6C:
		MPU6050_WirteByte(SMPLRT_DIV, 0x01); 	//0x19: Sample Rate Divider: 50Hz
		MPU6050_WirteByte(MPU6050_CONFIG, 0x02);//0x1A: DLPF = rate / 2
	}
	#endif
}

/**********************************************************************
Function：void MPU6050_getDeviceID(u8 reg)
Description：read  MPU6050 WHO_AM_I register
Input:None
Return:	
	uint8_t: 0x68 
Others:None
***********************************************************************/
static uint8_t MPU6050_getDeviceID(void) 
{
	uint8_t id;
	
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);              // Transmit device address + write signal
    IIC_Send_Byte(WHO_AM_I);                    // Register address to be read
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE + 1);          // Transmit device address + read signal
    id = IIC_Read_Byte(0);                      // Reading data and generate nACK
    IIC_Stop();
	
    return id;
}

/**********************************************************************
Function：void MPU6050_testConnection(void)
Description：Test mpu6050 connection
Input:None
Return:	
		1: Connect ok.
		2: No connection.
Others:None
***********************************************************************/
static uint8_t MPU6050_testConnection(void) 
{
	if(MPU6050_getDeviceID() == 0x68)  //0b01101000;
		return 1;
	else 
		return 0;
}

/**********************************************************************
Function：void MPU6050_Check(void) 
Description：Check MPU6050 found or not
Input:None
Return:None
Others:None
***********************************************************************/
void MPU6050_Check(void) 
{ 
  switch(MPU6050_testConnection())
  {
    case 0:
		printf("MPU6050 not found...\r\n");
		break;
    case 1:
		printf("MPU6050 check success...\r\n");
		break;
}

/*********************************************
Function：short MPU_Get_Temperature(void)
Description：Get MPU6050 temperature
Input:None
Return:
		temperature * 100
Others:None
*********************************************/
short MPU_Get_Temperature(void)
{
	u8 H1, L1;
	short raw;
	float temp;
	
	IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);              // Transmit device address + write signal
    IIC_Send_Byte(reg);                         // Register address to be read
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE + 1);          // Transmit device address + read signal
    H1 = IIC_Read_Byte(1);                      // Reading data and generate ACK
    L1 = IIC_Read_Byte(0);                      // Read from low to high in order of address
    IIC_Stop();

    raw = (H1 << 8) + L1;

	temp = 36.53 + ((double)raw)/340;
	
	return temp * 100;;
}

/*********************************************
Function：void Get_Accel_Data(u8 reg)
Description：Get MPU6050 accelerometer data
Input:
	u8 reg: Register address
Return:None
Others:None
*********************************************/
void Get_Accel_Data(u8 reg)
{
    u8 H1, L1;
    u8 H2, L2;
    u8 H3, L3;

    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);          // Transmit device address + write signal
    IIC_Send_Byte(reg);                     // Register address to be read
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE + 1);      // Transmit device address + read signal
    H1 = IIC_Read_Byte(1);                  // Reading data and generate ACK
    L1 = IIC_Read_Byte(1);                  // Read from low to high in order of address
    H2 = IIC_Read_Byte(1);
    L2 = IIC_Read_Byte(1);
    H3 = IIC_Read_Byte(1);
    L3 = IIC_Read_Byte(0);
    IIC_Stop();

    g_MPU6050Data.accel_x = (H1 << 8) + L1;
    g_MPU6050Data.accel_y = (H2 << 8) + L2;
    g_MPU6050Data.accel_z = (H3 << 8) + L3;
}

/*************************************
Function：void Get_Gyro_Data(u8 reg)
Description：Get MPU6050 gyro data
Input:
	u8 reg: Register address
Return:None
Others:None
*************************************/
void Get_Gyro_Data(u8 reg)
{
    u8 H1, L1;
    u8 H2, L2;
    u8 H3, L3;

    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);              // Transmit device address + write signal
    IIC_Send_Byte(reg);                         // Register address to be read
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE + 1);          // Transmit device address + read signal
    H1 = IIC_Read_Byte(1);                      // Reading data and generate ACK
    L1 = IIC_Read_Byte(1);                      // Read from low to high in order of address
    H2 = IIC_Read_Byte(1);
    L2 = IIC_Read_Byte(1);
    H3 = IIC_Read_Byte(1);
    L3 = IIC_Read_Byte(0);
    IIC_Stop();

    g_MPU6050Data.gyro_x = (H1 << 8) + L1;
    g_MPU6050Data.gyro_y = (H2 << 8) + L2;
    g_MPU6050Data.gyro_z = (H3 << 8) + L3;
}

/*************************************
Function：void ReadFromIMU(void)
Description：Read the data of the MPU6050, including the accelerometer and gyroscope
Input:None
Return:None
Others:None
*************************************/
void ReadFromIMU(void)
{
    Get_Accel_Data(ACCEL_XOUT_H);       //accelerometer( total 3 data )
    Get_Gyro_Data(GYRO_XOUT_H);         //gyroscope( total 3 data )
}


/*************************************
Function：void IMU_Calibration(void)
Description：MPU6050 Calibration
Input:None
Return:None
Others:None
*************************************/
void IMU_Calibration(void)
{
	u8 i;

	for (i = 0; i < 30; i++)	// Continuous sampling 30 times, total time consuming : 30 * 3 = 90ms
	{
		ReadFromIMU();			// Read the data of MPU6050
		g_Gyro_xoffset += g_MPU6050Data.gyro_x;
		g_Gyro_yoffset += g_MPU6050Data.gyro_y;
		g_Gyro_zoffset += g_MPU6050Data.gyro_z;
		delay_ms(3);
	}
	g_Gyro_xoffset /= 30;		// Get calibration offset
	g_Gyro_yoffset /= 30;
	g_Gyro_zoffset /= 30;
}
