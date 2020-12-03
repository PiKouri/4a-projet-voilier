/*
	Peripherique Recepteur RF : t�l�commande
*/

/* =====================================================================================
Configuration
=======================================================================================*/

/**
	* @brief  Configure le moteur. 
  * @note   A lancer avant toute autre fonction.
	* @param  None
  * @retval None
  */
void RecepteurRF_Conf(void) ;

/* =====================================================================================
Reception infos
=======================================================================================*/

/**
	* @brief  R�cup�re le rapport cyclique. 
  * @note   None
	* @param  None
  * @retval rapport cyclique (%)
  */
float RecepteurRF_Get_Duty_Cycle(void) ;

/**
	* @brief  R�cup�re les informations (vitesse) de la t�l�commande. 
  * @note   None
	* @param  None
  * @retval vitesse (%)
  */
float getVitesse(void) ;

/**
	* @brief  R�cup�re les informations (cap) de la t�l�commande. 
  * @note   None
	* @param  None
  * @retval Cap
  */
char getCap(void) ;
