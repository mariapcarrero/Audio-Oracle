//
// Created by MARIA PAULA CARRERO on 7/27/19.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FactorOracle.h"


void PrepareTestAddLetter(FactorOracle& oracle_relations)
{


    ///States
    ///State zero
    State state_0;
    state_0.state_= 0;
    state_0.suffix_transition_ = -1;
    state_0.lrs_ = 0;
    //state_0.transition_.push_back(transition_0_1);

    ///Complete factor oracle
    oracle_relations.states_.push_back(state_0);

}
void PrepareTestAddLetterOne(FactorOracle& oracle_relations)
{

    ///Transitions from zero
    SingleTransition transition_0_1;
    transition_0_1.first_state_ = 0;
    transition_0_1.last_state_ = 1;
    transition_0_1.symbol_ = 'a';
    SingleTransition transition_0_2;
    transition_0_2.first_state_ = 0;
    transition_0_2.last_state_ = 2;
    transition_0_2.symbol_ = 'b';
    SingleTransition transition_0_4;
    transition_0_4.first_state_ = 0;
    transition_0_4.last_state_ = 4;
    transition_0_4.symbol_ = 'c';
    /// Transitions from one
    SingleTransition transition_1_2;
    transition_1_2.first_state_ = 1;
    transition_1_2.last_state_ = 2;
    transition_1_2.symbol_ = 'b';
    /// Transitions from two
    SingleTransition transition_2_3;
    transition_2_3.first_state_ = 2;
    transition_2_3.last_state_ = 3;
    transition_2_3.symbol_ = 'b';
    SingleTransition transition_2_4;
    transition_2_4.first_state_ = 2;
    transition_2_4.last_state_ = 4;
    transition_2_4.symbol_ = 'c';
    ///Transitions from three
   SingleTransition transition_3_4;
    transition_3_4.first_state_ = 3;
    transition_3_4.last_state_ = 4;
    transition_3_4.symbol_ = 'c';
    ///States
    ///State zero
    State state_0;
    state_0.state_= 0;
    state_0.suffix_transition_ = -1;
    state_0.lrs_ = 0;
    state_0.transition_.push_back(transition_0_1);
    state_0.transition_.push_back(transition_0_2);
    state_0.transition_.push_back(transition_0_4);
  //  state_0.transition_.push_back(transition_0_8);

    ///State one
    State state_1;
    state_1.state_= 1;
    state_1.suffix_transition_ = 0;
    state_1.lrs_ = 0;
    state_1.transition_.push_back(transition_1_2);
    ///State two
    State state_2;
    state_2.state_= 2;
    state_2.suffix_transition_ = 0;
    state_2.lrs_ = 0;
    state_2.transition_.push_back(transition_2_3);
    state_2.transition_.push_back(transition_2_4);
    ///State three
    State state_3;
    state_3.state_= 3;
    state_3.suffix_transition_ = 2;
    state_3.lrs_ = 1;
    state_3.transition_.push_back(transition_3_4);
    ///State four

    ///Complete factor oracle
    oracle_relations.states_.push_back(state_0);
    oracle_relations.states_.push_back(state_1);
    oracle_relations.states_.push_back(state_2);
    oracle_relations.states_.push_back(state_3);
    oracle_relations.states_.resize(11);


}
TEST_CASE( "AddLetter (5) symbol_ == a (pass) with string abbcabcdabc", "[fo]") {
    FactorOracle oracle_relations;
    string word = "abbcabcdabc";
    int len = word.size();
    oracle_relations.T = {{1,2,3},{},{3}, {},{}};
    PrepareTestAddLetterOne(oracle_relations);
    oracle_relations.AddLetter(5,word);
    REQUIRE(oracle_relations.states_[4].transition_[0].symbol_ == 'a');
}

TEST_CASE( "AddLetter (5) T  == a (pass) with string abbcabcdabc", "[fo]") {
    FactorOracle oracle_relations;
    string word = "abbcabcdabc";
    int len = word.size();
    oracle_relations.T = {{1,2,3,4},{},{3}, {},{}};
    PrepareTestAddLetterOne(oracle_relations);
    oracle_relations.AddLetter(5,word);
    REQUIRE(oracle_relations.T[1][0] == 5);
}


TEST_CASE( "AddLetter one letter word (pass) with string a", "[fo]") {
    FactorOracle oracle_relations;
    string word = "a";
    int len = word.size();
    oracle_relations.T = {{},{}};
    oracle_relations.states_.resize(len+1);
    PrepareTestAddLetter(oracle_relations);
    oracle_relations.AddLetter(1,word);
    REQUIRE(oracle_relations.states_[0].transition_[0].first_state_ == 0);
    REQUIRE(oracle_relations.states_[0].transition_[0].last_state_ == 1);
    REQUIRE(oracle_relations.states_[0].transition_[0].symbol_ == 'a');
  // Ask if there is a way to add a null symbol
}

