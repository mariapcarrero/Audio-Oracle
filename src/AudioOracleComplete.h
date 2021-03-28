//
// Created by MARIA PAULA CARRERO on 3/27/21.
//

#ifndef FACTORORACLESTRING_AUDIOORACLECOMPLETE_H
#define FACTORORACLESTRING_AUDIOORACLECOMPLETE_H

#include <iostream>
#include <new>
#include <string>
#include <utility>
#include <vector>
#include <variant>
#include <random>
#include <algorithm>
#include <cmath>
#include <map>
#define USE_ACCELERATE_FFT
#include "Gist.h"
#include "../3rd-party/AudioFile.h"



#define NUMBER_R 10
#define RAND_MAX 0x7fffffff
#include <iostream>
using namespace std;


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


/** The class SingleTransition denotes the elements that belong to each transition
  */

class SingleTransitionComplete
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
class StateComplete
{
public:
    int state_; /*!< denotes the number of the state */
    vector <SingleTransitionComplete> transition_; /*!< denotes the number of the state */
    int suffix_transition_;
    int lrs_ = 0;
    int starting_frame_ = 0;
    void singleTransitionResize(){
        transition_.resize(NUMBER_R);
    }
};

class FilteredTransitionComplete
{
public:
    int current_lrs_;
    SingleTransitionComplete current_transition_; /**< denotes the transition */
};


class AudioOracleComplete
{
public:
    vector <StateComplete> states_; /**< vector of all the states */
    vector <vector<int>> T; /**< vector where each position has all the suffix transitions directed to each state */
    vector <vector <double>> S;
    map <int, double*> feature_map;
    void AddFrame( int i, vector <double> vector_real, double threshold, int start_frame, int hop_size);
    void CreateState(int m);
    void AnalyseAudio(string sfName, int hop_size, string feature);
    int LengthCommonSuffix(int phi_one, int phi_two);
    vector<int> AOGenerate(int i, int total_length, float q, int k);
    void GenerateAudio(int i, int total_length, float q, int k_interal, int hop_size, int buffer_size, string input_filename, string output_filename);
    static vector<double> MakeWindow(int n);
    static double VectorDistance(double *first, double* last, double *first2);
    void FindBetter(vector <double> vector_real, int state_i_plus_one, int hop_size);
    void AddState(int first_state, int state, int start_frame);
    void AddTransition(int first_state, int last_state, vector <double> vector_real, int feature_state, int starting_frame);
    void AddInitialTransition();
};

/**
 * The Subsystem can accept requests either from the facade or client directly.
 * In any case, to the Subsystem, the Facade is yet another client, and it's not
 * a part of the Subsystem.
 */
