//
// Created by MARIA PAULA CARRERO on 3/27/21.
//

#include "AudioOracleComplete.h"

#include <marsyas/system/MarSystem.h>
#include <marsyas/system/MarSystemManager.h>
#include <portaudio.h>
#include "../3rd-party/AudioFile.h"

#include <cmath>
#include <utility>
int pi_1, pi_2, k, fo_iter;

double AudioOracleComplete::VectorDistance(double *first, double* last, double *first2) {
    double ret = 0.0;
    while (first != last) {
        double dist = (*first++) - (*first2++);
        ret += dist * dist;
    }
    return ret > 0.0 ? sqrt(ret) : 0.0;
}

vector<double> AudioOracleComplete::MakeWindow(int n)
{
    vector<double> window;
    window.reserve(n);
    for(int i = 0; i < n; i++) window.push_back((0.5 * (1 - cos(2*M_PI*i/(n-1))))+ 0.00001);
    return window;
}

vector<int> AudioOracleComplete::AOGenerate(int i, int total_length, float q, int k)
{
    ///! A normal member taking four arguments and returning a string value.
    /*!
           \param i an integer argument.
           \param v a string argument.
           \param q a float argument.
           \return The factor oracle improvisation
    */
    vector<int> improvisation_vector;
    int iter = 0;
    for(iter = 0; iter < total_length; iter++)
    {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);
        float u = dis(gen);
        if (this->states_.size() == 2) {
            improvisation_vector.push_back(this->states_[0].state_);
        } else {
            if (u < q) //Preguntar si debe iniciar en 1 o en 0
            {
                int len = this->states_.size();
                if (i >= len - 1)
                {
                    i = len - 1; // estaba sacando una excepción porque el estado 103 era el último y no tenía starting frame. REVISAR EN EL FACTOR ORACLE
                    improvisation_vector.push_back(this->states_[i].state_);
                }
                else{
                    improvisation_vector.push_back(this->states_[i].transition_[0].last_state_);
                }
                i++;
            } else {
                if(i == states_.size()) i = i - 1;
                int lenSuffix = this->states_[this->states_[i].suffix_transition_].transition_.size() - 1;
                int rand_alpha = 0;
                if (lenSuffix == -1)
                {
                    improvisation_vector.push_back(this->states_[i].state_);
                    i++;
                }
                else{
                    std::random_device rd;  //Will be used to obtain a seed for the random number engine
                    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
                    std::uniform_int_distribution<> dis_int(0, lenSuffix);
                    rand_alpha = dis_int(gen);
                    improvisation_vector.push_back(this->states_[this->states_[i].suffix_transition_].transition_[rand_alpha].last_state_);
                }
                i = this->states_[this->states_[i].suffix_transition_].transition_[rand_alpha].last_state_;
                if (i == -1) i = 0;
            }
        }
    }
    return improvisation_vector;
};

