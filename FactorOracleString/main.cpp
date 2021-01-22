//
// Created by MARIA PAULA CARRERO on 7/17/19.
//

#include "FactorOracle.h"
/*! \file main.cpp
    \brief A file that contains the main functions, which starts all the algorithm.

    One functions: main.
*/


int main() {
    string word;
    cout << "The string is: ";
    cin >> word;
    FactorOracle oracle_relations;
    oracle_relations.FactorOracleStart(word);
    oracle_relations.CallGenerate(10,0.6);
    return 0;
}
