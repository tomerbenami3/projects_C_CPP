/*
 * sd_card.h
 *
 *  Created on: Apr 1, 2025
 *      Author: tomerbenami
 */

#ifndef INC_SD_CARD_H_
#define INC_SD_CARD_H_

#include "ff.h"
#include "date_time.h"

void SD_Init(void);
void SD_CreateFile(const char *filename, const char *content);
void SD_ReadFile(const char *filename, char *buffer, UINT bufferSize);
void SD_ReadFilePrint(const char *filename);
void SD_AppendToFile(const char *filename, const char *content);
void SD_ReadFilePrintRange(const char* filename, DateTime* start, DateTime* end);


#endif /* INC_SD_CARD_H_ */
