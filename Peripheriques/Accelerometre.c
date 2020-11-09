#include "Accelerometre.h"
#include <math.h>

void GPIOConfAccelero(){
	MyGPIO_pin_conf(GPIOC, 0, 'a');
	MyGPIO_pin_conf(GPIOC, 1, 'a');
}

void ADCConfAccelero(){
	MyADC_conf(ADC1, 11);
}

int getAngleRoulis(){
	int valueADC, angleRoulis;
	valueADC = MyADC_get_value(ADC1);
	angleRoulis = acos(valueADC/0.48);
	return angleRoulis;
}