class LibrarySubsystem {
public:
    static void ZeroCrossingsFeatureExtraction(AudioOracleComplete * audio_oracle, vector<vector<double>> audio_vector,int hop_size) {
        vector <vector <double>> vector_real;
        cout << "INSIDE ZCR F" << endl;
        int numFrames = audio_vector.size();
        cout << "numFrames: " << numFrames << endl;
        int counter = 0;
        int sampleRate = 44100;
        vector<double> temp_vector;
        temp_vector.reserve(1);
        for(int i = 0; i < numFrames; i++)
        {
            temp_vector = {};
            Gist<double> gist (hop_size, sampleRate);
            gist.processAudioFrame(audio_vector[i]);
            double zcr = gist.zeroCrossingRate();
            cout << "zcr: " << zcr << endl;
            temp_vector.push_back(zcr);
            double * map_pointer = &(temp_vector[0]);
            audio_oracle->feature_map.insert({counter, map_pointer});
            audio_oracle->AddFrame(counter, temp_vector, 250 , i * hop_size, hop_size);
            counter = counter +1;
        }
    }
    static void RootMeanSquareFeatureExtraction(AudioOracleComplete * audio_oracle, vector<vector<double>> audio_vector,int hop_size) {
        vector <vector <double>> vector_real;
        cout << "INSIDE RMS F" << endl;
        int numFrames = audio_vector.size();
        cout << "numFrames: " << numFrames << endl;
        int counter = 0;
        int frameSize = hop_size;
        int sampleRate = 44100;
        vector<double> temp_vector;
        temp_vector.reserve(1);
        auto start = chrono::steady_clock::now();
        for(int i = 0; i < numFrames; i++)
        {
            temp_vector = {};
            Gist<double> gist (frameSize, sampleRate);
            gist.processAudioFrame(audio_vector[i]);
            double rms = gist.rootMeanSquare();
            cout << "rms: " << rms << endl;
            temp_vector.push_back(rms);
            double * map_pointer = &(temp_vector[0]);
            audio_oracle->feature_map.insert({counter, map_pointer});
            audio_oracle->AddFrame(counter, temp_vector, 0.1 , i * hop_size, hop_size);
            counter = counter +1;
        }
        auto end = chrono::steady_clock::now();
        cout << "rms_final: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
    }
    static void MFCCFeatureExtraction(AudioOracleComplete * audio_oracle, vector<vector<double>> audio_vector,int hop_size) {
        vector <vector <double>> vector_real;
        cout << "INSIDE MFCC F" << endl;
        int numFrames = audio_vector.size();
        cout << "numFrames: " << numFrames << endl;
        int counter = 0;
        int frameSize = hop_size;
        int sampleRate = 44100;
        vector<double> temp_vector;
        for(int i = 0; i < numFrames; i++)
        {
            temp_vector = {};
            Gist<double> gist (frameSize, sampleRate);
            gist.processAudioFrame(audio_vector[i]);
            const std::vector<double>& mfcc = gist.getMelFrequencyCepstralCoefficients();
            vector<double> mfcc_temp = mfcc;
            for (double j : mfcc_temp) cout << j << " ";
            cout << endl;
            double * map_pointer = &(mfcc_temp[0]);
            audio_oracle->feature_map.insert({counter, map_pointer});
            audio_oracle->AddFrame(counter, mfcc_temp, 400 , i * hop_size, hop_size);
            counter = counter +1;
        }
    }
    static void PitchFeatureExtraction(AudioOracleComplete * audio_oracle, vector<vector<double>> audio_vector,int hop_size) {
        vector <vector <double>> vector_real;
        cout << "INSIDE PITCH F" << endl;
        int numFrames = audio_vector.size();
        cout << "numFrames: " << numFrames << endl;
        int counter = 0;
        int frameSize = hop_size;
        int sampleRate = 44100;
        vector<double> temp_vector;
        temp_vector.reserve(1);
        auto start = chrono::steady_clock::now();
        for(int i = 0; i < numFrames; i++)
        {
            temp_vector = {};
            Gist<double> gist (frameSize, sampleRate);
            gist.processAudioFrame(audio_vector[i]);
            double pitch = gist.pitch();
            //cout << "pitch: " << pitch << endl;
            temp_vector.push_back(pitch);
            double * map_pointer = &(temp_vector[0]);
            audio_oracle->feature_map.insert({counter, map_pointer});
            audio_oracle->AddFrame(counter, temp_vector, 50 , i * hop_size, hop_size);
            counter = counter +1;
        }
        auto end = chrono::steady_clock::now();
        cout << "pitch_final: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;

    }
    typedef void (*FnPtr)(AudioOracleComplete * audio_oracle, vector<vector<double>> audio_vector,int hop_size);
    map<string, FnPtr> functionMapper = {
            {"ZeroCrossings",ZeroCrossingsFeatureExtraction},
            {"RootMeanSquare",RootMeanSquareFeatureExtraction},
            {"MFCC",MFCCFeatureExtraction},
            {"Pitch",PitchFeatureExtraction}
    };
    // ...
    string OperationN() const {
        return "LibrarySubsystem: Go!\n";
    }
};
/**
 * Some facades can work with multiple subsystems at the same time.
 */
