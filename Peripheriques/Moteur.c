
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
void Moteur_Conf() {
	
	//									A calculer
	
	int Arr = 1000; 
	int Psc = 1000; 
	int Ccr = Arr/30;
	
	MyTimer_Conf(TIM2, Arr, Psc)
	
	LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);  // TIM2_CH2 : Mode PWM1 = active as long as TIMx_CNT<TIMx_CCRy else inactive
	LL_TIM_OC_SetCompareCH2(TIM2, Ccr);
	//LL_TIM_OC_SetPolarity();
	//LL_TIM_CHANNEL_CH2;
	
}