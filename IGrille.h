#ifndef IGRILLE_H
#define IGRILLE_H

#include <vector>
#include <string>
#include "Cellule.h"
#include "Regles_du_jeu.h"

class IGrille {
private:
    std::vector<std::vector<Cellule>> cellules;
    int largeur;
    int longueur;
    Regles_du_jeu* regles;

public:
    Grille(int l, int L);
    
    virtual void chargerGrille(const std::vector<std::vector<bool>>& matriceInitiale);

    virtual int compterVoisins(int x, int y) const;

    virtual void mettreAJourGrille(); 
    
    virtual int getLargeur() const;
    virtual int getLongueur() const;
    virtual const Cellule& getCellule(int x, int y) const;
};

#endif