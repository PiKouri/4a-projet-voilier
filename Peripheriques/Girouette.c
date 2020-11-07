#include "Girouette.h"

void timerConfGirouette(){
	// PSC=3 pour une pr�cision au degr� et non au quart de degr�, � v�rifier
	EncoderMode_Init(TIM3, 359, 3);
}

void GPIOConfGirouette(){
	MyGPIO_pin_conf(GPIOA, 6, 'i'); //a verifier
	MyGPIO_pin_conf(GPIOA, 7, 'i'); //a verifier
	MyGPIO_pin_conf(GPIOA, 5, 'f');
}

void initAngleGirouette(){
	//Polling : mise � 0 de CNT au passage sur l'index
	MyGPIO_wait_for_pin(GPIOA, 5);
	Reset_Count_Timer(TIM3);
}

int getAngleVent() {
	return Get_Count_Timer(TIM3);
}
