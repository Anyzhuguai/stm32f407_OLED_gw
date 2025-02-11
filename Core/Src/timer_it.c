#include <stdint.h>  // 使用 uint8_t 明确数据类型
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
// 定义PWM最大值（对应100%占空比）
#define PWM_MAX 100

// 外部声明定时器句柄（需根据实际配置修改）


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//定时器1用来i2c通信
	if(htim == &htim1){
			ret_receive = HAL_I2C_Master_Receive(&hi2c1, GW_GRAY_ADDR << 1, &recv_value, 8, 1000);
			if (ret_receive) {
				Error_Handler(); //i2c 错误
			}
			HAL_UART_Transmit_IT(&huart2, sensor_arr,strlen(sensor_arr));
	}
	
	//定时器2用来控制电机
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
  * @brief  根据八路传感器数据判断转向方向（无循环，资源友好）
  * @param  sensor_data 传感器数据（bit7为最左侧，bit0为最右侧）
  * @retval 1:左转  2:右转  3:直行
  */
int DetermineDirection(uint8_t sensor_data) {
    // 左转条件：左侧至少连续2个传感器触发（如11xxxxxx）
    if ((sensor_data & 0xC0) == 0xC0||(sensor_data & 0x80) == 0x80){  // 0xE0 = 11000000
        return 1;
    }
    
    // 右转条件：右侧至少连续2个传感器触发（如xxxxxx11）
    if ((sensor_data & 0x03) == 0x03||(sensor_data & 0x01) == 0x01) {  // 0x03 = 00000011
        return 2;
    }
    
    // 其他情况直行
    return 3;
}


// 直行：两个电机全速
void Straight(void) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM_MAX); // 左电机
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM_MAX); // 右电机
}

// 左转：右电机全速，左电机停止
void TurnLeft(void) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);       // 左电机停止
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM_MAX); // 右电机全速
}

// 右转：左电机全速，右电机停止
void TurnRight(void) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM_MAX); // 左电机全速
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);       // 右电机停止
}
