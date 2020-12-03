#include "ControleVoile.h"

void confDriversVoile(){
	//timer et GPIO du servo-moteur /!\ l'ordre "GPIO puis Timer" est important !
	GPIOConfServo();
	timerConfServo();
	GPIOConfGirouette();
	timerConfGirouette();
	GPIOConfAccelero();
	ADCConfAccelero();
	
	// /!\Initialisation de l'angle de la girouette, partie bloquante !
	initAngleGirouette();
}

void reglerVoile(){
	int angleVent;
	if (getAngleRoulis()>40) {
		setAngleVoile(0);
	}
	else {
		angleVent=getAngleVent();
		if (angleVent>45 && angleVent<180){
			setAngleVoile(((angleVent-45)/(180-45))*90);
		} else if (angleVent>180 && angleVent < 315) {
			setAngleVoile(((315-angleVent)/(315-180))*90);
		}
	}
}
