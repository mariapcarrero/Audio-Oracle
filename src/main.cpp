//
// Created by MARIA PAULA CARRERO on 7/17/19.
//

#include "Factor-Oracle/FactorOracle.h"
/*! \file main.cpp
    \brief A file that contains the main functions, which starts all the algorithm.

    One functions: main.
*/


int main() {
    /*FactorOracle<int> oracle_relations;
  //  oracle_relations.FactorOracleStart({1});
    oracle_relations.FactorOracleStart({1,2,2,3,1,2,3,4,1,2,3});
    oracle_relations.CallGenerate(10,0.6);*/
    FactorOracle<char> oracle_relations;
    oracle_relations.FactorOracleStart({'a','b','b','c','a','b','c','d','a','b','c'});
    //oracle_relations.FactorOracleStart({'a','b','b','c','a'});
    int lensuf = oracle_relations.RevSuffix.size();
    for (int x = 0; x < lensuf; x++)
    {
        int leninteral = oracle_relations.RevSuffix[x].size();
        cout << "Estado: " << x << "\n";
        for (int i = 0; i < leninteral; i++) {
            cout << oracle_relations.RevSuffix[x][i] << " ";
        }
        cout << endl;
    }
    oracle_relations.CallGenerate(10,0.6);
    return 0;
}
