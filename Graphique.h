#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "Grille.h"

class Graphique {
private:
    const Grille& grille;

public:
    Graphique(const Grille& g);
    void ouvrirFenetre();
    void affichageCellules();
};

#endif