//
// Created by MARIA PAULA CARRERO on 7/28/19.
//

//
// Created by MARIA PAULA CARRERO on 7/27/19.
//
#define CATCH_CONFIG_MAIN
#include "../../3rd-party/catch.hpp"
#include "../../src/Factor-Oracle/FactorOracle.h"

TEST_CASE( "FactorOracleStart empty string (pass)", "[fo]") {
    FactorOracle<char> oracle_relations;
    oracle_relations.FactorOracleStart({});
    REQUIRE(oracle_relations.states_[0].transition_[0].first_state_ == 0);
    REQUIRE(oracle_relations.states_[0].transition_[0].last_state_ == 0);
    REQUIRE(oracle_relations.states_[0].transition_[0].symbol_ == '\0');
}

TEST_CASE( "FactorOracleStart a (pass) with string a", "[fo]") {
    FactorOracle<char> oracle_relations;
    oracle_relations.FactorOracleStart({'a'});
    REQUIRE(oracle_relations.states_[0].transition_[0].last_state_ == 1);
}

TEST_CASE( "FactorOracleStart long string (160 chars) (pass) with len+1 states", "[fo]") {
    FactorOracle<char> oracle_relations;
    vector<char> word = {'a','s','f','a','f','s','s','a'};
    int len = word.size();
    oracle_relations.FactorOracleStart(word);
    REQUIRE(oracle_relations.states_.size() == len+1);
}

TEST_CASE( "FactorOracleStart symbol = word[len]", "[fo]") {
    FactorOracle<char> oracle_relations;
    vector<char> word = {'a','s','f','a','f','s','s','a','f'};
    int len = word.size();
    oracle_relations.FactorOracleStart(word);
    REQUIRE(oracle_relations.states_[len-1].transition_[0].symbol_ == word[len-1]);
}

