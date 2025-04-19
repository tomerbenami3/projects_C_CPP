/*
 * event_logger.c
 *
 *  Created on: Apr 4, 2025
 *      Author: tomerbenami
 */

#include "event_logger.h"
#include "cmsis_os.h"
#include <string.h>
#include <stdio.h>

extern osMessageQueueId_t eventQueueHandle;

//void EventLogger_Init(void) {
//    // TODO
//}
//
//void EventLogger_LogModeChange(SystemMode old_mode, SystemMode new_mode, Date date, Time time) {
//    SystemEvent event = {
//        .type = EVENT_MODE_CHANGED,
//        .old_mode = old_mode,
//        .new_mode = new_mode,
//        .date = date,
//        .time = time
//    };
//
//    osMessageQueuePut(eventQueueHandle, &event, 0, 0);
//}
