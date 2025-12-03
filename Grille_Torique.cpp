#include "Grille_Torique.h"
#include "Regles_initiales.h"
#include <cmath>
#include <iostream>

Grille_Torique::Grille_Torique(int l, int c) : IGrille(), ligne(l), colonne(c) {
    regles = new Regles_initiales();
    cellules.resize(ligne, std::vector<Cellule>(colonne));
}

Grille_Torique::~Grille_Torique() {
    delete regles;
}


void Grille_Torique::chargerGrille(const std::vector<std::vector<bool>>& matrice) {
    if (matrice.empty() || matrice[0].empty()) return;

    if (cellules.size() != ligne || cellules[0].size() != colonne) {
        cellules.clear();
        cellules.resize(ligne, std::vector<Cellule>(colonne));
    }

    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
            if (matrice[i][j] != cellules[i][j].getEtat()->estVivante()) {
                cellules[i][j].changementEtat();
            }
        }
    }
}

int Grille_Torique::compterVoisins(int x, int y) {
    int nb_voisins = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (dx == 0 && dy == 0) continue;
            
            int nx = (x + dx + ligne) % ligne;
            int ny = (y + dy + colonne) % colonne;

            if (cellules[nx][ny].getEtat()->estVivante())
                nb_voisins++;
        }
    }

    return nb_voisins;
}

int Grille_Torique::getLigne()const{return ligne;}
int Grille_Torique::getColonne()const{return colonne;}
Cellule& Grille_Torique::getCellule(int x, int y){return cellules[x][y];}

bool Grille_Torique::mettreAJourGrille() {
    if(!regles) return 0;


    // Créer une matrice de bool au lieu de copier les Cellule
    std::vector<std::vector<bool>> nouveauxEtats(ligne, std::vector<bool>(colonne));

    for (int x = 0; x < ligne; x++) {
        for (int y = 0; y < colonne; y++) {
            int voisins = compterVoisins(x, y);
            Cellule* resultat = regles->calculerProchainEtat(cellules[x][y], voisins);
            nouveauxEtats[x][y] = resultat->getEtat()->estVivante();
            delete resultat;
        }
    }

    // Appliquer les changements
    for (int x = 0; x < ligne; x++) {
        for (int y = 0; y < colonne; y++) {
            bool etatActuel = cellules[x][y].getEtat()->estVivante();
            if (etatActuel != nouveauxEtats[x][y]) {
                cellules[x][y].changementEtat();
            }
        }
    }
    return 1;
}

void Grille_Torique::fill(int value) {
    //std::cout << "Début fill, value=" << value << std::endl;
    bool val = (value != 0);
    
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
            // Vérifier que getEtat() ne renvoie pas nullptr
            const Etat_cellule* etat = cellules[i][j].getEtat();
            if (etat == nullptr) {
                std::cout << "ERREUR: cellule[" << i << "][" << j << "] a un état null!" << std::endl;
                continue;
            }
            
            bool actuel = etat->estVivante();
            if (actuel != val) {
                cellules[i][j].changementEtat();
            }
        }
    }
    //std::cout << "Fin fill" << std::endl;
}

std::vector<std::vector<bool>> Grille_Torique::getMatriceEtat() const {
    // 1. On crée une matrice vide de la bonne taille
    std::vector<std::vector<bool>> matrice(ligne, std::vector<bool>(colonne));

    // 2. On remplit en demandant à chaque cellule si elle est vivante
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
            matrice[i][j] = cellules[i][j].getEtat()->estVivante();
        }
    }
    return matrice;
}