/*
	Peripherique Batterie
*/

#include "stm32f103xb.h" 

/* =====================================================================================
Configuration
=======================================================================================*/

/**
	* @brief  Configure le moteur. 
  * @note   A lancer avant toute autre fonction.
	* @param  None
  * @retval None
  */
void Batterie_Conf(void) ;

/* =====================================================================================
R�cup�ration niveau batterie
=======================================================================================*/

/**
	* @brief  R�cup�re le niveau de la batterie
  * @note  	None
	* @param  None
  * @retval NiveauBatterie
  */
double getNiveau(void) ;
