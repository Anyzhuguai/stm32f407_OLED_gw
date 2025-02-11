#include "main.h"
	
#include "i2c.h"


//���ҵ�ַʱ��find_addr�����ݷŽ�main�����У������������Ž�main.c��,debug��addr_tab��ֵ��ȷ����ַ
  
	
	extern I2C_HandleTypeDef hi2c1;
	unsigned char found = 'A';
	unsigned char addr_tab[128]; // ���ҵ����豸��ַ����ַ������ǰ�棬������0����������豸��ַ
  char* addr_ptr = (char *)addr_tab; //ûɶ�ã����Ƿ�ֹunsed �� addr_tab���Ż�����

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
			// ��ACK
			addr_tab[addr] = 0;
		} else {
			// ��ACK�����豸����
			addr_tab[found] = addr;
			found += 1;
		}
	}
	return found;
}


int find_addr(void)
{
	// �������е�"volatile"�����ڹ۲����ݣ�volatile����ֹ��������Ŀ����Ż�������ֲ��ʱ����ȥ��"volatile"���δ�
//	volatile unsigned char found;
//	unsigned char addr_tab[128]; // ���ҵ����豸��ַ����ַ������ǰ�棬������0����������豸��ַ
//	volatile char* volatile addr_ptr = (char *)addr_tab; //ûɶ�ã����Ƿ�ֹunsed �� addr_tab���Ż�����

	while (1) {
		// ��ʼ��
		found = 0;
		clear_addr_tab((unsigned char *)addr_tab);

		found = i2c_scan((unsigned char *)addr_tab);
		/* ɨ�����,��debug�鿴found�Ƿ�>=1,>=1�������,��ַ����addr_tab,���鲻��0�ľ����ҵ����豸��ַ */

		// �ȴ�1ms
		HAL_Delay(1);
	}
}
