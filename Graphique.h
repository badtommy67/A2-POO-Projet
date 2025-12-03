#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include <SFML/Graphics.hpp>
#include "IGrille.h"
#include "Fichier.h"
#include <vector>


class Graphique {
private:
    IGrille& grille;
    const int cellSize;
    Fichier* gestionFichierGraph;

public:
    Graphique(IGrille& g, int tailleCellule = 10);
    void affichageCellules(sf::RenderWindow &window);
    const int getCellSize()const{return cellSize;}
};

#endif