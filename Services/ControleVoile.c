#include "ControleVoile.h"


void timerConfVoile(){
	
	
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