#ifndef IGRILLE_H
#define IGRILLE_H

#include <vector>
#include "Cellule.h"

class IGrille {
public:
    virtual ~IGrille() = default;
    
    virtual void chargerGrille(const std::vector<std::vector<bool>>& matrice) = 0;
    virtual void mettreAJourGrille() = 0;
    
    // Accesseurs pour Console/Graphique
    virtual int getligne() const = 0;   // Hauteur
    virtual int getcolonne() const = 0; // Largeur
    virtual const Cellule& getCellule(int i, int j) const = 0;

    // Méthode appelée dans votre Gestion_jeu.cpp actuel
    virtual void fill(int k) = 0; 
};

#endif