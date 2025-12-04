#include "Gestion_jeu.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


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
    cout << "Quel grille souhaitez-vous ? 1-Normal | 2-Torique" << endl;
    int mode_grille;
    cin >> mode_grille;

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
    if(mode_grille==1)
    grille = new Grille(nb_ligne, nb_colonne);
    else if(mode_grille==2)
    grille = new Grille_Torique(nb_ligne, nb_colonne);
    else {
        cout<<"Grille invalide"<<endl;
        return;
    }
    
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

        gestionFichier->ecriture(matrice_a_ecrire);
    }
}

void Gestion_jeu::jouerGraphique(){
    Graphique graphique(*grille);
    int ligne=grille->getLigne();
    int colonne=grille->getColonne();
    const int cellSize=graphique.getCellSize();
    sf::RenderWindow window(sf::VideoMode(colonne * cellSize, ligne * cellSize), "Jeu de la vie - Groupe 12 - CESI_", sf::Style::Default);
    

    int iteration=0;

    while (window.isOpen() && iteration<nb_iterations) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                sf::sleep(sf::milliseconds(100));
                window.close();
            }
        }

        graphique.affichageCellules(window);

        grille->mettreAJourGrille();
        iteration++;
        
        std::vector<std::vector<bool>> matrice_a_ecrire = grille->getMatriceEtat();


        gestionFichier->ecriture(matrice_a_ecrire);

        sf::sleep(sf::milliseconds(100));
    }
    window.close();
}