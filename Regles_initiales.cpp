#include "Regles_initiales.h"

Cellule* Regles_initiales::calculerProchainEtat(Cellule& cel, int nb_voisins){
    bool vivante = cel.getEtat()->estVivante();

    // on va creer une copie identique de la cellule actuelle. si elle est vivante, la copie sera aussi vivante. et inversement si elle est morte
    Etat_cellule* etatInitial = vivante 
        ? (Etat_cellule*) new Est_vivant()
        : (Etat_cellule*) new Est_mort();

    Cellule* nouvelle = new Cellule(etatInitial);

    if (vivante) {
        if (nb_voisins < 2 || nb_voisins > 3) // condition initiales de mort d'une cellule
            nouvelle->changementEtat();  // meurt
    } else {
        if (nb_voisins == 3) // condition initiales de naissance d'une cellule
            nouvelle->changementEtat();  // naît
    }

    return nouvelle;
}