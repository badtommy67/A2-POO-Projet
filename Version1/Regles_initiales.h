#ifndef REGLES_INITIALES_H
#define REGLES_INITIALES_H

#include "Regles_du_jeu.h"

class Regles_initiales : public Regles_du_jeu {
public:
    Etat_cellule* calculerProchainEtat(bool estVivant, int nb_voisins) override;
};

#endif