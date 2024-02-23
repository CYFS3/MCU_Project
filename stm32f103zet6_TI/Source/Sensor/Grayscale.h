#ifndef _GRAYSCALE_H__
#define _GRAYSCALE_H__
#include "config.h"
/* 默认地址 */
#define GW_GRAY_ADDR_DEF 0x4C
#define GW_GRAY_PING 0xAA
#define GW_GRAY_PING_OK 0x66
#define GW_GRAY_PING_RSP GW_GRAY_PING_OK
/* 开启开关数据模式 */
#define GW_GRAY_DIGITAL_MODE 0xDD
/* 传感器归一化寄存器(v3.6及之后的固件) */
#define GW_GRAY_ANALOG_NORMALIZE 0xCF
/* 黑色滞回比较参数操作 */
#define GW_GRAY_CALIBRATION_BLACK 0xD0
/* 白色滞回比较参数操作 */
#define GW_GRAY_CALIBRATION_WHITE 0xD1
/* 读取错误信息 */
#define GW_GRAY_ERROR 0xDE
/* 设备软件重启 */
#define GW_GRAY_REBOOT 0xC0
/* 读取固件版本号 */
#define GW_GRAY_FIRMWARE 0xC1
/* 设置设备I2C地址 */
#define GW_GRAY_CHANGE_ADDR 0xAD


extern uint8_t gray_sensor[8];
u8* Update_Grayscale(void);
void Init_Graycale(void);

/***************************************商家提供**************************************************************/
__inline void i2c_set_timeout(uint32_t timeout);
int8_t spl_i2c_write_byte(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t data);
int8_t spl_i2c_read_byte(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data);
int8_t spl_i2c_read(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t data_size);
int8_t spl_i2c_write(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t data_size);
int8_t spl_i2c_mem8_write(I2C_TypeDef *I2Cx, uint8_t dev_addr, uint8_t mem_addr, uint8_t *data, uint8_t data_size);
int8_t spl_i2c_mem8_read(I2C_TypeDef *I2Cx, uint8_t dev_addr, uint8_t mem_addr, uint8_t *data, uint8_t data_size);



#endif
