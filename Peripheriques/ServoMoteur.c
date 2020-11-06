#include "ServoMoteur.h"
#include <math.h>

//Résolution de la PWM
int resPWM;  //Pb ici : la résolution est tjr = 0, voir avec JR et Clémentine
int CCR_value; //A passer en local dès que pb resPWM résolu

void timerConfServo(){
	resPWM=PWM_Init(TIM4, '3', 1, 'o', ' ');
}

void GPIOConfServo(){
	MyGPIO_pin_conf(GPIOB, 8, 'l');	
}

void setAngleVoile(int angle){

	CCR_value = angle/90*(pow(2, resPWM));
	PWM_Set_CCR(TIM4, '3', CCR_value);
}