void AudioOracleComplete::GenerateAudio(int i, int total_length, float q, int k_interal, int hop_size, int buffer_size, string input_filename, string output_filename)
{
    AudioFile<double> audioFile;
    audioFile.load(std::move(input_filename));
    AudioFile<double>::AudioBuffer buffer;
    AudioFile<double>::AudioBuffer window_buffer;
    AudioFile<double>::AudioBuffer complete_buffer;
    int automaton_size = this->states_.size();
    cout << automaton_size << endl;
    int repetitions = (automaton_size * hop_size);
    int numChannels = audioFile.getNumChannels();
    int j = 0;
    vector<vector<double>> buffer_matrix;
    vector<double> sample;
    while (j < repetitions) {
        int j_temp = j;
        sample = {};
        int temp_final = j_temp + buffer_size;
        while (j_temp < temp_final) {
            sample.push_back(audioFile.samples[0][j_temp]);
            j_temp++;
        }
        buffer_matrix.push_back(sample);
        j = j + hop_size;
    }
/*    for(int f = 0; f < total_length; f++){
        cout << "row: " << f << endl;
        for(int g = 0; g < buffer_size; g++)
            cout << buffer_matrix[f][g] << " ";
        cout << endl;
    }*/
    vector<int> improvisation = AOGenerate(i, total_length, q, k_interal);

    for(int f = 0; f < total_length; f++) {
        cout << improvisation[f] << " ";
    }
    cout << endl;
    // 2. Set to (e.g.) two channels
    buffer.resize(2);
    // repetitions = (total_length * buffer_size);
    repetitions = (total_length * hop_size);
    // 3. Set number of samples per channel
    buffer[0].resize(repetitions);
    buffer[1].resize(repetitions);

    // 2. Set to (e.g.) two channels
    complete_buffer.resize(2);


    // 3. Set number of samples per channel
    complete_buffer[0].resize(repetitions);
    complete_buffer[1].resize(repetitions);

    window_buffer.resize(2);
    window_buffer[0].resize(repetitions);
    window_buffer[1].resize(repetitions);

    vector<double> win = MakeWindow(buffer_size);
    cout << "win: " << endl;
    for(int f = 0; f < total_length; f++) {
        cout << win[f] << " ";
    }
    cout << endl << buffer_matrix[improvisation[0]].size() << endl;
    int iter = 0;
    int real_iter = 0;
    repetitions = (total_length * hop_size);
    while (iter < repetitions) {
        //z = this->states_[improvisation[real_iter]].starting_frame_;
        for(int z = 0; z < buffer_size; z++)
        {
            for (int channel = 0; channel < numChannels; channel++)
                buffer[channel][iter] = buffer[channel][iter] + (buffer_matrix[improvisation[real_iter]][z] * win[z]) + 0.00001;
            iter++;
        }
        if (iter < repetitions){
            iter = iter - (hop_size);
            real_iter++;
        }
    }
    iter = 0;


    while (iter < repetitions) {
        //z = this->states_[improvisation[real_iter]].starting_frame_;

        for(int z = 0; z < buffer_size; z++)
        {
            for (int channel = 0; channel < numChannels; channel++)
                window_buffer[channel][iter] = window_buffer[channel][iter] + win[z];
            iter++;
        }
        if (iter < repetitions){
            iter = iter - (hop_size);
        }
    }
    iter = 0;
    while (iter < repetitions) {
        //z = this->states_[improvisation[real_iter]].starting_frame_;

        for(int z = 0; z < buffer_size; z++)
        {
            for (int channel = 0; channel < numChannels; channel++)
                buffer[channel][iter] = buffer[channel][iter]/window_buffer[channel][iter];
            iter++;
        }
    }

    bool ok = audioFile.setAudioBuffer (buffer);
    // audioFile.setSampleRate (44100);
    cout << ok << endl;
    audioFile.save (std::move(output_filename), AudioFileFormat::Wave);
}

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
    int w = 0;
    for(int j = 0; j < numFrames; j++)
    {
        sample = {};
        int current_len = w + hop_size;
        while (w < current_len) {
            sample.push_back(audioFile.samples[0][w]);
            w++;
        }
        buffer_matrix.push_back(sample);
    }
    return buffer_matrix;
}


void AudioOracleComplete::AnalyseAudio(string sfName, int hop_size, string feature)
{
    auto *librarySubsystem = new LibrarySubsystem;
    auto *facade = new Facade(librarySubsystem);
    vector<vector<double>> audioFrame;
    audioFrame = ClientCodeFrames(facade,std::move(sfName),hop_size);
    this->AddInitialTransition();
    ClientCode(facade,this,audioFrame,hop_size,std::move(feature));
    int counter = this->states_.size();
    cout << "COUNTER IS:" << counter << endl;
    for (int w = 0; w < counter; w++)
    {
        cout << "STATE: " << w << endl;
        cout << "suffix: " << this->states_[w].suffix_transition_ << endl;
        cout << "start frame: " << this->states_[w].starting_frame_ << endl;
        for (auto & x : this->states_[w].transition_)
        {
            cout << "first state:" << x.first_state_ << endl << "second state: " << x.last_state_ << endl  << "corresponding state: " << x.corresponding_state_ << endl << "starting frame: " << x.starting_frame_ << endl;
        }
    }
    cout << endl;

    for (int w = 0; w < counter; w++)
    {
        cout << "STATE: " << w << endl;
        cout << "LRS: " << this->states_[w].lrs_ << endl;
        if (this->T[w].empty())
            cout << "empty" << endl;
        for (int x : this->T[w])
        {
            cout <<  x << endl;
        }

    }
}

void AudioOracleComplete::AddState(int first_state, int state, int start_frame){
    this->states_[first_state].suffix_transition_ = state;
    this->states_[first_state].lrs_ = state;
    this->states_[first_state].starting_frame_ = start_frame;
}


void AudioOracleComplete::CreateState(int m) {
    StateComplete newstate;
    newstate.state_ = m;
    this->states_.push_back(newstate);
    //cout << "state: " << this->states_[m].state_ << endl;
}
void AudioOracleComplete::AddTransition(int first_state, int last_state, vector <double> vector_real, int feature_state, int starting_frame) {
    SingleTransitionComplete transition_i;
    transition_i.first_state_ = first_state;
    transition_i.last_state_ = last_state;
    transition_i.vector_real_ = std::move(vector_real);
    transition_i.corresponding_state_ = feature_state;
    transition_i.starting_frame_ = starting_frame;
    this->states_[first_state].transition_.push_back(transition_i);
}

