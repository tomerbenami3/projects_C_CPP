/*
 * message_data.h
 *
 *  Created on: Apr 3, 2025
 *      Author: tomerbenami
 */

#ifndef INC_MESSAGE_DATA_H_
#define INC_MESSAGE_DATA_H_

#include <stdint.h>
#include "date_time.h"

typedef struct {
    uint8_t temperature_int;
    uint8_t temperature_dec;
    uint8_t humidity_int;
    uint8_t humidity_dec;
    uint16_t potent_int;
    uint16_t potent_dec;
    uint32_t light;
    Time time;
    Date date;
} MessageData;


#endif /* INC_MESSAGE_DATA_H_ */
