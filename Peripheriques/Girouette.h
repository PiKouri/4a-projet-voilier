#include "MyTimer.h"
#include "MyGPIO.h"
extern int toto;
//Configurent le timer et la broche du GPIO liés à la girouette
void timerConfGirouette(void);
void GPIOConfGirouette(void);

//Initialisation de l'angle de la girouette (/!\ fonction scrutative, bloquante)
void initAngleGirouette(void);

//Retourne l'angle actuel du vent
int getAngleVent(void);

