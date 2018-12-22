/*
 * servoCommand.h
 */

#ifndef INC_SERVOCOMMAND_H_
#define INC_SERVOCOMMAND_H_

#include "main.h"

void servoCommand_Init(void);
void servoHigh_Set(int cons_pos);
void servoLow_Set(int cons_pos);
int servoHigh_Get(void);
int servoLow_Get(void);

#endif /* INC_SERVOCOMMAND_H_ */
