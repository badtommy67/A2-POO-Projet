#include "Grille.h"
#include "Regles_initiales.h"
#include "Est_vivant.h"
#include "Est_mort.h"

Grille::Grille(int lignes, int colonnes) : nb_lignes(lignes), nb_colonnes(colonnes) {
    // Initialisation du vecteur de cellules
    cellules.resize(nb_lignes, std::vector<Cellule>(nb_colonnes));
    
    // On utilise les règles classiques par défaut
    regles = new Regles_initiales();
}

Grille::~Grille() {
    delete regles;
}

// Implémentation de fill (appelé dans votre code)
void Grille::fill(int k) {
    // Ici on pourrait forcer toutes les cellules à un état, 
    // mais le constructeur initialise déjà tout à Mort par défaut via Cellule().
    // On laisse vide ou on remet à mort si besoin.
}

const Cellule& Grille::getCellule(int i, int j) const {
    return cellules[i][j];
}

void Grille::chargerGrille(const std::vector<std::vector<bool>>& matrice) {
    // On redimensionne si besoin (sécurité)
    if (matrice.empty()) return;
    
    // Attention : i = ligne, j = colonne
    for (int i = 0; i < nb_lignes; ++i) {
        for (int j = 0; j < nb_colonnes; ++j) {
            if (matrice[i][j]) {
                cellules[i][j].setEtat(new Est_vivant());
            } else {
                cellules[i][j].setEtat(new Est_mort());
            }
        }
    }
}

int Grille::compterVoisins(int x, int y) const {
    int voisins = 0;
    // On regarde les 8 cases autour
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            // On s'ignore soi-même
            if (i == x && j == y) continue;

            // Vérification des limites (Bords de la grille)
            if (i >= 0 && i < nb_lignes && j >= 0 && j < nb_colonnes) {
                if (cellules[i][j].estVivante()) {
                    voisins++;
                }
            }
        }
    }
    return voisins;
}

void Grille::mettreAJourGrille() {
    // 1. Calculer les futurs états SANS modifier la grille actuelle
    // On stocke les futurs états dans une matrice temporaire de pointeurs
    std::vector<std::vector<Etat_cellule*>> futursEtats(nb_lignes, std::vector<Etat_cellule*>(nb_colonnes));

    for (int i = 0; i < nb_lignes; ++i) {
        for (int j = 0; j < nb_colonnes; ++j) {
            int nb_voisins = compterVoisins(i, j);
            bool vivant = cellules[i][j].estVivante();
            
            // La règle nous rend un NOUVEL objet état (new)
            futursEtats[i][j] = regles->calculerProchainEtat(vivant, nb_voisins);
        }
    }

    // 2. Appliquer les changements
    for (int i = 0; i < nb_lignes; ++i) {
        for (int j = 0; j < nb_colonnes; ++j) {
            cellules[i][j].setEtat(futursEtats[i][j]);
        }
    }
}