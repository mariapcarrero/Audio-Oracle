//
// Created by MARIA PAULA CARRERO on 7/28/19.
//

#define CATCH_CONFIG_MAIN
#include "../../3rd-party/catch.hpp"
#include "../../src/Factor-Oracle/FactorOracle.h"


void PrepareTest(FactorOracle<char>& oracle_relations)
{


    ///Transitions from zero
    SingleTransition<char> transition_0_1;
    transition_0_1.first_state_ = 0;
    transition_0_1.last_state_ = 1;
    transition_0_1.symbol_ = 'a';
    SingleTransition<char> transition_0_2;
    transition_0_2.first_state_ = 0;
    transition_0_2.last_state_ = 2;
    transition_0_2.symbol_ = 'b';
    SingleTransition<char> transition_0_4;
    transition_0_4.first_state_ = 0;
    transition_0_4.last_state_ = 4;
    transition_0_4.symbol_ = 'c';
    SingleTransition<char> transition_0_8;
    transition_0_8.first_state_ = 0;
    transition_0_8.last_state_ = 8;
    transition_0_8.symbol_ = 'd';
    /// Transitions from one
    SingleTransition<char> transition_1_2;
    transition_1_2.first_state_ = 1;
    transition_1_2.last_state_ = 2;
    transition_1_2.symbol_ = 'b';
    /// Transitions from two
    SingleTransition<char> transition_2_3;
    transition_2_3.first_state_ = 2;
    transition_2_3.last_state_ = 3;
    transition_2_3.symbol_ = 'b';
    SingleTransition<char> transition_2_4;
    transition_2_4.first_state_ = 2;
    transition_2_4.last_state_ = 4;
    transition_2_4.symbol_ = 'c';
    ///Transitions from three
    SingleTransition<char> transition_3_4;
    transition_3_4.first_state_ = 3;
    transition_3_4.last_state_ = 4;
    transition_3_4.symbol_ = 'c';
    ///Transitions from four
    SingleTransition<char> transition_4_5;
    transition_4_5.first_state_ = 4;
    transition_4_5.last_state_ = 5;
    transition_4_5.symbol_ = 'a';
    SingleTransition<char> transition_4_8;
    transition_4_8.first_state_ = 4;
    transition_4_8.last_state_ = 8;
    transition_4_8.symbol_ = 'd';
    ///Transitions from five
    SingleTransition<char> transition_5_6;
    transition_5_6.first_state_ = 5;
    transition_5_6.last_state_ = 6;
    transition_5_6.symbol_ = 'b';
    ///Transitions from six
    SingleTransition<char> transition_6_7;
    transition_6_7.first_state_ = 6;
    transition_6_7.last_state_ = 7;
    transition_6_7.symbol_ = 'c';
    ///Transitions from seven
    SingleTransition<char> transition_7_8;
    transition_7_8.first_state_ = 7;
    transition_7_8.last_state_ = 8;
    transition_7_8.symbol_ = 'd';
    ///Transitions from eight
    SingleTransition<char> transition_8_9;
    transition_8_9.first_state_ = 8;
    transition_8_9.last_state_ = 9;
    transition_8_9.symbol_ = 'a';
    ///Transitions from nine
    SingleTransition<char> transition_9_10;
    transition_9_10.first_state_ = 9;
    transition_9_10.last_state_ = 10;
    transition_9_10.symbol_ = 'b';
    ///Transitions from ten
    SingleTransition<char> transition_10_11;
    transition_10_11.first_state_ = 10;
    transition_10_11.last_state_ = 11;
    transition_10_11.symbol_ = 'c';

    ///States
    ///State<char> zero
    State<char> state_0;
    state_0.state_= 0;
    state_0.suffix_transition_ = -1;
    state_0.lrs_ = 0;
    state_0.transition_.push_back(transition_0_1);
    state_0.transition_.push_back(transition_0_2);
    state_0.transition_.push_back(transition_0_4);
    state_0.transition_.push_back(transition_0_8);

    ///State<char> one
    State<char> state_1;
    state_1.state_= 1;
    state_1.suffix_transition_ = 0;
    state_1.lrs_ = 0;
    state_1.transition_.push_back(transition_1_2);
    ///State<char> two
    State<char> state_2;
    state_2.state_= 2;
    state_2.suffix_transition_ = 0;
    state_2.lrs_ = 0;
    state_2.transition_.push_back(transition_2_3);
    state_2.transition_.push_back(transition_2_4);
    ///State<char> three
    State<char> state_3;
    state_3.state_= 3;
    state_3.suffix_transition_ = 2;
    state_3.lrs_ = 1;
    state_3.transition_.push_back(transition_3_4);
    ///State<char> four
    State<char> state_4;
    state_4.state_= 4;
    state_4.suffix_transition_ = 0;
    state_4.lrs_ = 0;
    state_4.transition_.push_back(transition_4_5);
    state_4.transition_.push_back(transition_4_8);
    ///State<char> five
    State<char> state_5;
    state_5.state_= 5;
    state_5.suffix_transition_ = 1;
    state_5.lrs_ = 1;
    state_5.transition_.push_back(transition_5_6);
    ///State<char> six
    State<char> state_6;
    state_6.state_= 6;
    state_6.suffix_transition_ = 2;
    state_6.lrs_ = 2;
    state_6.transition_.push_back(transition_6_7);
    ///State<char> seven
    State<char> state_7;
    state_7.state_= 7;
    state_7.suffix_transition_ = 4;
    state_7.lrs_ = 2;
    state_7.transition_.push_back(transition_7_8);
    ///State<char> eight
    State<char> state_8;
    state_8.state_= 8;
    state_8.suffix_transition_ = 0;
    state_8.lrs_ = 0;
    state_8.transition_.push_back(transition_8_9);
    ///State<char> nine
    State<char> state_9;
    state_9.state_= 9;
    state_9.suffix_transition_ = 1;
    state_9.lrs_ = 1;
    state_9.transition_.push_back(transition_9_10);
    ///State<char> ten
    State<char> state_10;
    state_10.state_= 10;
    state_10.suffix_transition_ = 2;
    state_10.lrs_ = 2;
    state_10.transition_.push_back(transition_10_11);
    ///State<char> eleven
    State<char> state_11;
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
void PrepareTestTwo(FactorOracle<char>& oracle_relations)
{


    ///Transitions from zero
    SingleTransition<char> transition_0_1;
    transition_0_1.first_state_ = 0;
    transition_0_1.last_state_ = 1;
    transition_0_1.symbol_ = 'a';
    SingleTransition<char> transition_0_2;
    transition_0_2.first_state_ = 0;
    transition_0_2.last_state_ = 2;
    transition_0_2.symbol_ = 'b';
    SingleTransition<char> transition_0_4;
    transition_0_4.first_state_ = 0;
    transition_0_4.last_state_ = 4;
    transition_0_4.symbol_ = 'c';
    SingleTransition<char> transition_0_8;
    transition_0_8.first_state_ = 0;
    transition_0_8.last_state_ = 8;
    transition_0_8.symbol_ = 'd';
    /// Transitions from one
    SingleTransition<char> transition_1_2;
    transition_1_2.first_state_ = 1;
    transition_1_2.last_state_ = 2;
    transition_1_2.symbol_ = 'b';
    /// Transitions from two
    SingleTransition<char> transition_2_3;
    transition_2_3.first_state_ = 2;
    transition_2_3.last_state_ = 3;
    transition_2_3.symbol_ = 'b';
    SingleTransition<char> transition_2_4;
    transition_2_4.first_state_ = 2;
    transition_2_4.last_state_ = 4;
    transition_2_4.symbol_ = 'c';
    ///Transitions from three
    SingleTransition<char> transition_3_4;
    transition_3_4.first_state_ = 3;
    transition_3_4.last_state_ = 4;
    transition_3_4.symbol_ = 'c';
    ///Transitions from four
    SingleTransition<char> transition_4_5;
    transition_4_5.first_state_ = 4;
    transition_4_5.last_state_ = 5;
    transition_4_5.symbol_ = 'a';
    SingleTransition<char> transition_4_8;
    transition_4_8.first_state_ = 4;
    transition_4_8.last_state_ = 8;
    transition_4_8.symbol_ = 'd';
    ///Transitions from five
    SingleTransition<char> transition_5_6;
    transition_5_6.first_state_ = 5;
    transition_5_6.last_state_ = 6;
    transition_5_6.symbol_ = 'b';
    ///Transitions from six
    SingleTransition<char> transition_6_7;
    transition_6_7.first_state_ = 6;
    transition_6_7.last_state_ = 7;
    transition_6_7.symbol_ = 'c';
    ///Transitions from seven
    SingleTransition<char> transition_7_8;
    transition_7_8.first_state_ = 7;
    transition_7_8.last_state_ = 8;
    transition_7_8.symbol_ = 'd';
    ///Transitions from eight
    SingleTransition<char> transition_8_9;
    transition_8_9.first_state_ = 8;
    transition_8_9.last_state_ = 9;
    transition_8_9.symbol_ = 'a';
    ///Transitions from nine
    SingleTransition<char> transition_9_10;
    transition_9_10.first_state_ = 9;
    transition_9_10.last_state_ = 10;
    transition_9_10.symbol_ = 'b';
    ///Transitions from ten
    SingleTransition<char> transition_10_11;
    transition_10_11.first_state_ = 10;
    transition_10_11.last_state_ = 11;
    transition_10_11.symbol_ = 'c';

    ///States
    ///State<char> zero
    State<char> state_0;
    state_0.state_= 0;
    state_0.suffix_transition_ = -1;
    state_0.lrs_ = 0;
    state_0.transition_.push_back(transition_0_1);
    state_0.transition_.push_back(transition_0_2);
    state_0.transition_.push_back(transition_0_4);
    state_0.transition_.push_back(transition_0_8);

    ///State<char> one
    State<char> state_1;
    state_1.state_= 1;
    state_1.suffix_transition_ = 0;
    state_1.lrs_ = 0;
    state_1.transition_.push_back(transition_1_2);
    ///State<char> two
    State<char> state_2;
    state_2.state_= 2;
    state_2.suffix_transition_ = 0;
    state_2.lrs_ = 0;
    state_2.transition_.push_back(transition_2_3);
    state_2.transition_.push_back(transition_2_4);
    ///State<char> three
    State<char> state_3;
    state_3.state_= 3;
    state_3.suffix_transition_ = 2;
    state_3.lrs_ = 1;
    state_3.transition_.push_back(transition_3_4);
    ///State<char> four
    State<char> state_4;
    state_4.state_= 4;
    state_4.suffix_transition_ = 0;
    state_4.lrs_ = 0;
    state_4.transition_.push_back(transition_4_5);
    state_4.transition_.push_back(transition_4_8);
    ///State<char> five
    State<char> state_5;
    state_5.state_= 5;
    state_5.suffix_transition_ = 1;
    state_5.lrs_ = 1;
    state_5.transition_.push_back(transition_5_6);
    ///State<char> six
    State<char> state_6;
    state_6.state_= 6;
    state_6.suffix_transition_ = 2;
    state_6.lrs_ = 2;
    state_6.transition_.push_back(transition_6_7);
    ///State<char> seven
    State<char> state_7;
    state_7.state_= 7;
    state_7.suffix_transition_ = 4;
    state_7.lrs_ = 2;
    state_7.transition_.push_back(transition_7_8);
    ///State<char> eight
    State<char> state_8;
    state_8.state_= 8;
    state_8.suffix_transition_ = 0;
    state_8.lrs_ = 0;
    state_8.transition_.push_back(transition_8_9);
    ///State<char> nine
    State<char> state_9;
    state_9.state_= 9;
    state_9.suffix_transition_ = 1;
    state_9.lrs_ = 1;
    state_9.transition_.push_back(transition_9_10);
    ///State<char> ten
    State<char> state_10;
    state_10.state_= 10;
    state_10.suffix_transition_ = 2;
    state_10.lrs_ = 2;
    state_10.transition_.push_back(transition_10_11);
    ///State<char> eleven
    State<char> state_11;
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
    FactorOracle<char> oracle_relations;
    vector<char> word = {'a','b','b','c','a','b','c','d','a','b','c'};
    oracle_relations.RevSuffix = {{1,2,4,8},{5,9},{3,6,10}, {}, {7}, {}, {},{11},{},{},{},{}};
    PrepareTest(oracle_relations);
    REQUIRE(oracle_relations.FindBetter(11, 'a', word) == 7);
}


TEST_CASE( "FindBetter 11 b == 7 (fail) with string abbcabcdabc", "[fo]") {
    FactorOracle<char> oracle_relations;
    vector<char> word = {'a','b','b','c','a','b','c','d','a','b','c'};
    oracle_relations.RevSuffix = {{1,2,4,8},{5,9},{3,6,10}, {}, {7}, {}, {},{11},{},{},{},{}};
    PrepareTest(oracle_relations);
    REQUIRE(oracle_relations.FindBetter(11, 'b', word) == 7);
}

TEST_CASE( "FindBetter 3 a == 0 (pass) with string abbcabcdabc", "[fo]") {
    FactorOracle<char> oracle_relations;
    vector<char> word = {'a','b','b','c','a','b','c','d','a','b','c'};
    oracle_relations.RevSuffix = {{1,2,4,8},{5,9},{3,6,10}, {}, {7}, {}, {},{11},{},{},{},{}};
    PrepareTest(oracle_relations);
    REQUIRE(oracle_relations.FindBetter(3, 'a', word) == 0);
}

