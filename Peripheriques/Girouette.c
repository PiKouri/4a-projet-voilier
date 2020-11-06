#include "Girouette.h"

void timerConfGirouette(){
	
}

void GPIOConfGirouette(){
	MyGPIO_pin_conf(GPIOA, 6, 'l');
	MyGPIO_pin_conf(GPIOA, 7, 'l');
	MyGPIO_pin_conf(GPIOA, 5, 'l');
}

int getAngleVent () {
	return 0;
}
