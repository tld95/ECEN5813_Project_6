/*
 *  PES Project Six DMA Control source code implementation
 *	Tristan Duenas
 *	Refereneces:
 *	SDK_2.x_FRDM-KL25Z
 */

#include "DMA_control.h"

dma_handle_t g_DMA_Handle;
volatile uint8_t g_Transfer_Done = 0;

// Referenced DMA example from SDK_2.x_FRDM-KL25Z
void DMA_Callback(dma_handle_t *handle, void *param)
{
    g_Transfer_Done = true;
    processDSP_BufferAndOutputReport(dspBuffer);
    LED_BLUE_OFF();
    Log_string(STATUS_LEVEL, DMA_TRANSFER, "DMA Transfer Complete");
}

// Referenced DMA example from SDK_2.x_FRDM-KL25Z
void DMA0_Transfer(uint16_t *srcAddr, uint16_t *destAddr)
{
	dma_transfer_config_t transferConfig;
    DMA_Init(DMA0);
    DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);
    DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
    transferConfig.srcAddr = (uint32_t)srcAddr;
    transferConfig.srcSize = sizeof(uint16_t) * MAX_SINE_WAVE_VALUES;
    transferConfig.destAddr = (uint32_t)destAddr;
    transferConfig.destSize = sizeof(uint16_t) * MAX_SINE_WAVE_VALUES;
    transferConfig.transferSize = sizeof(uint16_t) * MAX_SINE_WAVE_VALUES;
    transferConfig.enableSrcIncrement = 1;
    transferConfig.enableDestIncrement = 1;
    DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
    DMA_StartTransfer(&g_DMA_Handle);
    while (g_Transfer_Done != 1)
    {
    }
}

// Referenced DMA example from SDK_2.x_FRDM-KL25Z
void initDMA0()
{
    DMAMUX_Init(DMAMUX0);
    DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL, DMA_SOURCE);
    DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL);
}
