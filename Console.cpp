#include "Console.h"
#include <iostream>

using namespace std;

Console::Console(IGrille& g) : grille(g) {} 

void Console::affichageCellules(){
    cout << "-- Affichage de la grille a la prochaine iteration --" << endl; // affichage permettant de separer les iterations entre elles

    int ligne = grille.getLigne(); // nb lignes
    int colonne = grille.getColonne(); //nb colonne
    // on parcours toute la grille et on affiche l'etat de la cellule
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
            bool etat = grille.getCellule(i, j).getEtat()->estVivante(); // ici on recupere l'objet Cellule aux coordonnees (i ;j), on recupere le pointeur vers l'etat et on verifie si elle est vivante.
            cout << etat;
        }
        cout << endl;
    }
    cout << endl;
}
