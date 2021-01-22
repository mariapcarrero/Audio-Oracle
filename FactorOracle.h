//
// Created by MARIA PAULA CARRERO on 7/16/19.
//
#include <iostream>
#include <new>
#include <string>
#include <vector>
#include <variant>
#include <random>
#include <algorithm>


#ifndef FACTORORACLESTRING_FACTORORACLE_H
#define FACTORORACLESTRING_FACTORORACLE_H

#define NUMBER_R 10

int phi, k, fo_iter;

#define RAND_MAX 0x7fffffff

/*! \file FactorOracle.h
    \brief A file that contains the definitions of the classes needed for the creation of a Factor Oracle.

    Three main classes: FactorOracle, State and SingleTransition.
*/
/*! \fn void AddLetter(FactorOracle& States, vector <vector<int>> &T, int i, string word)
    \brief Adds new transitions from state i-1 to state i.
    \param T A vector where each position has all the suffix transitions directed to each state.
    \param i The integer of the current state.
    \param word The input string.

*/
/*! \fn int LengthCommonSuffix(FactorOracle& States, int phi_one, int phi_two)
    \brief Finds the length of a common suffix ending at the position phi_one and phi_two by traversing the suffix links.
    \param phi_one The position of the state.
    \param phi_two The position of the state.
*/
/*! \fn int FindBetter(FactorOracle& States, vector <vector<int>> &T, int i, char alpha, string word)
    \brief Writes \a count bytes from \a buf to the filedescriptor \a fd.
    \param T A vector where each position has all the suffix transitions directed to each state.
    \param i The integer of the current state.
    \param alpha The transition symbol.
    \param word The input string.
    \return A better state
*/
/*! \fn string FOGenerate(FactorOracle& States, int i, string v, float q)
    \brief Generates the Factor Oracle improvisation.
    \param i The integer of the current state.
    \param v The sequence v.
    \param q A float argument.
    \return The factor oracle improvisation
*/
/*! \fn void FactorOracleStart(FactorOracle& OracleRelations,string word)
    \brief Starts the process of the Factor Oracle generation .
    \param word The input string.
*/




using namespace std;
/** The class SingleTransition denotes the elements that belong to each transition
  */
template <class T>
class SingleTransition
{
public:
    int first_state_; /**< denotes the first state of the transition */
    int last_state_; /**< denotes the last state of the transition */
    T symbol_; /**< denotes the symbol (letter) of the transition */
};

/** The class State denotes the elements that belong to each state
 * state denotes de number of the state
 * vector <SingleTransition> transition is the vector where all forward links of the state are defined
 * suffix_transition denotes which is the suffix link of this state
 * lrs is the longest repeated subsequence of this state
 * */
template <class T>
class State
{
public:
    int state_; /*!< denotes the number of the state */
    vector <SingleTransition<T>> transition_; /*!< denotes the number of the state */
    int suffix_transition_;
    int lrs_ = 0;
    void singleTransitionResize(){
        transition_.resize(NUMBER_R);
    }
};

