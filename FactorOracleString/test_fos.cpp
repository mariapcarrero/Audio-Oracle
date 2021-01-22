//
// Created by MARIA PAULA CARRERO on 7/28/19.
//

//
// Created by MARIA PAULA CARRERO on 7/27/19.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FactorOracle.h"

TEST_CASE( "FactorOracleStart empty string (pass)", "[fo]") {
    FactorOracle oracle_relations;
    string word = "";
    int len = word.size();
    oracle_relations.FactorOracleStart(word);
    REQUIRE(oracle_relations.states_[0].transition_[0].first_state_ == 0);
    REQUIRE(oracle_relations.states_[0].transition_[0].last_state_ == 0);
    REQUIRE(oracle_relations.states_[0].transition_[0].symbol_ == '\0');
}

TEST_CASE( "FactorOracleStart a (pass) with string a", "[fo]") {
    FactorOracle oracle_relations;
    string word = "a";
    int len = word.size();
    oracle_relations.FactorOracleStart(word);
    REQUIRE(oracle_relations.states_[0].transition_[0].last_state_ == 1);
}

TEST_CASE( "FactorOracleStart long string (160 chars) (pass) with len+1 states", "[fo]") {
    FactorOracle oracle_relations;
    string word = "asafaslkdjasdlkasdjkasalsasdklasdljasdklasjdlaskdjaskldjasldkasdklasdlaaskjdajsdlkasjdlaskdajlsdjalskdajsdlaksdjalsdkaslasjdlaksdalsdjalsdalskdjalsdkjasdsldalkd";
    int len = word.size();
    oracle_relations.FactorOracleStart(word);
    REQUIRE(oracle_relations.states_.size() == len+1);
}

TEST_CASE( "FactorOracleStart symbol = word[len]", "[fo]") {
    FactorOracle oracle_relations;
    string word = "asafaslkdjasdlkasdjkasalsasdklasdljasdklasjdlaskdjaskldjasldkasdklasdlaaskjdajsdlkasjdlaskdajlsdjalskdajsdlaksdjalsdkaslasjdlaksdalsdjalsdalskdjalsdkjasdsldalkd";
    int len = word.size();
    oracle_relations.FactorOracleStart(word);
    REQUIRE(oracle_relations.states_[len-1].transition_[0].symbol_ == word[len-1]);
}