void AudioOracleComplete::AddInitialTransition()
{
    this->CreateState(0);
    this->states_[0].state_ = 0;
    this->states_[0].lrs_ = 0;
    this->states_[0].suffix_transition_ = -1;
    this->states_[0].starting_frame_ = 0;
    this->T.push_back({});
}

int AudioOracleComplete::LengthCommonSuffix( int pi_1, int pi_2)
{
    if (pi_2 == this->states_[pi_1].suffix_transition_) return this->states_[pi_1].lrs_;
    else
    {
        while (this->states_[pi_1].suffix_transition_ != this->states_[pi_2].suffix_transition_) pi_2 = this->states_[pi_2].suffix_transition_;
    }
    return min(this->states_[pi_1].lrs_,this->states_[pi_2].lrs_) + 1;
}

void AudioOracleComplete::AddFrame(int i, vector <double> vector_real, double threshold, int start_frame, int hop_size) {
    //! A normal member taking four arguments and returning no value.
    /*!
      \param i an integer argument.
      \param vector_real a vector of mrs_real (aka double) values.
      \param threshold a double value which determines the level of similarity between vectors.
    */
    cout << "inside AddFrame, state: " << i << endl;
    this->CreateState(i + 1);
    int state_i_plus_one = i + 1;
    this->T.emplace_back();
    this->AddTransition(i, state_i_plus_one, vector_real, i, (state_i_plus_one + 1) * hop_size);
    k = this->states_[i].suffix_transition_; // < k = S[i]
    this->AddState(state_i_plus_one, 0, start_frame);
/*    this->states_[state_i_plus_one].suffix_transition_ = 0;
    this->states_[state_i_plus_one].lrs_ = 0;
    this->states_[state_i_plus_one].starting_frame_ = start_frame;*/
    pi_1 = i; //<  phi_one = i
    int flag = 0, iter = 0, counter = 0, s;
    while (k > -1 && flag == 0) {
        iter = 0;
        while (iter < this->states_[k].transition_.size() && k > -1) {
            double *v2_pointer = &(this->states_[k].transition_[iter].vector_real_[0]);
            double *v1_pointer = &(vector_real[0]);
            iter++;
            double euclidean_result = VectorDistance(v1_pointer, (v1_pointer + (hop_size - 1)), v2_pointer);
            cout << "eucr: " << euclidean_result << endl;
            if (euclidean_result < threshold) {
                AddTransition(k, state_i_plus_one, vector_real, i, (state_i_plus_one + 1) * hop_size);
                pi_1 = k;
                k = this->states_[k].suffix_transition_;
            }
            if (iter >= this->states_[k].transition_.size())
                flag = 1;
        }
        if (iter == this->states_[k].transition_.size() && flag == 0) {
            flag = 1;
        }
    }
    if (k == -1) {

        this->states_[state_i_plus_one].suffix_transition_ = 0;
        this->states_[state_i_plus_one].lrs_ = 0;
    } else {
        FindBetter(vector_real, state_i_plus_one, hop_size);
        }
        this->T[this->states_[state_i_plus_one].suffix_transition_].push_back(state_i_plus_one);
}

void AudioOracleComplete::FindBetter(vector <double> vector_real, int state_i_plus_one, int hop_size)
{
    int s = 0;
    int flag = 0, iter = 0;
    double min_distance = INFINITY;
    cout << "INSIDE FINDBETTER" << endl;
    while (iter < this->states_[k].transition_.size()) {

        double *v1_pointer = &(vector_real[0]);
        double *v2_pointer = &(this->states_[k].transition_[iter].vector_real_[0]);
        cout << "inside last: " << *v1_pointer << " " << *v2_pointer << endl;
        double euclidean_result = VectorDistance(v1_pointer, (v1_pointer + 1), v2_pointer);

        if (euclidean_result < min_distance) {
            s = this->states_[k].transition_[iter].last_state_;
            //   cout << "s prev: " << s << " k: " << k << endl;
            cout << "min: " << min_distance << " euc r: " << euclidean_result <<  endl;
            min_distance = euclidean_result;
        }
        iter++;
    }
    this->states_[state_i_plus_one].suffix_transition_ = s;
    this->states_[state_i_plus_one].lrs_ = this->LengthCommonSuffix(pi_1,this->states_[state_i_plus_one].suffix_transition_ - 1);

}