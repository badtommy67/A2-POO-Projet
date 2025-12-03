#ifndef CELLULE_H
#define CELLULE_H

#include "Etat_cellule.h"
#include "Est_vivant.h"
#include "Est_mort.h"

class Cellule {
private:
    Etat_cellule* etatActuel;

public:
    Cellule(Etat_cellule* etatInitial);
    Cellule();
    ~Cellule();
    
    Cellule(const Cellule& autre);

    void changementEtat();
    const Etat_cellule* getEtat() const;
};

#endif