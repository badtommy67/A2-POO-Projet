#ifndef CELLULE_H
#define CELLULE_H

class Cellule {
private:
    bool vivante; // Simple booléen pour l'instant (mock)

public:
    Cellule() : vivante(false) {}

    // Méthode utilisée par Console
    bool estVivante() const { return vivante; }

    // Méthode utilisée par le TEST (MockGrille) pour forcer l'état
    void setVivante(bool v) { vivante = v; }
};

#endif