#include "Gestion_jeu.h"
#include <iostream>
#include <vector>


using namespace std;

Gestion_jeu::Gestion_jeu(string nom_entree, int nb_iterations, int compteur_iteration)
    : nom_entree(nom_entree), nb_iterations(nb_iterations), compteur_iteration(compteur_iteration), grille(nullptr), gestionFichier(nullptr) {}

Gestion_jeu::Gestion_jeu() : grille(nullptr), gestionFichier(nullptr), nb_iterations(0), compteur_iteration(0) {}

Gestion_jeu::~Gestion_jeu() {
    delete grille;
    delete gestionFichier;
}

void Gestion_jeu::initialiser(){
    //std::cout << "Début initialisation" << std::endl;
    
    cout << "Quel est le fichier à prendre en entrée ?" << endl;
    cin >> nom_entree;
    cout << "Combien d'itérations souhaitez-vous ?" << endl;
    cin >> nb_iterations;
    int mode;
    cout << "Quel mode souhaitez-vous ? 1-Console | 2-Graphique" << endl;
    cin >> mode;

    //std::cout << "Création gestionFichier" << std::endl;
    gestionFichier = new Fichier(nom_entree);
    gestionFichier->creationDossier();

    //std::cout << "Lecture du fichier" << std::endl;
    vector<vector<bool>> matrice = gestionFichier->lecture();

    if (matrice.empty() || matrice[0].empty()) {
        cout << "Erreur: La grille lue est vide ou mal formatée. Abandon." << endl;
        return;
    }

    int nb_ligne = matrice.size();
    int nb_colonne = matrice[0].size();

    //std::cout << "Création grille " << nb_ligne << "x" << nb_colonne << std::endl;
    grille = new Grille(nb_ligne, nb_colonne);
    
    //std::cout << "Fill grille" << std::endl;
    grille->fill(0);

    //std::cout << "Chargement grille" << std::endl;
    grille->chargerGrille(matrice);
    
    //std::cout << "Lancement du jeu, mode=" << mode << std::endl;
    if (mode == 1){
        jouerConsole();
    } else if (mode == 2){
        jouerGraphique();
    } else{
        cout << "Entree non valide !" << endl;
    }
    
    //std::cout << "Fin initialisation" << std::endl;
}

void Gestion_jeu::jouerConsole(){
    Console console(*grille);
    for (int i = 0; i < nb_iterations; ++i) {
        compteur_iteration++;
        console.affichageCellules(); 

        grille->mettreAJourGrille();


        vector<vector<bool>> matrice_a_ecrire = grille->getMatriceEtat();
        
        // On l'envoie au gestionnaire de fichier
        gestionFichier->ecriture(matrice_a_ecrire);
    }
}

void Gestion_jeu::jouerGraphique(){
    Graphique graphique(*grille);
    for (int i = 0; i < nb_iterations; ++i) {
        compteur_iteration++;
        
        graphique.affichageCellules(); 

        grille->mettreAJourGrille();
    }
}
