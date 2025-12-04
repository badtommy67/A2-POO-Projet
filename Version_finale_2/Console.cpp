#include "Console.h"
#include <iostream>

using namespace std;

Console::Console(IGrille& g) : grille(g) {} 

void Console::affichageCellules(){
    cout << "-- Affichage de la grille a la prochaine iteration --" << endl;
    int ligne = grille.getLigne(); // nb lignes
    int colonne = grille.getColonne(); //nb colonne
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
            bool etat = grille.getCellule(i, j).getEtat()->estVivante();
            cout << etat;
        }
        cout << endl;
    }
    cout << endl;
}
