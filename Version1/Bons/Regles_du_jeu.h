#ifndef REGLES_DU_JEU_H
#define REGLES_DU_JEU_H

#include "Etat_cellule.h"

class Regles_du_jeu {
public:
    virtual ~Regles_du_jeu() = default;
    virtual Etat_cellule* calculerProchainEtat(bool estVivant, int nb_voisins) = 0;
};

#endif