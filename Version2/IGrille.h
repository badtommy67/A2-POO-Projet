#ifndef IGRILLE_H
#define IGRILLE_H

#include <vector>
#include "Cellule.h"

class IGrille {
protected:
    IGrille() = default;
    
public:
    virtual ~IGrille() = default;

    virtual void fill(int value) = 0;
    virtual void chargerGrille(const std::vector<std::vector<bool>>& matrice) = 0;
    virtual int compterVoisins(int x, int y) = 0;
    virtual void mettreAJourGrille() = 0; 
    virtual int getLigne() const = 0;
    virtual int getColonne() const = 0;
    virtual const Cellule& getCellule(int x, int y) const = 0;
    virtual std::vector<std::vector<bool>> getMatriceEtat() const = 0;
};

#endif