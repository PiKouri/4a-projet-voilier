#include "MyTimer.h"
#include "MyGPIO.h"

//Configurent le timer et la broche du GPIO li�s au servomoteur
void timerConfServo(void);
void GPIOConfServo(void);

//Positionne la voile � l'angle d�sir�
void setAngleVoile(int angle);
