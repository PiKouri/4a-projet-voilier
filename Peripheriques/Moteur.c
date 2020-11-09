
#include "Moteur.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"

// Moteur
//		PA1 
//		PA2(sens)

void Moteur_Conf(void) {
	
	MyGPIO_pin_conf(GPIOA, 1, 'p'); // Pushpull ?
	MyGPIO_pin_conf(GPIOA, 2, 'p'); // Pushpull ?
	double Res = PWM_Init(TIM2,'2',20, 'o', ' '); //20kHz

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
		PWM_Set_CCR(TIM2,'2',Ccr);
	} else ; // Error
}
