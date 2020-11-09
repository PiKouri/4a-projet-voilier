#include "ControleMoteur.h"
#include "RecepteurRF.h"
#include "Moteur.h"

void confDriversMoteur(void) {
	Moteur_Conf();
	RecepteurRF_Conf();
};

void reglerVitesseMot(void) {
	double vitesse = getVitesse() ;
	setVitesse(vitesse);
};

void reglerCap(void) {
	char cap = getCap();
	setCap(cap);
};
