#include "Fichier.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem> // pour la creation de dossiers

using namespace std;
namespace fs = std::filesystem;

Fichier::Fichier(string entree) : nom_entree(entree){}

vector<vector<bool>> Fichier::lecture() {
    ifstream fichier(nom_entree.c_str());
    if (!fichier) {
        cout << "Erreur à l'ouverture !" << endl;
        return {}; // renvoie une matrice vide en cas d'erreur
    }

    int colonne;
    int ligne;
    fichier >> ligne >> colonne; // on met la ligne dans ligne et la colonne dans colonne

    vector<vector<bool>> matrice(ligne, vector<bool>(colonne)); // creation de la matrice

    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            char c;
            fichier >> c; // on recupere un caractere de la lecture, mais on cherche un booléen
            bool val;
            if (c=='0'){ // donc si le caractère est un 0 on défini le boléen à 0
                val=0;
            }else{
                val=1;
            }
            matrice[i][j] = val; // on met la valeur booléenne dans la matrice
        }
    }
    fichier.close();
    return matrice;
}

void Fichier::ecriture(const vector<vector<bool>>& matriceEtat){
    fs::path chemin_entree(nom_entree);
    string nom_dossier = chemin_entree.stem().string() + "_out";
    fs::path dossier_cible = fs::path("Fichiers_sortie") / nom_dossier;

    if (!fs::exists(dossier_cible)) { // par acquis de conscience, on créer le dossier s'il n'existe pas encore.
        fs::create_directories(dossier_cible);
    }
    int i = 1; // ce compteur nous permet de savoir quel est le prochain numero de fichier disponible
    fs::path chemin_final;

    bool trouve=false;

    while (trouve==false) {
        string nom_fichier = "iteration" + to_string(i) + ".txt";
        chemin_final = dossier_cible / nom_fichier;

        // si le fichier existe, on teste le suivant
        if (fs::exists(chemin_final)) {
            i++;
        } else {
            // si le fichier n'existe pas, parfait ! on le prend !
            trouve=true;
        }
    }
    ofstream flux(chemin_final);
    // on va ecrire la matrice dans le fichier
    for (const auto& ligne : matriceEtat) {
        for (int i = 0; i < ligne.size(); i++) {
            bool val = ligne[i]; // On récupère la valeur
            if (val == true) {
                flux << '1';
            } else {
                flux << '0';
            }
        flux << ""; // On ajoute l'espace
        }
        flux << endl;
    }
    flux.close();
}

void Fichier::creationDossier(){
    fs::path chemin_source(nom_entree);
    string nom_dossier = chemin_source.stem().string();

    nom_dossier += "_out";  // ajouter "_out"
    fs::path chemin_complet = fs::path("Fichiers_sortie") / nom_dossier; // ici on va creer le chemin complet

    try {
        if (fs::create_directories(chemin_complet)) {
            cout << "Dossier '" << chemin_complet << "' créé avec succès !" << endl;
        } else {
            cout << "Le dossier '" << chemin_complet << "' existe déjà." << endl;
        }
    }catch (fs::filesystem_error& e) {
        cout << "Erreur lors de la création du dossier : " << e.what() << endl;
    }
}