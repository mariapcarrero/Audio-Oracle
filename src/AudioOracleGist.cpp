//
// Created by MARIA PAULA CARRERO on 3/20/21.
//

#include "AudioOracleGist.h"

#include <marsyas/system/MarSystem.h>
#include <marsyas/system/MarSystemManager.h>
#include <portaudio.h>
#include "../3rd-party/AudioFile.h"

#include <cmath>
int pi_1, pi_2, k, fo_iter;

double AudioOracleGist::VectorDistance(double *first, double* last, double *first2) {
    double ret = 0.0;
    while (first != last) {
        double dist = (*first++) - (*first2++);
        ret += dist * dist;
    }
    return ret > 0.0 ? sqrt(ret) : 0.0;
}

vector<double> AudioOracleGist::MakeWindow(int n)
{
    vector<double> window;
    window.reserve(n);
    for(int i = 0; i < n; i++) window.push_back((0.5 * (1 - cos(2*M_PI*i/(n-1))))+ 0.00001);
    return window;
}

vector<int> AudioOracleGist::AOGenerate(int i, int total_length, float q, int k)
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

void AudioOracleGist::GenerateAudio(int i, int total_length, float q, int k, int hop_size, int buffer_size, string input_filename, string output_filename)
{
    AudioFile<double> audioFile;
    audioFile.load(input_filename);
    AudioFile<double>::AudioBuffer buffer;
    AudioFile<double>::AudioBuffer window_buffer;
    AudioFile<double>::AudioBuffer complete_buffer;
    int automaton_size = this->states_.size();
    cout << automaton_size << endl;
    int numSamples = audioFile.getNumSamplesPerChannel();
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
    vector<int> improvisation = AOGenerate(i, total_length, q, k);

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
    int w = 0;
    // int z = 0;
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
    audioFile.save (output_filename, AudioFileFormat::Wave);
}

vector<vector<double>> GenerateAudioFrames(string input_filename, int start_frame, int hop_size)
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


void AudioOracleGist::AnalyseAudio(string sfName, int hop_size, string feature)
{
    int frameSize = hop_size;
    int sampleRate = 44100;
    auto start = chrono::steady_clock::now();
    Gist<double> gist (frameSize, sampleRate);
    //vector<double> audioFrame;
    vector<vector<double>> audioFrame = GenerateAudioFrames(sfName,0,hop_size);
    auto end = chrono::steady_clock::now();
    cout << "gen: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
    cout << "len: " << audioFrame.size() << endl;
    cout << "int_len: " << audioFrame[0].size() << endl;
    this->AddInitialTransition();
    if(feature == "centroid")
    {
        cout << "centroid" << endl;
        this->CentroidFeatureExtraction(audioFrame,hop_size,feature);
    }
    if(feature == "spectrum")
    {
        this->SpectrumFeatureExtraction(audioFrame,hop_size,feature);
    }
    if(feature == "mfcc")
    {
        this->MFCCFeatureExtraction(audioFrame,hop_size,feature);
    }
    if(feature == "chroma")
    {
        this->ChromaFeatureExtraction(audioFrame,hop_size,feature);
    }
    if(feature == "rms")
    {
        cout << "rms" << endl;
        this->RootMeanSquareFeatureExtraction(audioFrame,hop_size,feature);
    }
    if(feature == "zeroCrossings")
    {
        cout << "zero crossings" << endl;
        this->ZeroCrossingsFeatureExtraction(audioFrame,hop_size,feature);
    }
    if(feature == "rolloff")
    {
        cout << "rolloff" << endl;
        this->RolloffFeatureExtraction(audioFrame,hop_size,feature);
    }
    int counter = this->states_.size();
    cout << "COUNTER IS:" << counter << endl;
    for (int w = 0; w < counter; w++)
    {
        cout << "STATE: " << w << endl;
        cout << "suffix: " << this->states_[w].suffix_transition_ << endl;
        cout << "start frame: " << this->states_[w].starting_frame_ << endl;
        for (int x = 0; x < this->states_[w].transition_.size(); x++)
        {
            cout << "first state:" << this->states_[w].transition_[x].first_state_ << endl << "second state: " << this->states_[w].transition_[x].last_state_ << endl  << "corresponding state: " << this->states_[w].transition_[x].corresponding_state_ << endl << "starting frame: " << this->states_[w].transition_[x].starting_frame_ << endl;
        }

    }
    cout << endl;

    for (int w = 0; w < counter; w++)
    {
        cout << "STATE: " << w << endl;
        cout << "LRS: " << this->states_[w].lrs_ << endl;
        if (this->T[w].empty())
            cout << "empty" << endl;
        for (int x = 0; x < this->T[w].size(); x++)
        {
            cout <<  this->T[w][x] << endl;
        }

    }
}

