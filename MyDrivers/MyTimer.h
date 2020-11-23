// RIEN A MODIFIER //

#ifndef MY_TIMER_H
#define MY_TIMER_H

/*
Driver pour Timer 1 � 4 du STM32F103RB

*/

#include "stm32f103xb.h" 

/**
	* @brief  Active l'horloge et r�gle l'ARR et le PSC du timer vis�
  * @note   Fonction � lancer avant toute autre. Le timer n'est pas encore lanc� (voir MyTimerStart)
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
	* 				int Arr   : valeur � placer dans ARR
	*					int Psc   : valeur � placer dans PSC
  * @retval None
  */
void MyTimer_Conf(TIM_TypeDef * Timer,int Arr, int Psc);


/**
	* @brief  D�marre le timer consid�r�
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_Start(TIM_TypeDef * Timer);


/**
	* @brief  Arr�t le timer consid�r�
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_Stop(TIM_TypeDef * Timer);


/**
	* @brief  Configure le Timer consid�r� en interruption sur d�bordement.
  * @note   A ce stade, les interruptions ne sont pas valid�s (voir  MyTimer_IT_Enable )
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
	* 				void (*IT_function) (void) : nom (adresse) de la fonction � lancer sur interruption
	*         int Prio : priorit� associ�e � l'interruption
  * @retval None
  */
void MyTimer_IT_Conf(TIM_TypeDef * Timer, void (*IT_function) (void),int Prio);


/**
	* @brief  Autorise les interruptions
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_IT_Enable(TIM_TypeDef * Timer);	


/**
	* @brief  Interdit les interruptions
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void MyTimer_IT_Disable(TIM_TypeDef * Timer);

/**
	* @brief  Initialise le Timer et la voie donn�s en PWM Output
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
						uint8_t Voie : 1, 2, 3, ou 4 
						float Frequence_PWM : frequence voulue pour la PWM
						float DutyCycle_PWM : rapport cyclique
	* @retval double res
  */
double PWM_Output_Init(TIM_TypeDef *Timer, int Voie, float Frequence_PWM, float DutyCycle_PWM);

/** 
	* @brief  Initialise le Timer et la voie donn�s en PWM Input (Utilise les voies 1 et 2)
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
				 int Voie : 1 ou 2 pour choisir la voie qui sera en Rising Edge
	* @retval None
  */
void PWM_Input_Init(TIM_TypeDef *Timer, int Voie);

/**
	* @brief  Change la valeur de CCR de la voie donn�e (pour un timer donn�)
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
						char Voie : 1, 2, 3, ou 4 
						float Frequence_PWM_Khz : frequence voulue en KHz
						char Mode : 'i' ou 'o' / input ou ouput
						char Polarite : 'r' ou 'f' = RISING ou FALLING pour PWM Input
  * @retval None
  */
void PWM_Set_CCR(TIM_TypeDef *Timer, int Voie, int Ccr);

/**
	* @brief  R�cup�re la valeur de CCR de la voie donn�e (pour un timer donn�)
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
						char Voie : 1, 2, 3, ou 4 
  * @retval int Ccr
  */
int PWM_Get_CCR(TIM_TypeDef *Timer, int Voie);
#endif

/**
	* @brief  Initialise un timer en mode encodeur x4 avec les voies 1 et 2 du timer
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
						int Arr : Valeur d'autoreload d�sir�e, 
						int Psc : valeur de prescaler d�sir�e
	* @retval None
  */
void EncoderMode_Init(TIM_TypeDef *Timer, int Arr, int Psc);

/**
	* @brief  Remet � z�ro manuellement le registre CNT d'un timer
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
	* @retval None
  */
	void Reset_Count_Timer(TIM_TypeDef *Timer);
	
	/**
	* @brief  Permet d'acc�der � la valeur contenue dans le registre CNT d'un timer
  * @note   
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
	* @retval int cnt
  */
	int Get_Count_Timer(TIM_TypeDef *Timer);
