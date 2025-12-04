#include <gtest/gtest.h>
#include "Regles_initiales.h"
#include "Est_vivant.h"
#include "Est_mort.h"

TEST(ReglesInitialesTest, CelluleVivanteMeurtAvecMoinsDe2Voisins) {
    Regles_initiales r;

    Cellule* result = r.calculerProchainEtat(true, 1);
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->getEtat()->estVivante());

    delete result;
}

TEST(ReglesInitialesTest, CelluleVivanteMeurtAvecPlusDe3Voisins) {
    Regles_initiales r;

    Cellule* result = r.calculerProchainEtat(true, 4);
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->getEtat()->estVivante());

    delete result;
}

TEST(ReglesInitialesTest, CelluleVivanteSurvitAvec2Ou3VoisinsRetournantNull) {
    Regles_initiales r;

    Cellule* result = r.calculerProchainEtat(true, 2);
    EXPECT_EQ(result, nullptr);

    result = r.calculerProchainEtat(true, 3);
    EXPECT_EQ(result, nullptr);
}

TEST(ReglesInitialesTest, CelluleMorteNaissanceAvec3Voisins) {
    Regles_initiales r;

    Cellule* result = r.calculerProchainEtat(false, 3);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->getEtat()->estVivante());

    delete result;
}

TEST(ReglesInitialesTest, CelluleMorteNeNaissancePasAvecMoinsDe3VoisinsRetournantNull) {
    Regles_initiales r;

    Cellule* result = r.calculerProchainEtat(false, 2);
    EXPECT_EQ(result, nullptr);
}
