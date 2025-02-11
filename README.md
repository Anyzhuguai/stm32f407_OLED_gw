# stm32f407_OLED_gw
ssd1306_olde和八路巡线移植代码  
  
传感器用的感为科技的八路灰度传感器，详情手册和历程请见：https://ganv.com.cn/grayscale_8ways.html  
文件中find_addr.c/h用来寻找从机i2c地址，gw_sensor.c用来读值。  
  
oled的代码是标准库移植到hal库，代码来自于中景园科技。  
需要注意的是oled.c的delay函数，已修改成hal库可用的函数。  
如果想要单独测试oled记得关掉定时器，i2c发送或者接收失败会跳出main函数，不执行oled代码。
