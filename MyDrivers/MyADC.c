#include "MyADC.h"

void MyADC_conf(ADC_TypeDef* ADCx, int voie){
	//Conversion � une seule voie : L=0000
	ADCx->SQR1&=~(0xF<<20);
	
	//Conversion sur la voie qui nous int�resse :
	ADCx->SQR3&=~(0xF);
	ADCx->SQR3|=voie;
}

int MyADC_get_value(ADC_TypeDef* ADCx){
	
	
}