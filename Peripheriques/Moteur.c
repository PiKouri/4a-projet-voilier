
#include "Moteur.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"

// Moteur
//		PA1 
//		PA2(sens)

void Moteur_Conf(void) {
	
	MyGPIO_pin_conf(GPIOA, 1, 'l'); // alternate pushpull
	MyGPIO_pin_conf(GPIOA, 2, 'p'); // pushpull 
	PWM_Output_Init(TIM2,2,50,0); //50 Hz (20 ms)
	MyTimer_Start(TIM2);
}

void setCap(char sens) {
	
	// A voir le sens pas sur: Set (babord) et Reset (Tribord) 
	
	switch (sens) {
		case 'b' : LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2); break;
		case 't' : LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2); break;
		default : ; // Error 
	}
}

void setVitesse(int vitesse) {
	if (0<=vitesse && vitesse<=10) {
		int Arr = LL_TIM_GetAutoReload(TIM2);
		int Ccr = Arr/10 * vitesse;
		PWM_Set_CCR(TIM2,2,Ccr);
	} else ; // Error
}
