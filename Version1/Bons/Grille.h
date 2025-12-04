#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <string>
#include "Cellule.h"
#include "Regles_du_jeu.h"

class Grille {
private:
    std::vector<std::vector<Cellule>> cellules;
    int largeur;
    int longueur;
    Regles_du_jeu* regles;

public:
    Grille(int l, int L);
    
    void chargerGrille(const std::vector<std::vector<bool>>& matriceInitiale);

    int compterVoisins(int x, int y) const;

    void mettreAJourGrille(); 
    
    int getLargeur() const;
    int getLongueur() const;
    const Cellule& getCellule(int x, int y) const;
};

#endif