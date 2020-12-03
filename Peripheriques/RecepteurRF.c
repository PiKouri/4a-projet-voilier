#include "RecepteurRF.h"
#include "MyTimer.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"
#include "Math.h"
#include "MyGPIO.h"

// RF TELECO : 
//		CH1 : PB6 = TIM4_CH1
//		CH2 : PB7 = TIM4_CH2
//Periode fixe 20 ou 25ms, selon modèle soit 
void RecepteurRF_Conf(void) {
	MyGPIO_pin_conf(GPIOB, 6, 'f'); // Floating input ?
	MyGPIO_pin_conf(GPIOB, 7, 'f'); // Floating input ?
	PWM_Input_Init(TIM4, 1); // Voie 1 en Rising Edge
}


// Information transmise contenue dans la durée de l'impulsion : 
//		Valeur mini 1,0 ms
//		Valeur neutre 1,5 ms
//		Valeur maxi 2,0 ms

float RecepteurRF_Get_Duty_Cycle(void) {
	int Val1 = LL_TIM_IC_GetCaptureCH1(TIM4);
	int Val2 = LL_TIM_IC_GetCaptureCH2(TIM4);
	float Duty_Cycle = ( ((float)Val2*100.0/(float)Val1))/10.0;
	return Duty_Cycle;
}

// A voir le sens pas sur: <=1.5 (babord) et >1.5 (Tribord) 
char getCap(void) {
	float Duty_Cycle = RecepteurRF_Get_Duty_Cycle();
	char cap;
	if (Duty_Cycle <= 1.5) cap='b';
	else cap='t';
	return cap;
}

float getVitesse(void){
	float Duty_Cycle = RecepteurRF_Get_Duty_Cycle(); // Duty_cycle en % 
	float vitesse = (Duty_Cycle-1.5)*100.0/0.5; // ecart (abs) entre la valeur moyenne : 1.5% et le duty cycle | report en % par rapport à la plage (1%-2%)
	if(vitesse <0) vitesse = -vitesse;
	//egs : Duty_cycle = 1% -> vitesse = 0.5*100/0.5 = 100
	vitesse = vitesse / 10.0 ; //Pas de 10%
	return vitesse;
}
