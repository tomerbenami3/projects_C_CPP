/*
 * sd_card.c
 *
 *  Created on: Apr 1, 2025
 *      Author: tomerbenami
 */


#include "sd_card.h"
#include "date_time.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

static FATFS fs;
static FIL fil;
extern osMutexId_t sdMutexHandle;

void SD_Init(void) {
    f_mount(&fs, "", 1);
}

void SD_CreateFile(const char *filename, const char *content) {
    UINT bw;
    if (f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK) {
        f_write(&fil, content, strlen(content), &bw);
        f_close(&fil);
    }
}

void SD_ReadFile(const char *filename, char *buffer, UINT bufferSize) {
    UINT br;
    if (f_open(&fil, filename, FA_READ) == FR_OK) {
        f_read(&fil, buffer, bufferSize - 1, &br);
        buffer[br] = 0;
        f_close(&fil);
    }
}

void SD_ReadFilePrint(const char *filename)
{
    FIL file;
    char buffer[64];
    char line[128] = {0};
    UINT bytesRead;
    int lineIndex = 0;

    osMutexAcquire(sdMutexHandle, osWaitForever);

    if (f_open(&file, filename, FA_READ) == FR_OK)
    {
        printf("Reading %s:\r\n", filename);

        do {
            FRESULT readResult = f_read(&file, buffer, sizeof(buffer) - 1, &bytesRead);

            if (readResult != FR_OK) {
                printf("f_read error: %d\r\n", readResult);
                break;
            }

            buffer[bytesRead] = '\0';

            for (UINT i = 0; i < bytesRead; ++i)
            {
                if (buffer[i] == '\n' || lineIndex >= sizeof(line) - 2)
                {
                    line[lineIndex] = '\0';
                    printf("DATA: %s\r\n", line);
                    lineIndex = 0;
                }
                else if (buffer[i] != '\r')
                {
                    line[lineIndex++] = buffer[i];
                }
            }

        } while (bytesRead > 0);

        if (lineIndex > 0)
        {
            line[lineIndex] = '\0';
            printf("DATA: %s\r\n", line);
        }

        f_close(&file);
    }
    else
    {
        printf("Failed to open %s for reading\r\n", filename);
    }

    osMutexRelease(sdMutexHandle);
}



void SD_AppendToFile(const char *filename, const char *content)
{
    UINT bytesWritten;
    FRESULT res = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);

    if (res == FR_OK)
    {
        f_write(&fil, content, strlen(content), &bytesWritten);
        f_close(&fil);
    }
    else
    {
        printf("f_open failed for '%s'. Error code: %d\r\n", filename, res);
    }
}

void SD_ReadFilePrintRange(const char* filename, DateTime* start, DateTime* end)
{
    FIL file;
    char buffer[64];
    char line[128] = {0};
    UINT bytesRead;
    int lineIndex = 0;

    osMutexAcquire(sdMutexHandle, osWaitForever);

    if (f_open(&file, filename, FA_READ) == FR_OK)
    {
        printf("Reading %s:\r\n", filename);

        do {
            FRESULT readResult = f_read(&file, buffer, sizeof(buffer) - 1, &bytesRead);
            if (readResult != FR_OK) {
                printf("f_read error: %d\r\n", readResult);
                break;
            }

            buffer[bytesRead] = '\0';

            for (UINT i = 0; i < bytesRead; ++i)
            {
                if (buffer[i] == '\n' || lineIndex >= sizeof(line) - 2)
                {
                    line[lineIndex] = '\0';

                    DateTime dt;
                    int full_year, month, day, hour, min, sec;

                    if (sscanf(line, "%d-%d-%d %d:%d:%d",
                            &full_year, &month, &day, &hour, &min, &sec) == 6)
                    {
                        dt.date.year = full_year % 100;
                        dt.date.month = (uint8_t)month;
                        dt.date.day = (uint8_t)day;
                        dt.time.hours = (uint8_t)hour;
                        dt.time.minutes = (uint8_t)min;
                        dt.time.seconds = (uint8_t)sec;

                        int cmp_start = DateTime_Compare(&dt, start);
                        int cmp_end = DateTime_Compare(&dt, end);

                        if (cmp_end > 0) {
                            // Reached past the end — break early
                            f_close(&file);
                            osMutexRelease(sdMutexHandle);
                            return;
                        }

                        if (cmp_start >= 0 && cmp_end <= 0) {
                            printf("DATA: %s\r\n", line);
                        }
                    }

                    lineIndex = 0;
                }
                else if (buffer[i] != '\r')
                {
                    line[lineIndex++] = buffer[i];
                }
            }

        } while (bytesRead > 0);


        if (lineIndex > 0)
        {
            line[lineIndex] = '\0';

            DateTime dt;
            int full_year, month, day, hour, min, sec;

            if (sscanf(line, "%d-%d-%d %d:%d:%d",
                    &full_year, &month, &day, &hour, &min, &sec) == 6)
            {
                dt.date.year = full_year % 100;
                dt.date.month = (uint8_t)month;
                dt.date.day = (uint8_t)day;
                dt.time.hours = (uint8_t)hour;
                dt.time.minutes = (uint8_t)min;
                dt.time.seconds = (uint8_t)sec;

                int cmp_start = DateTime_Compare(&dt, start);
                int cmp_end = DateTime_Compare(&dt, end);

                if (cmp_end <= 0 && cmp_start >= 0) {
                    printf("DATA: %s\r\n", line);
                }
            }
        }

        f_close(&file);
    }
    else
    {
        printf("Failed to open %s for reading\r\n", filename);
    }

    osMutexRelease(sdMutexHandle);
}


// GET 2025-04-11 14:45:00 TO 2025-04-11 14:55:00

