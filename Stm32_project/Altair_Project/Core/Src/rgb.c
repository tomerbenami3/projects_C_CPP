/*
 * rgb.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tomerbenami
 */


#include "rgb.h"
#include "gpio.h"
#include "config.h"



void RGB_SetColor(uint8_t _r, uint8_t _g, uint8_t _b)
{
    HAL_GPIO_WritePin(RGB_RED_PORT, RGB_RED_PIN, _r ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(RGB_GREEN_PORT, RGB_GREEN_PIN, _g ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(RGB_BLUE_PORT, RGB_BLUE_PIN, _b ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

