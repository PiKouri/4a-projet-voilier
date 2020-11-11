#include "MyADC.h"


void MyADC_conf(ADC_TypeDef* ADCx, int voie){
	//Conversion à une seule voie : L=0000
	ADCx->SQR1&=~(0xF<<20);
	
	//Conversion sur la voie qui nous intéresse :
	ADCx->SQR3&=~(0xF);
	ADCx->SQR3|=voie;
}

int MyADC_get_value(ADC_TypeDef* ADCx){
	int conversion_finie=0;
	int value;
	
	//Lance la conversion
	ADCx->CR2&=~1;
	ADCx->CR2|=1;
	
	//Attend la fin de la conversion
	while(!conversion_finie){
		conversion_finie=(ADCx->SR)&~(1<<1);
	}
	
	//Récupère la valeur
	value=(ADCx->DR)&~(0xFFFF0000);
	return value;
}