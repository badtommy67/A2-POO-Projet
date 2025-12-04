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

Cellule::Cellule(const Cellule& autre) {
    if (autre.etatActuel->estVivante()) {
        etatActuel = new Est_vivant();
    } else {
        etatActuel = new Est_mort();
    }
}

void Cellule::changementEtat() {
    Etat_cellule* ancienEtat = etatActuel; // Copie le pointeur
    if (etatActuel->estVivante()) {
        etatActuel = new Est_mort();
    } else {
        etatActuel = new Est_vivant();
    }
    delete ancienEtat; // Supprime l'ancien objet pointé
}

const Etat_cellule* Cellule::getEtat()const{return etatActuel;}