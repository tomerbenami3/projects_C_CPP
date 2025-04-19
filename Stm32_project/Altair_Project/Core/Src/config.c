/*
 * config.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tomerbenami
 */
#include <stdio.h>
#include "config.h"
#include "flash_config.h"

static SystemConfig config = {
    .temp_min = 15,
    .temp_max = 35,
    .humidity_min = 20,
    .light_min = 20,
    .voltage_min = 4
};

void Config_Init(void)
{
    FlashConfig_Load(&config);

    if (config.magic != CONFIG_MAGIC)
    {
        config.temp_min = 15;
        config.temp_max = 35;
        config.humidity_min = 20;
        config.light_min = 20;
        config.voltage_min = 4.0;
        config.magic = CONFIG_MAGIC;

        FlashConfig_Save(&config);
    }

    printf("Loaded config from Flash: T=%d–%d, H>%d, L>%d, V>%.2f\r\n",
        config.temp_min, config.temp_max, config.humidity_min,
        config.light_min, config.voltage_min);
}


SystemConfig* Config_Get(void) {
    return &config;
}

void Config_Set(SystemConfig newConfig) {
    config = newConfig;
}
