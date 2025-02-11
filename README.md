# stm32f407_OLED_gw
ssd1306_olde和八路巡线移植代码
传感器用的感为科技的八路灰度传感器，详情手册和历程请见：https://ganv.com.cn/grayscale_8ways.html
文件中find_addr.c/h用来寻找从机i2c地址，gw_sensor.c用来读值。
oled的代码是标准库移植到hal库
