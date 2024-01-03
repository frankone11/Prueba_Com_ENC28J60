/*
 * enc28j60.h
 *
 *  Created on: Jan 2, 2024
 *      Author: paco
 */

#ifndef INC_ENC28J60_H_
#define INC_ENC28J60_H_

void ENC28J60_Init(SPI_HandleTypeDef *hspi);
void ENC28J60_RegDump();
void ENC28J60_BitSet(uint8_t address, uint8_t mask);
void ENC28J60_BitClear(uint8_t address, uint8_t mask);

#endif /* INC_ENC28J60_H_ */
