#ifndef CELLULE_H
#define CELLULE_H

#include "Etat_cellule.h"

class Cellule {
private:
    Etat_cellule* etatActuel;

public:
    Cellule();
    ~Cellule(); // Important pour nettoyer la mémoire

    void setEtat(Etat_cellule* nouvelEtat);
    bool estVivante() const;
};

#endif