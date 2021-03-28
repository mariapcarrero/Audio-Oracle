//
// Created by MARIA PAULA CARRERO on 3/20/21.
//

#ifndef FACTORORACLESTRING_AUDIOORACLEGIST_H
#define FACTORORACLESTRING_AUDIOORACLEGIST_H


#include <iostream>
#include <new>
#include <string>
#include <vector>
#include <variant>
#include <random>
#include <algorithm>
#include <cmath>
#include <marsyas/system/MarSystem.h>
#include <marsyas/system/MarSystemManager.h>
#include <map>
#define USE_ACCELERATE_FFT
#include "Gist.h"


#define NUMBER_R 10
#define RAND_MAX 0x7fffffff

/*! \file AudioOracle.h
    \brief A file that contains the definitions of the classes needed for the creation of a Factor Oracle.

    Three main classes: AudioOracle, State and SingleTransition.
*/
/*! \fn void AddFrame(AudioOracle& States, vector <vector<int>> &T, int i, string word)
    \brief Adds new transitions from state i-1 to state i.
    \param T A vector where each position has all the suffix transitions directed to each state.
    \param i The integer of the current state.
    \param word The input string.

*/
/*! \fn int LengthCommonSuffix(AudioOracle& States, int phi_one, int phi_two)
    \brief Finds the length of a common suffix ending at the position phi_one and phi_two by traversing the suffix links.
    \param phi_one The position of the state.
    \param phi_two The position of the state.
*/
/*! \fn int FindBetter(AudioOracle& States, vector <vector<int>> &T, int i, char alpha, string word)
    \brief Writes \a count bytes from \a buf to the filedescriptor \a fd.
    \param T A vector where each position has all the suffix transitions directed to each state.
    \param i The integer of the current state.
    \param alpha The transition symbol.
    \param word The input string.
    \return A better state
*/
/*! \fn string AOGenerate(AudioOracle& States, int i, string v, float q)
    \brief Generates the Factor Oracle improvisation.
    \param i The integer of the current state.
    \param v The sequence v.
    \param q A float argument.
    \return The factor oracle improvisation
*/
/*! \fn void AudioOracleStart(AudioOracle& OracleRelations,string word)
    \brief Starts the process of the Factor Oracle generation .
    \param word The input string.
*/




using namespace std;
using namespace Marsyas;
/** The class SingleTransition denotes the elements that belong to each transition
  */

class SingleTransitionGist
{
public:
    int first_state_; /**< denotes the first state of the transition */
    int last_state_; /**< denotes the last state of the transition */
    vector <double> vector_real_; /**< denotes the feature vector of the transition */
    int corresponding_state_;
    int starting_frame_;
    // double * vector_real_;
};

/** The class State denotes the elements that belong to each state
 * state denotes de number of the state
 * vector <SingleTransition> transition is the vector where all forward links of the state are defined
 * suffix_transition denotes which is the suffix link of this state
 * lrs is the longest repeated subsequence of this state
 * */
class StateGist
{
public:
    int state_; /*!< denotes the number of the state */
    vector <SingleTransitionGist> transition_; /*!< denotes the number of the state */
    int suffix_transition_;
    int lrs_ = 0;
    int starting_frame_ = 0;
    void singleTransitionResize(){
        transition_.resize(NUMBER_R);
    }
};

class FilteredTransitionGist
{
public:
    int current_lrs_;
    SingleTransitionGist current_transition_; /**< denotes the transition */
};


class AudioOracleGist
{
public:
    vector <StateGist> states_; /**< vector of all the states */
    vector <vector<int>> T; /**< vector where each position has all the suffix transitions directed to each state */
    vector <vector <mrs_real>> S;
    map <int, double*> feature_map;
    void AddFrame( int i, vector <double> vector_real, double threshold, int start_frame, int hop_size);
    void CreateState(int m);
    void AnalyseAudio(string sfName, int hop_size, string feature);
    int LengthCommonSuffix(int phi_one, int phi_two);
    void FindBetter(int i, double threshold, vector <double> vector_real);
    vector<int> AOGenerate(int i, int total_length, float q, int k);
    void GenerateAudio(int i, int total_length, float q, int k, int hop_size, int buffer_size, string input_filename, string output_filename);
    static vector<double> MakeWindow(int n);
    static double VectorDistance(double *first, double* last, double *first2);
    void FindBetter(vector <double> vector_real, int state_i_plus_one, int hop_size);
    void AddState(int first_state, int state, int start_frame);
    void AddTransition(int first_state, int last_state, vector <double> vector_real, int feature_state, int starting_frame);
    void AddInitialTransition();
    void CentroidFeatureExtraction(vector<vector<double>> audio_vector, int hop_size, string feature);
    void SpectrumFeatureExtraction(vector<vector<double>> audio_vector, int hop_size, string feature);
    void PowerSpectrumFeatureExtraction(vector<vector<double>> audio_vector, int hop_size, string feature);
    void MFCCFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature);
    void ChromaFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature);
    void RootMeanSquareFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature);
    void ZeroCrossingsFeatureExtraction(vector<vector<double>> audio_vector, int hop_size, string feature);
    void RolloffFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature);
    MarSystem* RealTimeInitialize(bool isInitialized);
    MarSystem* RealTimeStop(MarSystem* realAudio, bool stop);
};



#endif //FACTORORACLESTRING_AUDIOORACLEGIST_H
