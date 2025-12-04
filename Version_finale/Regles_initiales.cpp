#include "Regles_initiales.h"

Cellule* Regles_initiales::calculerProchainEtat(Cellule& cel, int nb_voisins){
    bool vivante = cel.getEtat()->estVivante();

    // Duplique l'état correctement
    Etat_cellule* etatInitial = vivante 
        ? (Etat_cellule*) new Est_vivant()
        : (Etat_cellule*) new Est_mort();

    Cellule* nouvelle = new Cellule(etatInitial);

    if (vivante) {
        if (nb_voisins < 2 || nb_voisins > 3) // Condition initiales de mort d'une cellule
            nouvelle->changementEtat();  // meurt
    } else {
        if (nb_voisins == 3) // Condition initiales de naissance d'une cellule
            nouvelle->changementEtat();  // naît
    }

    return nouvelle;
}