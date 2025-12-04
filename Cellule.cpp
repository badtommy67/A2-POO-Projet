#include "Cellule.h"
#include "Est_mort.h"
#include "Est_vivant.h"

Cellule::Cellule(Etat_cellule* etatInitial)
    : etatActuel(etatInitial ? etatInitial : new Est_mort()) {}

Cellule::Cellule()
    : etatActuel(new Est_mort()) {}

Cellule::~Cellule() {
    delete etatActuel;
}

Cellule::Cellule(const Cellule& autre) { // on creer un nouvel objet avec le nouvel état de notre cellule
    if (autre.etatActuel->estVivante()) {
        etatActuel = new Est_vivant();
    } else {
        etatActuel = new Est_mort();
    }
}

void Cellule::changementEtat() {
    Etat_cellule* ancienEtat = etatActuel; // on va changer l'etat de notre cellule (mort->vivant ou vivant->mort)
    if (etatActuel->estVivante()) {
        etatActuel = new Est_mort();
    } else {
        etatActuel = new Est_vivant();
    }
    delete ancienEtat; // suppression de cet objet
}

const Etat_cellule* Cellule::getEtat()const{return etatActuel;} // permet de recuperer l'etat actuel de la cellule