template <class T>
class FactorOracle
{
public:
    vector <State<T>> states_; /**< vector of all the states */
    vector <vector<int>> RevSuffix; /**< vector where each position has all the suffix transitions directed to each state */
    void AddLetter( int i, vector<T> word)
    {
        //! A normal member taking four arguments and returning no value.
        /*!
          \param i an integer argument.
          \param word a string argument.
        */
        T alpha = word[i-1];
        this->AddState(i-1);
        int statemplusone = i;
        this->AddTransition(i-1,i,alpha);
        k = this->states_[i-1].suffix_transition_; /*!< k = S[i-1] */
        cout << "statemplusone first: "<< statemplusone << endl;
        phi = i-1; /*!< phi_one = i-1 */
        int flag = 0, iter = 0;
        /**
         * while k > -1 and delta(k,p[i]) is undefined
         *      do delta(k, p[i]) <- i
         *      phi_one = k
         *      k = S[k]
         * */
        while (k > -1 && flag == 0)
        {
            while (iter < this->states_[k].transition_.size())
            {
                if (this->states_[k].transition_[iter].symbol_ == alpha)
                {
                    flag = 1;
                }
                iter++;
            }
            if (flag == 0)
            {
                this->AddTransition(k,statemplusone,alpha);
                phi = k;
                k = this->states_[k].suffix_transition_;
                iter = 0;
            }
        }
        if (k == -1)
        {
            this->states_[statemplusone].suffix_transition_ = 0;
            this->states_[statemplusone].lrs_ = 0;
        }
        else
        {
            flag = 0, iter = 0;
            if (this->states_[k].transition_[iter].symbol_ == alpha)
            {
                flag = 1;
                this->states_[statemplusone].suffix_transition_ = this->states_[k].transition_[iter].last_state_;
                this->states_[statemplusone].lrs_ = this->LengthCommonSuffix(phi, this->states_[statemplusone].suffix_transition_ -1) + 1;
            }
            while (iter < this->states_[k].transition_.size() && flag == 0)
            {
                if (this->states_[k].transition_[iter].symbol_ == alpha)
                {

                    this->states_[statemplusone].suffix_transition_ = this->states_[k].transition_[iter].last_state_;
                    this->states_[statemplusone].lrs_ = this->LengthCommonSuffix( phi, this->states_[statemplusone].suffix_transition_ -1) + 1;
                    flag = 1;
                }

                iter++;
            }


        }
        cout << "statemplusone: "<< statemplusone << endl;
        cout << "next: "<< this->states_[statemplusone].lrs_ - 1 << endl;
        T temp_word = word[statemplusone - this->states_[statemplusone].lrs_ - 1];
        k = this->FindBetter( statemplusone, temp_word, word);
        if (k != 0)
        {
            this->states_[statemplusone].lrs_ = this->states_[statemplusone].lrs_ + 1;
            this->states_[statemplusone].suffix_transition_ = k;
        }
        RevSuffix[this->states_[statemplusone].suffix_transition_].push_back(statemplusone);
        /*for (int f = 0; f < RevSuffix.size(); f++)
        {
            for (int p = 0; p < RevSuffix[f].size(); p++)
                cout << RevSuffix[f][p] << " ";
            cout << "\n";
        }*/
    };
    int LengthCommonSuffix(int phi_one, int phi_two)
    {
        if (phi_two == this->states_[phi_one].suffix_transition_)
            return this->states_[phi_one].lrs_;
        else
        {
            while (this->states_[phi_one].suffix_transition_!= this->states_[phi_two].suffix_transition_)
                phi_two = this->states_[phi_two].suffix_transition_;
        }
        if (this->states_[phi_one].lrs_ <= this->states_[phi_two].lrs_)
            return this->states_[phi_one].lrs_;
        else return this->states_[phi_two].lrs_;
    };
    int FindBetter(int i, T alpha, vector<T> word)
    {
        //! A normal member taking five arguments and returning an integer value.
        /*!
          \param RevSuffix a reference to a vector of vector of integers.
          \param i an integer argument.
          \param alpha a char argument.
          \param word a string argument.
          \return A better state
        */

        int len_t = this->RevSuffix[this->states_[i].suffix_transition_].size();
        int statei = this->states_[i].suffix_transition_;
        if (len_t == 0) return 0;
        sort(this->RevSuffix[statei].begin(), this->RevSuffix[statei].end());
        for (int j = 0; j < len_t; j++)
        {
            if (this->states_[this->RevSuffix[this->states_[i].suffix_transition_][j]].lrs_ == this->states_[i].lrs_ && word[this->RevSuffix[this->states_[i].suffix_transition_][j] - this->states_[i].lrs_ - 1] == alpha)
            {
                int out = RevSuffix[this->states_[i].suffix_transition_][j];
                return out;
            }

        }
        return 0;
    };
    vector<T> FOGenerate(int& i, vector<T> v, float q)
    {
        //! A normal member taking four arguments and returning a string value.
        /*!
          \param i an integer argument.
          \param v a string argument.
          \param q a float argument.
          \return The factor oracle improvisation
        */
        std::random_device rd;  ///Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); ///Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);
        float u = dis(gen);
        /// float u = (float)rand() / RAND_MAX;
        if (this->states_.size() == 2)
        {
            v.push_back(this->states_[0].transition_[0].symbol_);
        }
        else{
            if (u < q) //Preguntar si debe iniciar en 1 o en 0
            {
                i = i + 1;
                int len = this->states_.size();
                if (i >= len)
                    i = len - 1;
                T w = this->states_[i].transition_[0].symbol_;
                v.push_back(w);
                //string s(1,w);
                //v = v + s;
            }
            else
            {
                int lenSuffix = this->states_[this->states_[i].suffix_transition_].transition_.size() - 1;
                std::random_device rd;  ///Will be used to obtain a seed for the random number engine
                std::mt19937 gen(rd()); ///Standard mersenne_twister_engine seeded with rd()
                std::uniform_int_distribution<> dis_int(0, lenSuffix);
                int rand_alpha = dis_int(gen);
                T alpha = this->states_[this->states_[i].suffix_transition_].transition_[rand_alpha].symbol_;
                i = this->states_[this->states_[i].suffix_transition_].transition_[rand_alpha].last_state_;
                if (i == -1)
                {
                    i = 0;
                }
                v.push_back(alpha);
            }
        }
        return v;
    };
    void FactorOracleStart( vector<T> word)
    {
        //! A normal member taking one argument and returning no value.
        /*!
          \param word a string argument.
        */
        int len = word.size();
        this->states_.resize(len+1);
        //SingleTransition statezero; /*!< Create state 0 */
        this->states_[0].state_ = 0;
        this->states_[0].lrs_ = 0;
        this->states_[0].suffix_transition_ = -1; /*!< S[0] = -1 */
        this->RevSuffix.resize(len+1);
        if (len+1 != 1)
        {
            for (int i = 1; i <= len; i++)
            {
                /*!< for i <- 1 to m
                * do AddLetter(i)
                */
                this->AddLetter( i, word);
            }
        }
        else
        {
            this->AddTransition(0,0,'\0');
        }

        for (int i = 0; i < len+1; i++){

            cout << "STATE[" << i << "]:\n" << "LRS: "<< this->states_[i].lrs_ << "\n";
            cout << "Suffix: " << this->states_[i].suffix_transition_ << "\n";
            cout << "Transitions: " << "\n";
            for (int w = 0; w < this->states_[i].transition_.size(); w++)
            {
                cout << this->states_[i].transition_[w].first_state_ << " " << this->states_[i].transition_[w].last_state_ << " "  << this->states_[i].transition_[w].symbol_ << "\n";
            }
            cout << "\n";

        }


    };
    void AddState(int first_state)
    {
        this->states_[first_state].state_ = first_state;
    };
    void AddTransition(int first_state, int last_state, T symbol)
    {
        SingleTransition<T> transition_i;
        transition_i.first_state_ = first_state;
        transition_i.last_state_ = last_state;
        transition_i.symbol_ = symbol;
        this->states_[first_state].transition_.push_back(transition_i);
    };
    void CallGenerate(int len, float q)
    {
        vector<T> oracle = {};
        fo_iter = 1;
        // int q = 0;
        // cout << "Input the q value: ";
        // cin >> q;
        for (int x = 0; x < len; x++)
        {
            oracle = this->FOGenerate(fo_iter,oracle,q);
            if (fo_iter == len)
                fo_iter = len-1;
            for (int w = 0; w < oracle.size(); w++)
                cout << oracle[w] << " ";
            cout << endl;
        }

    };
    ;
};





#endif //FACTORORACLESTRING_FACTORORACLE_H