void AudioOracleGist::AddState(int first_state, int state, int start_frame){
    this->states_[first_state].suffix_transition_ = state;
    this->states_[first_state].lrs_ = state;
    this->states_[first_state].starting_frame_ = start_frame;
}


void AudioOracleGist::CreateState(int m) {
    StateGist newstate;
    newstate.state_ = m;
    this->states_.push_back(newstate);
    //cout << "state: " << this->states_[m].state_ << endl;
}
void AudioOracleGist::AddTransition(int first_state, int last_state, vector <double> vector_real, int feature_state, int starting_frame) {
    SingleTransitionGist transition_i;
    transition_i.first_state_ = first_state;
    transition_i.last_state_ = last_state;
    transition_i.vector_real_ = vector_real;
    transition_i.corresponding_state_ = feature_state;
    transition_i.starting_frame_ = starting_frame;
    this->states_[first_state].transition_.push_back(transition_i);
}

void AudioOracleGist::AddInitialTransition()
{
    this->CreateState(0);
    this->states_[0].state_ = 0;
    this->states_[0].lrs_ = 0;
    this->states_[0].suffix_transition_ = -1;
    this->states_[0].starting_frame_ = 0;
    this->T.push_back({});
}

void AudioOracleGist::CentroidFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature)
{
    vector <vector <double>> vector_real;
    cout << "INSIDE CENTROID " << endl;
    int numFrames = audio_vector.size();
    cout << "numFrames: " << numFrames << endl;
    int counter = 0;
    int frameSize = hop_size;
    int sampleRate = 44100;
    vector<double> temp_vector;
    temp_vector.reserve(1);
    for(int i = 0; i < numFrames; i++)
    {
        temp_vector = {};
        Gist<double> gist (frameSize, sampleRate);
        gist.processAudioFrame(audio_vector[i]);
        double specCent = gist.spectralCentroid();
        cout << "specCent: " << specCent << endl;
        temp_vector.push_back(specCent);
        double * map_pointer = &(temp_vector[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, temp_vector, 200 , i * hop_size, hop_size);
        counter = counter +1;
    }
}

/*

void AudioOracleGist::CentroidFeatureExtraction(MarSystem *pnet, int hop_size, string feature)
{
    vector <vector <double>> vector_real;
    cout << "INSIDE CENTROID " << endl;
    int counter = 0;
    while ( pnet->getctrl("SoundFileSource/src/mrs_bool/hasData")->to<mrs_bool>() )
    {
        pnet->tick();
        const realvec& processedData = pnet->getctrl("Centroid/cntd/mrs_realvec/processedData")->to<mrs_realvec>();
        Marsyas::mrs_real * real_pointer;
        real_pointer = processedData.getData();
        vector <Marsyas::mrs_real> temp_vector;
        cout << "realvec: ";
        for (int i = 0; i< hop_size; i++) cout << *(real_pointer + i) << " ";
        cout << endl;
        cout << "realp: " << *real_pointer << endl;
        for (int temp_counter = 0; temp_counter < hop_size; temp_counter ++ ) temp_vector.push_back(*(real_pointer+temp_counter));
        double * map_pointer = &(temp_vector[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, temp_vector, 15 , pnet->getctrl("SoundFileSource/src/mrs_natural/pos")->to<mrs_natural>(), hop_size);
        counter = counter +1;
    }
}
*/

void AudioOracleGist::ChromaFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature)
{
    vector <vector <double>> vector_real;
    cout << "INSIDE CENTROID " << endl;
    int numFrames = audio_vector.size();
    int counter = 0;
    int frameSize = hop_size;
    int sampleRate = 44100;
    vector<double> temp_vector;
    temp_vector.reserve(1);
    for(int i = 0; i < numFrames; i++)
    {
        temp_vector = {};
        Gist<double> gist (frameSize, sampleRate);
        gist.processAudioFrame(audio_vector[0]);
        double specCent = gist.spectralCentroid();
/*        cout << "realvec: ";
        for (int i = 0; i< hop_size; i++) cout << *(real_pointer + i) << " ";
        cout << endl;*/

        temp_vector.push_back(specCent);
        double * map_pointer = &(temp_vector[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, temp_vector, 15 , i * hop_size, hop_size);
        counter = counter +1;
    }
}

void AudioOracleGist::RolloffFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature)
{
    vector <vector <double>> vector_real;
    cout << "INSIDE CENTROID " << endl;
    int numFrames = audio_vector.size();
    int counter = 0;
    int frameSize = hop_size;
    int sampleRate = 44100;
    vector<double> temp_vector;
    temp_vector.reserve(1);
    for(int i = 0; i < numFrames; i++)
    {
        Gist<double> gist (frameSize, sampleRate);
        gist.processAudioFrame(audio_vector[0]);
        double specCent = gist.spectralCentroid();
/*        cout << "realvec: ";
        for (int i = 0; i< hop_size; i++) cout << *(real_pointer + i) << " ";
        cout << endl;*/

        temp_vector.push_back(specCent);
        double * map_pointer = &(temp_vector[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, temp_vector, 15 , i * hop_size, hop_size);
        counter = counter +1;
    }
}
void AudioOracleGist::SpectrumFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature)
{
    vector <vector <double>> vector_real;
    cout << "INSIDE CENTROID " << endl;
    int numFrames = audio_vector.size();
    int counter = 0;
    int frameSize = hop_size;
    int sampleRate = 44100;
    vector<double> temp_vector;
    temp_vector.reserve(1);
    for(int i = 0; i < numFrames; i++)
    {
        Gist<double> gist (frameSize, sampleRate);
        gist.processAudioFrame(audio_vector[0]);
        double specCent = gist.spectralCentroid();
/*        cout << "realvec: ";
        for (int i = 0; i< hop_size; i++) cout << *(real_pointer + i) << " ";
        cout << endl;*/

        temp_vector.push_back(specCent);
        double * map_pointer = &(temp_vector[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, temp_vector, 15 , i * hop_size, hop_size);
        counter = counter +1;
    }
}

void AudioOracleGist::PowerSpectrumFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature)
{
    vector <vector <double>> vector_real;
    cout << "INSIDE CENTROID " << endl;
    int numFrames = audio_vector.size();
    int counter = 0;
    int frameSize = hop_size;
    int sampleRate = 44100;
    vector<double> temp_vector;
    temp_vector.reserve(1);
    for(int i = 0; i < numFrames; i++)
    {
        Gist<double> gist (frameSize, sampleRate);
        gist.processAudioFrame(audio_vector[0]);
        double specCent = gist.spectralCentroid();
/*        cout << "realvec: ";
        for (int i = 0; i< hop_size; i++) cout << *(real_pointer + i) << " ";
        cout << endl;*/

        temp_vector.push_back(specCent);
        double * map_pointer = &(temp_vector[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, temp_vector, 15 , i * hop_size, hop_size);
        counter = counter +1;
    }
}

void AudioOracleGist::MFCCFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature)
{
    vector <vector <double>> vector_real;
    cout << "INSIDE ZCR " << endl;
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
        // cout << "rms: " << zcr << endl;

        for (double j : mfcc) cout << j << " ";
        cout << endl;

        vector<double> mfcc_temp = mfcc;

        for (double j : mfcc_temp) cout << j << " ";
        cout << endl;

        double * map_pointer = &(mfcc_temp[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, mfcc_temp, 400 , i * hop_size, hop_size);
        counter = counter +1;
    }
}

