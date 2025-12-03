#include "Graphique.h"

#include "Fichier.h"
#include <ctime>
#include <cstdlib>
#include <vector>

Graphique::Graphique(IGrille& g, int tailleCellule) 
    : grille(g), cellSize(tailleCellule) {}


void Graphique::initialiserGrille() {
    std::srand(std::time(0));
    for (int x = 0; x < grille.getColonne(); ++x) {
        for (int y = 0; y < grille.getLigne(); ++y) {
            if(std::rand() % 2)  // Randomly initialize cells as alive or dead
                grille.getCellule(x,y).changementEtat();
        }
    }
}

void Graphique::affichageCellules(sf::RenderWindow &window) {
    window.clear(sf::Color::White);

    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    cell.setFillColor(sf::Color::Black);

    int ligne=grille.getLigne();
    int colonne=grille.getColonne();

    for (int x = 0; x < ligne; x++) {
        for (int y = 0; y < colonne; y++) {
            if (grille.getCellule(x,y).getEtat()->estVivante()) {
                cell.setPosition(y * cellSize, x * cellSize);
                window.draw(cell);
            }
        }
    }
    window.display();
}