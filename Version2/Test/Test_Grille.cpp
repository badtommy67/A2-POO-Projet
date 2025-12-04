#include <iostream>
#include <vector>
#include <cmath>
#include <cassert> // Utilisation de l'assertion standard

// --- Déclarations anticipées et Simples Mockings ---

// (Les dépendances Cellule, Etat, Regles_initiales doivent être incluses ici ou définies)
// Pour la simplicité, nous allons définir les classes Cellule et Etat.
// Note : Le constructeur de Grille est simulé à la fin.

class Etat {
public:
    virtual ~Etat() = default;
    virtual bool estVivante() const = 0;
};

class Est_vivant : public Etat {
public:
    bool estVivante() const override { return true; }
};

class Est_mort : public Etat {
public:
    bool estVivante() const override { return false; }
};

class Etat_cellule; // Alias pour l'ancienne version, si nécessaire
class Regles_du_jeu; // Forward declaration
class Gestion_jeu;   // Forward declaration

class Cellule {
private:
    Etat* etat;
public:
    // Constructeur par défaut (Initialisation à Mort, nécessaire pour std::vector)
    Cellule() : etat(new Est_mort()) {} 
    
    // Constructeur pour copie
    Cellule(const Cellule& autre) : etat(nullptr) {
        if (autre.etat->estVivante()) {
            etat = new Est_vivant();
        } else {
            etat = new Est_mort();
        }
    }

    // Opérateur d'affectation
    Cellule& operator=(const Cellule& autre) {
        if (this != &autre) {
            delete etat;
            if (autre.etat->estVivante()) {
                etat = new Est_vivant();
            } else {
                etat = new Est_mort();
            }
        }
        return *this;
    }
    
    ~Cellule() { delete etat; }
    
    void changementEtat() {
        Etat* ancienEtat = etat;
        if (etat->estVivante()) {
            etat = new Est_mort();
        } else {
            etat = new Est_vivant();
        }
        delete ancienEtat;
    }
    const Etat* getEtat() const { return etat; }
    
    // Méthode pour le test simple
    bool estVivante() const { return etat->estVivante(); }
};

// Simulation de Regles_du_jeu et Regles_initiales
class Regles_du_jeu {
public:
    virtual ~Regles_du_jeu() = default;
    virtual Cellule* calculerProchainEtat(Cellule& cel, int nb_voisins) = 0;
};

class Regles_initiales : public Regles_du_jeu {
public:
    // Implémentation corrigée (retourne un nouvel objet alloué dynamiquement)
    Cellule* calculerProchainEtat(Cellule& cel, int nb_voisins) override {
        bool estVivanteActuelle = cel.getEtat()->estVivante();
        bool devraitEtreVivante = estVivanteActuelle;

        if (estVivanteActuelle) {
            // Règle de MORT (Sous-population < 2, Surpopulation > 3)
            if (nb_voisins < 2 || nb_voisins > 3) {
                devraitEtreVivante = false;
            }
        } else {
            // Règle de NAISSANCE
            if (nb_voisins == 3) {
                devraitEtreVivante = true;
            }
        }

        Cellule* nouvelleCel = new Cellule(cel);
        
        if (devraitEtreVivante != estVivanteActuelle) {
            nouvelleCel->changementEtat();
        }
        
        return nouvelleCel;
    }
};

// --- Définition et Simulation de Grille (incluant les corrections de syntaxe) ---

class Grille {
private:
    std::vector<std::vector<Cellule>> cellules; 
    int ligne;
    int colonne;
    Regles_du_jeu* regles;
    Gestion_jeu* jeu; // Déclaré mais non utilisé/initialisé ici

public:
    // Implémentation du constructeur pour le test
    Grille(int l, int L) : ligne(l), colonne(L), regles(new Regles_initiales()), jeu(nullptr) {
        // Redimensionnement de la grille (colonne x ligne)
        cellules.resize(colonne, std::vector<Cellule>(ligne));
    }
    ~Grille() { delete regles; }

    void chargerGrille(const std::vector<std::vector<bool>>& matrice) {
        // Redimensionnement de précaution
        if (cellules.size() != colonne || cellules[0].size() != ligne) {
            cellules.resize(colonne, std::vector<Cellule>(ligne));
        }
        
        for (int i = 0; i < colonne; ++i) {
            for (int j = 0; j < ligne; ++j) {
                if (matrice[i][j]) {
                    // Si la cellule est morte par défaut, un seul changementEtat() la rend vivante.
                    // Si la cellule est déjà vivante, on ne fait rien (ou on la tue puis la ressuscite, ce qui est inutile).
                    // On suppose que les cellules sont Mortes initialement, chargerGrille les rend Vivantes si nécessaire.
                    if (!cellules[i][j].getEtat()->estVivante()) {
                         cellules[i][j].changementEtat();
                    }
                } else {
                    // S'assurer qu'elle est morte si la matrice dit false
                    if (cellules[i][j].getEtat()->estVivante()) {
                        cellules[i][j].changementEtat();
                    }
                }
            }
        }
    }

