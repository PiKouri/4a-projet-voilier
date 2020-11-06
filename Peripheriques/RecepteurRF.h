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
double RecepteurRF_Get_Duty_Cycle(void) ;

/**
	* @brief  Récupère les informations (vitesse) de la télécommande. 
  * @note   None
	* @param  None
  * @retval vitesse (%)
  */
double RecepteurRF_Get_Vitesse(void) ;

/**
	* @brief  Récupère les informations (cap) de la télécommande. 
  * @note   None
	* @param  None
  * @retval Cap
  */
char RecepteurRF_Get_Cap(void) ;

