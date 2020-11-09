#include "ControleVoile.h"

void confDriversVoile(){
	//timer et GPIO du servo-moteur /!\ l'ordre "GPIO puis Timer" est important !
	GPIOConfServo();
	timerConfServo();
	GPIOConfGirouette();
	timerConfGirouette();
	GPIOConfAccelero();
	
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
		if (angleVent>45){
			setAngleVoile((angleVent-45)*2);
		}
	}
}
