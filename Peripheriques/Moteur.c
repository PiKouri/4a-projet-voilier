
#include "Moteur.h"
#include "MyTimer.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"

/**
	* @brief  Configure le moteur. 
  * @note   A lancer avant toute autre fonction.
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void Moteur_Conf(void) {
	
	double Res = PWM_Init(TIM2,'2',20, 'o', ' '); //20kHz
	
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL); // A voir pour le PushPull
}

/**
	* @brief  Configure le cap/sens du moteur. 
  * @note  	None
	* @param  Sens du moteur : 'b' babord ou 't' tribord
  * @retval None
  */
void Set_Cap(char sens) {
	
	// A voir le sens pas sur: Set (babord) et Reset (Tribord) 
	
	switch (sens) {
		case 'b' : LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2); break;
		case 't' : LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2); break;
		default : ; // Error 
	}
}

/**
	* @brief  Configure la vitesse du moteur. 
  * @note   None
	* @param  Vitesse du moteur à régler : 0 à 10 = pas de 10% (entre 0% - 100% )
  * @retval None
  */
void Set_Vitesse(int vitesse) {
	if (0<=vitesse && vitesse<=10) {
		int Arr = LL_TIM_GetAutoReload(TIM2);
		int Ccr = Arr/10 * vitesse;
		PWM_Set_CCR(TIM2,'2',Ccr);
	} else ; // Error
}
