#ifndef FICHIER_H
#define FICHIER_H

#include <string>
#include <vector>

class Fichier {
private:
    std::string nom_entree;
    std::string nom_sortie;

public:
    Fichier(std::string entree, std::string sortie);

    std::vector<std::vector<bool>> lecture();

    void ecriture(const std::vector<std::vector<bool>>& matriceEtat, int iteration);
    
    void creationDossier();
};

#endif