# RTOS-in-STM32
Creating tasks in FreeRTOS with STM32 | STM32F103C8T6 | Arm Cortex M3 

**Blog post:** https://embedded-electronicsproject.blogspot.com/2025/01/rtos-in-stm32-stm32f103c8t6-arm-cortex.html


We are using Free RTOS in STM32 in Keil IDE.

**Steps to include RTOS in KEIL:**


1. Download Free RTOS from https://www.freertos.org/

   Also available in GitHub repository

2.  Include the required C and header files in your Keil project which are present in below folders

Necessary folders:

-- FreeRTOS -> FreeRTOS-Kernel: contains necessary C files like task.c, timer.c, etc.,.

-- FreeRTOS -> FreeRTOS-Kernel -> include: contains necessary header files

-- FreeRTOS -> FreeRTOS-Kernel ->  portable

  - MemMang: contains heap files
          
 - Then use the folder based on the board and compiler you are using, in our case GCC -> ARM_CM3 (ARM Cortex M3 and ARM compiler 6, if using compiler 5, then use RVDS instead of GCC)
          
-- **FreeRTOSConfig.h file:**

 Use the FreeRTOSConfig.h from GitHub, which is suitable for your specific board and copy that file to your local RTOS folder, In our case for STM32F103C8T6 in KEIL compiler
 https://github.com/FreeRTOS/FreeRTOS/blob/main/FreeRTOS/Demo/CORTEX_STM32F103_Keil/FreeRTOSConfig.h
 
 Lets copy the file to the new folder, lets say "include" inside path
 
 FreeRTOS -> FreeRTOS-Kernel -> include, which also need to be included in KEIL
 

**Header files:**

In KEIL -> Project -> options for target -> C/C++ -> Include Paths

**C files:**

Include the C files in Source group

- Right click on Source Group 1 -> Add existing files to group

**Heap management:** Include any one of the heap C file from FreeRTOS -> FreeRTOS-Kernel   ->  portable -> MemMang. Heap 4 implementation is preferred.


OR, instead of manually including FreeRTOS, we can select RTOS when creating KEIL project


3. Include the following header files in your main program:
   

   #include "FreeRTOS.h"
   #include "task.h" - If you are going to use task functions


- If you are using queue / semaphore / timer - include related header files
  

4. RTOS uses one of the STM32 timer as SysTick Timer
   
    - Configure the RCC registers to get desired system clock, for more details see this RCC  post
      
    - SysClk / 8 is Cortex system timer, which is the SysTick timer
   

The SysTick calibration value is set to 9000, which gives a reference time base of 1 ms with the SysTick clock set to 9 MHz (max HCLK/8)

SysClk = 72 MHz

system Timer = 72 / 8 = 9 MHz

9 MHz / 9000 = 1000 Hz

Tick_HZ = 1000 Hz = 1 ms

