/*
 * date_time.h
 *
 *  Created on: Apr 3, 2025
 *      Author: tomerbenami
 */

#ifndef INC_DATE_TIME_H_
#define INC_DATE_TIME_H_

#include "rtc.h"
#include "main.h"
#include "usart.h"
#include <stdint.h>

typedef enum {
	DateTime_OK = 0,
	DateTime_ERROR,
	DateTime_INVALID,
	DateTime_SetAlarm_Error
}DateTimeStatus;

typedef struct {
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
}Time;

typedef struct {
	uint8_t day;
	uint8_t month;
	uint8_t year;
}Date;

typedef struct {
	RTC_HandleTypeDef *hrtc;
	Date date;
	Time time;
} DateTime;

DateTime* DateTimeCreate(RTC_HandleTypeDef *hrtc);
DateTimeStatus DateTimeGet(DateTime *dt);
DateTimeStatus DateTimeSetTime(DateTime *dt, uint8_t hours, uint8_t minutes, uint8_t seconds);
DateTimeStatus DateTimeSetDate(DateTime *dt, uint8_t year, uint8_t month, uint8_t day);
DateTimeStatus DateTimeSetAlarm(DateTime* dt, uint8_t hours, uint8_t minutes, uint8_t seconds);
void DateTimePrint(DateTime* dt);
void DateTime_NextDay(Date* date);
int DateTime_Compare(const DateTime* a, const DateTime* b);

#endif /* INC_DATE_TIME_H_ */
