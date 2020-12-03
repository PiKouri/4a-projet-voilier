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
	float vitesse = getVitesse() ;
	int vit = (int) vitesse;
	if (vit>=10) vit = 10;
	if (vit<=0) vit = 0;
	setVitesse(vit);
};


