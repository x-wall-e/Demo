#include "mpu6050.h"

//-----IMUֱ�Ӳ���ֵ�ṹ��-----//
struct MPU6050_tag g_MPU6050Data;
//-----IMU�˲����궨���Ľṹ��-----//
struct MPU6050Filter_tag g_MPU6050Data_Filter;
//-----IMU�궨����-----//
s32 g_Gyro_xoffset = 0, g_Gyro_yoffset = 0, g_Gyro_zoffset = 0;
s32 g_Acc_xoffset = 0, g_Acc_yoffset = 0, g_Acc_zoffset = 0;



/***********************************************
��������void MPU6050_WirteByte(u8 reg, u8 data)
˵����MPU6050����д�ֽ�
���ڣ�u8 reg		�Ĵ�����ַ
			u8 data		��Ҫд�����ֽ�
���ڣ���
��ע����
***********************************************/
void MPU6050_WirteByte(u8 reg, u8 data)
{
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);      // ����������ַ+д�ź�
    IIC_Send_Byte(reg);                 // �Ĵ�����ַ
    IIC_Send_Byte(data);                // ��Ҫд��������
    IIC_Stop();
}

/***********************************
��������u8 MPU6050_ReadByte(u8 reg)
˵����MPU6050���ζ��ֽ�
���ڣ�u8	reg		�Ĵ�����ַ
���ڣ�u8	��ȡ�����ֽ�
��ע����
************************************/
u8 MPU6050_ReadByte(u8 reg)
{
    u8 tmp;

    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);          // ����������ַ+д�ź�
    IIC_Send_Byte(reg);                     // ��Ҫ��ȡ�ļĴ�����ַ
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE + 1);      // ����������ַ+���ź�
    tmp = IIC_Read_Byte(0);                 // ��ȡ���ݲ�����Ӧ��
    IIC_Stop();

    return tmp;
}



/*******************************
��������void MPU6050_Init(void)
˵����MPU6050��ʼ��
���ڣ���
���ڣ���
��ע����
********************************/
void MPU6050_Init(void)
{
    MPU6050_WirteByte(PWR_MGMT_1, 0x00);            // ��������״̬,ʹ���¶ȴ�����
    MPU6050_WirteByte(SMPLRT_DIV, 0x01);            // �����Ǻͼ��ٶȼƲ����ʣ�������������Ƶ�����أ�����DLPF���ء�����Խ����Խ����������Խ������Ҫ������Ƶ��Խ�󣬴Ӷ�������Խ��
    MPU6050_WirteByte(MPU6050_CONFIG, 0x06);        // DLPF�еĴ�������Ϊ��С5Hz����Ȼ����������������С
    MPU6050_WirteByte(GYRO_CONFIG, 0x08);           // ����Ϊ500��/s,(SMPLRT_DIV + 1) / 1KHz= 500Hz����Ƶ�ʣ�����������Ƶ��Ϊ1KHz
    MPU6050_WirteByte(ACCEL_CONFIG, 0x08);          // ����Ϊ+/-4g
}

/***********************************
��������void Get_Accel_Data(u8 reg)
˵�����õ�MPU6050���ٶȼ�����
���ڣ�u8	reg		�Ĵ�����ַ
���ڣ���
��ע����
***********************************/
void Get_Accel_Data(u8 reg)
{
    u8 H1, L1;
    u8 H2, L2;
    u8 H3, L3;

    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);          // ����������ַ+д�ź�
    IIC_Send_Byte(reg);                     // ��Ҫ��ȡ�ļĴ�����ַ
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE + 1);      // ����������ַ+���ź�
    H1 = IIC_Read_Byte(1);                  // ��ȡ���ݲ���Ӧ��
    L1 = IIC_Read_Byte(1);                  // ���յ�ַ˳���ӵ����߶�ȡ
    H2 = IIC_Read_Byte(1);
    L2 = IIC_Read_Byte(1);
    H3 = IIC_Read_Byte(1);
    L3 = IIC_Read_Byte(0);
    IIC_Stop();

    g_MPU6050Data.accel_x = (H1 << 8) + L1;
    g_MPU6050Data.accel_y = (H2 << 8) + L2;
    g_MPU6050Data.accel_z = (H3 << 8) + L3;
}

/**********************************
��������void Get_Gyro_Data(u8 reg)
˵�����õ�MPU6050����������
���ڣ�u8	reg		�Ĵ�����ַ
���ڣ���
��ע����
**********************************/
void Get_Gyro_Data(u8 reg)
{
    u8 H1, L1;
    u8 H2, L2;
    u8 H3, L3;

    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE);              // ����������ַ+д�ź�
    IIC_Send_Byte(reg);                         // ��Ҫ��ȡ�ļĴ�����ַ
    IIC_Start();
    IIC_Send_Byte(MPU6050_DEVICE + 1);          // ����������ַ+���ź�
    H1 = IIC_Read_Byte(1);                      // ��ȡ���ݲ���Ӧ��
    L1 = IIC_Read_Byte(1);                      // ���յ�ַ˳���ӵ����߶�ȡ
    H2 = IIC_Read_Byte(1);
    L2 = IIC_Read_Byte(1);
    H3 = IIC_Read_Byte(1);
    L3 = IIC_Read_Byte(0);
    IIC_Stop();

    g_MPU6050Data.gyro_x = (H1 << 8) + L1;
    g_MPU6050Data.gyro_y = (H2 << 8) + L2;
    g_MPU6050Data.gyro_z = (H3 << 8) + L3;
}

void ReadFromIMU(void)
{
    Get_Accel_Data(ACCEL_XOUT_H);       //¼ÓËÙ¶È¼Æ
    Get_Gyro_Data(GYRO_XOUT_H);         //ÍÓÂÝÒÇ
}


/**********************************
��������void IMU_Calibration(void)
˵����MPU6050�궨
���ڣ���
���ڣ���
��ע����������ʱ�趨�����ǵ���ֵ
**********************************/

void IMU_Calibration(void)
{
	u8 i;

	for (i = 0; i < 30; i++)	//��������30�Σ�һ����ʱ30*3=90ms
	{
		ReadFromIMU();			// ��ȡMPU6050��ֵ
		g_Gyro_xoffset += g_MPU6050Data.gyro_x;
		g_Gyro_yoffset += g_MPU6050Data.gyro_y;
		g_Gyro_zoffset += g_MPU6050Data.gyro_z;
		delay_ms(3);
	}
	g_Gyro_xoffset /= 30;		// �õ��궨ƫ��
	g_Gyro_yoffset /= 30;
	g_Gyro_zoffset /= 30;
}
