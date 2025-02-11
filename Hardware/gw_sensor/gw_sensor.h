/*
 * Copyright (c) 2022 ��Ϊ���ܿƼ�(����)
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */
#ifndef INC_GW_GRAYSCALE_SENSOR_H_
#define INC_GW_GRAYSCALE_SENSOR_H_

#define USE_GW_GRAY_NORMALIZE 0

#define GW_GRAY_ADDR GW_GRAY_ADDR_DEF

#include <stdint.h>
#include "i2c.h"
//	int ret_transmit;
//	int ret_receive;
//	uint8_t recv_value = 0;
//	uint8_t i2c_cmd;
//	uint8_t sensor_arr[8];
/* Ĭ�ϵ�ַ */
#define GW_GRAY_ADDR_DEF 0x4C
#define GW_GRAY_PING 0xAA
#define GW_GRAY_PING_OK 0x66
#define GW_GRAY_PING_RSP GW_GRAY_PING_OK

/* ������������ģʽ */
#define GW_GRAY_DIGITAL_MODE 0xDD

/* ����������ȡģ������ģʽ */
#define GW_GRAY_ANALOG_BASE_ 0xB0
#define GW_GRAY_ANALOG_MODE  (GW_GRAY_ANALOG_BASE_ + 0)

/* ��������һ���Ĵ���(v3.6��֮��Ĺ̼�) */
#define GW_GRAY_ANALOG_NORMALIZE 0xCF

/* ѭ����ȡ����̽ͷģ������ n��1��ʼ��8 */
#define GW_GRAY_ANALOG(n) (GW_GRAY_ANALOG_BASE_ + (n))

/* ��ɫ�ͻرȽϲ������� */
#define GW_GRAY_CALIBRATION_BLACK 0xD0
/* ��ɫ�ͻرȽϲ������� */
#define GW_GRAY_CALIBRATION_WHITE 0xD1

// ��������̽ͷ��ģ���ź�(CE: channel enable)
#define GW_GRAY_ANALOG_CHANNEL_ENABLE 0xCE
#define GW_GRAY_ANALOG_CH_EN_1 (0x1 << 0)
#define GW_GRAY_ANALOG_CH_EN_2 (0x1 << 1)
#define GW_GRAY_ANALOG_CH_EN_3 (0x1 << 2)
#define GW_GRAY_ANALOG_CH_EN_4 (0x1 << 3)
#define GW_GRAY_ANALOG_CH_EN_5 (0x1 << 4)
#define GW_GRAY_ANALOG_CH_EN_6 (0x1 << 5)
#define GW_GRAY_ANALOG_CH_EN_7 (0x1 << 6)
#define GW_GRAY_ANALOG_CH_EN_8 (0x1 << 7)
#define GW_GRAY_ANALOG_CH_EN_ALL (0xFF)

/* ��ȡ������Ϣ */
#define GW_GRAY_ERROR 0xDE

/* �豸������� */
#define GW_GRAY_REBOOT 0xC0

/* ��ȡ�̼��汾�� */
#define GW_GRAY_FIRMWARE 0xC1


/**
 * @brief ��I2C�õ���8λ�������źŵ����� ��ȡ��nλ������
 * @param sensor_value_8 ����IO������
 * @param n ��1λ��1��ʼ, n=1 �Ǵ������ĵ�һ��̽ͷ����, n=8�����һ��
 * @return
 */
#define GET_NTH_BIT(sensor_value, nth_bit) (((sensor_value) >> ((nth_bit)-1)) & 0x01)


/**
 * @brief ��һ��������������е�bit
 */
#define SEP_ALL_BIT8(sensor_value, val1, val2, val3, val4, val5, val6, val7, val8) \
do {                                                                              \
val1 = GET_NTH_BIT(sensor_value, 1);                                              \
val2 = GET_NTH_BIT(sensor_value, 2);                                              \
val3 = GET_NTH_BIT(sensor_value, 3);                                              \
val4 = GET_NTH_BIT(sensor_value, 4);                                              \
val5 = GET_NTH_BIT(sensor_value, 5);                                              \
val6 = GET_NTH_BIT(sensor_value, 6);                                              \
val7 = GET_NTH_BIT(sensor_value, 7);                                              \
val8 = GET_NTH_BIT(sensor_value, 8);                                              \
} while(0)

/* �����豸I2C��ַ */
#define GW_GRAY_CHANGE_ADDR 0xAD

/* �㲥���õ�ַ����Ҫ�������� */
#define GW_GRAY_BROADCAST_RESET "\xB8\xD0\xCE\xAA\xBF\xC6\xBC\xBC"

#if defined (ESP_PLATFORM)
/* ESP32 */


#endif


//int mainnm(void)
//{

//  int ret_transmit, ret_receive;
//	uint8_t recv_value = 0;
//	uint8_t i2c_cmd;
//	uint8_t sensor_arr[8];


//#if (USE_GW_GRAY_NORMALIZE)
//	uint8_t write_data = 0xFF;
//	ret_transmit = HAL_I2C_Mem_Write(&hi2c1,
//	                        GW_GRAY_ADDR << 1, GW_GRAY_ANALOG_NORMALIZE, 1,
//	                        &write_data, 1, 100);
//	if (ret_transmit != HAL_OK) {
//		// i2c ����
//	}
//#endif

//	/* ����ģ������ģʽ, �������֮��, ѭ����ȡ8��̽ͷ��ģ������ */
//	i2c_cmd = GW_GRAY_ANALOG_MODE;
//	ret_transmit = HAL_I2C_Master_Transmit(&hi2c1, GW_GRAY_ADDR << 1, &i2c_cmd, 1, 100);
//	if (ret_transmit != HAL_OK) {
//		Error_Handler();
//	}
//	
//	while (1) {
//		ret_receive = HAL_I2C_Master_Receive(&hi2c1, GW_GRAY_ADDR << 1, sensor_arr, 8, 100);
// 		if (ret_receive) {
//			Error_Handler(); //i2c ����
//		}
//		// sensor_arr[0] ��̽ͷ1
//		// ...
//		// sensor_arr[7] ��̽ͷ8
//		
//		HAL_Delay(1);
//	}
//}

#endif /* INC_GW_GRAYSCALE_SENSOR_H_ */
