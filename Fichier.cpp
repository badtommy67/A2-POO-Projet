#include "Fichier.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem> // pour la creation de dossiers

using namespace std;
namespace fs = std::filesystem;

Fichier::Fichier(string entree) : nom_entree(entree){}

void Fichier::remplirMatriceDepuisFichier(ifstream& fichier, vector<vector<bool>>& matrice) {
    int lignes = matrice.size();
    int colonnes = matrice[0].size();
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            char c;
            fichier >> c;
            matrice[i][j] = (c != '0'); // Si c'est pas '0', c'est vrai (1)
        }
    }
}

vector<vector<bool>> Fichier::lecture() {
    ifstream fichier(nom_entree.c_str());
    if (!fichier) {
        cout << "Erreur à l'ouverture !" << endl;
        return {}; 
    }

    int lignes, colonnes;
    fichier >> lignes >> colonnes;

    vector<vector<bool>> matrice(lignes, vector<bool>(colonnes));
    remplirMatriceDepuisFichier(fichier, matrice);
    
    fichier.close();
    return matrice;
}

fs::path Fichier::preparerDossierSortie() {
    fs::path chemin_entree(nom_entree);
    string nom_dossier = chemin_entree.stem().string() + "_out";
    fs::path dossier_cible = fs::path("Fichiers_sortie") / nom_dossier;

    if (!fs::exists(dossier_cible)) {
        fs::create_directories(dossier_cible);
    }
    return dossier_cible;
}

fs::path Fichier::trouverFichierDispo(const fs::path& dossier) {
    int i = 1;
    while (true) {
        string nom_fichier = "iteration" + to_string(i) + ".txt";
        fs::path chemin = dossier / nom_fichier;
        if (!fs::exists(chemin)) return chemin;
        i++;
    }
}

void Fichier::ecrireContenuMatrice(ofstream& flux, const vector<vector<bool>>& matrice) {
    for (const auto& ligne : matrice) {
        for (bool val : ligne) {
            if (val) flux << '1';
            else flux << '0';
            flux << "";
        }
        flux << endl;
    }
}

void Fichier::ecriture(const vector<vector<bool>>& matriceEtat) {
    fs::path dossier = preparerDossierSortie();
    fs::path chemin_final = trouverFichierDispo(dossier);
    ofstream flux(chemin_final);
    ecrireContenuMatrice(flux, matriceEtat);
    flux.close();
}

void Fichier::creationDossier() {
    fs::path chemin_source(nom_entree);
    string nom_dossier = chemin_source.stem().string() + "_out";
    fs::path chemin_complet = fs::path("Fichiers_sortie") / nom_dossier;

    try {
        if (fs::create_directories(chemin_complet))
            cout << "Dossier '" << chemin_complet << "' créé avec succès !" << endl;
    } catch (fs::filesystem_error& e) {
        cout << "Erreur création dossier : " << e.what() << endl;
    }
}

vector<vector<bool>> Fichier::genererMatriceAleatoire(int lignes, int colonnes) {
    vector<vector<bool>> matrice(lignes, vector<bool>(colonnes));
    srand(time(0));
    
    for (int x = 0; x < lignes; ++x) {
        for (int y = 0; y < colonnes; ++y) {
            matrice[x][y] = rand() % 2;
        }
    }
    return matrice;
}

void Fichier::sauvegarderConfigurationInitiale(const vector<vector<bool>>& matrice) {
    ofstream flux(nom_entree);
    // on écrit les dimensions en entête pour pouvoir etre reprises par la suite
    flux << matrice.size() << " " << matrice[0].size() << endl;
    
    ecrireContenuMatrice(flux, matrice);
    flux.close();
}

vector<vector<bool>> Fichier::aleatoire(int lignes, int colonnes) {
    vector<vector<bool>> matrice = genererMatriceAleatoire(lignes, colonnes);
    sauvegarderConfigurationInitiale(matrice);
    return matrice;
}
