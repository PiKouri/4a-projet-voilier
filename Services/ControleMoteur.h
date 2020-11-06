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
	* @brief  Récupère les informations de la télécommande et les envoie au moteur CC. 
  * @note   None
	* @param  None
  * @retval None
  */
void manageRecepteurRF_Moteur(void);
