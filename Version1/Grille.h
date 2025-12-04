#ifndef GRILLE_H
#define GRILLE_H

#include "IGrille.h"
#include "Regles_du_jeu.h"
#include <vector>

class Grille : public IGrille {
private:
    std::vector<std::vector<Cellule>> cellules;
    int nb_lignes;
    int nb_colonnes;
    Regles_du_jeu* regles; // La grille possède les règles

    int compterVoisins(int i, int j) const;

public:
    Grille(int lignes, int colonnes);
    ~Grille();

    void chargerGrille(const std::vector<std::vector<bool>>& matrice) override;
    void mettreAJourGrille() override;
    
    int getligne() const override { return nb_lignes; }
    int getcolonne() const override { return nb_colonnes; }
    const Cellule& getCellule(int i, int j) const override;

    void fill(int k) override; // Implémentation requise
};

#endif