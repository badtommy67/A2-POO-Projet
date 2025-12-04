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

    bool demanderTypeSource();
    void configurerSource(bool estFichier);
    void demanderParametresJeu(int& modeVisu, int& modeGrille);
    std::vector<std::vector<bool>> recupererMatrice(bool estFichier);
    void instancierGrilleSelonMode(int modeGrille, const std::vector<std::vector<bool>>& matrice);
    
    sf::RenderWindow* initialiserFenetre(int cellSize);
    void gererEvenements(sf::RenderWindow& window);
    void etapeGraphique(sf::RenderWindow& window, Graphique& graphique);
    void sauvegarderEtape();

public:
    Gestion_jeu(std::string fichierEntree, int nb_iterations, int compteur_iteration);
    Gestion_jeu();
    ~Gestion_jeu();
    
    void initialiser();
    void jouerConsole();
    void jouerGraphique();
};

#endif
