// TOUT A FAIRE !! //

/*
 indispensable pour pouvoir adresser les registres des périphériques.
 Rem : OBLIGATION d'utiliser les définitions utiles contenues dans ce fichier (ex : TIM_CR1_CEN, RCC_APB1ENR_TIM2EN ...)
 pour une meilleure lisibilité du code.

 Pour les masques, utiliser également les définitions proposée
 Rappel : pour mettre à 1  , reg = reg | Mask (ou Mask est le représente le ou les bits à positionner à 1)
				  pour mettre à 0  , reg = reg&~ Mask (ou Mask est le représente le ou les bits à positionner à 0)
 
*/ 

#include "MyTimer.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_tim.h" 
#include <math.h>


// variable pointeur de fonction permettant de mémoriser le callback à appeler depuis
// le handler d'IT
void (*Ptr_ItFct_TIM1)(void); 
void (*Ptr_ItFct_TIM2)(void); 
void (*Ptr_ItFct_TIM3)(void); 
void (*Ptr_ItFct_TIM4)(void); 




/**
	* @brief  Active l'horloge et règle l'ARR et le PSC du timer visé
  * @note   Fonction à lancer avant toute autre. Le timer n'est pas encore lancé (voir MyTimerStart)
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
	* 				int Arr   : valeur à placer dans ARR
	*					int Psc   : valeur à placer dans PSC
  * @retval None
  */
void MyTimer_Conf(TIM_TypeDef * Timer,int Arr, int Psc)
{
	LL_TIM_InitTypeDef My_LL_Tim_Init_Struct;
	
	// Validation horloge locale
	if (Timer==TIM1) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	else if (Timer==TIM2) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	else if (Timer==TIM3) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	else  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	
	// chargement structure Arr, Psc, Up Count
	My_LL_Tim_Init_Struct.Autoreload=Arr;
	My_LL_Tim_Init_Struct.Prescaler=Psc;
	My_LL_Tim_Init_Struct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	My_LL_Tim_Init_Struct.CounterMode=LL_TIM_COUNTERMODE_UP;
	My_LL_Tim_Init_Struct.RepetitionCounter=0;
	
	LL_TIM_Init(Timer,&My_LL_Tim_Init_Struct);
	

	// Blocage IT
	LL_TIM_DisableIT_UPDATE(Timer);
	
	
	// Blocage Timer
	LL_TIM_DisableCounter(Timer);
	

		
}


/**
	* @brief  Démarre le timer considéré
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_Start(TIM_TypeDef * Timer)
{
		LL_TIM_EnableCounter(Timer);
}

/**
	* @brief  Arrêt le timer considéré
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_Stop(TIM_TypeDef * Timer)
{
	LL_TIM_DisableCounter(Timer);
}


/**
	* @brief  Configure le Timer considéré en interruption sur débordement.
  * @note   A ce stade, les interruptions ne sont pas validés (voir  MyTimer_IT_Enable )
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
	* 				void (*IT_function) (void) : nom (adresse) de la fonction à lancer sur interruption
	*         int Prio : priorité associée à l'interruption
  * @retval None
  */
void MyTimer_IT_Conf(TIM_TypeDef * Timer, void (*IT_function) (void),int Prio)
{
	// affectation de la fonction
	if (Timer==TIM1) Ptr_ItFct_TIM1=IT_function;
	else if (Timer==TIM2)	Ptr_ItFct_TIM2=IT_function;
	else if (Timer==TIM3)	Ptr_ItFct_TIM3=IT_function;
	else  Ptr_ItFct_TIM4=IT_function;

	
	// Blocage IT (il faudra la débloquer voir fct suivante)
	LL_TIM_DisableIT_UPDATE(Timer);
	
	// validation du canal NVIC
	IRQn_Type TIM_irq;
	
	if (Timer==TIM1) TIM_irq=TIM1_UP_IRQn;
	else if (Timer==TIM2)	TIM_irq=TIM2_IRQn;
	else if (Timer==TIM3)	TIM_irq=TIM3_IRQn;
	else 	TIM_irq=TIM4_IRQn;
	
	NVIC_SetPriority(TIM_irq, Prio);
	NVIC_EnableIRQ(TIM_irq);

	
}


/**
	* @brief  Autorise les interruptions
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_IT_Enable(TIM_TypeDef * Timer)
{
		LL_TIM_EnableIT_UPDATE(Timer);
}


/**
	* @brief  Interdit les interruptions
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_IT_Disable(TIM_TypeDef * Timer)
{
			LL_TIM_DisableIT_UPDATE(Timer); 
}	


/*
============ LES INTERRUPTIONS =================================

*/

void TIM1_UP_IRQHandler(void)
{
	// rabaisser le flag d'IT
	LL_TIM_ClearFlag_UPDATE(TIM1);
	(*Ptr_ItFct_TIM1)();
}	

void TIM2_IRQHandler(void)
{
	// rabaisser le flag d'IT
	LL_TIM_ClearFlag_UPDATE(TIM2);
	(*Ptr_ItFct_TIM2)();
}	

