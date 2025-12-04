#ifndef ETAT_CELLULE_H
#define ETAT_CELLULE_H

class Etat_cellule {
public:
    virtual ~Etat_cellule() = default; // ces deux méthodes seront redefinies dans les classes filles.
    virtual bool estVivante() const = 0;
};

#endif