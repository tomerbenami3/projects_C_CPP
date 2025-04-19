/*
 * command_parser.h
 *
 *  Created on: Apr 6, 2025
 *      Author: tomerbenami
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_

#include "date_time.h"

void ParseCommand_New(const char* rawMessage);
void ParseCommand(const char* cmd);

#endif /* INC_COMMAND_PARSER_H_ */
