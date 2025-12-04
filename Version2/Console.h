#ifndef CONSOLE_H
#define CONSOLE_H

#include "IGrille.h"

class Console {
private:
    const IGrille& grille;

public:
    Console();
    Console(const IGrille& g);
    void affichageCellules();
};

#endif