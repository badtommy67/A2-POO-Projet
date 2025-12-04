#include "Gestion_jeu.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp> // bibliotheque pour affichage graphique et visuel
#include <fstream>
#include "Test_unitaire.h" // utilisation de cette classe pour le test unitaire

using namespace std;

Gestion_jeu::Gestion_jeu(string nom_entree, int nb_iterations, int compteur_iteration) : nom_entree(nom_entree), nb_iterations(nb_iterations), compteur_iteration(compteur_iteration), grille(nullptr), gestionFichier(nullptr) {}

Gestion_jeu::Gestion_jeu() : grille(nullptr), gestionFichier(nullptr), nb_iterations(0), compteur_iteration(0) {}

Gestion_jeu::~Gestion_jeu() { // evite les fuites de memoire
    delete grille;
    delete gestionFichier;
}

void Gestion_jeu::initialiser() {
    cout << "Voulez-vous faire un test unitaire ? 1 : Oui - 0 : Non" << endl; // on demande l'utilisateur s'il veut faire un test unitaire ou non (faire avec sa grille)
    bool faire_test;
    cin >> faire_test;

    if (faire_test){
        Test_unitaire test;
        test.lancerTest(); // on va faire le test unitaire si l'utilisateur a entre 1
    } else {
        bool estFichier = demanderTypeSource(); // sinon on va effectuer le programme normalement. on demande donc le type de la source (soit via un fichier de l'utilisateur soit via une grille aleatoire)
        configurerSource(estFichier); // si l'utilisateur veut renseigner son fichier, on lui demande ou il est et sinon, on genere une grille aleatoire

        int modeVisu, modeGrille;
        demanderParametresJeu(modeVisu, modeGrille); // ici on va chercher a avoir le nombre d'iterations, un affichage console ou graphique et l'utilisation d'une grille normale ou d'une grille torique

        vector<vector<bool>> matrice = recupererMatrice(estFichier); // on recupere donc la matrice selon ce que l'utilisateur a indiqué
        if (matrice.empty() || matrice[0].empty()) {
            cout << "Erreur: Grille vide." << endl; return;
        }

        instancierGrilleSelonMode(modeGrille, matrice); // ici on va definir notre grille en etant soit normale soit torique

        if (modeVisu == 1) jouerConsole(); // et ici l'utilisateur a voulu un affichage console
        else if (modeVisu == 2) jouerGraphique(); // et ici l'utilisateur a voulu un affichage graphique
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
    } else {
        nom_entree = "Fichiers_source/aleatoire.txt"; // chemin par defaut du fichier contenant la grille aleatoire
    }
    gestionFichier = new Fichier(nom_entree);
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
    
    if (!estFichier) { // on recupere donc le nombre de lignes et de colonnes que l'utilisateur souhaite avoir pour sa grille aleatoire
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
        grille = new Grille_Torique(nb_ligne, nb_colonne); // l'utilisateur a voulu une grille torique
    else 
        grille = new Grille(nb_ligne, nb_colonne); // par defaut on aura une grille normale, de base

    grille->chargerGrille(matrice); // on va donc charger la grille
}

void Gestion_jeu::jouerConsole() { // ici on gere l'affichage console
    Console console(*grille);
    for (int i = 0; i < nb_iterations; ++i) {
        compteur_iteration++;
        console.affichageCellules(); // on va afficher les cellules
        grille->mettreAJourGrille(); // calculer la prochaine iteration
        sauvegarderEtape(); // ecrire la nouvelle matrice dans le fichier
    }
}

void Gestion_jeu::sauvegarderEtape() {
    vector<vector<bool>> matrice_a_ecrire = grille->getMatriceEtat(); // on recupere la nouvelle grille et on va l'ecrire dans un fichier
    gestionFichier->ecriture(matrice_a_ecrire);
}

sf::RenderWindow* Gestion_jeu::initialiserFenetre(int cellSize) {
    int ligne = grille->getLigne();
    int colonne = grille->getColonne();
    
    if (cellSize <= 0 || colonne <= 0 || ligne <= 0) {
        cout << "Erreur dimensions invalides." << endl;
        return nullptr;
    }
    return new sf::RenderWindow(sf::VideoMode(colonne * cellSize, ligne * cellSize), "Jeu de la vie - Groupe 12 - CESI_"); // on va creer notre fenetre qui sera utile pour l'affichage graphique
}

void Gestion_jeu::gererEvenements(sf::RenderWindow& window) { // on gere les evenements de l'utilisateur comme fermer la fenetre quand on clique sur la croix
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Gestion_jeu::etapeGraphique(sf::RenderWindow& window, Graphique& graphique) {
    graphique.affichageCellules(window); // on dessine les cellules dans la fenetre
    grille->mettreAJourGrille(); // on met a jour la grille a l'iteration i+1
    sauvegarderEtape(); // on ecrit cette iteration dans un fichier texte
    sf::sleep(sf::milliseconds(100)); // on marque un temps de pause avant d'afficher la nouvelle iteration, cela permet de bien voir l'evolution de la grille au cours du temps
}

void Gestion_jeu::jouerGraphique() {
    Graphique graphique(*grille);
    sf::RenderWindow* windowPtr = initialiserFenetre(graphique.getCellSize()); // on initialise la fenetre
    
    if (!windowPtr) return; // Gestion erreur dimensions

    int iteration = 0;
    while (windowPtr->isOpen() && iteration < nb_iterations) { // tant que la fenetre est ouverte et qu'on a pas atteint le nombre maximal d'iterations, on continue le jeu
        gererEvenements(*windowPtr);
        etapeGraphique(*windowPtr, graphique);
        iteration++;
    }
    
    windowPtr->close(); // on fini par fermer la fenetre quand toutes les iterations ont ete faites ou que l'utilisateur a cliqué sur la croix
    delete windowPtr; // et liberer la memoire
}