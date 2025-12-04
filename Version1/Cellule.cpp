#include "Cellule.h"
#include "Est_mort.h"   // <--- Indispensable pour le new
#include "Est_vivant.h" // Indispensable si utilisé ailleurs

// CONSTRUCTEUR
Cellule::Cellule() {
    // --- C'EST CETTE LIGNE QUI VOUS MANQUE ---
    this->etatActuel = new Est_mort(); 
    // Ou a minima : this->etatActuel = nullptr;
}

// DESTRUCTEUR
Cellule::~Cellule() {
    if (this->etatActuel != nullptr) {
        delete this->etatActuel;
    }
}

// SETTER
void Cellule::setEtat(Etat_cellule* nouvelEtat) {
    // Si etatActuel n'est pas initialisé (nullptr) dans le constructeur,
    // cette ligne fait planter le programme !
    if (this->etatActuel != nullptr) {
        delete this->etatActuel;
    }
    this->etatActuel = nouvelEtat;
}

// GETTER
bool Cellule::estVivante() const {
    // Sécurité supplémentaire
    if (this->etatActuel == nullptr) return false; 
    return this->etatActuel->estVivante();
}