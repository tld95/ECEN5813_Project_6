/*
 * PES Project Four Functions Enum List Source Code
 * Tristan Duenas
 * References:
 */

#include "functions_enum_list.h"

void getFunctionName(Function_Names function, char* name)
{
	switch(function)
	{
		case COLOR_SENSOR_INIT:
			strcpy(name, "Color Sensor Init");
			break;
		case COLOR_SENSOR_POST_TEST:
			strcpy(name, "Color Sensor POST Test");
			break;
		case GET_COLOR_SENSOR_REGISTER_VALUE:
			strcpy(name, "Get Color Sensor Register Value");
			break;
		case I2C_WAIT:
			strcpy(name, "I2C Wait");
			break;
		case I2C_TRANSMIT:
			strcpy(name, "I2C Transmit");
			break;
		case LED_CONTROL:
			strcpy(name, "LED Control");
			break;
		case RUN_STATE_MACHINES:
			strcpy(name, "Run State Machines");
			break;
		case RUN_STATE_MACHINE_ONE:
			strcpy(name, "Run State Machine One");
			break;
		case RUN_STATE_MACHINE_TWO:
			strcpy(name, "Run State Machine Two");
			break;
		case DELAY:
			strcpy(name, "Delay");
			break;
		case MAIN:
			strcpy(name, "Main");
			break;
		case UART_0_INIT:
			break;
		case UART_0_TRANSMITTER_AVAILABLE:
			strcpy(name, "UART_0_TRANSMITTER_AVAILABLE");
			break;
		case UART_0_TRANSMIT_CHARACTER:
			strcpy(name, "UART_0_TRANSMIT_CHARACTER");
			break;
		case UART_0_POLLING_TRANSMIT_CHARACTER_ON_AVAILABILITY:
			strcpy(name, "UART_0_POLLING_TRANSMIT_CHARACTER_ON_AVAILABILITY");
			break;
		case UART_0_RECEIVER_CHARACTER_AVAILABLE:
			strcpy(name, "UART_0_RECEIVER_CHARACTER_AVAILABLE");
			break;
		case UART_0_RECEIVE_CHARACTER:
			strcpy(name, "UART_0_RECEIVE_CHARACTER");
			break;
		case UART_0_RECEIVE_CHARACTER_ON_AVAILABILITY:
			strcpy(name, "UART_0_RECEIVE_CHARACTER_ON_AVAILABILITY");
			break;
		case UART_0_POLLING_ECHO_CHARACTER:
			strcpy(name, "UART_0_POLLING_ECHO_CHARACTER");
			break;
		case UART_0_IRQ_HANDLER:
			strcpy(name, "UART_0_IRQ_HANDLER");
			break;
		case UART_0_INTERRUPT_TRANSMIT_CHARACTER_ON_AVAILABILITY:
			strcpy(name, "UART_0_INTERRUPT_TRANSMIT_CHARACTER_ON_AVAILABILITY");
			break;
		case UART_0_INTERRUPT_RECEIVE_CHARACTER_ON_AVAILABILITY:
			strcpy(name, "UART_0_INTERRUPT_RECEIVE_CHARACTER_ON_AVAILABILITY");
			break;
		case UART_0_INTERRUPT_CHECK_ERRORS:
			strcpy(name, "UART_0_INTERRUPT_CHECK_ERRORS");
			break;
		case UART_0_INTERRUPT_ECHO_CHARACTERS:
			strcpy(name, "UART_0_INTERRUPT_ECHO_CHARACTERS");
			break;
		case INITIALIZE_BUFFER:
			strcpy(name, "INITIALIZE_BUFFER");
			break;
		case ADD_ITEM:
			strcpy(name, "ADD_ITEM");
			break;
		case REMOVE_ITEM:
			strcpy(name, "REMOVE_ITEM");
			break;
		case CHECK_IF_BUFFER_IS_FULL:
			strcpy(name, "CHECK_IF_BUFFER_IS_FULL");
			break;
		case CHECK_IF_BUFFER_IS_EMPTY:
			strcpy(name, "CHECK_IF_BUFFER_IS_EMPTY");
			break;
		case CHECK_IF_BUFFER_IS_INITIALIZED:
			strcpy(name, "CHECK_IF_BUFFER_IS_INITIALIZED");
			break;
		case CHECK_IF_BUFFER_POINTER_IS_VALID:
			strcpy(name, "CHECK_IF_BUFFER_POINTER_IS_VALID");
			break;
		case APPLICATION_INIT:
			strcpy(name, "APPLICATION_INIT");
			break;
		case PROCESS_AND_DISPLAY_RECEIVED_CHARACTERS:
			strcpy(name, "PROCESS_AND_DISPLAY_RECEIVED_CHARACTERS");
			break;
		case UPDATE_ASCII_TRACKER:
			strcpy(name, "UPDATE_ASCII_TRACKER");
			break;
		case DISPLAY_ASCII_TRACKER:
			strcpy(name, "DISPLAY_ASCII_TRACKER");
			break;
		default:
			// Do nothing
			break;
	}
}
