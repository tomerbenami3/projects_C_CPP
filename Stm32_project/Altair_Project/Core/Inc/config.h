/*
 * config.h
 *
 *  Created on: Apr 3, 2025
 *      Author: tomerbenami
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include <stdint.h>

#define CONFIG_MAGIC 0xDEADBEEF

typedef struct {
    uint8_t temp_min;
    uint8_t temp_max;
    uint8_t humidity_min;
    uint8_t light_min;
    float voltage_min;
    uint32_t magic;
} SystemConfig;


void Config_Init(void);
SystemConfig* Config_Get(void);
void Config_Set(SystemConfig newConfig);


#endif /* INC_CONFIG_H_ */
