#ifndef GESTION_JEU_H
#define GESTION_JEU_H

#include "Grille.h"
#include "Grille_Torique.h"
#include "Fichier.h"
#include "Console.h"
#include "Graphique.h"

class Gestion_jeu {
private:
    int nb_iterations;
    int compteur_iteration;
    std::string nom_entree;
    IGrille* grille;
    Fichier* gestionFichier;

public:
    Gestion_jeu(std::string fichierEntree, int nb_iterations, int compteur_iteration);
    Gestion_jeu();
    ~Gestion_jeu();
    
    void initialiser();
    void jouerConsole();
    void jouerGraphique();
};

#endif