#include "MyADC.h"


void MyADC_conf(ADC_TypeDef* ADCx, int voie){
	int periph;
	if (ADCx==ADC1) periph = LL_APB2_GRP1_PERIPH_ADC1;
	else if (ADCx==ADC2) periph = LL_APB2_GRP1_PERIPH_ADC2;
	
	
	//Active l'horloge
	LL_APB2_GRP1_EnableClock(periph);
	
	//Conversion à une seule voie : L=0000
	ADCx->SQR1&=~(0xF<<20);
	
	//Conversion sur la voie qui nous intéresse :
	ADCx->SQR3&=~(0xF);
	ADCx->SQR3|=voie;
	
	ADCx->CR2 |= ADC_CR2_ADON;
}

int MyADC_get_value(ADC_TypeDef* ADCx){
	//int conversion_finie=0;
	int value;
	
	ADCx->CR2 |= ADC_CR2_ADON; // lancement de la conversion
  while(!(ADCx->SR & ADC_SR_EOC) ) {} // attente de la fin de conversion
	
	//Récupère la valeur
	value=(ADCx->DR)&(0x00000FFF);
	return value;
}