    int compterVoisins(int x, int y) const {
        int nb_voisins = 0;

        // Limites sûres
        for (int i = std::max(0, x - 1); i <= std::min(colonne - 1, x + 1); i++) {
            for (int j = std::max(0, y - 1); j <= std::min(ligne - 1, y + 1); j++) {

                if (i == x && j == y) continue;

                if (cellules[i][j].getEtat()->estVivante())
                    nb_voisins++;
            }
        }
        return nb_voisins;
    }

    void mettreAJourGrille() {
        std::vector<std::vector<Cellule>> nouvelleGrille = cellules;

        for (int x = 0; x < colonne; x++) {
            for (int y = 0; y < ligne; y++) {

                int voisins = compterVoisins(x, y);
                Cellule* resultat = regles->calculerProchainEtat(cellules[x][y], voisins);
                nouvelleGrille[x][y] = *resultat;

                delete resultat;
            }
        }
        cellules = nouvelleGrille;
    }

    const Cellule& getCellule(int x, int y) const { return cellules[x][y]; }
    int getLigne() const { return ligne; }
    int getColonne() const { return colonne; }
};

// --- Fonctions de Test Simples ---

// Fonction d'aide pour afficher le résultat du test
void print_test_result(const std::string& test_name, bool passed) {
    std::cout << (passed ? "[PASS] ✅ " : "[FAIL] ❌ ") << test_name << std::endl;
    if (!passed) {
        std::cerr << "!!! Le test " << test_name << " a échoué." << std::endl;
        // Optionnel: utiliser assert pour arrêter le programme en cas d'échec critique
    }
}

void Test_CompterVoisins_Centre() {
    Grille grille3x3(3, 3);
    // Schéma : V V V
    //          V X V
    //          V V V
    std::vector<std::vector<bool>> matrice = {
        {true, true, true},
        {true, false, true},
        {true, true, true}
    };
    grille3x3.chargerGrille(matrice);
    
    int voisins = grille3x3.compterVoisins(1, 1);
    bool passed = (voisins == 8);
    print_test_result("CompterVoisins_Centre (8 voisins)", passed);
}

void Test_CompterVoisins_Coin() {
    Grille grille3x3(3, 3);
    // Schéma : X V .
    //          V V .
    //          . . .
    std::vector<std::vector<bool>> matrice = {
        {false, true, false},
        {true, true, false},
        {false, false, false}
    };
    grille3x3.chargerGrille(matrice);

    int voisins = grille3x3.compterVoisins(0, 0);
    bool passed = (voisins == 3);
    print_test_result("CompterVoisins_Coin (3 voisins)", passed);
}

void Test_MiseAJour_Stabilité() {
    // Test du motif 'Bloc' qui est stable (4 cellules vivantes, 3 voisins chacune)
    Grille grille4x4(4, 4);
    std::vector<std::vector<bool>> matrice = {
        {false, false, false, false},
        {false, true, true, false},
        {false, true, true, false},
        {false, false, false, false}
    };
    grille4x4.chargerGrille(matrice);
    
    // Assurez-vous que le centre (1, 1) a 3 voisins (pour la survie)
    assert(grille4x4.compterVoisins(1, 1) == 3); 

    grille4x4.mettreAJourGrille();

    // Vérifier que toutes les cellules restent vivantes
    bool passed = grille4x4.getCellule(1, 1).estVivante() &&
                  grille4x4.getCellule(1, 2).estVivante() &&
                  grille4x4.getCellule(2, 1).estVivante() &&
                  grille4x4.getCellule(2, 2).estVivante();
                  
    // Vérifier qu'aucune cellule n'est née autour
    passed = passed && !grille4x4.getCellule(0, 1).estVivante() &&
                      !grille4x4.getCellule(3, 3).estVivante();

    print_test_result("MiseAJour_Stabilité (Bloc stable)", passed);
}

