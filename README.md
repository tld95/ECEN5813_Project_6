# ECEN5813_Project_6
# Tristan Duenas 
# Project Demonstration YouTube Video Link https://youtu.be/3rgBDsAhFZs 

# Bruce Montgomery has approved not needing to submit an oscilloscope trace due to distance learning resource limitations
# I completed the 5 point extra credit for using a FreeRTOS Mutex to control access to the shared LED

The source folder of the ECEN5813_Project_6 repository contains all of the files created by hand for this project.

# Project Files 
DAC_control.c/.h: Contains Sine Wave Look Up Table that has the raw DAC register machine unit values for 1V to 3V and 3V to 1V.
Contains implementation of DAC0 initialization and control using FREERTOS timer/callback function to transfer Sine Wave values over DAC.
DAC timer runs at 10Hz. Blue LED toggles during Program One DAC transfers. Green LED toggles during program two transfers. FreeRTOS Mutex
is used to protect LED control.

ADC_control.c/.h: Contains implementation of ADC0 initialization and control using FREERTOS timer/callback function to read Sine Wave values 
from DAC on ADC. ADC timer runs at 10Hz. Once the full Sine Wave transfers a DMA transfer is initiated from the ADC FREERTOS 
timer call back function. The DMA transfer, transfers data from the ADC data array to the DSP data array using by DSP_control.c.
 Prior to starting the DMA transfer the blue LED is turned of for 0.5 seconds. The FreeRTOS Mutex is used to protect LED control.

DMA_control.c/.h: Contains implementation of DMA transfer initialization and callback for when DMA transfer is complete. Blue LED is turned 
off once transfer is complete. 

DSP_control.c/.h: Contains implementation for processing the DSP buffer after the DMA transfer has completed. Min, max, average, and standard 
deviation values are calculated based on the voltages read off of the ADC.

timing_control.c/.h: Contains implementation of FREERTOS timer for keeping track of the time since the program started. The timer runs at 1kHz.

functions_enum_list.c/.h: Updated functions enums to include functions needed in Project 6 for logging.

logger.c/.h: Used PRINTF to log integer and string values in Project 6.

main.c: Contains impelentation of DAC, ADC, and DMA initialization, along with the start of the FREERTOS scheduler. Contains FREERTOS timer/callback
that runs at 10Hz for checking if Program completed and stops DAC/ADC FREERTOS timers.

# Observations
I experienced issues at first using the DMA transfer, but I later realized it was due to how I was configuring DMA with the source and dest addresses.
Updating the timing control to use the FREERTOS timer helped me later with using the FREERTOS timer in ADC/DAC control. I had difficulty integrating my 
circular buffer implementation and instead used a new array for data that will just get overwritten by the DAC values.

# Installation/Execution Notes
I used the auto-generated makefile for this project.
Building requires performing a clean, then rebuild.
# Building for the Program One requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the PROGRAM_ONE and removing PROGRAM_TWO if present
# Building for the Program Two requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the PROGRAM_TWO and removing PROGRAM_TWO if present
# Building for the DEBUG build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the DEBUG_FLAG
# Building for the STATUS build requires going to Project Properties/Settings/Tool Settings/Preprocessor/ and adding the STATUS_FLAG
# ECEN5813_Project_6.axf is stored in the Debug folder of the repository and can be run through the GDB PEMicro Interface Debugging Debug configurations using the axf file generated.