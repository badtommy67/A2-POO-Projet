#ifndef GRILLE_TORIQUE_H
#define GRILLE_TORIQUE_H

#include <vector>
#include <string>
#include "Cellule.h"
#include "Regles_du_jeu.h"
#include "IGrille.h"

class Grille_Torique: public IGrille {
private:
    std::vector<std::vector<Cellule>> cellules;  //cellules[ligne][colonne]
    int ligne;
    int colonne;
    Regles_du_jeu* regles;

public:
    Grille_Torique(int l, int c);
    ~Grille_Torique();

    void fill(int value) override;
    
    void chargerGrille(const std::vector<std::vector<bool>>& matrice)override;

    int compterVoisins(int x, int y)override;

    bool mettreAJourGrille()override; 
    
    int getLigne() const override;
    int getColonne() const override;
    Cellule& getCellule(int x, int y)override;
    std::vector<std::vector<bool>> getMatriceEtat() const override;
};

#endif