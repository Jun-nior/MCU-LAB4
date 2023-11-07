/*
 * fsm.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Vostro
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "software_timer.h"
#define IDLE	1
#define RECEIVE 2
#define INFO 	3
#define MAX_BUFFER_SIZE 30

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint32_t ADC_value;
extern int command_flag;

void command_parser_fsm();
void uart_communication_fsm();
void clear_buffer();

extern int command_flag;
extern int state;

#endif /* INC_FSM_H_ */
