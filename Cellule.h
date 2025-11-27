#ifndef CELLULE_H
#define CELLULE_H

#include "Etat_cellule.h"

class Cellule {
private:
    Etat_cellule* etatActuel;

public:
    Cellule(Etat_cellule* etatInitial = nullptr);
    ~Cellule();

    void setEtat(Etat_cellule* nouvelEtat);
    bool estVivante() const;
};

#endif