/*
Driver pour GPIO A à D du STM32F103RB
/!\ N'a pas encore été testé (pb de multiple defs à la compilation)
*/

#include "stm32f1xx_ll_gpio.h"

/**
	* @brief  Configure une broche d'un GPIO donné
  * @note   
	* @param  GPIO_TypeDef* GPIOx : GPIO à utiliser (ex : GPIOA)
						int pin : broche à configurer
						char mode : 'i' pour input, 'd' pour output open drain, 'p' pour output push-pull, 'f' pour floating, 'l' pour alternate function, 
							'n' pour analog
  * @retval None
  */
	void MyGPIO_pin_conf(GPIO_TypeDef* GPIOx, int pin, char mode);
	