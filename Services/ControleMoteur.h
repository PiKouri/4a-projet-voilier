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
	* @brief  R�cup�re la vitesse depuis la t�l�commande et l'envoie au moteur CC. 
  * @note   None
	* @param  None
  * @retval None
  */
void reglerVitesseMot(void);

/**
	* @brief  R�cup�re le cap depuis la t�l�commande et l'envoie au moteur CC. 
  * @note   None
	* @param  None
  * @retval None
  */
void reglerCap(void);