void TIM3_IRQHandler(void)
{
	// rabaisser le flag d'IT
	LL_TIM_ClearFlag_UPDATE(TIM3);
	(*Ptr_ItFct_TIM3)();
}	

void TIM4_IRQHandler(void)
{
	// rabaisser le flag d'IT
	LL_TIM_ClearFlag_UPDATE(TIM4);
	(*Ptr_ItFct_TIM4)();
}	

/*

============ PWM =================================

*/

double PWM_Init(TIM_TypeDef *Timer, char Voie, float Frequence_PWM_Khz, char Mode, char Polarite) {
//
// Cette fonction initialise la voie spécifiée du timer voulu en PWM.
// La fréquence souhaitée est passée en paramètre.
// La fonction renvoie un entier qui correspond à la résolution de la PWM pour
// pouvoir ensuite régler les rapports cycliques.
//
// 3 Timer "general Purpose", TIM2, TIM3 et TIM4 + TIM1
// Chacun d'entre eux dispose de 4 voies de sorties numérotées de 1 à 4
// Mapping des IO:
// TIM1_CH1 - PA08 TM2_CH1_ETR - PA0 TM3_CH1 - PA6 TIM4_CH1 - PB6
// TIM1_CH1 - PA09 TM2_CH2 - PA1 TM3_CH2 - PA7 TIM4_CH2 - PB7
// TIM1_CH1 - PA10 TM2_CH3 - PA2 TM3_CH3 - PB0 TIM4_CH3 - PB8
// TIM1_CH4 – PA11 TM2_CH4 - PA3 TM3_CH4 - PB1 TIM4_CH4 - PB9
	
	int CH;
	switch (Voie) {
		case '1' : CH = LL_TIM_CHANNEL_CH1; break;
		case '2' : CH = LL_TIM_CHANNEL_CH2; break;
		case '3' : CH = LL_TIM_CHANNEL_CH3; break;
		case '4' : CH = LL_TIM_CHANNEL_CH4; break;
	}
	
	//int Arr = LL_TIM_GetAutoReload(Timer);
	
	int Psc = 0; 
	int Ttimer = 1/Frequence_PWM_Khz;
	int Thorloge = 8000; // Par défaut 8MHz ???
	int Arr = (Ttimer / Thorloge) - 1;
	MyTimer_Conf(TIM2, Arr, Psc);

	double Res = log2(Arr); // A voir
	
	double pol;
	switch (Mode) {
		case 'o' : LL_TIM_OC_SetMode(Timer, CH, LL_TIM_OCMODE_PWM1); break; // TIM2_CH2 : Mode PWM1 = active as long as TIMx_CNT<TIMx_CCRy else inactive 
		case 'i' : 						// INPUT plutot utiliser registres 
			switch (Polarite) {
				case 'r' : pol = LL_TIM_IC_POLARITY_RISING;break;
				case 'f' : pol = LL_TIM_IC_POLARITY_FALLING;break;
			}
			LL_TIM_IC_SetActiveInput(Timer, CH, LL_TIM_ACTIVEINPUT_TRC);  // A VERIFIER
			LL_TIM_IC_SetFilter(Timer, CH, LL_TIM_IC_FILTER_FDIV1);	// A verifier
			LL_TIM_IC_SetPrescaler (Timer, CH, LL_TIM_ICPSC_DIV1); // A verifier
			LL_TIM_IC_SetPolarity (TIM4, LL_TIM_CHANNEL_CH1, pol);
			break;
	}
	LL_TIM_CC_EnableChannel(TIM2, CH);
	
	return Res;
	
}

void PWM_Set_CCR(TIM_TypeDef *Timer, char Voie, int Ccr) {
	switch (Voie) {
		case '1' : LL_TIM_OC_SetCompareCH1(Timer, Ccr); break;
		case '2' : LL_TIM_OC_SetCompareCH2(Timer, Ccr); break;
		case '3' : LL_TIM_OC_SetCompareCH3(Timer, Ccr); break;
		case '4' : LL_TIM_OC_SetCompareCH4(Timer, Ccr); break;
	}
}

int PWM_Get_CCR(TIM_TypeDef *Timer, char Voie) {
	int Ccr;
	switch (Voie) {
		case '1' : Ccr = LL_TIM_OC_GetCompareCH1(Timer); break;
		case '2' : Ccr = LL_TIM_OC_GetCompareCH2(Timer); break;
		case '3' : Ccr = LL_TIM_OC_GetCompareCH3(Timer); break;
		case '4' : Ccr = LL_TIM_OC_GetCompareCH4(Timer); break;
	}
	return Ccr;
}

/*

============ Mode Encodeur ================================= 
/!\ EN COURS, A TERMINER

*/

void EncoderMode_Init(TIM_TypeDef *Timer, char Voie1, char Voie2 /*, ??? index*/){
	
	//Initialisation de la structure auxilliaire
		LL_TIM_ENCODER_InitTypeDef *structInit;
		LL_TIM_ENCODER_StructInit(structInit);
	
	//Paramétrage de la structure auxilliaire
	structInit->EncoderMode = LL_TIM_ENCODERMODE_X4_TI12;
}
