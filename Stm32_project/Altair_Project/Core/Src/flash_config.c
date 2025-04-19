/*
 * flash_config.c
 *
 *  Created on: Apr 8, 2025
 *      Author: tomerbenami
 */


#include "stm32l4xx_hal.h"
#include "config.h"
#include <string.h>

#define FLASH_CONFIG_START_ADDR  0x08080000

uint8_t FlashConfig_Save(SystemConfig* cfg)
{
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef eraseInit = {
        .TypeErase = FLASH_TYPEERASE_PAGES,
        .Page = 256,
        .NbPages = 1,
        .Banks = FLASH_BANK_2
    };

    uint32_t pageError;
    if (HAL_FLASHEx_Erase(&eraseInit, &pageError) != HAL_OK) {
        HAL_FLASH_Lock();
        return 0;
    }

    uint64_t* data = (uint64_t*)cfg;
    for (size_t i = 0; i < sizeof(SystemConfig); i += 8) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, FLASH_CONFIG_START_ADDR + i, *data++) != HAL_OK) {
            HAL_FLASH_Lock();
            return 0;
        }
    }

    HAL_FLASH_Lock();
    return 1;
}

uint8_t FlashConfig_Load(SystemConfig* cfg)
{
    memcpy(cfg, (void*)FLASH_CONFIG_START_ADDR, sizeof(SystemConfig));

    // You can add a checksum or magic value check here later
    return 1;
}
