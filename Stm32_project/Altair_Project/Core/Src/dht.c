/*
 * dht.c
 *
 *  Created on: Apr 1, 2025
 *      Author: tomerbenami
 */


#include "dht.h"
#include "gpio.h"
#include "time.h"
#include "cmsis_os2.h"
#include "main.h"
#include "usart.h"
#include <stdint.h>
#include <stdio.h>

DHT11 dht = {0};
DHT11_Data data = {0};

DHT11* DHT_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN, TIM_HandleTypeDef* _timer)
{
	dht.port = GPIOx;
	dht.pin = GPIO_PIN;
	dht._timer = _timer;

	return &dht;
}

void DHT11_SetAsInput(DHT11* dht)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = dht->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(dht->port, &GPIO_InitStruct);
}

void DHT11_SetAsOutput(DHT11* dht)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = dht->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(dht->port, &GPIO_InitStruct);
}

void DHT11_Starter(DHT11* dht)
{
	DHT11_SetAsOutput(dht);

	HAL_GPIO_WritePin(dht->port, dht->pin, GPIO_PIN_RESET);
	__HAL_TIM_SET_COUNTER(dht->_timer, 0);
	while (__HAL_TIM_GET_COUNTER(dht->_timer) < 18000);

	HAL_GPIO_WritePin(dht->port, dht->pin, GPIO_PIN_SET);
	__HAL_TIM_SET_COUNTER(dht->_timer, 0);
	while (__HAL_TIM_GET_COUNTER(dht->_timer) < 40);

	DHT11_SetAsInput(dht);
}

uint8_t DHT11_ReadData(DHT11 *dht, DHT11_Data *data)
{
	uint8_t buffer[5] = {0};

	DHT11_Starter(dht);

	__HAL_TIM_SET_COUNTER(dht->_timer, 0);
	while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_RESET)
	{
		if (__HAL_TIM_GET_COUNTER(dht->_timer) > 100) return 3;
	}

	__HAL_TIM_SET_COUNTER(dht->_timer, 0);
	while (HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_SET)
	{
		if (__HAL_TIM_GET_COUNTER(dht->_timer) > 100) return 3;
	}

	for (uint8_t i = 0; i < 40; i++) {
		buffer[i / 8] <<= 1;
		buffer[i / 8] |= DHT11_ReadBit(dht);
	}

	data->humidity_int = buffer[0];
	data->humidity_dec = buffer[1];
	data->temperature_int = buffer[2];
	data->temperature_dec = buffer[3];
	data->checksum = buffer[4];


	uint8_t checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
	return (checksum == buffer[4]) ? 0 : 2;
}

uint8_t DHT11_ReadBit(DHT11 *dht)
{
	while(HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_RESET);

	__HAL_TIM_SET_COUNTER(dht->_timer, 0);
	while(HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_SET);
	uint32_t pulse_length = __HAL_TIM_GET_COUNTER(dht->_timer);

	return (pulse_length > 50) ? 1 : 0;
}


void callfunction()
{
	DHT11_ReadData(&dht, &data);
	return;
}
