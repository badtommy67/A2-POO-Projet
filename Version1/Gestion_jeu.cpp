#include "Gestion_jeu.h"
#include <iostream>
#include <vector>

using namespace std;

Gestion_jeu::Gestion_jeu(string nom_fichier, int nb_iterations, int compteur_iteration) : nom_fichier(nom_fichier),nb_iterations(0),compteur_iteration(0) {}
Gestion_jeu::Gestion_jeu() : grille(nullptr), gestionFichier(nullptr) {}

void Gestion_jeu::initialiser(){
    //cout << "Quel est le fichier à prendre en entrée ?" << endl;
    //cin >> nom_fichier;
    nom_fichier="Fichiers_source/test2.txt";
    cout << "Combien d'itérations souhaitez-vous ?" << endl;
    cin >> nb_iterations;
    int mode;
    cout << "Quel mode souhaitez-vous ? 1-Console | 2-Graphique" << endl;
    cin >> mode;

    gestionFichier = new Fichier(nom_fichier);
    gestionFichier->creationDossier();

    cout << "--- DEBUG: Lecture fichier... ---" << endl;
    vector<vector<bool>> matrice = gestionFichier->lecture();
    cout << "--- DEBUG: Lecture terminee. Taille: " << matrice.size() << " ---" << endl;

    if (matrice.empty()) {
        cout << "ERREUR CRITIQUE : Le fichier est introuvable ou vide !" << endl;
        cout << "Vérifiez que le fichier '" << nom_fichier << "' existe bien." << endl;
        return; // On arrête tout pour éviter le crash
    }

    int nb_lignes = matrice.size(); // nb de lignes
    int nb_colonnes = matrice[0].size(); // nb de colonnes

    cout << "--- DEBUG: Creation Grille (" << nb_lignes << "x" << nb_colonnes << ")... ---" << endl;
    grille = new Grille(nb_lignes, nb_colonnes);
    cout << "--- DEBUG: Grille creee. Chargement donnees... ---" << endl;
    //grille->fill(0);

    grille->chargerGrille(matrice);
    cout << "--- DEBUG: Chargement termine. ---" << endl;
    if (mode == 1){
        jouerConsole();
    } else if (mode == 2){
        //jouerGraphique();
    } else{
        cout << "Entree non valide !" << endl;
    }
}

void Gestion_jeu::jouerConsole(){
    Console console(*grille);
    for (int i = 0; i < nb_iterations; ++i) {
        compteur_iteration++;
        
        console.affichageCellules(); 

        grille->mettreAJourGrille();
    }
}

/*void Gestion_jeu::jouerGraphique(){
    Graphique graphique(*grille);
    for (int i = 0; i < nb_iterations; ++i) {
        compteur_iteration++;
        
        graphique.affichageCellules(); 

        grille->mettreAJourGrille();
    }
}*/