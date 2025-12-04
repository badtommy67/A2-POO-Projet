#include "Gestion_jeu.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;

Gestion_jeu::Gestion_jeu(string nom_entree, int nb_iterations, int compteur_iteration) : nom_entree(nom_entree), nb_iterations(nb_iterations), compteur_iteration(compteur_iteration), grille(nullptr), gestionFichier(nullptr) {}

Gestion_jeu::Gestion_jeu() : grille(nullptr), gestionFichier(nullptr), nb_iterations(0), compteur_iteration(0) {}

Gestion_jeu::~Gestion_jeu() {
    delete grille;
    delete gestionFichier;
}

void Gestion_jeu::initialiser() {
    cout << "Voulez-vous faire un test unitaire ? 1 : Oui - 0 : Non" << endl;
    bool test_unitaire;
    cin >> test_unitaire;
    if (test_unitaire){
        test_unitaire_fonction();
    }else{
        bool estFichier = demanderTypeSource();
        configurerSource(estFichier);

        int modeVisu, modeGrille;
        demanderParametresJeu(modeVisu, modeGrille);

        vector<vector<bool>> matrice = recupererMatrice(estFichier);
        if (matrice.empty() || matrice[0].empty()) {
            cout << "Erreur: Grille vide." << endl; return;
        }

        instancierGrilleSelonMode(modeGrille, matrice);

        if (modeVisu == 1) jouerConsole();
        else if (modeVisu == 2) jouerGraphique();
        else cout << "Entree non valide !" << endl;
    }
}

bool Gestion_jeu::demanderTypeSource() {
    bool reponse;
    cout << "Voulez-vous utiliser un fichier source ? 0-Non 1-Oui" << endl;
    cin >> reponse;
    return reponse;
}

void Gestion_jeu::configurerSource(bool estFichier) {
    if (estFichier) {
        cout << "Quel est le fichier à prendre en entrée ?" << endl;
        cin >> nom_entree;
        gestionFichier = new Fichier(nom_entree);
    } else {
        nom_entree = "Fichiers_source/aleatoire.txt";
        gestionFichier = new Fichier(nom_entree);
    }
}

void Gestion_jeu::demanderParametresJeu(int& modeVisu, int& modeGrille) {
    cout << "Combien d'itérations souhaitez-vous ?" << endl;
    cin >> nb_iterations;
    
    cout << "Quel mode souhaitez-vous ? 1-Console | 2-Graphique" << endl;
    cin >> modeVisu;
    
    cout << "Quelle grille souhaitez-vous ? 1-Normale | 2-Torique" << endl;
    cin >> modeGrille;
}

vector<vector<bool>> Gestion_jeu::recupererMatrice(bool estFichier) {
    gestionFichier->creationDossier();
    
    if (!estFichier) {
        int ligne, colonne;
        cout << "Combien de lignes ?" << endl; cin >> ligne;
        cout << "Nombre de colonnes ?" << endl; cin >> colonne;
        gestionFichier->aleatoire(ligne, colonne);
    }
    return gestionFichier->lecture();
}

void Gestion_jeu::instancierGrilleSelonMode(int modeGrille, const vector<vector<bool>>& matrice) {
    int nb_ligne = matrice.size();
    int nb_colonne = matrice[0].size();

    if (modeGrille == 2) 
        grille = new Grille_Torique(nb_ligne, nb_colonne);
    else 
        grille = new Grille(nb_ligne, nb_colonne); // Par défaut ou mode 1

    grille->chargerGrille(matrice);
}

void Gestion_jeu::jouerConsole() {
    Console console(*grille);
    for (int i = 0; i < nb_iterations; ++i) {
        compteur_iteration++;
        
        console.affichageCellules();
        grille->mettreAJourGrille();
        sauvegarderEtape();
    }
}

void Gestion_jeu::sauvegarderEtape() {
    vector<vector<bool>> matrice_a_ecrire = grille->getMatriceEtat();
    gestionFichier->ecriture(matrice_a_ecrire);
}

sf::RenderWindow* Gestion_jeu::initialiserFenetre(int cellSize) {
    int ligne = grille->getLigne();
    int colonne = grille->getColonne();
    
    if (cellSize <= 0 || colonne <= 0 || ligne <= 0) {
        cout << "Erreur dimensions invalides." << endl;
        return nullptr;
    }
    return new sf::RenderWindow(sf::VideoMode(colonne * cellSize, ligne * cellSize), "Jeu de la vie - Groupe 12 - CESI_");
}

void Gestion_jeu::gererEvenements(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Gestion_jeu::etapeGraphique(sf::RenderWindow& window, Graphique& graphique) {
    graphique.affichageCellules(window);
    grille->mettreAJourGrille();
    sauvegarderEtape();
    sf::sleep(sf::milliseconds(100));
}

void Gestion_jeu::jouerGraphique() {
    Graphique graphique(*grille);
    sf::RenderWindow* windowPtr = initialiserFenetre(graphique.getCellSize());
    
    if (!windowPtr) return; // Gestion erreur dimensions

    int iteration = 0;
    while (windowPtr->isOpen() && iteration < nb_iterations) {
        gererEvenements(*windowPtr);
        etapeGraphique(*windowPtr, graphique);
        iteration++;
    }
    
    windowPtr->close();
    delete windowPtr;
}

void Gestion_jeu::test_unitaire_fonction(){
    nom_entree="Fichiers_source/test_unitaire.txt";
    gestionFichier = new Fichier(nom_entree);
    nb_iterations=10;
    gestionFichier->creationDossier();
    vector<vector<bool>> matrice =gestionFichier->lecture();
    instancierGrilleSelonMode(0, matrice);
    jouerConsole();
    verifier_correction();
}

void Gestion_jeu::verifier_correction(){
    string chemin1 = "test_unitaire_cligno.txt";
    string chemin2 = "Fichiers_sortie/test_unitaire_out/iteration9.txt";
    vector<vector<char>> v1;
    vector<vector<char>> v2;
    string ligne;
    ifstream f1(chemin1);
    while (getline(f1, ligne)) {
        vector<char> row;

        for (char c : ligne) {
            if (c == '0' || c == '1')
                row.push_back(c);
        }

        if (!row.empty())
            v1.push_back(row);
    }
    f1.close();

    // ---- Lecture fichier 2 ----
    ifstream f2(chemin2);
    if (!f2.is_open()) {
        cout << "Impossible d'ouvrir " << chemin2 << endl;
        return;
    }

    while (getline(f2, ligne)) {
        vector<char> row;

        for (char c : ligne) {
            if (c == '0' || c == '1')
                row.push_back(c);
        }

        if (!row.empty())
            v2.push_back(row);
    }
    f2.close();

    if (v1.size() != v2.size()) {
        cout << "Les fichiers sont différents (nombre de lignes différent)." << endl;
        return;
    }
    cout << "Les fichiers sont identiques !" << endl;
}
