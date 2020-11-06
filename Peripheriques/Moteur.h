/*
	Peripherique Moteur CC : plateau
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
void Moteur_Conf(void) ;

/**
	* @brief  Configure le cap/sens du moteur. 
  * @note  	None
	* @param  Sens du moteur : 'b' babord ou 't' tribord
  * @retval None
  */
void Set_Cap(char sens) ;

/**
	* @brief  Configure la vitesse du moteur. 
  * @note   None
	* @param  Vitesse du moteur à régler : 0 à 10 = pas de 10% (entre 0% - 100% 
  * @retval None
  */
void Set_Vitesse(int vitesse) ;
