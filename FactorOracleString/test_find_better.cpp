//
// Created by MARIA PAULA CARRERO on 7/28/19.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FactorOracle.h"


void PrepareTest(FactorOracle& oracle_relations)
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
    SingleTransition transition_0_8;
    transition_0_8.first_state_ = 0;
    transition_0_8.last_state_ = 8;
    transition_0_8.symbol_ = 'd';
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
    ///Transitions from four
    SingleTransition transition_4_5;
    transition_4_5.first_state_ = 4;
    transition_4_5.last_state_ = 5;
    transition_4_5.symbol_ = 'a';
    SingleTransition transition_4_8;
    transition_4_8.first_state_ = 4;
    transition_4_8.last_state_ = 8;
    transition_4_8.symbol_ = 'd';
    ///Transitions from five
    SingleTransition transition_5_6;
    transition_5_6.first_state_ = 5;
    transition_5_6.last_state_ = 6;
    transition_5_6.symbol_ = 'b';
    ///Transitions from six
    SingleTransition transition_6_7;
    transition_6_7.first_state_ = 6;
    transition_6_7.last_state_ = 7;
    transition_6_7.symbol_ = 'c';
    ///Transitions from seven
    SingleTransition transition_7_8;
    transition_7_8.first_state_ = 7;
    transition_7_8.last_state_ = 8;
    transition_7_8.symbol_ = 'd';
    ///Transitions from eight
    SingleTransition transition_8_9;
    transition_8_9.first_state_ = 8;
    transition_8_9.last_state_ = 9;
    transition_8_9.symbol_ = 'a';
    ///Transitions from nine
    SingleTransition transition_9_10;
    transition_9_10.first_state_ = 9;
    transition_9_10.last_state_ = 10;
    transition_9_10.symbol_ = 'b';
    ///Transitions from ten
    SingleTransition transition_10_11;
    transition_10_11.first_state_ = 10;
    transition_10_11.last_state_ = 11;
    transition_10_11.symbol_ = 'c';

    ///States
    ///State zero
    State state_0;
    state_0.state_= 0;
    state_0.suffix_transition_ = -1;
    state_0.lrs_ = 0;
    state_0.transition_.push_back(transition_0_1);
    state_0.transition_.push_back(transition_0_2);
    state_0.transition_.push_back(transition_0_4);
    state_0.transition_.push_back(transition_0_8);

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
    State state_4;
    state_4.state_= 4;
    state_4.suffix_transition_ = 0;
    state_4.lrs_ = 0;
    state_4.transition_.push_back(transition_4_5);
    state_4.transition_.push_back(transition_4_8);
    ///State five
    State state_5;
    state_5.state_= 5;
    state_5.suffix_transition_ = 1;
    state_5.lrs_ = 1;
    state_5.transition_.push_back(transition_5_6);
    ///State six
    State state_6;
    state_6.state_= 6;
    state_6.suffix_transition_ = 2;
    state_6.lrs_ = 2;
    state_6.transition_.push_back(transition_6_7);
    ///State seven
    State state_7;
    state_7.state_= 7;
    state_7.suffix_transition_ = 4;
    state_7.lrs_ = 2;
    state_7.transition_.push_back(transition_7_8);
    ///State eight
    State state_8;
    state_8.state_= 8;
    state_8.suffix_transition_ = 0;
    state_8.lrs_ = 0;
    state_8.transition_.push_back(transition_8_9);
    ///State nine
    State state_9;
    state_9.state_= 9;
    state_9.suffix_transition_ = 1;
    state_9.lrs_ = 1;
    state_9.transition_.push_back(transition_9_10);
    ///State ten
    State state_10;
    state_10.state_= 10;
    state_10.suffix_transition_ = 2;
    state_10.lrs_ = 2;
    state_10.transition_.push_back(transition_10_11);
    ///State eleven
    State state_11;
    state_11.state_= 11;
    state_11.suffix_transition_ = 4;
    state_11.lrs_ = 2;

    ///Complete factor oracle
    oracle_relations.states_.push_back(state_0);
    oracle_relations.states_.push_back(state_1);
    oracle_relations.states_.push_back(state_2);
    oracle_relations.states_.push_back(state_3);
    oracle_relations.states_.push_back(state_4);
    oracle_relations.states_.push_back(state_5);
    oracle_relations.states_.push_back(state_6);
    oracle_relations.states_.push_back(state_7);
    oracle_relations.states_.push_back(state_8);
    oracle_relations.states_.push_back(state_9);
    oracle_relations.states_.push_back(state_10);
    oracle_relations.states_.push_back(state_11);

}
void PrepareTestTwo(FactorOracle& oracle_relations)
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
    SingleTransition transition_0_8;
    transition_0_8.first_state_ = 0;
    transition_0_8.last_state_ = 8;
    transition_0_8.symbol_ = 'd';
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
    ///Transitions from four
    SingleTransition transition_4_5;
    transition_4_5.first_state_ = 4;
    transition_4_5.last_state_ = 5;
    transition_4_5.symbol_ = 'a';
    SingleTransition transition_4_8;
    transition_4_8.first_state_ = 4;
    transition_4_8.last_state_ = 8;
    transition_4_8.symbol_ = 'd';
    ///Transitions from five
    SingleTransition transition_5_6;
    transition_5_6.first_state_ = 5;
    transition_5_6.last_state_ = 6;
    transition_5_6.symbol_ = 'b';
    ///Transitions from six
    SingleTransition transition_6_7;
    transition_6_7.first_state_ = 6;
    transition_6_7.last_state_ = 7;
    transition_6_7.symbol_ = 'c';
    ///Transitions from seven
    SingleTransition transition_7_8;
    transition_7_8.first_state_ = 7;
    transition_7_8.last_state_ = 8;
    transition_7_8.symbol_ = 'd';
    ///Transitions from eight
    SingleTransition transition_8_9;
    transition_8_9.first_state_ = 8;
    transition_8_9.last_state_ = 9;
    transition_8_9.symbol_ = 'a';
    ///Transitions from nine
    SingleTransition transition_9_10;
    transition_9_10.first_state_ = 9;
    transition_9_10.last_state_ = 10;
    transition_9_10.symbol_ = 'b';
    ///Transitions from ten
    SingleTransition transition_10_11;
    transition_10_11.first_state_ = 10;
    transition_10_11.last_state_ = 11;
    transition_10_11.symbol_ = 'c';

    ///States
    ///State zero
    State state_0;
    state_0.state_= 0;
    state_0.suffix_transition_ = -1;
    state_0.lrs_ = 0;
    state_0.transition_.push_back(transition_0_1);
    state_0.transition_.push_back(transition_0_2);
    state_0.transition_.push_back(transition_0_4);
    state_0.transition_.push_back(transition_0_8);

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
    State state_4;
    state_4.state_= 4;
    state_4.suffix_transition_ = 0;
    state_4.lrs_ = 0;
    state_4.transition_.push_back(transition_4_5);
    state_4.transition_.push_back(transition_4_8);
    ///State five
    State state_5;
    state_5.state_= 5;
    state_5.suffix_transition_ = 1;
    state_5.lrs_ = 1;
    state_5.transition_.push_back(transition_5_6);
    ///State six
    State state_6;
    state_6.state_= 6;
    state_6.suffix_transition_ = 2;
    state_6.lrs_ = 2;
    state_6.transition_.push_back(transition_6_7);
    ///State seven
    State state_7;
    state_7.state_= 7;
    state_7.suffix_transition_ = 4;
    state_7.lrs_ = 2;
    state_7.transition_.push_back(transition_7_8);
    ///State eight
    State state_8;
    state_8.state_= 8;
    state_8.suffix_transition_ = 0;
    state_8.lrs_ = 0;
    state_8.transition_.push_back(transition_8_9);
    ///State nine
    State state_9;
    state_9.state_= 9;
    state_9.suffix_transition_ = 1;
    state_9.lrs_ = 1;
    state_9.transition_.push_back(transition_9_10);
    ///State ten
    State state_10;
    state_10.state_= 10;
    state_10.suffix_transition_ = 2;
    state_10.lrs_ = 2;
    state_10.transition_.push_back(transition_10_11);
    ///State eleven
    State state_11;
    state_11.state_= 11;
    state_11.suffix_transition_ = 4;
    state_11.lrs_ = 2;

    ///Complete factor oracle
    oracle_relations.states_.push_back(state_0);
    oracle_relations.states_.push_back(state_1);
    oracle_relations.states_.push_back(state_2);
    oracle_relations.states_.push_back(state_3);
    oracle_relations.states_.push_back(state_4);
    oracle_relations.states_.push_back(state_5);
    oracle_relations.states_.push_back(state_6);
    oracle_relations.states_.push_back(state_7);
    oracle_relations.states_.push_back(state_8);
    oracle_relations.states_.push_back(state_9);
    oracle_relations.states_.push_back(state_10);
    oracle_relations.states_.push_back(state_11);

}
TEST_CASE( "FindBetter 11 a == 7 (pass) with string abbcabcdabc", "[fo]") {
    FactorOracle oracle_relations;
    string word = "abbcabcdabc";
    int len = word.size();
    oracle_relations.T = {{1,2,3,4},{5,9},{3,6,10}, {}, {7,11}, {}, {},{},{},{},{},{}};
    PrepareTest(oracle_relations);
    REQUIRE(oracle_relations.FindBetter(11, 'a', word) == 7);
}


TEST_CASE( "FindBetter 11 b == 7 (fail) with string abbcabcdabc", "[fo]") {
    FactorOracle oracle_relations;
    string word = "abbcabcdabc";
    int len = word.size();
    oracle_relations.T = {{1,2,3,4},{5,9},{3,6,10}, {}, {7,11}, {}, {},{},{},{},{},{}};
    PrepareTest(oracle_relations);
    REQUIRE(oracle_relations.FindBetter(11, 'b', word) == 7);
}

TEST_CASE( "FindBetter 4 b == 0 (pass) with string abbcabcdabc", "[fo]") {
    FactorOracle oracle_relations;
    string word = "abbcabcdabc";
    int len = word.size();
    oracle_relations.T = {{1,2,3,4},{5,9},{3,6,10}, {}, {7,11}, {}, {},{},{},{},{},{}};
    PrepareTest(oracle_relations);
    REQUIRE(oracle_relations.FindBetter(4, 'a', word) == 0);
}

