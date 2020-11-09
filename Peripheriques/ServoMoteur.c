#include "ServoMoteur.h"
#include <math.h>

//R�solution de la PWM
int resPWM;  //Pb ici : la r�solution est tjr = 0, voir avec JR et Cl�mentine


void timerConfServo(){
	resPWM=PWM_Init(TIM4, '3', 1, 'o', ' ');
	MyTimer_Start(TIM4);
	
	//On r�gle l'angle de la voile � 0 avant tout
	PWM_Set_CCR(TIM4, '3', 0);
}

void GPIOConfServo(){
	MyGPIO_pin_conf(GPIOB, 8, 'l');	
}

void setAngleVoile(double angle){
	double CCR_value;
	CCR_value = (angle/90)*(pow(2, resPWM));
	PWM_Set_CCR(TIM4, '3', CCR_value);
}
