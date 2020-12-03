#include "Girouette.h"

void timerConfGirouette(){
	//Très possiblement pb ici, p-e un psc de 4 pour pas compter les quarts de degré ? voir avec le prof
	EncoderMode_Init(TIM3, 719, 0);
}

void GPIOConfGirouette(){
	MyGPIO_pin_conf(GPIOA, 6, 'f'); 
	MyGPIO_pin_conf(GPIOA, 7, 'f'); 
	MyGPIO_pin_conf(GPIOA, 5, 'f');
}

void initAngleGirouette(){
	//Polling : mise à 0 de CNT au passage sur l'index
	MyGPIO_wait_for_pin(GPIOA, 5);
	Reset_Count_Timer(TIM3);
}

int getAngleVent() {
	int tutu ;
	tutu= Get_Count_Timer(TIM3)/2;
	toto=tutu ;
	return tutu;
}
