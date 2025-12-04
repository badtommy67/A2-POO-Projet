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

    if (cellules.size() != ligne || cellules[0].size() != colonne) { // si la taille diffère, elle redimensionne la grille
        cellules.clear();
        cellules.resize(ligne, std::vector<Cellule>(colonne));
    }

    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
            if (matrice[i][j] != cellules[i][j].getEtat()->estVivante()) { // on parcours chaque case et on change l'etat si l'etat actuel diffère de celui souhaité
                cellules[i][j].changementEtat();
            }
        }
    }
}

int Grille_Torique::compterVoisins(int x, int y) {
    int nb_voisins = 0;

    for (int dx = -1; dx <= 1; dx++) { // ici on va donc parcourir tous les voisins de notre cellule de (-1;1) à (1;-1) en prenant en compte les bords qui sont continus
        for (int dy = -1; dy <= 1; dy++) {

            if (dx == 0 && dy == 0) continue; // en ignorant la cellule en question.
            
            int nx = (x + dx + ligne) % ligne; // ici on va donc chercher la cellule de l'autre cote de la grille si nous sommes sur un bord de gauche a droite
            int ny = (y + dy + colonne) % colonne; // idem ici, pour de haut en bas et vice versa

            if (cellules[nx][ny].getEtat()->estVivante()) // si la cellule autour est vivante, on ajoute 1 au compteur
                nb_voisins++;
        }
    }

    return nb_voisins;
}

int Grille_Torique::getLigne()const{return ligne;} // on recupere ligne
int Grille_Torique::getColonne()const{return colonne;} // on recupere colonne
Cellule& Grille_Torique::getCellule(int x, int y){return cellules[x][y];}

bool Grille_Torique::mettreAJourGrille() {
    if(!regles) return 0;

    // on creer notre nouvelle matrice
    std::vector<std::vector<bool>> nouveauxEtats(ligne, std::vector<bool>(colonne));

    for (int x = 0; x < ligne; x++) {
        for (int y = 0; y < colonne; y++) { // pour chacune des cellules de la matrice
            int voisins = compterVoisins(x, y); //on compte le nombre de voisins
            Cellule* resultat = regles->calculerProchainEtat(cellules[x][y], voisins); // on verifie si on doit changer l'etat de la cellule en fonction du nb de voisins
            nouveauxEtats[x][y] = resultat->getEtat()->estVivante();
            delete resultat;
        }
    }

    // on applique les changements
    for (int x = 0; x < ligne; x++) {
        for (int y = 0; y < colonne; y++) {
            bool etatActuel = cellules[x][y].getEtat()->estVivante();
            if (etatActuel != nouveauxEtats[x][y]) {
                cellules[x][y].changementEtat(); // on met dans la grille nos changements
            }
        }
    }
    return 1;
}

void Grille_Torique::fill(int value) {
    // on rempli toute la grille avec la value (normalement 0)
    bool val = (value != 0);
    
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
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
}

std::vector<std::vector<bool>> Grille_Torique::getMatriceEtat() const {
    //on crée une matrice vide de la bonne taille
    std::vector<std::vector<bool>> matrice(ligne, std::vector<bool>(colonne));

    // on remplit en demandant à chaque cellule si elle est vivante
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
            matrice[i][j] = cellules[i][j].getEtat()->estVivante();
        }
    }
    return matrice;
}