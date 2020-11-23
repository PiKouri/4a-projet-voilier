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

double PWM_Output_Init(TIM_TypeDef *Timer, int Voie, float Frequence_PWM, float DutyCycle_PWM) {
	// Configure la PWM en output

	int CH;
	switch (Voie) {
		case 1 : CH = LL_TIM_CHANNEL_CH1; break;
		case 2 : CH = LL_TIM_CHANNEL_CH2; break;
		case 3 : CH = LL_TIM_CHANNEL_CH3; break;
		case 4 : CH = LL_TIM_CHANNEL_CH4; break;
	}

	// Active l'horloge
	if(Timer == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if(Timer == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if(Timer == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if(Timer == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	// Configure la fréquence
	int psc = 1;
	int arr = 0;
	int found = 0;
	while(!found) {
		arr = 72000000 / (Frequence_PWM * psc);
		if(arr <= 65535) {
			found = 1;
		} else {
			psc++;
		}
	}
	
	Timer->PSC = psc - 1;
	Timer->ARR = arr;
	
	// Configuration du rapport cyclique
	int ccr = arr * DutyCycle_PWM;
	if(Voie == 1) {
		Timer->CCR1 = ccr;
	} else if(Voie == 2) {
		Timer->CCR2 = ccr;
	} else if(Voie == 3) {
		Timer->CCR3 = ccr;
	} else if(Voie == 4) {
		Timer->CCR4 = ccr;
	}
	
	LL_TIM_OC_SetMode(Timer, CH, LL_TIM_OCMODE_PWM1);
	
	LL_TIM_CC_EnableChannel(Timer, CH);

	return log2(arr); // A verifier : résolution

}

void PWM_Input_Init(TIM_TypeDef *Timer, int Voie) {
	// Configure la PWM en input
	// Seulement sur les channels 1 ou 2
	
	// Active l'horloge
	if(Timer == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if(Timer == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if(Timer == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if(Timer == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	Timer->PSC = 0;
	Timer->ARR = 0xFFFF;
	
	// Configure les Voies

	if (Voie == 1) {
		//Channel 1 : Rising edge
		LL_TIM_IC_SetPolarity (Timer, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
		//Channel 2 : Falling edge
		LL_TIM_IC_SetPolarity (Timer, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_FALLING);

		//Channel 1 -> Period
		LL_TIM_IC_SetActiveInput(Timer, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);
		//Channel 2 -> Duty_cycle
		LL_TIM_IC_SetActiveInput(Timer, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);

		//Trigger input (reset) 
		LL_TIM_SetTriggerInput(Timer, LL_TIM_TS_TI1FP1);// Filtered Timer Input 1

	} else if (Voie == 2) {
		//Channel 2 : Rising edge
		LL_TIM_IC_SetPolarity (Timer, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);
		//Channel 1 : Falling edge
		LL_TIM_IC_SetPolarity (Timer, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_FALLING);

		//Channel 2 -> Period
		LL_TIM_IC_SetActiveInput(Timer, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);
		//Channel 1 -> Duty_cycle
		LL_TIM_IC_SetActiveInput(Timer, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);

		//Trigger input (reset) 
		LL_TIM_SetTriggerInput(Timer, LL_TIM_TS_TI2FP2);// Filtered Timer Input 2
	}

	//Slave mode reset -> Rising edge of the selected trigger input (TRGI) reinitializes the counter and generates an update of the registers
	LL_TIM_EnableMasterSlaveMode(Timer);
	LL_TIM_SetSlaveMode(Timer, LL_TIM_SLAVEMODE_RESET);
	
	//Active les voies
	LL_TIM_CC_EnableChannel(Timer,LL_TIM_CHANNEL_CH1);
	LL_TIM_CC_EnableChannel(Timer,LL_TIM_CHANNEL_CH2);

}
void PWM_Set_CCR(TIM_TypeDef *Timer, int Voie, int Ccr) {
	switch (Voie) {
		case 1 : LL_TIM_OC_SetCompareCH1(Timer, Ccr); break;
		case 2 : LL_TIM_OC_SetCompareCH2(Timer, Ccr); break;
		case 3 : LL_TIM_OC_SetCompareCH3(Timer, Ccr); break;
		case 4 : LL_TIM_OC_SetCompareCH4(Timer, Ccr); break;
	}
}

int PWM_Get_CCR(TIM_TypeDef *Timer, int Voie) {
	int Ccr;
	switch (Voie) {
		case 1 : Ccr = LL_TIM_OC_GetCompareCH1(Timer); break;
		case 2 : Ccr = LL_TIM_OC_GetCompareCH2(Timer); break;
		case 3 : Ccr = LL_TIM_OC_GetCompareCH3(Timer); break;
		case 4 : Ccr = LL_TIM_OC_GetCompareCH4(Timer); break;
	}
	return Ccr;
}

/*

============ Mode Encodeur ================================= 
Réglages page 392
*/

void EncoderMode_Init(TIM_TypeDef *Timer, int Arr, int Psc){
	
	// Démarre l'horloge
	if(Timer == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if(Timer == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if(Timer == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if(Timer == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	//Réglages ARR et PSC
	Timer->ARR=Arr;
	Timer->PSC=Psc;
	
	//Mode encodeur x4 : SMS = 001
	Timer->SMCR&=~(0x7);
	Timer->SMCR|=0x1;
	
	//Réglages CHA
		//CC1S=01
	Timer->CCMR1&=~(0x2);
	Timer->CCMR1|=0x1;
		//CC1P=0
	Timer->CCER&=~(1<<1);
		//IC1F=0000
	Timer->CCMR1&=~(0xF0);
	
	
	//Réglages CHB
		//CC2S=01
	Timer->CCMR1&=~(0x200);
	Timer->CCMR1|=0x100;
		//CC2P = 0
	Timer->CCER&=~(1<<5);
		//IC2F=0000
	Timer->CCMR1&=~(0xF000);
	
	
	//Activation compteur : CEN=1
	Timer->CR1|=0x1;	

/*
// Active l'horloge
	
	// Selectionne le mode encodeur
	LL_TIM_SetEncoderMode(Timer, LL_TIM_ENCODERMODE_X4_TI12); // Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
	// On configure le channel 1
	LL_TIM_IC_SetActiveInput(Timer, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);
	// On configure le channel 2
	LL_TIM_IC_SetActiveInput(Timer, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);
	// On configure la polarite du channel 1
	LL_TIM_IC_SetPolarity (Timer, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
	// On configure la polarite du channel 2
	LL_TIM_IC_SetPolarity (Timer, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);
	
	Timer->ARR = 0xFFFF;
*/

}


/*
======= Manipulation du registre CNT ========================
*/

void Reset_Count_Timer(TIM_TypeDef *Timer){
	Timer->CNT=0x0;
}

int Get_Count_Timer(TIM_TypeDef *Timer){
	int cnt;
	cnt=Timer->CNT;
	return cnt;
}
	