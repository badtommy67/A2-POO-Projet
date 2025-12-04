#ifndef REGLES_INITIALES_H
#define REGLES_INITIALES_H

#include "Regles_du_jeu.h"
#include "Est_vivant.h"
#include "Est_mort.h"

class Regles_initiales : public Regles_du_jeu {
public:
    Cellule* calculerProchainEtat(Cellule& cel, int nb_voisins)override;
};

#endif