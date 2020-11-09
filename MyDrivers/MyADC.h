/*
Driver pour ADC 1 et 2
*/
#include "system_stm32f1xx.c"


/**
	* @brief  Configure un ADC pour convertir sur la voie (une et une seule voie) qui nous intéresse 
  * @note   
	* @param  ADC_TypeDef* ADCx : ADC utilisé (1 ou 2)
						int voie : numéro de la voie utilisée				
  * @retval None
  */
	void MyADC_conf(ADC_TypeDef* ADCx, int voie);
	
	/**
	* @brief  Lance la conversion d'un ADC, attends qu'elle termine et retourne la valeur lue sous forme d'entier 
  * @note   
	* @param  ADC_TypeDef* ADCx : ADC utilisé (1 ou 2)		
  * @retval int value
  */
	int MyADC_get_value(ADC_TypeDef* ADCx);