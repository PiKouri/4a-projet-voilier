/*
	User Service : Controle Moteur = t�l�commande + plateau
*/

/* =====================================================================================
Configuration
=======================================================================================*/

/**
	* @brief  Configure les drivers n�cessaires pour la communication
  * @note   A lancer avant toute autre fonction.
	* @param  None
  * @retval None
  */

void confDriversMoteur(void);

/* =====================================================================================
Gestion des informations
=======================================================================================*/

/**
	* @brief  R�cup�re les informations de la t�l�commande et les envoie au moteur CC. 
  * @note   None
	* @param  None
  * @retval None
  */
void manageRecepteurRF_Moteur(void);
