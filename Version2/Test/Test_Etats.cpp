#include <gtest/gtest.h>
#include "Est_vivant.h"
#include "Est_mort.h"

TEST(EtatCelluleTest, EstVivantRetourneTrue) {
    Est_vivant v;
    EXPECT_TRUE(v.estVivante());
}

TEST(EtatCelluleTest, EstMortRetourneFalse) {
    Est_mort m;
    EXPECT_FALSE(m.estVivante());
}
