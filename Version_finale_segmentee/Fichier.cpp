#include "Fichier.h"
#include <fstream> // pour ecrire dans les fichiers
#include <iostream>
#include <vector> // pour gerer des vecteurs (tableaux dynamiques)
#include <filesystem> // pour la creation de dossiers - chemins vers des fichiers/dossiers

using namespace std;
namespace fs = std::filesystem;

Fichier::Fichier(string entree) : nom_entree(entree){}

void Fichier::remplirMatriceDepuisFichier(ifstream& fichier, vector<vector<bool>>& matrice) { //elle prend référence vers le fichier ouvert et une référence vers la matrice à remplir
    int lignes = matrice.size(); // le nb de lignes se caracterise par le nombre de sous-tableaux 
    int colonnes = matrice[0].size(); // le nb de colonnes se caracterise par le nombre d'elements par sous-tableaux
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) { // pn parcours notre vecteur de vecteur
            char c;
            fichier >> c; // on lit le prochain caractere
            matrice[i][j] = (c != '0'); // Si c'est pas '0', c'est vrai (1) 
        }
    }
}

vector<vector<bool>> Fichier::lecture() {
    ifstream fichier(nom_entree.c_str()); // creer le flux de lecture et tente d'ouvrir le fichier. conversion en chaine avec c_str(), normalement plus utile a l'heure actuelle, mais par securité, en fonction du compilateur, cela reste utile
    if (!fichier) { // verification de l'ouverture du fichier
        cout << "Erreur à l'ouverture !" << endl;
        return {}; 
    }

    int lignes, colonnes;
    fichier >> lignes >> colonnes; // dans notre fichier on a sur la premiere ligne, deux nombre, ligne puis colonne. on va attribuer ces valeurs aux bonnes variables

    vector<vector<bool>> matrice(lignes, vector<bool>(colonnes)); // creer la matrice de 2 dimensions avec ces valeurs
    remplirMatriceDepuisFichier(fichier, matrice); // on lit le fichier et on rempli notre matrice avec
    
    fichier.close();
    return matrice;
}

fs::path Fichier::preparerDossierSortie() { // cette méthode prépare le dossier où les fichiers seront sauvegardés
    fs::path chemin_entree(nom_entree); // transforme le nom du chemin donné en chaine de caractere en objet path (chemin)
    string nom_dossier = chemin_entree.stem().string() + "_out"; // on creer le nom du dossier ou l'on aura nos fichiers. stem() permet de recuperer le nom du fichier sans extension
    fs::path dossier_cible = fs::path("Fichiers_sortie") / nom_dossier; // on construit le chemin entier

    if (!fs::exists(dossier_cible)) { // on verifie que le dossier existe, sinon on le creer
        fs::create_directories(dossier_cible);
    }
    return dossier_cible;
}

fs::path Fichier::trouverFichierDispo(const fs::path& dossier) { // cette fonction cherche le prochain fichier disponible
    int i = 1; // on commence notre iteration a 1
    while (true) { // on va avoir une boucle infinie qui cherche le prochain nom disponible
        string nom_fichier = "iteration" + to_string(i) + ".txt"; // on construit le nom du fichier avec iterationX.txt avec X un entier
        fs::path chemin = dossier / nom_fichier;
        if (!fs::exists(chemin)) return chemin; // si le fichier n'existe pas, parfait, on va utiliser celui-ci. sinon, on continue a chercher
        i++;
    }
}

void Fichier::ecrireContenuMatrice(ofstream& flux, const vector<vector<bool>>& matrice) {
    for (const auto& ligne : matrice) { // boucle de boucle qui parcourt chaque ligne de la matrice pour chaque valeur booleenne de la ligne
        for (bool val : ligne) {
            if (val) flux << '1'; // si le booleen est true, on ecrit 1
            else flux << '0'; // et 0 sinon
            flux << ""; // on ne met pas d'espace entre les booleens
        }
        flux << endl; // on revient a la ligne apres chaque ligne parcourue
    }
}

void Fichier::ecriture(const vector<vector<bool>>& matriceEtat) {
    fs::path dossier = preparerDossierSortie(); // prepare le dossier pour ecrire nos fichiers de sortie
    fs::path chemin_final = trouverFichierDispo(dossier); // on cherche le prochain fichier.txt disponible
    ofstream flux(chemin_final); // on ouvre le fichier en ecriture
    ecrireContenuMatrice(flux, matriceEtat); // on ecrire notre matrice dans le fichier
    flux.close(); // on ferme le fichier
}

void Fichier::creationDossier() {
    fs::path chemin_source(nom_entree); // meme logique que plus haut
    string nom_dossier = chemin_source.stem().string() + "_out";
    fs::path chemin_complet = fs::path("Fichiers_sortie") / nom_dossier;

    try { // on tente de creer le dossier, si reussi, message de succes, et message d'erreur sinon
        if (fs::create_directories(chemin_complet))
            cout << "Dossier '" << chemin_complet << "' créé avec succès !" << endl;
    } catch (fs::filesystem_error& e) {
        cout << "Erreur création dossier : " << e.what() << endl; // e.what() affiche la cause de l'echec.
    }
}

vector<vector<bool>> Fichier::genererMatriceAleatoire(int lignes, int colonnes) {
    vector<vector<bool>> matrice(lignes, vector<bool>(colonnes)); // on creer une matrice vide aux dimensions voulues
    srand(time(0)); // initialise le generateur de nombre aleatoire avec l'heure actuelle pour avoir des resultats differents a chaque iteration
    
    for (int x = 0; x < lignes; ++x) {
        for (int y = 0; y < colonnes; ++y) {
            matrice[x][y] = rand() % 2; // on parcours toutes les lignes et on genere soit un 1 soit un 0
        }
    }
    return matrice;
}

void Fichier::sauvegarderConfigurationInitiale(const vector<vector<bool>>& matrice) {
    ofstream flux(nom_entree); // on ouvre le fichier en mode ecriture et en ecrasant le contenu precedent. car on a un nouveau fichier aleatoire
    // on écrit les dimensions en entête pour pouvoir etre reprises par la suite
    flux << matrice.size() << " " << matrice[0].size() << endl;
    
    ecrireContenuMatrice(flux, matrice);  // on ecrit le contenu de notre matrice aleatoire dans le fichier
    flux.close();
}

vector<vector<bool>> Fichier::aleatoire(int lignes, int colonnes) {
    vector<vector<bool>> matrice = genererMatriceAleatoire(lignes, colonnes); // generation de la matrice
    sauvegarderConfigurationInitiale(matrice); // sauvegarde dans un fichier
    return matrice; // retourner la matrice pour pouvoir jouer au jeu de la vie
}