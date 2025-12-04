#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <string>
#include "Cellule.h"
#include "Regles_du_jeu.h"
#include "IGrille.h"

//#include "Gestion_jeu.h"

class Grille: public IGrille {
private:
    std::vector<std::vector<Cellule>> cellules;  //cellules[ligne][colonne]
    int ligne;
    int colonne;
    Regles_du_jeu* regles;
    //Gestion_jeu* jeu;

public:
    Grille(int l, int c);
    ~Grille();

    void fill(int value) override;
    
    void chargerGrille(const std::vector<std::vector<bool>>& matrice)override;

    int compterVoisins(int x, int y)override;

    void mettreAJourGrille()override; 
    
    int getLigne() const override;
    int getColonne() const override;
    const Cellule& getCellule(int x, int y) const override;
    std::vector<std::vector<bool>> getMatriceEtat() const override;

};

#endif