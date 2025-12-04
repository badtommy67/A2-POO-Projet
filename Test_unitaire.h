#ifndef TEST_UNITAIRE_H
#define TEST_UNITAIRE_H

#include <iostream>
#include <vector>
#include <string>

class Gestion_jeu;

class Test_unitaire {
private:
    void verifier_correction();

public:
    Test_unitaire();
    ~Test_unitaire();

    void lancerTest();
};

#endif