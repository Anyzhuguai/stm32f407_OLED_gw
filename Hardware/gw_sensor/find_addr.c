#include "main.h"
	
#include "i2c.h"


//查找地址时把find_addr的内容放进main函数中，把其他函数放进main.c中,debug看addr_tab的值来确定地址
  
	
	extern I2C_HandleTypeDef hi2c1;
	unsigned char found = 'A';
	unsigned char addr_tab[128]; // 存找到的设备地址，地址会排在前面，不等于0的数组就是设备地址
  char* addr_ptr = (char *)addr_tab; //没啥用，就是防止unsed 的 addr_tab被优化掉。

static void clear_addr_tab(unsigned char *addr_tab)
{
	unsigned int i = 0;
	for (i = 0; i < 128; i++) {
		addr_tab[i] = 0;
	}
}

unsigned char i2c_scan(unsigned char *addr_tab)
{
	HAL_StatusTypeDef result;
	uint8_t addr;
	unsigned char found = 0;
	for (addr = 1; addr < 128; addr++) {
		result = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t) (addr << 1), 2, 100);
		if (result != HAL_OK) {
			// HAL_ERROR or HAL_BUSY or HAL_TIMEOUT
			// 无ACK
			addr_tab[addr] = 0;
		} else {
			// 有ACK：有设备存在
			addr_tab[found] = addr;
			found += 1;
		}
	}
	return found;
}


int find_addr(void)
{
	// 此例程中的"volatile"仅用于观察数据（volatile会阻止编译器对目标的优化），移植的时候请去掉"volatile"修饰词
//	volatile unsigned char found;
//	unsigned char addr_tab[128]; // 存找到的设备地址，地址会排在前面，不等于0的数组就是设备地址
//	volatile char* volatile addr_ptr = (char *)addr_tab; //没啥用，就是防止unsed 的 addr_tab被优化掉。

	while (1) {
		// 初始化
		found = 0;
		clear_addr_tab((unsigned char *)addr_tab);

		found = i2c_scan((unsigned char *)addr_tab);
		/* 扫描完毕,用debug查看found是否>=1,>=1的情况下,地址存于addr_tab,数组不是0的就是找到的设备地址 */

		// 等待1ms
		HAL_Delay(1);
	}
}
