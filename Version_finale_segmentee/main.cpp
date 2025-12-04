#include <iostream>
#include <vector>
#include "Fichier.h"
#include "Gestion_jeu.h"

using namespace std;

int main() {
    Gestion_jeu gj;

    gj.initialiser();

    return 0;
}

// g++ *.cpp -o jeu -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs