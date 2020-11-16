/*
Driver pour ADC 1 et 2
*/

//A d�placer ailleurs !!!!
#include "stm32f1xx_ll_rcc.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_bus.h"

/**
	* @brief  Configure un ADC pour convertir sur la voie (une et une seule voie) qui nous int�resse 
  * @note   
	* @param  ADC_TypeDef* ADCx : ADC utilis� (1 ou 2)
						int voie : num�ro de la voie utilis�e	(trouvable page 28 de la petite doc)			
  * @retval None
  */
	void MyADC_conf(ADC_TypeDef* ADCx, int voie);
	
	/**
	* @brief  Lance la conversion d'un ADC, attends qu'elle termine et retourne la valeur lue sous forme d'entier 
  * @note   
	* @param  ADC_TypeDef* ADCx : ADC utilis� (1 ou 2)		
  * @retval int value
  */
	int MyADC_get_value(ADC_TypeDef* ADCx);