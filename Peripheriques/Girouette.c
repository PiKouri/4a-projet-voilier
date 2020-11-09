#include "Girouette.h"

void timerConfGirouette(){
	EncoderMode_Init(TIM3, 359, 0);
}

void GPIOConfGirouette(){
	MyGPIO_pin_conf(GPIOA, 6, 'f'); //a verifier
	MyGPIO_pin_conf(GPIOA, 7, 'f'); //a verifier
	MyGPIO_pin_conf(GPIOA, 5, 'f');
}

void initAngleGirouette(){
	//Polling : mise à 0 de CNT au passage sur l'index
	MyGPIO_wait_for_pin(GPIOA, 5);
	Reset_Count_Timer(TIM3);
}

int getAngleVent() {
	return Get_Count_Timer(TIM3);
}
