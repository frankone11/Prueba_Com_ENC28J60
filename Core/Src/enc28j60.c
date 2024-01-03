#include "main.h"
#include <stdint.h>
#include "string.h"
#include "enc28j60.h"
#include "stdio.h"

#define ENC28J60_CS_Low()	HAL_GPIO_WritePin(ENC28J60_CS_GPIO_Port, ENC28J60_CS_Pin, GPIO_PIN_RESET)
#define ENC28J60_CS_High()	HAL_GPIO_WritePin(ENC28J60_CS_GPIO_Port, ENC28J60_CS_Pin, GPIO_PIN_SET)

SPI_HandleTypeDef *spi = NULL;
extern UART_HandleTypeDef huart1;

void ENC28J60_Init(SPI_HandleTypeDef *hspi)
{
	spi = hspi;
}

uint8_t ENC28J60_ReadRegETH(uint8_t address)
{
	uint8_t cmd[2] = {0,0}, reg_value[2]={0,0};

	cmd[0] = address & 0x1FU;

	ENC28J60_CS_Low();

	HAL_SPI_TransmitReceive(spi, cmd, reg_value, 2, 1000);

	ENC28J60_CS_High();

	return reg_value[1];

}

uint8_t ENC28J60_ReadRegMACMII(uint8_t address)
{
	uint8_t cmd[3] = {0,0,0}, reg_value[3] = {0,0,0};

	cmd[0] = address & 0x1FU;

	ENC28J60_CS_Low();

	HAL_SPI_TransmitReceive(spi, cmd, reg_value, 2, 1000);

	ENC28J60_CS_High();

	return reg_value[2];
}

void ENC28J60_RegDump()
{
	uint8_t reg;

	printf("\nREG DUMP START ...\n");

	for(uint8_t i = 0; i < 32; i++)
	{
		reg = ENC28J60_ReadRegETH(i);
		printf("REG%02d(0x%02X) = %03d(0x%02X)\n", i, i, reg, reg);
	}

	printf("REG DUMP FINISHED !\n");
}

void ENC28J60_BitSet(uint8_t address, uint8_t mask)
{
	uint8_t cmd[2] = {0,0};

	cmd[0] = (address & 0x1FU) | 0x80U;
	cmd[1] = mask;

	ENC28J60_CS_Low();

	HAL_SPI_Transmit(spi, cmd, 2, 1000);

	ENC28J60_CS_High();
}


void ENC28J60_BitClear(uint8_t address, uint8_t mask)
{
	uint8_t cmd[2] = {0,0};

	cmd[0] = (address & 0x1FU) | 0xA0U;
	cmd[1] = mask;

	ENC28J60_CS_Low();

	HAL_SPI_Transmit(spi, cmd, 2, 1000);

	ENC28J60_CS_High();
}
