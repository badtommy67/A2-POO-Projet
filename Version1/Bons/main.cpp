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
    Fichier fichier("Fichiers_source/test2.txt");

    vector<vector<bool>> matrice = fichier.lecture();

    if (matrice.empty()) {
        cout << "Aucune matrice n'a été lue." << endl;
        return 1;
    }

    cout << "Matrice lue :" << endl;
    afficher(matrice);
    fichier.creationDossier();
    fichier.ecriture(matrice);
    fichier.ecriture(matrice);

    return 0;
}
