#ifndef FICHIER_H
#define FICHIER_H

#include <string>
#include <vector>
#include <filesystem> // pour la creation de dossiers

class Fichier {
    std::string nom_entree;

public:
    Fichier(std::string entree);
    std::vector<std::vector<bool>> lecture();
    void ecriture(const std::vector<std::vector<bool>>& matriceEtat);
    void creationDossier();
    std::vector<std::vector<bool>> aleatoire(int lignes, int colonnes);

private:
    // ces méthodes sont privees car elles ne doivent etres accessibles qu'aux méthodes et objet de cette classe. aucune autre classe ne doit par exemple creer un dossier
    void remplirMatriceDepuisFichier(std::ifstream& fichier, std::vector<std::vector<bool>>& matrice);
    std::filesystem::path preparerDossierSortie();
    std::filesystem::path trouverFichierDispo(const std::filesystem::path& dossier);
    void ecrireContenuMatrice(std::ofstream& flux, const std::vector<std::vector<bool>>& matrice);
    std::vector<std::vector<bool>> genererMatriceAleatoire(int lignes, int colonnes);
    void sauvegarderConfigurationInitiale(const std::vector<std::vector<bool>>& matrice);
};

#endif