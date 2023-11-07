/*
 * fsm.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Vostro
 */

#include "fsm.h"
#include <string.h>
#include <stdio.h>

int state=IDLE;
int command_flag=0;
uint8_t temp=0;
uint8_t index_buffer=0;
uint8_t buffer_flag=0;
uint32_t ADC_value=0;
uint8_t buffer[MAX_BUFFER_SIZE];

ADC_HandleTypeDef hadc1;


UART_HandleTypeDef huart2;

void clear_buffer() {
	memset(buffer,0,sizeof(buffer));
	index_buffer=0;
}

void command_parser_fsm() {
	switch(state) {
	case IDLE:
		if (temp=='!') {
			state=RECEIVE;
			clear_buffer();
		}
		break;
	case RECEIVE:
		if (!strcmp(buffer,"RST#")) {
			command_flag=1;
			HAL_ADC_Start(&hadc1);
			ADC_value=HAL_ADC_GetValue(&hadc1);
			HAL_ADC_Stop(&hadc1);
			state=IDLE;
			clear_buffer();
		} else if (!strcmp(buffer,"OK#")) {
			command_flag=0;
			state=IDLE;
			clear_buffer();
			timer1_flag=1;
		} else if (temp=='!') {
			clear_buffer();
		}
		break;
	default:
		break;
	}
}

char str[100];
void uart_communication_fsm() {
	switch(command_flag) {
	case 1:
		if (timer1_flag==1) {
			HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			HAL_UART_Transmit(&huart2, "\r\n !ADC=",10,1000);
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "%d#\r\n", ADC_value), 1000);
			setTimer1(300);
		}
		break;
	default:
		break;
	}
}


