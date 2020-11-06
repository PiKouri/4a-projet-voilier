#include "ControleMoteur.h"
#include "RecepteurRF.h"
#include "Moteur.h"

void confDriversMoteur(void) {
	Moteur_Conf();
	RecepteurRF_Conf();
};

void manageRecepteurRF_Moteur(void) {
	double vitesse = RecepteurRF_Get_Vitesse() ;
	char cap = RecepteurRF_Get_Cap();
	Set_Vitesse(vitesse);
	Set_Cap(cap);
};
