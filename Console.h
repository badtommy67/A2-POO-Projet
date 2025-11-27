#ifndef CONSOLE_H
#define CONSOLE_H

#include "Grille.h"

class Console {
private:
    const Grille& grille;

public:
    Console(const Grille& g);
    void affichageCellules();
};

#endif