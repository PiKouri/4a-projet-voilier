#include "ControleMoteur.h"
#include "RecepteurRF.h"
#include "Moteur.h"

void confDriversMoteur(void) {
	Moteur_Conf();
	RecepteurRF_Conf();
};

void reglerCap(void) {
	char cap = getCap();
	setCap(cap);
};

void reglerVitesseMot(void) {
	double vitesse = getVitesse() ;
	setVitesse(vitesse);
};


