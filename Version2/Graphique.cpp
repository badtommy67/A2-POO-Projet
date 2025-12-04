#include "Graphique.h"

using namespace sf;

Graphique::Graphique(const IGrille& g) : grille(g), fenetre(nullptr) {
    tailleCellule = 20; // taille de 20 px pour chaque case
}

Graphique::~Graphique() {
    if (fenetre) {
        delete fenetre;
    }
}

void Graphique::ouvrirFenetre() {
    // calcul automatique de la taille de la fenêtre selon la taille de la grille
    int largeurFenetre = grille.getColonne() * tailleCellule;
    int hauteurFenetre = grille.getLigne() * tailleCellule;

    // création de la fenêtre
    fenetre = new RenderWindow(VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie - Groupe 12 - CESI");
    
    // Limite à 60 images/sec pour ne pas surchauffer le processeur
    //fenetre->setFramerateLimit(60);
}

bool Graphique::estOuverte() const {
    return (fenetre != nullptr && fenetre->isOpen());
}

void Graphique::traiterEvenements() {
    if (!fenetre) return;
    
    // gestionnaire d'événements (pour pouvoir fermer la fenêtre avec la croix)
    Event event;
    while (fenetre->pollEvent(event)) {
        if (event.type == Event::Closed)
            fenetre->close();
    }
}

void Graphique::affichageCellules() {
    if (!fenetre || !fenetre->isOpen()) return;

    // 1. On gère les clics (fermeture)
    traiterEvenements();

    // 2. On efface tout en Blanc (comme le fond de votre image)
    fenetre->clear(Color::White);

    int nb_lignes = grille.getLigne();
    int nb_colonnes = grille.getColonne();

    // 3. Préparation du rectangle (Optimisation : on crée un seul objet qu'on déplace)
    RectangleShape cell(Vector2f(tailleCellule, tailleCellule));
    
    // Style du quadrillage (Bordure grise)
    cell.setOutlineThickness(-1.0f); // -1 pour que la bordure soit vers l'intérieur
    cell.setOutlineColor(Color(100, 100, 100)); // Gris foncé pour la grille

    // Couleur personnalisée "Marron" pour correspondre à votre image
    Color couleurVivante(101, 67, 33); // Un marron foncé (Dark Brown)

    // 4. Boucle de dessin
    for (int i = 0; i < nb_lignes; ++i) {
        for (int j = 0; j < nb_colonnes; ++j) {
            
            // Positionnement : x = colonne * taille, y = ligne * taille
            cell.setPosition(j * tailleCellule, i * tailleCellule);

            // Choix de la couleur selon l'état
            if (grille.getCellule(i, j).estVivante()) {
                cell.setFillColor(couleurVivante); // Marron
            } else {
                cell.setFillColor(Color::White);   // Blanc
            }

            // Dessin
            fenetre->draw(cell);
        }
    }

    // 5. Affichage final à l'écran
    fenetre->display();
}