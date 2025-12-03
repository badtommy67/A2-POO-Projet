#ifndef EST_MORT_H
#define EST_MORT_H

#include "Etat_cellule.h"

class Est_mort : public Etat_cellule {
public:
    bool estVivante() const;
    
};

#endif
