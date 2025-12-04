#include <gtest/gtest.h>
#include "Cellule.h"
#include "Est_vivant.h"
#include "Est_mort.h"

TEST(CelluleTest, EtatInitialVivant) {
    Cellule c(new Est_vivant());
    EXPECT_TRUE(c.getEtat()->estVivante());
}

TEST(CelluleTest, EtatInitialMort) {
    Cellule c(new Est_mort());
    EXPECT_FALSE(c.getEtat()->estVivante());
}

TEST(CelluleTest, ChangementEtatVivantDevientMort) {
    Cellule c(new Est_vivant());

    c.changementEtat();  // Ne retourne plus rien

    EXPECT_FALSE(c.getEtat()->estVivante());
}

TEST(CelluleTest, ChangementEtatMortDevientVivant) {
    Cellule c(new Est_mort());

    c.changementEtat();

    EXPECT_TRUE(c.getEtat()->estVivante());
}
