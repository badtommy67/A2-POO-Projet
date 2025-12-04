#include "Test_unitaire.h"
#include "Gestion_jeu.h"
#include "Fichier.h"
#include <fstream>
#include <iostream>

using namespace std;

// CETTE CLASSE ACCEDE AUX METHODES PRIVEES DE GESTION_JEU GRACE A UN LIEU D'AMITIE

Test_unitaire::Test_unitaire() {}

Test_unitaire::~Test_unitaire() {}

void Test_unitaire::lancerTest() {
    cout << "--- Démarrage du Test Unitaire ---" << endl;

    string nom_entree = "Fichiers_source/test_unitaire.txt"; // pour le test unitaire, on prend un fichier arbitrairement choisi, un clignotant
    int nb_iterations = 10; // nous allons faire un nombre arbitraire d'iterations, 10

    Gestion_jeu* jeuTest = new Gestion_jeu(nom_entree, nb_iterations, 0);

    jeuTest->gestionFichier = new Fichier(nom_entree);
    jeuTest->gestionFichier->creationDossier(); // on creer le dossier de sortie

    vector<vector<bool>> matrice = jeuTest->gestionFichier->lecture();
    jeuTest->instancierGrilleSelonMode(0, matrice);

    jeuTest->jouerConsole(); // tout se passera dans la console, c'est une procedure de test

    verifier_correction(); // cette methode va verifier si l'iteration X correspond a celle qu'elle devrait etre (calculee au prelable manuellement)

    delete jeuTest;
}

void Test_unitaire::verifier_correction() {
    string chemin1 = "test_unitaire_cligno.txt"; // c'est le fichier comprenant la matrice que nous sommes censés retrouver
    string chemin2 = "Fichiers_sortie/test_unitaire_out/iteration9.txt"; // c'est le fichier que nous allons generer, a la 9eme iteration. il doit normalement etre identique a l'autre fichier
    
    vector<vector<char>> v1; // on va creer 2 vecteurs qui vont nous permettre de stocker chacun des fichiers pour les comparer
    vector<vector<char>> v2;
    string ligne;

    ifstream f1(chemin1);
    if (!f1.is_open()) {
        cout << "Erreur : Impossible d'ouvrir le fichier de référence " << chemin1 << endl;
        return;
    }
    while (getline(f1, ligne)) { // on rempli le premier vecteur
        vector<char> row;
        for (char c : ligne) {
            if (c == '0' || c == '1')
                row.push_back(c);
        }
        if (!row.empty()) v1.push_back(row);
    }
    f1.close();

    // ---- Lecture fichier sortie du jeu ----
    ifstream f2(chemin2);
    if (!f2.is_open()) {
        cout << "Erreur : Impossible d'ouvrir le fichier de sortie " << chemin2 << endl;
        return;
    }

    while (getline(f2, ligne)) { // on rempli le second vecteur
        vector<char> row;
        for (char c : ligne) {
            if (c == '0' || c == '1')
                row.push_back(c);
        }
        if (!row.empty()) v2.push_back(row);
    }
    f2.close();
    
    bool identique = true;
    for(size_t i = 0; i < v1.size(); ++i) { // on va les comparer booleen par booleen. si l'un differe, c'est un ECHEC !
        if(v1[i] != v2[i]) {
            identique = false;
            break;
        }
    }

    if (identique) {
        cout << "SUCCES : Les fichiers sont identiques ! Le test est validé !" << endl; // FELICITATIONS ! VOTRE JEU DE LA VIE FONCTIONNE !
    } else {
        cout << "ECHEC : Le contenu des fichiers diffère." << endl;
    }
}
