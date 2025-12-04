#ifndef IGRILLE_H
#define IGRILLE_H

#include "Cellule.h"
#include <vector>

class IGrille {
public:
    virtual ~IGrille() = default;

    // Méthodes virtuelles pures (Le contrat)
    virtual int getligne() const = 0;
    virtual int getcolonne() const = 0;
    virtual const Cellule& getCellule(int x, int y) const = 0;

    // Ces méthodes sont aussi nécessaires car utilisées dans votre projet
    virtual void chargerGrille(const std::vector<std::vector<bool>>& matrice) = 0;
    virtual void mettreAJourGrille() = 0;
    virtual int compterVoisins(int x, int y) = 0;
    virtual void fill(int k) = 0; // Ajouté car présent dans votre Mock
};

#endif