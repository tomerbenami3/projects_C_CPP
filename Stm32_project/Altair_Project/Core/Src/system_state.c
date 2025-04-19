/*
 * system_state.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tomerbenami
 */


#include "system_state.h"
#include "event_logger.h"
#include "app_freertos.h"
#include "date_time.h"
#include "cmsis_os2.h"
#include "rgb.h"

#include <stdio.h>

#define SAMPLE_RATE_NORMAL 5000
#define SAMPLE_RATE_ERROR 10000

static SystemMode currentMode = MODE_NORMAL;
extern osMessageQueueId_t eventQueueHandle;
extern DateTime* g_dt;


void UpdateSampleRateForMode(SystemMode mode)
{
    uint32_t newDelay = (mode == MODE_ERROR) ? SAMPLE_RATE_ERROR : SAMPLE_RATE_NORMAL;
    osTimerStop(timID);
    osTimerStart(timID, newDelay);
}


void SystemState_Init(void) {
    currentMode = MODE_NORMAL;
}

SystemMode SystemState_Get(void) {
    return currentMode;
}

int SystemState_Update(MessageData* msg, SystemConfig* cfg) {
    SystemMode newMode = MODE_NORMAL;

    if (
        msg->potent_int < cfg->voltage_min ||
        msg->temperature_int < cfg->temp_min ||
        msg->temperature_int > cfg->temp_max ||
        msg->humidity_int < cfg->humidity_min ||
        msg->light < cfg->light_min
    ) {
        newMode = MODE_ERROR;
    }

    if (newMode != currentMode) {
        printf("MODE CHANGED: %d → %d\r\n", currentMode, newMode);

        SystemEvent event = {
            .type = EVENT_MODE_CHANGED,
            .old_mode = currentMode,
            .new_mode = newMode,
            .date = g_dt->date,
            .time = g_dt->time
        };

        osMessageQueuePut(eventQueueHandle, &event, 0, 0);
        currentMode = newMode;
        UpdateSampleRateForMode(currentMode);

        switch (currentMode) {
            case MODE_NORMAL:
                RGB_SetColor(1, 0, 0); // Green
                break;
            case MODE_ERROR:
                RGB_SetColor(0, 0, 1); // Red
                break;
        }

        return 1;
    }

    return 0;
}

