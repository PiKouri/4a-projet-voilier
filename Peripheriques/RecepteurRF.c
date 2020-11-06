#include "RecepteurRF.h"
#include "MyTimer.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"
#include "Math.h"

// RF TELECO : 
//		CH1 : PB6 = TIM4_CH1
//		CH2 : PB7 = TIM4_CH2
//Periode fixe 20 ou 25ms, selon modèle soit 
void RecepteurRF_Conf(void) {
	double Res = PWM_Init(TIM4,'1',0.05, 'i', 'r'); // 50 Hz ou 40 Hz
	double Res2 = PWM_Init(TIM4,'2',0.05, 'i', 'f'); // 50 Hz ou 40 Hz
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
char RecepteurRF_Get_Cap(void) {
	double Duty_Cycle = RecepteurRF_Get_Duty_Cycle();
	char cap;
	if (Duty_Cycle <= 1.5) cap='b';
	else cap='t';
	return cap;
}

double RecepteurRF_Get_Vitesse(void){
	double Duty_Cycle = RecepteurRF_Get_Duty_Cycle();
	double vitesse = fabs(Duty_Cycle-1.5)*100/0.5;
	return vitesse;
}