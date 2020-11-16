#include "MyGPIO.h"

void MyGPIO_pin_conf(GPIO_TypeDef* GPIOx, int pinNb, char mode){
	
	int32_t pin;
	int periph;
	if (GPIOx == GPIOA) periph = LL_APB2_GRP1_PERIPH_GPIOA;
	else if (GPIOx == GPIOB) periph = LL_APB2_GRP1_PERIPH_GPIOB;
	else if (GPIOx == GPIOC) periph = LL_APB2_GRP1_PERIPH_GPIOC;
	else if (GPIOx == GPIOD) periph = LL_APB2_GRP1_PERIPH_GPIOD;
	
	LL_APB2_GRP1_EnableClock(periph);
	
	switch (pinNb){
		case 0 : pin = LL_GPIO_PIN_0; break;
		case 1 : pin = LL_GPIO_PIN_1; break;
		case 2 : pin = LL_GPIO_PIN_2; break;
		case 3 : pin = LL_GPIO_PIN_3; break;
		case 4 : pin = LL_GPIO_PIN_4; break;
		case 5 : pin = LL_GPIO_PIN_5; break;
		case 6 : pin = LL_GPIO_PIN_6; break;
		case 7 : pin = LL_GPIO_PIN_7; break;
		case 8 : pin = LL_GPIO_PIN_8; break;
		case 9 : pin = LL_GPIO_PIN_9; break;
		case 10 : pin = LL_GPIO_PIN_10; break;
		case 11 : pin = LL_GPIO_PIN_11; break;
		case 12 : pin = LL_GPIO_PIN_12; break;
		case 13 : pin = LL_GPIO_PIN_13; break;
		case 14 : pin = LL_GPIO_PIN_14; break;
		case 15 : pin = LL_GPIO_PIN_15; break;
	}
	
	
	switch(mode){
		case 'i' : LL_GPIO_SetPinMode(GPIOx, pin, LL_GPIO_MODE_INPUT); break;
		case 'd' : LL_GPIO_SetPinMode(GPIOx, pin, LL_GPIO_MODE_OUTPUT);
							LL_GPIO_SetPinOutputType(GPIOx, pin, LL_GPIO_OUTPUT_OPENDRAIN); break;
		case 'p' : LL_GPIO_SetPinMode(GPIOx, pin, LL_GPIO_MODE_OUTPUT);
							LL_GPIO_SetPinOutputType(GPIOx, pin, LL_GPIO_OUTPUT_PUSHPULL); break;
		case 'f' : LL_GPIO_SetPinMode(GPIOx, pin, LL_GPIO_MODE_FLOATING); break;
		case 'l' : LL_GPIO_SetPinMode(GPIOx, pin, LL_GPIO_MODE_ALTERNATE); break;
		case 'n' : LL_GPIO_SetPinMode(GPIOx, pin, LL_GPIO_MODE_ANALOG); break;
	}
}

void MyGPIO_wait_for_pin(GPIO_TypeDef* GPIOx, int pinNb){
	
	uint32_t pin;
	
	switch (pinNb){
		case 0 : pin = LL_GPIO_PIN_0; break;
		case 1 : pin = LL_GPIO_PIN_1; break;
		case 2 : pin = LL_GPIO_PIN_2; break;
		case 3 : pin = LL_GPIO_PIN_3; break;
		case 4 : pin = LL_GPIO_PIN_4; break;
		case 5 : pin = LL_GPIO_PIN_5; break;
		case 6 : pin = LL_GPIO_PIN_6; break;
		case 7 : pin = LL_GPIO_PIN_7; break;
		case 8 : pin = LL_GPIO_PIN_8; break;
		case 9 : pin = LL_GPIO_PIN_9; break;
		case 10 : pin = LL_GPIO_PIN_10; break;
		case 11 : pin = LL_GPIO_PIN_11; break;
		case 12 : pin = LL_GPIO_PIN_12; break;
		case 13 : pin = LL_GPIO_PIN_13; break;
		case 14 : pin = LL_GPIO_PIN_14; break;
		case 15 : pin = LL_GPIO_PIN_15; break;
	}
	

	while(!LL_GPIO_IsInputPinSet(GPIOx, pin))
	 {
	}
}
