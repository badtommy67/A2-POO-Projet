#include "Console.h"
#include <iostream>

using namespace std;

Console::Console(const IGrille& g) : grille(g) {}

void Console::affichageCellules(){
    cout << "-- Affichage de la grille a la prochaine iteration --" << endl;

    int nb_colonnes = grille.getcolonne(); // nb de lignes
    int nb_lignes = grille.getligne(); // nb de colonnes

    for (int i = 0 ; i<nb_lignes;i++){
        for (int j=0; j<nb_colonnes;j++){
            bool etat;
            etat = grille.getCellule(i, j).estVivante();
            cout << etat;
        }
        cout << endl;
    }
    cout << endl;
}