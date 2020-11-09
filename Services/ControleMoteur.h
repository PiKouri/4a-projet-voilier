/*
	User Service : Controle Moteur = télécommande + plateau
*/

/* =====================================================================================
Configuration
=======================================================================================*/

/**
	* @brief  Configure les drivers nécessaires pour la communication
  * @note   A lancer avant toute autre fonction.
	* @param  None
  * @retval None
  */

void confDriversMoteur(void);

/* =====================================================================================
Gestion des informations
=======================================================================================*/

/**
	* @brief  Récupère la vitesse depuis la télécommande et l'envoie au moteur CC. 
  * @note   None
	* @param  None
  * @retval None
  */
void reglerVitesseMot(void);

/**
	* @brief  Récupère le cap depuis la télécommande et l'envoie au moteur CC. 
  * @note   None
	* @param  None
  * @retval None
  */
void reglerCap(void);
