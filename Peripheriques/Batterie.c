#include "Batterie.h"
#include "MyGPIO.h"
#include "stm32f1xx_ll_adc.h" 
#include "MyADC.h"

// Batterie : 
//		PC2 : ADC_IN12
// 	3.3V

void Batterie_Conf(void) {
	MyGPIO_pin_conf(GPIOC, 2, 'n');
	/*LL_ADC_InitTypeDef ADCInit;
	ADCInit.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	ADCInit.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
	LL_ADC_Init(ADC , &ADCInit)*/


	/* ADC_SR : status register
			EOC : End of conversion 
	CR1 EOCIE : 
	CR2 ADON : converter on/off + set 1 to start conversion
	SMPR1 et SMPR2 : Sample time register
	SQR regular sequence register : for multiple channels
	SQR1 : L : 1 conversion
	ADC_DR : Data register 

	LIBLL : EOS instead of EOC : sequence
	*/
	
	MyADC_conf(ADC2, 12);

}

double getNiveau(void) {
	double result = MyADC_get_value(ADC2);
	result = result *100 / 4096;
	return result;
}
