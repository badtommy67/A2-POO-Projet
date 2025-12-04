#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "IGrille.h"
#include <SFML/Graphics.hpp> // pour SFML

class Graphique {
private:
    const IGrille& grille;
    sf::RenderWindow* fenetre; // pointeur vers la fenêtre SFML
    int tailleCellule; // taille d'un carré en pixels (ex: 20px)

public:
    Graphique(const IGrille& g);
    ~Graphique();
    void ouvrirFenetre();
    void affichageCellules();
    void traiterEvenements();
    bool estOuverte() const;
};

#endif