/*
 * flash_config.h
 *
 *  Created on: Apr 8, 2025
 *      Author: tomerbenami
 */

#ifndef INC_FLASH_CONFIG_H_
#define INC_FLASH_CONFIG_H_

#include <stdint.h>
#include "config.h"

uint8_t FlashConfig_Save(SystemConfig* cfg);
uint8_t FlashConfig_Load(SystemConfig* cfg);

#endif /* INC_FLASH_CONFIG_H_ */
