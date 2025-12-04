#ifndef EST_VIVANT_H
#define EST_VIVANT_H
#include "Etat_cellule.h"

class Est_vivant : public Etat_cellule {
public:
    bool estVivante() const override { return true; }
};
#endif