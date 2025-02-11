#include <stdint.h>  // ʹ�� uint8_t ��ȷ��������
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "i2c.h"
#include "gpio.h"
#include "string.h"
#include "gw_sensor.h"
	char mesg[10] = {0};
	char start[] = "start";
	int pwmval = 0;
	
	
extern TIM_HandleTypeDef htim1;	
extern  int ret_transmit, ret_receive;
extern	uint8_t recv_value;
extern	uint8_t i2c_cmd;
extern	uint8_t sensor_arr[8];
int dir= 0;	

int DetermineDirection(uint8_t sensor_data);
void TurnLeft(void);
void Straight(void);
void TurnRight(void);
// ����PWM���ֵ����Ӧ100%ռ�ձȣ�
#define PWM_MAX 100

// �ⲿ������ʱ������������ʵ�������޸ģ�


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//��ʱ��1����i2cͨ��
	if(htim == &htim1){
			ret_receive = HAL_I2C_Master_Receive(&hi2c1, GW_GRAY_ADDR << 1, &recv_value, 8, 1000);
			if (ret_receive) {
				Error_Handler(); //i2c ����
			}
			HAL_UART_Transmit_IT(&huart2, sensor_arr,strlen(sensor_arr));
	}
	
	//��ʱ��2�������Ƶ��
	if(htim == &htim2){
			dir = DetermineDirection(recv_value);
		if(dir == 1){
				TurnLeft();
		}else if(dir == 2){
				TurnRight();
		}else{
				Straight();
		}
	}
}



/**
  * @brief  ���ݰ�·�����������ж�ת������ѭ������Դ�Ѻã�
  * @param  sensor_data ���������ݣ�bit7Ϊ����࣬bit0Ϊ���Ҳࣩ
  * @retval 1:��ת  2:��ת  3:ֱ��
  */
int DetermineDirection(uint8_t sensor_data) {
    // ��ת�����������������2����������������11xxxxxx��
    if ((sensor_data & 0xC0) == 0xC0||(sensor_data & 0x80) == 0x80){  // 0xE0 = 11000000
        return 1;
    }
    
    // ��ת�������Ҳ���������2����������������xxxxxx11��
    if ((sensor_data & 0x03) == 0x03||(sensor_data & 0x01) == 0x01) {  // 0x03 = 00000011
        return 2;
    }
    
    // �������ֱ��
    return 3;
}


// ֱ�У��������ȫ��
void Straight(void) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM_MAX); // ����
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM_MAX); // �ҵ��
}

// ��ת���ҵ��ȫ�٣�����ֹͣ
void TurnLeft(void) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);       // ����ֹͣ
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM_MAX); // �ҵ��ȫ��
}

// ��ת������ȫ�٣��ҵ��ֹͣ
void TurnRight(void) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM_MAX); // ����ȫ��
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);       // �ҵ��ֹͣ
}
