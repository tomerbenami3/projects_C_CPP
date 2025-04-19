/*
 * event_logger.h
 *
 *  Created on: Apr 4, 2025
 *      Author: tomerbenami
 */

#ifndef INC_EVENT_LOGGER_H_
#define INC_EVENT_LOGGER_H_

#include "system_state.h"
#include "date_time.h"

typedef enum {
    EVENT_MODE_CHANGED,
	EVENT_CONFIG_UPDATED
} EventType;

typedef struct {
    EventType type;
    SystemMode old_mode;
    SystemMode new_mode;
    Date date;
    Time time;
} SystemEvent;

//void EventLogger_Init(void);
//void EventLogger_LogModeChange(SystemMode old_mode, SystemMode new_mode, Date date, Time time);


#endif /* INC_EVENT_LOGGER_H_ */