void AudioOracleGist::RootMeanSquareFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature)
{
    vector <vector <double>> vector_real;
    cout << "INSIDE RMS " << endl;
    int numFrames = audio_vector.size();
    cout << "numFrames: " << numFrames << endl;
    int counter = 0;
    int frameSize = hop_size;
    int sampleRate = 44100;
    vector<double> temp_vector;
    temp_vector.reserve(1);
    for(int i = 0; i < numFrames; i++)
    {
        temp_vector = {};
        Gist<double> gist (frameSize, sampleRate);
        gist.processAudioFrame(audio_vector[i]);
        double rms = gist.rootMeanSquare();
        cout << "rms: " << rms << endl;
        /*for (int i = 0; i< hop_size; i++) cout << *(real_pointer + i) << " ";
        cout << endl;*/

        temp_vector.push_back(rms);
        double * map_pointer = &(temp_vector[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, temp_vector, 0.1 , i * hop_size, hop_size);
        counter = counter +1;
    }
}

void AudioOracleGist::ZeroCrossingsFeatureExtraction(vector<vector<double>> audio_vector,int hop_size, string feature)
{
    vector <vector <double>> vector_real;
    cout << "INSIDE ZCR " << endl;
    int numFrames = audio_vector.size();
    cout << "numFrames: " << numFrames << endl;
    int counter = 0;
    int frameSize = hop_size;
    int sampleRate = 44100;
    vector<double> temp_vector;
    temp_vector.reserve(1);
    for(int i = 0; i < numFrames; i++)
    {
        temp_vector = {};
        Gist<double> gist (frameSize, sampleRate);
        gist.processAudioFrame(audio_vector[i]);
        double zcr = gist.zeroCrossingRate();
        cout << "rms: " << zcr << endl;
        /*for (int i = 0; i< hop_size; i++) cout << *(real_pointer + i) << " ";
        cout << endl;*/

        temp_vector.push_back(zcr);
        double * map_pointer = &(temp_vector[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, temp_vector, 0.1 , i * hop_size, hop_size);
        counter = counter +1;
    }
}/*
void AudioOracleGist::FindBetter(int state_i_plus_one, double threshold, vector <double> vector_real)
{
    //! A normal member taking five arguments and returning an integer value.
    *//*!
      \param T a reference to a vector of vector of integers.
      \param i an integer argument.
      \param alpha a char argument.
      \param word a string argument.
      \return A better state
    *//*

    int iter = 0;
    double min_distance = INFINITY;
    vector <FilteredTransitionGist> filtered_transitions;
    while (iter < this->states_[k].transition_.size()) {
        double *v1_pointer = &(vector_real[0]);
        double *v2_pointer = &(this->states_[k].transition_[iter].vector_real_[0]);
        // cout << "inside lst: " << *v1_pointer << " " << *v2_pointer << endl;
        double euclidean_result = VectorDistance(v1_pointer, (v1_pointer + 4095), v2_pointer);
        // cout << "euc result1: " << euclidean_result << endl;
        if (euclidean_result < threshold) {
            //  cout << "inside euc res " << endl;
            FilteredTransitionGist current_filtered_trans;
            current_filtered_trans.current_transition_ = this->states_[k].transition_[iter];
            current_filtered_trans.current_lrs_ = this->states_[this->states_[k].transition_[iter].last_state_].lrs_;
            filtered_transitions.push_back(current_filtered_trans);
        }
        iter++;
    }
    typedef std::function<bool(FilteredTransitionGist transition_1, FilteredTransitionGist transition_2)> Comparator;
    // Defining a lambda function to compare two lrs
    Comparator compFunctor =
            [](FilteredTransitionGist transition_1, FilteredTransitionGist transition_2)
            {
                return transition_1.current_lrs_ < transition_2.current_lrs_;
            };
    sort(filtered_transitions.begin(),filtered_transitions.end(), compFunctor);
    for (int w = 0; w < filtered_transitions.size(); w++)
    {
        this->states_[state_i_plus_one].suffix_transition_ = filtered_transitions[w].current_transition_.last_state_; //preguntar a jaime
        this->T[filtered_transitions[w].current_transition_.last_state_].push_back(state_i_plus_one);
    }

}*/
int AudioOracleGist::LengthCommonSuffix( int pi_1, int pi_2)
{
    if (pi_2 == this->states_[pi_1].suffix_transition_) return this->states_[pi_1].lrs_;
    else
    {
        while (this->states_[pi_1].suffix_transition_ != this->states_[pi_2].suffix_transition_) pi_2 = this->states_[pi_2].suffix_transition_;
    }
    return min(this->states_[pi_1].lrs_,this->states_[pi_2].lrs_) + 1;
}

void AudioOracleGist::AddFrame(int i, vector <double> vector_real, double threshold, int start_frame, int hop_size) {
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
    this->AddTransition(i, state_i_plus_one, vector_real,i,(state_i_plus_one + 1) * hop_size);
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
            double euclidean_result = VectorDistance(v1_pointer, (v1_pointer + (hop_size-1)), v2_pointer);
            cout << "eucr: " << euclidean_result << endl;
            if (euclidean_result < threshold) {
                AddTransition(k, state_i_plus_one, vector_real,i,(state_i_plus_one + 1) * hop_size);
                pi_1 = k;
                k = this->states_[k].suffix_transition_;
            }
            if (iter >= this->states_[k].transition_.size())
                flag = 1;
        }
        if (iter == this->states_[k].transition_.size() && flag == 0)
        {
            flag = 1;
        }
    }
    if (k == -1) {

        this->states_[state_i_plus_one].suffix_transition_ = 0;
        this->states_[state_i_plus_one].lrs_ = 0;
    }
    else {
        FindBetter(vector_real,state_i_plus_one,hop_size);
        /*s = 0;
        flag = 0, iter = 0;
        double min_distance = INFINITY;
        cout << "INSIDE FINDBETTER" << endl;
        while (iter < this->states_[k].transition_.size()) {
            double *v1_pointer = &(vector_real[0]);
            double *v2_pointer = &(this->states_[k].transition_[iter].vector_real_[0]);
            double euclidean_result = VectorDistance(v1_pointer, (v1_pointer + (hop_size-1)), v2_pointer);
            if (euclidean_result < min_distance) {
                s = this->states_[k].transition_[iter].last_state_;
                min_distance = euclidean_result;
            }
            iter++;
        }
        this->states_[state_i_plus_one].suffix_transition_ = s;
        this->states_[state_i_plus_one].lrs_ = this->LengthCommonSuffix(pi_1,this->states_[state_i_plus_one].suffix_transition_ - 1);*/
    }
    /*if (k != 0)
    {
        this->states_[state_i_plus_one].lrs_ = this->states_[state_i_plus_one].lrs_ + 1;
        this->states_[state_i_plus_one].suffix_transition_ = k;
    }*/
    this->T[this->states_[state_i_plus_one].suffix_transition_].push_back(state_i_plus_one);
}

