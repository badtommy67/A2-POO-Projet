#ifndef CONSOLE_H
#define CONSOLE_H

#include "IGrille.h"

class Console {
private:
    IGrille& grille;

public:
    Console();
    Console(IGrille& g);
    void affichageCellules();
};

#endif