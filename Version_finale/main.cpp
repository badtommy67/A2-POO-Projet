#include <iostream>
#include <vector>
#include "Fichier.h"
#include "Gestion_jeu.h"

using namespace std;

void afficher(const vector<vector<bool>>& matrice) {
    for (const auto& ligne : matrice) {
        for (bool val : ligne) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    Gestion_jeu gj;
    //Fichier fichier("Fichiers_source/test2.txt");
    gj.initialiser();
  
    //fichier.ecriture(matrice);
    //fichier.ecriture(matrice);
    return 0;
}

// g++ *.cpp -o jeu -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs