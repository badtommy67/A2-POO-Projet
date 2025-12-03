#ifndef FICHIER_H
#define FICHIER_H

#include <string>
#include <vector>

class Fichier {
private:
    std::string nom_entree;

public:
    Fichier()=default;
    Fichier(std::string entree);

    std::vector<std::vector<bool>> lecture();

    void ecriture(const std::vector<std::vector<bool>>& matriceEtat);
    
    void creationDossier();

    std::vector<std::vector<bool>> aleatoire(int lignes, int colonnes);
};

#endif