/**
  ******************************************************************************
  * @file    Templates_LL/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body through the LL API
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */


#include "Communication.h"
#include "ControleMoteur.h"
#include "ControleVoile.h"
/*#include "Moteur.h"
#include "ServoMoteur.h"*/

void  SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	

//entier utilisé pour visualiser des valeurs lors des tests, à dégager
int test;



int main(void)
{
  /* Configure the system clock to 72 MHz */
  SystemClock_Config();

  /* Add your application code here */
	confDriversMoteur();
	confDriversVoile();	
// tests des pwm output
	/*setVitesse(1); // TIM2->CNT et (GPIOA->IDR & GPIO_IDR_IDR1)>>1
	setCap('b');
	//setCap('t');
	setAngleVoile(90); // TIM4->CNT et (GPIOB->IDR & GPIO_IDR_IDR8)>>8
	*/
	
  /* Infinite loop */
  while (1)
  {
		reglerVoile();
		reglerCap();
		reglerVitesseMot();
  }
}


void mainfinal(){
	  /* Configure the system clock to 72 MHz */
  SystemClock_Config();

  /* Add your application code here */
	confDriversMoteur();
	confDriversVoile();	
	
  /* Infinite loop */
  while (1)
  {
		reglerVoile();
		reglerVitesseMot();
		reglerCap();
  }
}

void testServo(){
	GPIOConfServo();
	timerConfServo();
	setAngleVoile(45);
	setAngleVoile(0);
	setAngleVoile(90);
	setAngleVoile(0);
}

void testGirouette(){
	GPIOConfGirouette();
	timerConfGirouette();
	initAngleGirouette();
	while(1){
		test=getAngleVent();
	}
}


void testAccelero() {
	GPIOConfAccelero();
	ADCConfAccelero();
	while(1){
		test=getAngleRoulis();
	}
}

void testVoile(){
	confDriversVoile();
	reglerVoile();
}





/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

  /* Enable HSE oscillator */
	// ********* Commenter la ligne ci-dessous pour MCBSTM32 *****************
	// ********* Conserver la ligne si Nucléo*********************************
 // LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 72MHz */
  LL_Init1msTick(72000000); // utile lorsqu'on utilise la fonction LL_mDelay

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(72000000);
}



/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
