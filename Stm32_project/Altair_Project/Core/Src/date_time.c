/*
 * date_time.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tomerbenami
 */

#include "date_time.h"
#include "rtc.h"
#include "usart.h"
#include <stdio.h>

static DateTime dt;

static uint8_t ConvertBcd2Dec(uint8_t byte);
static uint8_t ConvertDec2Bcd(uint8_t byte);
static void PopulateDateTime(DateTime* dt, RTC_TimeTypeDef* CurrentTime, RTC_DateTypeDef* CurrentDate);

static const uint8_t daysInMonth[12] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
};

DateTime* DateTimeCreate(RTC_HandleTypeDef *hrtc)
{
	if(dt.hrtc == NULL) {

		if(hrtc == NULL) {
			return NULL;
		}

		dt.hrtc = hrtc;

	}

	return &dt;
}

DateTimeStatus DateTimeGet(DateTime *dt)
{
	if(dt == NULL) {
		return DateTime_INVALID;
	}

	RTC_TimeTypeDef CurrentTime;
	RTC_DateTypeDef CurrentDate;

	if (HAL_RTC_GetTime(dt->hrtc, &CurrentTime, RTC_FORMAT_BCD) != HAL_OK) {
		return DateTime_ERROR;
	}

	if (HAL_RTC_GetDate(dt->hrtc, &CurrentDate, RTC_FORMAT_BCD) != HAL_OK) {
		return DateTime_ERROR;
	}

	PopulateDateTime(dt, &CurrentTime, &CurrentDate);

	return DateTime_OK;

}

DateTimeStatus DateTimeSetTime(DateTime *dt, uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	if(dt == NULL || hours >= 24 || minutes >= 60 || seconds >= 60) {
			return DateTime_INVALID;
	}

	RTC_TimeTypeDef time;

	time.Hours = ConvertDec2Bcd(hours);
	time.Minutes = ConvertDec2Bcd(minutes);
	time.Seconds = ConvertDec2Bcd(seconds);

	if (HAL_RTC_SetTime(dt->hrtc, &time, RTC_FORMAT_BCD) != HAL_OK) {
		return DateTime_ERROR;
	}

	return DateTime_OK;

}

DateTimeStatus DateTimeSetDate(DateTime *dt, uint8_t year, uint8_t month, uint8_t day)
{
	if(dt == NULL || month > 12 || day > 31) {
			return DateTime_INVALID;
	}

	RTC_DateTypeDef date;

	date.Year = ConvertDec2Bcd(year);
	date.Month = ConvertDec2Bcd(month);
	date.Date = ConvertDec2Bcd(day);
	date.WeekDay = RTC_WEEKDAY_TUESDAY;

	if (HAL_RTC_SetDate(dt->hrtc, &date, RTC_FORMAT_BCD) != HAL_OK) {
		return DateTime_ERROR;
	}

	return DateTime_OK;

}

void DateTimePrint(DateTime* dt)
{
	if(dt == NULL) {
		return;
	}

	printf("Date: %02d/%02d/%02d, Time: %02d:%02d:%02d\r\n",
			dt->date.month,
			dt->date.day,
			dt->date.year,
			dt->time.hours,
			dt->time.minutes,
			dt->time.seconds);
}

DateTimeStatus DateTimeSetAlarm(DateTime* dt, uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	RTC_AlarmTypeDef sAlarm = {0};

	sAlarm.AlarmTime.Hours   = ConvertDec2Bcd(hours);
	sAlarm.AlarmTime.Minutes = ConvertDec2Bcd(minutes);
	sAlarm.AlarmTime.Seconds = ConvertDec2Bcd(seconds);

	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;

	sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
	sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;

	sAlarm.AlarmDateWeekDay = 0x1;
	sAlarm.Alarm = RTC_ALARM_A;

	if (HAL_RTC_SetAlarm_IT(dt->hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
	{
		return DateTime_SetAlarm_Error;
	}

	return DateTime_OK;
}

static void PopulateDateTime(DateTime* dt, RTC_TimeTypeDef* CurrentTime, RTC_DateTypeDef* CurrentDate)
{
	dt->time.hours = ConvertBcd2Dec(CurrentTime->Hours);
	dt->time.minutes = ConvertBcd2Dec(CurrentTime->Minutes);
	dt->time.seconds = ConvertBcd2Dec(CurrentTime->Seconds);

	dt->date.year  = ConvertBcd2Dec(CurrentDate->Year);
	dt->date.month = ConvertBcd2Dec(CurrentDate->Month);
	dt->date.day   = ConvertBcd2Dec(CurrentDate->Date);
}

static uint8_t ConvertBcd2Dec(uint8_t byte)
{
	return ((byte >> 4) * 10) + (byte & 0x0F);
}

static uint8_t ConvertDec2Bcd(uint8_t byte)
{
	return ((byte / 10) << 4) | (byte % 10);
}

void DateTime_NextDay(Date* date)
{
    if (!date) return;

    date->day++;

    uint8_t maxDay = daysInMonth[date->month - 1];

    if (date->day > maxDay)
    {
        date->day = 1;
        date->month++;

        if (date->month > 12)
        {
            date->month = 1;
            date->year++;
        }
    }
}

int DateTime_Compare(const DateTime* a, const DateTime* b)
{
    if (a->date.year != b->date.year)
        return a->date.year - b->date.year;
    if (a->date.month != b->date.month)
        return a->date.month - b->date.month;
    if (a->date.day != b->date.day)
        return a->date.day - b->date.day;
    if (a->time.hours != b->time.hours)
        return a->time.hours - b->time.hours;
    if (a->time.minutes != b->time.minutes)
        return a->time.minutes - b->time.minutes;
    return a->time.seconds - b->time.seconds;
}
