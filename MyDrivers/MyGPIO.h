/*
Driver pour GPIO A à D du STM32F103RB
*/

#include "stm32f1xx_ll_gpio.h"

#include "stm32f1xx_ll_bus.h"

/**
	* @brief  Configure une broche d'un GPIO donné
  * @note   
	* @param  GPIO_TypeDef* GPIOx : GPIO à utiliser (ex : GPIOA)
						int pinNb : numéro de la broche à configurer
						char mode : 'd' pour output open drain, 'p' pour output push-pull, 'l' pour alternate function output,
												'f' pour floating input, 'i' pour input pullup/pulldown, 'n' pour analog input
							
  * @retval None
  */
	void MyGPIO_pin_conf(GPIO_TypeDef* GPIOx, int pinNb, char mode);
	
	/**
	* @brief  Attends un front montant sur une broche donnée d'un GPIO donné
  * @note   Fonction scrutative et bloquante
	* @param  GPIO_TypeDef* GPIOx : GPIO à utiliser (ex : GPIOA)
						int pinNb : numéro de la broche à utiliser
  * @retval None
  */
	void MyGPIO_wait_for_pin(GPIO_TypeDef* GPIOx, int pinNb);
