#ifndef GESTION_JEU_H
#define GESTION_JEU_H

#include "Grille.h"
#include "Fichier.h"
#include "Console.h"
#include "Graphique.h"

class Gestion_jeu {
private:
    int nb_iterations;
    int compteur_iteration;
    Grille grille;
    Fichier gestionFichier;

public:
    Gestion_jeu(std::string fichierEntree);
    
    void jouerConsole();
    void jouerGraphique();
};

#endif