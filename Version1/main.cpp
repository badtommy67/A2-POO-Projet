#include "Gestion_jeu.h"
#include <iostream>

using namespace std;

int main() {
    // Instanciation du contrôleur de jeu
    Gestion_jeu jeu;
    
    // Lancement de l'initialisation (qui lancera ensuite la boucle de jeu)
    jeu.initialiser();

    return 0;
}