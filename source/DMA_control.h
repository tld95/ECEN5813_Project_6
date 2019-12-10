/*
 *  PES Project Six DMA Control header code implementation
 *	Tristan Duenas
 *	Refereneces:
 *	SDK_2.x_FRDM-KL25Z
 */

#ifndef __DMA_CONTROL_H__
#define __DMA_CONTROL_H__

#include "ADC_control.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_dma.h"
#include "fsl_dmamux.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "logger.h"
#include "DSP_control.h"
#include "ADC_control.h"
#include <stdlib.h>
#include <stdint.h>

#define BUFF_LENGTH 4
#define DMA_CHANNEL 0
#define DMA_SOURCE 63

extern dma_handle_t g_DMA_Handle;

// DMA0 initialization
void initDMA0();
// Transfers data through DMA from the srcAddr to the destAddr
void DMA0_Transfer(uint16_t *srcAddr, uint16_t *destAddr);
// DMA0 Callback for when DMA transfers are complete
void DMA_Callback(dma_handle_t *handle, void *param);

#endif
