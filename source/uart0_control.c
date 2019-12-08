/*
 *  PES Project Five UART0 Control source code implementation
 *	Tristan Duenas
 *	Refereneces:
 *	https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/src/UART.c
 */

#include "uart0_control.h"
#include "circular_buffer.h"

circularBuffer rxBuffer;
circularBuffer txBuffer;

void uart0_Init(uint32_t baudRate, Parity parity)
{
	led_control(BLUE);

	// Referenced https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/src/UART.c
	uint16_t sbr = 0;

	initializeBuffer(&rxBuffer);
	initializeBuffer(&txBuffer);

	// Enable UART0/PORTA clocks
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Disable transmit and receive in C2 before UART0 init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Connect UART0 to 48Mhz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	// Connect UART0 pins to Tx/RX
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);

	// Set UART0 baud rate/oversampling ratio
	sbr = (uint16_t)((BUS_CLOCK) / (baudRate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE - 1);

	// Disable interrupts for RX active edge and LIN break detect, select one stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
			| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

#ifdef UART_INTERRUPT_DRIVEN
	NVIC_SetPriority(UART0_IRQn, 2);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable UART0 interrupt for receiving
	UART0->C2 = UART_C2_RIE(1);
#endif

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	UART0->S1 &= ~UART0_S1_RDRF_MASK;
}

// Polling
uint8_t uart0_TransmitterAvailable()
{
	return (UART0->S1 & UART0_S1_TDRE_MASK);
}

void uart0_TransmitCharacter(uint8_t character)
{
	UART0->D = character;
}

void uart0_PollingTransmitCharacterOnAvailablity(uint8_t character)
{
	while (!uart0_TransmitterAvailable())
	{
		__asm("NOP");
	}
	uart0_TransmitCharacter(character);
}

uint8_t uart0_ReceiverCharacterAvailable()
{
	return (UART0->S1 & UART0_S1_RDRF_MASK);
}

uint8_t uart0_ReceiveCharacter()
{
	return UART0->D;
}

uint8_t uart0_PollingReceiveCharacterOnAvailability()
{
	while (!uart0_ReceiverCharacterAvailable())
	{
		__asm("NOP");
	}
	return uart0_ReceiveCharacter();
}

void uart0_PollingEchoCharacter()
{
	uint8_t character;
	character = uart0_PollingReceiveCharacterOnAvailability();
	uart0_PollingTransmitCharacterOnAvailablity(character);
}

// Interrupt
void UART0_IRQHandler()
{
	// Check errors
	uart0_InterruptCheckErrors();

	// Receive
	uart0_InterruptReceiveCharacterOnAvailability();

	// Transmit
	uart0_InterruptTransmitCharacterOnAvailablity();
}

void uart0_InterruptTransmitCharacterOnAvailablity()
{
	if (uart0_TransmitterAvailable())
	{
		uint8_t character;
		if (removeItem(&txBuffer, &character) == NO_ERROR)
		{
			uart0_TransmitCharacter(character);
		}
		else
		{
			// Buffer empty disable transmit interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
}

void uart0_InterruptReceiveCharacterOnAvailability()
{
	if (uart0_ReceiverCharacterAvailable())
	{
		uint8_t character = uart0_ReceiveCharacter();
		addItem(&rxBuffer, character);
	}
}

void uart0_InterruptCheckErrors()
{
	// Referenced https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/src/UART.c
	uint8_t character;
	if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK |
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {

			led_control(RED);
			// clear the error flags
			UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;
			// read the data register to clear RDRF
			character = UART0->D;
			if (character == ' ')
			{
				// Do nothing
				// This is to remove warning for not usin character
			}
	}
}

void uart0_InterruptEchoCharacter()
{
	uint8_t character;
	UART0->C2 &= ~UART0_C2_TIE_MASK;
	led_control(BLUE);
	while (checkIfBufferIsEmpty(&rxBuffer) != NO_ERROR)
	{
		__asm("NOP");
	}
	removeItem(&rxBuffer, &character);

	led_control(GREEN);
	delay(50);
	while (checkIfBufferIsFull(&txBuffer) != NO_ERROR)
	{
		__asm("NOP");
	}
	addItem(&txBuffer, character);
	UART0->C2 |= UART_C2_TIE(1);

#ifdef DEBUG_FLAG
	char buf[3];
	buf[0] = character;
	buf[1] = ' ';
	buf[2] = '\0';
	if (character != '\r')
	{
		Log_string(DEBUG_LEVEL, UART_0_INTERRUPT_ECHO_CHARACTERS, buf);
	}
#endif
}

