#ifndef ETAT_CELLULE_H
#define ETAT_CELLULE_H

class Etat_cellule {
public:
    virtual ~Etat_cellule() = default;
    virtual bool estVivante() const = 0;
};

#endif