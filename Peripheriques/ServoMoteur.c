#include "ServoMoteur.h"

//Résolution de la PWM
int resPWM;

void timerConfServo(){
	resPWM=PWM_Init(TIM4, '3', 1, 'o', ' ');
}

void GPIOConfServo(){
	MyGPIO_pin_conf(GPIOB, 8, 'l');	
}

void setAngleVoile(int angle){
	int CCR_value;
	CCR_value = angle/90*resPWM;
	PWM_Set_CCR(TIM4, '3', CCR_value);
}