void Test_MiseAJour_Oscillation() {
    // Test du motif 'Clignotant' (Oscillation d'une ligne à une colonne)
    Grille grille3x3(3, 3);
    // État 1: Ligne
    // . V .
    // . V .
    // . V .
    std::vector<std::vector<bool>> matrice_ligne = {
        {false, true, false},
        {false, true, false},
        {false, true, false}
    };
    grille3x3.chargerGrille(matrice_ligne);
    
    // Mise à jour 1: La ligne devrait devenir une colonne
    grille3x3.mettreAJourGrille();

    // État attendu 2: Colonne
    // . . .
    // V V V
    // . . .
    bool est_colonne = grille3x3.getCellule(1, 0).estVivante() &&
                       grille3x3.getCellule(1, 1).estVivante() &&
                       grille3x3.getCellule(1, 2).estVivante() &&
                       !grille3x3.getCellule(0, 1).estVivante(); // s'assurer que l'ancienne V est Morte

    // Mise à jour 2: La colonne devrait redevenir une ligne
    grille3x3.mettreAJourGrille();

    // État attendu 3: Ligne (Retour à l'état initial)
    bool est_ligne = grille3x3.getCellule(0, 1).estVivante() &&
                     grille3x3.getCellule(1, 1).estVivante() &&
                     grille3x3.getCellule(2, 1).estVivante() &&
                     !grille3x3.getCellule(1, 0).estVivante(); // s'assurer que l'ancienne V est Morte

    bool passed = est_colonne && est_ligne;
    print_test_result("MiseAJour_Oscillation (Clignotant)", passed);
}

