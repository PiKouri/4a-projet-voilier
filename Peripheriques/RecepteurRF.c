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
	MyGPIO_pin_conf(GPIOB, 6, 'i'); // Floating input ?
	MyGPIO_pin_conf(GPIOB, 7, 'i'); // Floating input ?
	PWM_Input_Init(TIM4, 1); // Voie 1 en Rising Edge
}


// Information transmise contenue dans la durée de l'impulsion : 
//		Valeur mini 1,0 ms
//		Valeur neutre 1,5 ms
//		Valeur maxi 2,0 ms

double RecepteurRF_Get_Duty_Cycle(void) {
	double Val1 = LL_TIM_IC_GetCaptureCH1(TIM4);
	double Val2 = LL_TIM_IC_GetCaptureCH2(TIM4);
	double Duty_Cycle = (Val2*100/Val1);
	return Duty_Cycle;
}

// A voir le sens pas sur: <=1.5 (babord) et >1.5 (Tribord) 
char getCap(void) {
	double Duty_Cycle = RecepteurRF_Get_Duty_Cycle();
	char cap;
	if (Duty_Cycle <= 7.5) cap='b';
	else cap='t';
	return cap;
}

double getVitesse(void){
	double Duty_Cycle = RecepteurRF_Get_Duty_Cycle(); // Duty_cycle en % 
	double vitesse = fabs(Duty_Cycle-7.5)*100/2.5; // ecart (abs) entre la valeur moyenne : 7.5% et le duty cycle | report en % par rapport à la plage (5%-10%)
	//egs : Duty_cycle = 10% -> vitesse = 2.5*100/2.5 = 100
	return vitesse;
}
