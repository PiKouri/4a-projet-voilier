#include "Girouette.h"

void timerConfGirouette(){
	
}

void GPIOConfGirouette(){
	MyGPIO_pin_conf(GPIOA, 6, 'l');
	MyGPIO_pin_conf(GPIOA, 7, 'l');
	MyGPIO_pin_conf(GPIOA, 5, 'l');
}

void initAngleGirouette(){
	//Polling : mise à 0 de CNT au passage sur l'index
}

int getAngleVent () {
	return 0;
}
