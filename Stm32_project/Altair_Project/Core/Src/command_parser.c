/*
 * command_parser.c
 *
 *  Created on: Apr 6, 2025
 *      Author: tomerbenami
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command_parser.h"
#include "sd_card.h"
#include "date_time.h"
#include "config.h"
#include "flash_config.h"
#include "event_logger.h"

extern DateTime* g_dt;
extern osMessageQueueId_t eventQueueHandle;

static int Date_Compare(Date* a, Date* b);

void ParseCommand(const char* cmd)
{
	printf("ParseCommand received: '%s'\r\n", cmd);

	if(cmd[0] == '\0' || strcmp(cmd, " \r\n") == strlen(cmd)) {
		return;
	}

    if (strncmp(cmd, "SETTIME ", 8) == 0)
    {
        int year, month, day, hour, minute, second;
        if (sscanf(cmd + 8, "%d-%d-%d %d:%d:%d",
                   &year, &month, &day,
                   &hour, &minute, &second) == 6)
        {
            DateTimeSetDate(g_dt, year % 100, month, day);
            DateTimeSetTime(g_dt, hour, minute, second);
            printf("RTC updated to: %04d-%02d-%02d %02d:%02d:%02d\r\n",
                   year, month, day, hour, minute, second);
        }
        else
        {
            printf("SETTIME format error\r\n");
        }
    }
    else if (strncmp(cmd, "GET ", 4) == 0)
    {
        int y1, m1, d1, h1, min1, s1;
        int y2, m2, d2, h2, min2, s2;

        if (sscanf(cmd + 4, "%d-%d-%d %d:%d:%d TO %d-%d-%d %d:%d:%d",
                   &y1, &m1, &d1, &h1, &min1, &s1,
                   &y2, &m2, &d2, &h2, &min2, &s2) == 12)
        {
            printf("Parsed GET range: %04d-%02d-%02d %02d:%02d:%02d to %04d-%02d-%02d %02d:%02d:%02d\r\n",
                   y1, m1, d1, h1, min1, s1,
                   y2, m2, d2, h2, min2, s2);

            DateTime start = {
                .date = { .year = y1 % 100, .month = m1, .day = d1 },
                .time = { .hours = h1, .minutes = min1, .seconds = s1 }
            };

            DateTime end = {
                .date = { .year = y2 % 100, .month = m2, .day = d2 },
                .time = { .hours = h2, .minutes = min2, .seconds = s2 }
            };

            DateTime current = start;

            while (Date_Compare(&current.date, &end.date) <= 0)
            {
                char filename[20];
                snprintf(filename, sizeof(filename), "%04d%02d%02d.TXT",
                         current.date.year + 2000,
                         current.date.month,
                         current.date.day);

                printf("Trying to open file: %s\r\n", filename);
                SD_ReadFilePrintRange(filename, &start, &end);

                DateTime_NextDay(&current.date);
            }
        }
        else
        {
            printf("Invalid GET command format.\r\n");
        }
    }
    else if (strncmp(cmd, "SETCONFIG ", 10) == 0)
    {
        SystemConfig newConfig;
        newConfig.magic = CONFIG_MAGIC;

        char tempStr[128];
        strncpy(tempStr, cmd + 10, sizeof(tempStr) - 1);
        tempStr[sizeof(tempStr) - 1] = '\0';

        char* token = strtok(tempStr, " ");
        printf("DEBUG parsed voltage_min: %.3f\r\n", newConfig.voltage_min);
        while (token != NULL) {
            if (strncmp(token, "temp_min=", 9) == 0)
                newConfig.temp_min = atoi(token + 9);
            else if (strncmp(token, "temp_max=", 9) == 0)
                newConfig.temp_max = atoi(token + 9);
            else if (strncmp(token, "humidity_min=", 13) == 0)
                newConfig.humidity_min = atoi(token + 13);
            else if (strncmp(token, "light_min=", 10) == 0)
                newConfig.light_min = atoi(token + 10);
            else if (strncmp(token, "voltage_min=", 12) == 0)
                newConfig.voltage_min = atof(token + 12);

            token = strtok(NULL, " ");
        }

        Config_Set(newConfig);
        FlashConfig_Save(&newConfig);

        printf("Config updated: T=%d–%d, H>%d, L>%d, V>%.2f\r\n",
               newConfig.temp_min, newConfig.temp_max,
               newConfig.humidity_min, newConfig.light_min, newConfig.voltage_min);

        SystemEvent event = {
            .type = EVENT_CONFIG_UPDATED,
            .date = g_dt->date,
            .time = g_dt->time,
            .old_mode = 0,
            .new_mode = 0
        };
        osMessageQueuePut(eventQueueHandle, &event, 0, 0);
    }


    else
    {
        printf("Unknown command.\r\n");
    }
}

static int Date_Compare(Date* a, Date* b)
{
    if (a->year != b->year)
        return a->year - b->year;
    if (a->month != b->month)
        return a->month - b->month;
    return a->day - b->day;
}
