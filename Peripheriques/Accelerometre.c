#include "Accelerometre.h"
#include <math.h>

void GPIOConfAccelero(){
	MyGPIO_pin_conf(GPIOC, 0, 'a');
	MyGPIO_pin_conf(GPIOC, 1, 'a');
}


int getAngleRoulis(){
	/*int valueADC, angleRoulis;
	valueADC = MyADC_get_value(numADC);
	angleRoulis = acos(valueADC/0.48);*/
	return /*angleRoulis*/ 0;
}