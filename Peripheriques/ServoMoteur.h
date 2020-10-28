#include "MyTimer.h"
#include "MyGPIO.h"

//Configurent le timer et la broche du GPIO liés au servomoteur
void timerConfServo(void);
void GPIOConfServo(void);

//Positionne la voile à l'angle désiré
void setAngleVoile(int angle);
