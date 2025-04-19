/*
 * dht.h
 *
 *  Created on: Apr 1, 2025
 *      Author: tomerbenami
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_

#include "dht.h"
#include "gpio.h"
#include "time.h"
#include "cmsis_os2.h"
#include "main.h"
#include <stdint.h>

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
	TIM_HandleTypeDef* _timer;
}DHT11;

typedef struct {
    uint8_t humidity_int;
    uint8_t humidity_dec;
    uint8_t temperature_int;
    uint8_t temperature_dec;
    uint8_t checksum;
} DHT11_Data;

extern DHT11 dht;
extern DHT11_Data data;

DHT11* DHT_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN, TIM_HandleTypeDef* _timer);
void DHT11_SetAsInput(DHT11* dht);
void DHT11_Starter(DHT11* dht);
void DHT11_SetAsOutput(DHT11* dht);
uint8_t DHT11_ReadData(DHT11 *dht, DHT11_Data *data);
uint8_t DHT11_ReadBit(DHT11 *dht);
void callfunction();


#endif /* INC_DHT_H_ */
