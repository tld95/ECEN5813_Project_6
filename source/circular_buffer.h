/*
 *  PES Project Five Circular Buffer header code implementation
 *	Tristan Duenas
 *	References:
 */

#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "uart0_control.h"
#include "led_control.h"

#define MAX_BUFFER_SIZE 81

typedef struct circularBuffer
{
	uint16_t buffer[MAX_BUFFER_SIZE];
	uint32_t head;
	uint32_t tail;
	uint32_t length;
	uint32_t count;
} circularBuffer;

typedef enum circularBufferErrors
{
	NO_ERROR = 0,
	BUFFER_FULL = 1,
	BUFFER_EMPTY = 2,
	BUFFER_UNINITIALIZED = 3,
	BUFFER_POINTER_INVALID = 4,
} circularBufferErrors;

// Initializes circular buffer
circularBufferErrors initializeBuffer(circularBuffer *cBuffer);

// Adds item to buffer and errors if buffer is full
circularBufferErrors addItem(circularBuffer *cBuffer, uint8_t data);

// Removes oldest item from buffer, errors if buffer is empty
circularBufferErrors removeItem(circularBuffer *cBuffer, uint8_t *data);

// Checks if buffer is full
circularBufferErrors checkIfBufferIsFull(circularBuffer *cBuffer);

// Checks if buffer is empty
circularBufferErrors checkIfBufferIsEmpty(circularBuffer *cBuffer);

// Checks if buffer is initialized
circularBufferErrors checkIfBufferIsInitialized(circularBuffer *cBuffer);

// Checks if buffer pointer is valid
circularBufferErrors checkIfBufferPointerIsValid(circularBuffer *cBuffer);

#endif
