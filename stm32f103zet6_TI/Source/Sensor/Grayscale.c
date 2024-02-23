#include "Grayscale.h"

uint8_t gray_sensor[8];//结果
uint8_t digital_data;

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    SPL_I2C_init
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-25
	* I2C初始化
	* I2C1 SLK->PB8 SDA->PB9  (重映射)
 **/
/* -------------------------------- end -------------------------------- */
void SPL_I2C_init(void)
{
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	
	//重映像
	GPIO_PinRemapConfig(GPIO_Remap_I2C1,ENABLE);
	
	//GPIO配置
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//I2C配置
	I2C_InitTypeDef I2C_InitStructure;	
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);

}

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Graycale_Init
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-25
	* 灰度传感器初始化
	* I2C读取端口电压 0代表黑 1代表白
	* I2C1 SLK->PB8 SDA->PB9 (重映射)
 **/
/* -------------------------------- end -------------------------------- */
void Init_Graycale(void)
{
	for(int i=0;i<8;i++)//给初始值1
	{
		gray_sensor[i]=1;
	}
	SPL_I2C_init();
	/* 打开开关量数据模式 */
	spl_i2c_write_byte(I2C1, 0x4C << 1, GW_GRAY_DIGITAL_MODE);	
	spl_i2c_read_byte(I2C1, 0x4C << 1, &digital_data); // digital_data 有1~8号探头开关数据

}

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Update_Grayscale
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-25
	* 更新灰度传感器的值
	* 八路
 **/
/* -------------------------------- end -------------------------------- */
u8* Update_Grayscale(void)
{
	/* 读取开关量数据 */
		spl_i2c_read_byte(I2C1, 0x4C << 1, &digital_data); // digital_data 有1~8号探头开关数据	
		for(int i=0;i<8;i++)
		{
			gray_sensor[i]=digital_data>>i&0x01;
		}
		return gray_sensor;
}

/*************************************下面为商家提供的代码**************************************************/

/* i2c超时时间变量,仅供参考,需要实际更改 */
static uint32_t i2c_timeout = 1000;

/* 等待事件发生,或者超时退出 */
static ErrorStatus spl_i2c_wait_event(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT, uint32_t timeout);

void i2c_set_timeout(uint32_t timeout)
{
	i2c_timeout = timeout;
}

int8_t spl_i2c_read(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t data_size)
{
	int i;
	ErrorStatus status;
	I2C_GenerateSTART(I2Cx, ENABLE);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_MODE_SELECT, i2c_timeout);
	if (status != SUCCESS)
		return 1;
	
	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Receiver);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED, i2c_timeout);
	if (status != SUCCESS)
		return 2;
	
	for (i = 0; i < data_size-1; ++i) {
		/* 因为需要应答,所以需要先准备应答位,然后再接受数据 */
		status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED, i2c_timeout);
		if (status != SUCCESS)
			return 3;
		*data++ = I2C_ReceiveData(I2Cx);
	}
	
	/* 发送数据前,拉低应答位,推高停止位,不然最后一个数据发送完再配置会导致停止位发送不及时 */
	/* 暂时关闭应答 */
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	I2C_GenerateSTOP(I2Cx, ENABLE);
	
	/* 接收最后一个数据 */
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED, i2c_timeout);
	if (status != SUCCESS)
		return 3;
	*data++ = I2C_ReceiveData(I2Cx);
	
	/* 重新打开默认的应答设置 */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	return 0;
}

int8_t spl_i2c_write_byte(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t data)
{
	return spl_i2c_write(I2Cx, addr, &data, 1);
}

int8_t spl_i2c_read_byte(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data)
{
	return spl_i2c_read(I2Cx, addr, data, 1);
}


int8_t spl_i2c_write(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t data_size)
{
	int i;
	ErrorStatus status;
	I2C_GenerateSTART(I2Cx, ENABLE);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_MODE_SELECT, i2c_timeout);
	if (status == ERROR)
		return 1;
	
	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Transmitter);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED, i2c_timeout);
	if (status == ERROR)
		return 2;
	
	for (i = 0; i < data_size-1; ++i) {
		I2C_SendData(I2Cx, *data++);
		status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING, i2c_timeout);
		if (status == ERROR)
			return 3;
	}
	
	I2C_SendData(I2Cx, *data++);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED, i2c_timeout);
	if (status == ERROR)
		return 4;
	
	I2C_GenerateSTOP(I2Cx, ENABLE);
	
	return 0;
}


int8_t spl_i2c_mem8_read(I2C_TypeDef *I2Cx, uint8_t dev_addr, uint8_t mem_addr, uint8_t *data, uint8_t data_size)
{
	int i;
	ErrorStatus status;

	/* 
		发送设备地址
	*/
	I2C_GenerateSTART(I2Cx, ENABLE);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_MODE_SELECT, i2c_timeout);
	if (status == ERROR)
		return 1;
	
	I2C_Send7bitAddress(I2Cx, dev_addr, I2C_Direction_Transmitter);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED, i2c_timeout);
	if (status == ERROR)
		return 2;

	/*
		发送寄存器地址
	*/
	
	I2C_SendData(I2Cx, mem_addr);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED, i2c_timeout);
	if (status == ERROR)
		return 3;


	/*
		无停止位重新使能,读取数据
	 */
	I2C_GenerateSTART(I2Cx, ENABLE);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_MODE_SELECT, i2c_timeout);
	if (status == ERROR)
		return 4;
	
	I2C_Send7bitAddress(I2Cx, dev_addr, I2C_Direction_Receiver);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED, i2c_timeout);
	if (status == ERROR)
		return 5;
	
	for (i = 0; i < data_size-1; ++i) {
		status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED, i2c_timeout);
		if (status != SUCCESS)
			return 6;
		*data++ = I2C_ReceiveData(I2Cx);
	}
	
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	I2C_GenerateSTOP(I2Cx, ENABLE);
	
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED, i2c_timeout);
	if (status != SUCCESS)
		return 7;
	*data++ = I2C_ReceiveData(I2Cx);
	
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	
	return 0;
}

int8_t spl_i2c_mem8_write(I2C_TypeDef *I2Cx, uint8_t dev_addr, uint8_t mem_addr, uint8_t *data, uint8_t data_size)
{
	int i;
	ErrorStatus status;
	I2C_GenerateSTART(I2Cx, ENABLE);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_MODE_SELECT, i2c_timeout);
	if (status == ERROR)
		return 1;
	
	I2C_Send7bitAddress(I2Cx, dev_addr, I2C_Direction_Transmitter);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED, i2c_timeout);
	if (status == ERROR)
		return 2;

	/* 发送寄存器地址 */
	I2C_SendData(I2Cx, mem_addr);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING, i2c_timeout);
	if (status == ERROR)
		return 3;

	/* 发送数据 */
	for (i = 0; i < data_size-1; ++i) {
		I2C_SendData(I2Cx, *data++);
		status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING, i2c_timeout);
		if (status == ERROR)
			return 3;
	}
	
	I2C_SendData(I2Cx, *data++);
	status = spl_i2c_wait_event(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED, i2c_timeout);
	if (status == ERROR)
		return 4;
	
	I2C_GenerateSTOP(I2Cx, ENABLE);
	
	return 0;
}

static ErrorStatus spl_i2c_wait_event(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT, uint32_t timeout)
{
	volatile uint32_t local_timeout = timeout;
	while(local_timeout != 0) {
		if (I2C_CheckEvent(I2Cx, I2C_EVENT) == SUCCESS) {
			return SUCCESS;
		}
		--local_timeout;
	}
	
	return ERROR;
}
