//
// Created by MARIA PAULA CARRERO on 7/23/19.
//

#define CATCH_CONFIG_MAIN
#include "../../3rd-party/catch.hpp"
#include "../../src/Factor-Oracle/FactorOracle.h"

TEST_CASE( "LengthCommonSuffix 4 0 == 0 (pass)", "[fo]") {
    FactorOracle<char> oracle_relations;
    string word = "abbcabcdabc";
    oracle_relations.FactorOracleStart({'a','b','b','c','a','b','c','d','a','b','c'});
    REQUIRE(oracle_relations.LengthCommonSuffix(4,0) == 0 );
}

TEST_CASE( "LengthCommonSuffix 4 0 == 2 (fail)", "[fo]") {
    FactorOracle<char> oracle_relations;
    string word = "abbcabcdabc";
    oracle_relations.FactorOracleStart({'a','b','b','c','a','b','c','d','a','b','c'});
    REQUIRE(oracle_relations.LengthCommonSuffix(4,0) == 2 );
}

TEST_CASE( "LengthCommonSuffix 5 1 == 1 (pass)", "[fo]") {
    FactorOracle<char> oracle_relations;
    string word = "abbcabcdabc";
    oracle_relations.FactorOracleStart({'a','b','b','c','a','b','c','d','a','b','c'});
    REQUIRE(oracle_relations.LengthCommonSuffix(5,1) == 1 );
}


TEST_CASE( "LengthCommonSuffix 6 3 == 1 (pass)", "[fo]") {
    FactorOracle<char> oracle_relations;
    string word = "abbcabcdabc";
    oracle_relations.FactorOracleStart({'a','b','b','c','a','b','c','d','a','b','c'});
    REQUIRE(oracle_relations.LengthCommonSuffix(6,3) == 1 );
}

TEST_CASE( "LengthCommonSuffix 9 1 == 1 (pass)", "[fo]") {
    FactorOracle<char> oracle_relations;
    string word = "abbcabcdabc";
    oracle_relations.FactorOracleStart({'a','b','b','c','a','b','c','d','a','b','c'});
    REQUIRE(oracle_relations.LengthCommonSuffix( 9,1) == 1 );
}

TEST_CASE( "LengthCommonSuffix 10 3 == 1 (pass)", "[fo]") {
    FactorOracle<char> oracle_relations;
    string word = "abbcabcdabc";
    oracle_relations.FactorOracleStart({'a','b','b','c','a','b','c','d','a','b','c'});
    REQUIRE(oracle_relations.LengthCommonSuffix(10,3) == 1 );
}

TEST_CASE( "LengthCommonSuffix 8 0 == 0 (pass)", "[fo]") {
    FactorOracle<char> oracle_relations;
    string word = "abbcabcdabc";
    oracle_relations.FactorOracleStart({'a','b','b','c','a','b','c','d','a','b','c'});
    REQUIRE(oracle_relations.LengthCommonSuffix(8,0) == 0 );
}


/*
unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}
     REQUIRE(LengthCommonSuffix(oracle_relations, 9,1) == 1);
    REQUIRE(LengthCommonSuffix(oracle_relations, 10,3) == 0);
    REQUIRE(LengthCommonSuffix(oracle_relations, 6,3) == 1);

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
*/