void Test_MiseAJour_Mort_SousPopulation() {
    std::cout << "\n--- Test : Mort par Sous-population (Vivant avec 1 voisin) ---" << std::endl;
    Grille grille3x3(3, 3);
    
    // Schéma initial : Une cellule vivante seule (1, 1) et un voisin (0, 0)
    // V . .
    // . X .
    // . . .
    std::vector<std::vector<bool>> matrice = {
        {true, false, false},
        {false, true, false},
        {false, false, false}
    };
    grille3x3.chargerGrille(matrice);

    // X=(1, 1) est VIVANTE et a 1 voisin (0, 0).
    assert(grille3x3.compterVoisins(1, 1) == 1);
    
    grille3x3.mettreAJourGrille();

    // Règle : Si VIVANTE et < 2 voisins, elle doit MOURIR.
    bool x_morte = !grille3x3.getCellule(1, 1).estVivante();
    
    // Le voisin (0, 0) avait 1 voisin (1, 1). Il doit aussi mourir.
    bool v_morte = !grille3x3.getCellule(0, 0).estVivante();

    bool passed = x_morte && v_morte;
    print_test_result("Règle: Mort par Sous-population", passed);
}
void Test_MiseAJour_Survie_TroisVoisins() {
    std::cout << "\n--- Test : Survie (Vivant avec 3 voisins) ---" << std::endl;
    Grille grille3x3(3, 3);
    
    // Schéma initial : Le coin supérieur gauche de la boîte
    // V V .
    // V X .
    // . . .
    // X=(1, 1) est VIVANTE et a 3 voisins : (0, 0), (0, 1), (1, 0).
    std::vector<std::vector<bool>> matrice = {
        {true, true, false},
        {true, true, false},
        {false, false, false}
    };
    grille3x3.chargerGrille(matrice);

    assert(grille3x3.compterVoisins(1, 1) == 3); 
    
    grille3x3.mettreAJourGrille();

    // Règle : Si VIVANTE et 2 ou 3 voisins, elle doit SURVIVRE.
    bool x_vivante = grille3x3.getCellule(1, 1).estVivante();
    
    // Note : (0, 2) était Morte et avait 2 voisins, donc ne naît pas.
    bool voisine_morte = !grille3x3.getCellule(0, 2).estVivante();

    bool passed = x_vivante && voisine_morte;
    print_test_result("Règle: Survie avec 3 voisins", passed);
}
void Test_MiseAJour_Mort_SurPopulation() {
    std::cout << "\n--- Test : Mort par Surpopulation (Vivant avec 4 voisins) ---" << std::endl;
    Grille grille3x3(3, 3);
    
    // Schéma initial : Une cellule (1, 1) est entourée par 4 voisins
    // V V .
    // V X V
    // . . .
    // X=(1, 1) est VIVANTE et a 4 voisins.
    std::vector<std::vector<bool>> matrice = {
        {true, true, false},
        {true, true, true},
        {false, false, false}
    };
    grille3x3.chargerGrille(matrice);

    assert(grille3x3.compterVoisins(1, 1) == 4);
    
    grille3x3.mettreAJourGrille();

    // Règle : Si VIVANTE et > 3 voisins, elle doit MOURIR.
    bool x_morte = !grille3x3.getCellule(1, 1).estVivante();
    
    // Cellule (0, 2) était Morte et avait 3 voisins (0, 1), (1, 1), (1, 2). Elle devrait NAÎTRE.
    bool voisine_nee = grille3x3.getCellule(0, 2).estVivante(); 

    bool passed = x_morte && voisine_nee;
    print_test_result("Règle: Mort par Surpopulation", passed);
}
void Test_MiseAJour_Naissance() {
    std::cout << "\n--- Test : Naissance (Mort avec 3 voisins) ---" << std::endl;
    Grille grille3x3(3, 3);
    
    // Schéma initial : Une forme en T (le bras du T est le point de naissance)
    // V V V
    // . X .
    // . . .
    // X=(1, 1) est MORTE et a 3 voisins : (0, 0), (0, 1), (0, 2).
    std::vector<std::vector<bool>> matrice = {
        {true, true, true},
        {false, false, false},
        {false, false, false}
    };
    grille3x3.chargerGrille(matrice);

    assert(grille3x3.getCellule(1, 1).estVivante() == false);
    assert(grille3x3.compterVoisins(1, 1) == 3); 
    
    grille3x3.mettreAJourGrille();

    // Règle : Si MORTE et exactement 3 voisins, elle doit NAÎTRE.
    bool x_nee = grille3x3.getCellule(1, 1).estVivante();
    
    // Les cellules vivantes initiales (0, 0), (0, 1), (0, 2) avaient 1, 2 et 1 voisin respectivement.
    // (0, 1) doit SURVIVRE (2 voisins).
    // (0, 0) et (0, 2) doivent MOURIR (1 voisin).
    bool survie_et_mort = grille3x3.getCellule(0, 1).estVivante() && 
                          !grille3x3.getCellule(0, 0).estVivante() && 
                          !grille3x3.getCellule(0, 2).estVivante();

    bool passed = x_nee && survie_et_mort;
    print_test_result("Règle: Naissance avec 3 voisins", passed);
}
void Test_MiseAJour_Glisseur() {
    std::cout << "\n--- Test : Motif Glisseur (Translation) ---" << std::endl;
    Grille grille5x5(5, 5); // Grille 5x5 pour la translation

    // Schéma initial (Glisseur en haut à gauche) :
    // . V . . .
    // . . V . .
    // V V V . .
    // . . . . .
    // . . . . .
    std::vector<std::vector<bool>> matrice_init = {
        {false, true, false, false, false},
        {false, false, true, false, false},
        {true, true, true, false, false},
        {false, false, false, false, false},
        {false, false, false, false, false}
    };
    grille5x5.chargerGrille(matrice_init);

    // Étape 1
    grille5x5.mettreAJourGrille();

    // Vérification rapide de la nouvelle position après 1 étape
    // Le centre du pattern se déplace légèrement. (2, 2) doit être vivante.
    bool step1_ok = grille5x5.getCellule(2, 2).estVivante() && 
                    grille5x5.getCellule(1, 3).estVivante();

    // Étape 2 (Total 2 générations)
    grille5x5.mettreAJourGrille();
    
    // Vérification rapide de la nouvelle position après 2 étapes
    // Le pattern revient à sa forme initiale, mais translaté.
    // Les coins (1, 3) et (3, 3) devraient être vivants
    bool step2_ok = grille5x5.getCellule(1, 3).estVivante() && 
                    grille5x5.getCellule(3, 3).estVivante();
    
    // On peut vérifier plus précisément la position finale (légèrement décalée)
    // Le point (2, 4) doit être vivant.
    bool step2_position = grille5x5.getCellule(2, 4).estVivante();

    bool passed = step1_ok && step2_ok && step2_position;
    print_test_result("Motif: Glisseur après 2 étapes", passed);
}
// --- Fonction Principale (Exécution) ---

int main() {
    std::cout << "--- Démarrage des Tests Unitaires (C++ Standard) ---" << std::endl;
    
    Test_CompterVoisins_Centre();
    Test_CompterVoisins_Coin();
    
    std::cout << "\n--- Tests de Mise à Jour (Règles du Jeu de la Vie) ---" << std::endl;
    
    Test_MiseAJour_Stabilité();
    Test_MiseAJour_Oscillation();
    Test_MiseAJour_Naissance();
    Test_MiseAJour_Mort_SousPopulation();
    Test_MiseAJour_Survie_TroisVoisins();
    Test_MiseAJour_Mort_SurPopulation();
    Test_MiseAJour_Naissance();
    Test_MiseAJour_Glisseur();


    std::cout << "\n--- Fin des Tests ---" << std::endl;
    return 0;
}