/*
	Peripherique Recepteur RF : télécommande
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
	* @brief  Récupère le rapport cyclique. 
  * @note   None
	* @param  None
  * @retval rapport cyclique (%)
  */
float RecepteurRF_Get_Duty_Cycle(void) ;

/**
	* @brief  Récupère les informations (vitesse) de la télécommande. 
  * @note   None
	* @param  None
  * @retval vitesse (%)
  */
float getVitesse(void) ;

/**
	* @brief  Récupère les informations (cap) de la télécommande. 
  * @note   None
	* @param  None
  * @retval Cap
  */
char getCap(void) ;