void AudioOracleGist::FindBetter(vector <double> vector_real, int state_i_plus_one, int hop_size)
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

MarSystem* AudioOracleGist::RealTimeInitialize(bool isInitialized)
{
    Marsyas::MarSystemManager mng;
    Marsyas::MarSystem* realAudio = mng.create("Series", "realAudio");
    // standard network
    realAudio->addMarSystem(mng.create("AudioSourceBlocking", "src"));
    realAudio->updControl("AudioSourceBlocking/src/mrs_bool/initAudio", true);
    realAudio->updControl("AudioSourceBlocking/src/mrs_natural/bufferSize", 8192);
    realAudio->updControl("AudioSourceBlocking/src/mrs_natural/nChannels", 2);
/*    realAudio->addMarSystem(mng.create("AudioSource", "src"));
    realAudio->updControl("AudioSource/src/mrs_bool/realtime",true);
    realAudio->updControl("AudioSource/src/mrs_bool/initAudio", true);
    realAudio->updControl("AudioSource/src/mrs_natural/bufferSize", 8192);
    realAudio->updControl("AudioSource/src/mrs_natural/nChannels", 1);*/

    return realAudio;
}

MarSystem* AudioOracleGist::RealTimeStop(MarSystem* realAudio, bool stop)
{
    realAudio->updControl("AudioSourceBlocking/src/mrs_bool/initAudio", false);
    int buffer = realAudio->getControl("AudioSourceBlocking/src/mrs_natural/bufferSize")->to<mrs_natural>();
    int size = realAudio->getControl("AudioSourceBlocking/src/mrs_natural/nBuffers")->to<mrs_natural>();
    bool hasData = realAudio->getControl("AudioSourceBlocking/src/mrs_bool/hasData")->to<mrs_bool>();
/*    realAudio->updControl("AudioSource/src/mrs_bool/initAudio", false);
    int buffer = realAudio->getControl("AudioSource/src/mrs_natural/bufferSize")->to<mrs_natural>();
    bool hasData = realAudio->getControl("AudioSource/src/mrs_bool/hasData")->to<mrs_bool>();*/
    cout << "hasData: " << hasData << endl;
    cout << "buffer: " << buffer << endl;
    cout << "size: " << size << endl;
}