class Subsystem2 {
public:

    vector<vector<double>> GenerateAudioFrames(string input_filename, int hop_size)
    {
        AudioFile<double> audioFile;
        audioFile.load(std::move(input_filename));
        int numSamples = audioFile.getNumSamplesPerChannel();
        int numFrames = numSamples/hop_size;
        vector<double> sample;
        sample.reserve(hop_size);
        vector<vector<double>> buffer_matrix;
        buffer_matrix.reserve(numFrames);
        int k = 0;
        for(int j = 0; j < numFrames; j++)
        {
            sample = {};
            int current_len = k + hop_size;
            while (k < current_len) {
                sample.push_back(audioFile.samples[0][k]);
                k++;
            }
            buffer_matrix.push_back(sample);
        }
        return buffer_matrix;
    }
    // ...
    string OperationZ() const {
        return "Subsystem2: Fire!\n";
    }
};

/**
 * The Facade class provides a simple interface to the complex logic of one or
 * several subsystems. The Facade delegates the client requests to the
 * appropriate objects within the subsystem. The Facade is also responsible for
 * managing their lifecycle. All of this shields the client from the undesired
 * complexity of the subsystem.
 */
class Facade {
protected:
    LibrarySubsystem *librarySubsystem_;
    Subsystem2 *subsystem2_;
    /**
     * Depending on your application's needs, you can provide the Facade with
     * existing subsystem objects or force the Facade to create them on its own.
     */
public:
    /**
     * In this case we will delegate the memory ownership to Facade Class
     */
    Facade(
            LibrarySubsystem *librarySubsystem = nullptr,
            Subsystem2 *subsystem2 = nullptr) {
        this->librarySubsystem_ = librarySubsystem ?: new LibrarySubsystem;
        this->subsystem2_ = subsystem2 ?: new Subsystem2;
    }
    ~Facade() {
        delete librarySubsystem_;
        delete subsystem2_;
    }
    /**
     * The Facade's methods are convenient shortcuts to the sophisticated
     * functionality of the subsystems. However, clients get only to a fraction of
     * a subsystem's capabilities.
     */
    std::string Operation(AudioOracleComplete * audio_oracle, vector<vector<double>> audio_vector,int hop_size, const string& feature) {
        string result = "Facade initializes subsystems:\n";
        this->librarySubsystem_->functionMapper[feature](audio_oracle, std::move(audio_vector),hop_size);

        return result;
    }
    vector<vector<double>> OperationGenerateFrames(string input_filename, int hop_size) {
        return this->subsystem2_->GenerateAudioFrames(std::move(input_filename), hop_size);
    }
};

/**
 * The client code works with complex subsystems through a simple interface
 * provided by the Facade. When a facade manages the lifecycle of the subsystem,
 * the client might not even know about the existence of the subsystem. This
 * approach lets you keep the complexity under control.
 */
void ClientCode(Facade *facade, AudioOracleComplete * audio_oracle, vector<vector<double>> audio_vector,int hop_size, string feature) {
    // ...
    cout << facade->Operation(audio_oracle,std::move(audio_vector),hop_size,feature);
    // ...
}

vector<vector<double>> ClientCodeFrames(Facade *facade,string input_filename, int hop_size)
{
    return facade->OperationGenerateFrames(std::move(input_filename),hop_size);
}
/**
 * The client code may have some of the subsystem's objects already created. In
 * this case, it might be worthwhile to initialize the Facade with these objects
 * instead of letting the Facade create new instances.
 */

int main() {
    AudioOracleComplete audio_oracle;
    audio_oracle.AnalyseAudio("/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/driverslicense.wav",8192, "MFCC");
    audio_oracle.GenerateAudio(1000,1200,0.8,0,8192,16384,"/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/driverslicense.wav","/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/3rd-party/audios/driversMFCC.wav");

    return 0;
}


#endif //FACTORORACLESTRING_AUDIOORACLECOMPLETE_H
