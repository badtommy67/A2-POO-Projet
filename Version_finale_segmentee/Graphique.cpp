#include "Graphique.h"

#include "Fichier.h"
#include <cstdlib>
#include <vector>

Graphique::Graphique(IGrille& g, int tailleCellule) : grille(g), cellSize(tailleCellule) {}

void Graphique::affichageCellules(sf::RenderWindow &window) {
    window.clear(sf::Color::White); // on efface tout pour remettre un fond blanc

    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f)); // creation de la forme rectangle pour creer nos cellules vivantes
    cell.setFillColor(sf::Color::Black); // couleur noire

    int ligne=grille.getLigne();
    int colonne=grille.getColonne();

    for (int x = 0; x < ligne; x++) { // on parcours la grille
        for (int y = 0; y < colonne; y++) {
            if (grille.getCellule(x,y).getEtat()->estVivante()) { // si la cellule est vivante on va l'afficher
                cell.setPosition(y * cellSize, x * cellSize); // aux coordonnées (x,y) | calcul : position en x * la longueur de la cellule et idem en y
                window.draw(cell); // on la dessine
            }
        }
    }
    window.display(); // on affiche a l'ecran la grille entiere mise a jour
}