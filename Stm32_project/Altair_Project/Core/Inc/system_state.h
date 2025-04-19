/*
 * system_state.h
 *
 *  Created on: Apr 3, 2025
 *      Author: tomerbenami
 */

#ifndef INC_SYSTEM_STATE_H_
#define INC_SYSTEM_STATE_H_

#include "config.h"
#include "date_time.h"
#include "message_data.h"

typedef enum {
    MODE_NORMAL,
    MODE_ERROR
} SystemMode;

void SystemState_Init(void);
SystemMode SystemState_Get(void);
int SystemState_Update(MessageData* msg, SystemConfig* cfg); // returns 1 if mode changed


#endif /* INC_SYSTEM_STATE_H_ */
