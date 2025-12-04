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
    virtual bool mettreAJourGrille() = 0; 
    virtual int getLigne() const = 0;
    virtual int getColonne() const = 0;
    virtual Cellule& getCellule(int x, int y)= 0;
    virtual std::vector<std::vector<bool>> getMatriceEtat() const=0;
};

#endif