#include "ServoMoteur.h"
#include <math.h>


void timerConfServo(){
	PWM_Output_Init(TIM4,3, 50, 0.05); // 50 Hz (20 ms) et 5% = 1ms => Voile à 0
	MyTimer_Start(TIM4);
}

void GPIOConfServo(){
	MyGPIO_pin_conf(GPIOB, 8, 'l');	
}

void setAngleVoile(double angle){
	double CCR_value;
	double une_ms = TIM4->ARR/20;
	CCR_value = (angle/90)*une_ms+une_ms;
	PWM_Set_CCR(TIM4, 3, CCR_value);
}
