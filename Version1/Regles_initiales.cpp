#include "Regles_initiales.h"
#include "Est_vivant.h"
#include "Est_mort.h"

Etat_cellule* Regles_initiales::calculerProchainEtat(bool estVivant, int nb_voisins) {
    if (estVivant) {
        // Une cellule vivante reste vivante si 2 ou 3 voisins
        if (nb_voisins == 2 || nb_voisins == 3) {
            return new Est_vivant();
        } else {
            return new Est_mort();
        }
    } else {
        // Une cellule morte naît si exactement 3 voisins
        if (nb_voisins == 3) {
            return new Est_vivant();
        } else {
            return new Est_mort();
        }
    }
}