/* FreeRTOS in STM32 */

#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

void led_on(void *);
void led_off(void *);

void led_on(void *pvParameters)
{
  while(1)                                 // Tasks runs forever
  {
    GPIOC -> BSRR = GPIO_BSRR_BR13;       // PC13 LED - ON
    vTaskDelay(500 / portTICK_PERIOD_MS); // wait for 500 ticks - 500 / tick_time = 500 / 1 ms = 500 ms
  }
}

void led_off(void *pvParameters)
{
  while(1)                                 // Tasks runs forever
  {
    GPIOC -> BSRR = GPIO_BSRR_BS13;       // PC13 LED - OFF
    vTaskDelay(500 / portTICK_PERIOD_MS); // wait for 500 ticks - 500 / tick_time = 500 / 1 ms = 500 ms
  }
}

void RCC_config(void);

void RCC_config() // RCC clock configuration
{
  RCC -> CR |= RCC_CR_HSEON;                               // HSE ON
  RCC -> CFGR |= (RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9);    
  // Setting PLL - HSE * 9, APB1 / 2
  RCC -> CFGR |= RCC_CFGR_SW_1;                            // SysClk = PLLCLK
  RCC -> CR |= RCC_CR_PLLON;                                               
  // Turn ON PLL after above PLL configurations, making SysClk = HSE * 9 = 8 * 9 = 72 MHz
  RCC -> CFGR |= RCC_CFGR_PPRE1_DIV2;                      
  // APB1 = AHB / 2 = 72 / 2 = 36 MHz (max)
}

int main()
{
  RCC_config();
  
  /* PC13 LED configuration */
  RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;                  // Enable Port-C Clock
  GPIOC -> CRH |= GPIO_CRH_MODE13_1 | GPIO_CRH_CNF13_0;  // PortC_Pin 13 as output @2MHZ with open-drain
  GPIOC -> BSRR = GPIO_BSRR_BS13;                       // Initialize PC13 LED - OFF
  
  if(xTaskCreate(led_on,           // Function / Task name
                 "ON",             // Descriptive name
                 128,              // Minimum Stack length in words
                 NULL,             // Argument to the function
                 0,                // Priority, 0 - Lowest
                 NULL)             // Task handle
    != pdPASS){                    // Check if task is created successfully using return value
     return 0;  }                  // else return
  
  if(xTaskCreate(led_off, "OFF", 128, NULL, 0, NULL) != pdPASS)
    {return 0;}   
  
  vTaskStartScheduler();           // Start the scheduler
  
  // Code after this will never gets executed
  return 0;
} 
