/*
 * rgb.h
 *
 *  Created on: Apr 3, 2025
 *      Author: tomerbenami
 */

#ifndef INC_RGB_H_
#define INC_RGB_H_

#include "main.h"

#define RGB_RED_PIN    RGB_0_Pin
#define RGB_RED_PORT   RGB_0_GPIO_Port

#define RGB_GREEN_PIN  RGB_1_Pin
#define RGB_GREEN_PORT RGB_1_GPIO_Port

#define RGB_BLUE_PIN   RGB_2_Pin
#define RGB_BLUE_PORT  RGB_2_GPIO_Port

void RGB_SetColor(uint8_t r, uint8_t g, uint8_t b);


#endif /* INC_RGB_H_ */
