
/*! \file AudioOracle.cpp
    \brief A file that contains the functions needed for the creation of an Audio Oracle.

    Five main functions: AnalyseAudio, AddFrame, LengthCommonSuffix, FindBetter and AOGenerate.
*/
#define _USE_MATH_DEFINES

#include "AudioOracle.h"
#include <marsyas/system/MarSystem.h>
#include <marsyas/system/MarSystemManager.h>
#include "../3rd-party/AudioFile.h"


#include <cmath>
int pi_1, pi_2, k, fo_iter;

double vectorDistance(double *first, double* last, double *first2) {
    double ret = 0.0;
  //  cout << "inside function: " << *first << " " << *last << " " << *first2 << endl;
    while (first != last) {
        double dist = (*first++) - (*first2++);
        ret += dist * dist;
    }
   // cout << "sqrt: " << sqrt(ret) << " ret: " << ret << endl;
    return ret > 0.0 ? sqrt(ret) : 0.0;
}

vector<double> AudioOracle::MakeWindow(int n)
{
    vector<double> window;
    for(int i = 0; i < n; i++)
    {
        window.push_back((0.5 * (1 - cos(2*M_PI*i/(n-1))))+ 0.00001);
    }
    return window;
}

vector<int> AudioOracle::AOGenerate(int i, int total_length, float q, int k)
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
    int j = 0;
    int w = 0;
    int j_temp = 0;
    for(iter = 0; iter < total_length; iter++)
    {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);
        float u = dis(gen);
        //cout << "u: " << u << endl;
        // float u = (float)rand() / RAND_MAX;
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
                //string s(1,w);
                //v = v + s;
            } else {
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
                /*std::random_device rd;  //Will be used to obtain a seed for the random number engine
                std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
                std::uniform_int_distribution<> dis_int(0, lenSuffix);
                int rand_alpha = dis_int(gen);*/

               // j = this->states_[this->states_[i].suffix_transition_].transition_[rand_alpha].starting_frame_;

                i = this->states_[this->states_[i].suffix_transition_].transition_[rand_alpha].last_state_;
                if (i == -1) {
                    i = 0;
                }
            }
        }
    }
  //  cout << improvisation_vector.size() << endl;
    return improvisation_vector;
};

void AudioOracle::GenerateAudio(int i, int total_length, float q, int k, int hop_size, int buffer_size, string input_filename, string output_filename)
{

    AudioFile<double> audioFile;
    audioFile.load(input_filename);

    AudioFile<double>::AudioBuffer buffer;

    AudioFile<double>::AudioBuffer complete_buffer;
    int automaton_size = this->states_.size();
    cout << automaton_size << endl;
    int numSamples = audioFile.getNumSamplesPerChannel();
    //int repetitions = total_length * hop_size;
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
    repetitions = (total_length * buffer_size);
    // 3. Set number of samples per channel
    buffer[0].resize(repetitions);
    buffer[1].resize(repetitions);

    // 2. Set to (e.g.) two channels
    complete_buffer.resize(2);

    // 3. Set number of samples per channel
    complete_buffer[0].resize(repetitions);
    complete_buffer[1].resize(repetitions);

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
    while (iter < repetitions) {
        //z = this->states_[improvisation[real_iter]].starting_frame_;

       for(int z = 0; z < buffer_size; z++)
       {
            for (int channel = 0; channel < numChannels; channel++)
                buffer[channel][iter] = (buffer_matrix[improvisation[real_iter]][z] * win[z]) + 0.00001;
            iter++;
        }
        real_iter++;
    }
    bool ok = audioFile.setAudioBuffer (buffer);
    audioFile.setSampleRate (44100);
    cout << ok << endl;
    audioFile.save (output_filename, AudioFileFormat::Wave);
}


void AudioOracle::AnalyseAudio(string sfName, int hop_size)
{
    cout << sfName << endl;
    Marsyas::MarSystemManager mng;
    Marsyas::MarSystem* pnet = mng.create("Series", "pnet");
    // standard network
    pnet->addMarSystem(mng.create("SoundFileSource", "src"));
    pnet->updctrl("SoundFileSource/src/mrs_string/filename", sfName);
    pnet->addMarSystem(mng.create("PowerSpectrum/pspk"));
    pnet->addMarSystem(mng.create("Centroid","cntd"));
    pnet->addMarSystem(mng.create("Gain", "gain"));
    pnet->addMarSystem(mng.create("Windowing/ham"));
    pnet->addMarSystem(mng.create("Rolloff/rolloff"));
    pnet->updControl("mrs_natural/inSamples", hop_size);
    int counter = 0;
    this->CreateState(0);
    this->states_[0].state_ = 0;
    this->states_[0].lrs_ = 0;
    this->states_[0].suffix_transition_ = -1;
    this->states_[0].starting_frame_ = 0;
    this->T.push_back({});
    int i = 0;
    vector <vector <double>> vector_real;
    while ( pnet->getctrl("SoundFileSource/src/mrs_bool/hasData")->to<mrs_bool>() )
    {
        cout << "sample: " << pnet->getctrl("SoundFileSource/src/mrs_natural/pos")->to<mrs_natural>() << endl;
        pnet->tick();
        // gets data from the Spectrum for read only!
        //const realvec& processedData =
        //       pnet->getctrl("Spectrum/spk/mrs_realvec/processedData")->to<mrs_realvec>();
        const Marsyas::realvec& processedData =
                pnet->getctrl("Centroid/cntd/mrs_realvec/processedData")->to<mrs_realvec>();
       // cout << "Original Spectrum = " << processedData << endl;
        Marsyas::mrs_real * real_pointer;
        real_pointer = processedData.getData();
        //cout << "val pointer: "<< *real_pointer << endl;
        vector <Marsyas::mrs_real> temp_vector;
        for (int temp_counter = 0; temp_counter < hop_size; temp_counter ++ )
        {
            temp_vector.push_back(*(real_pointer+temp_counter));
        }

        double * map_pointer = &(temp_vector[0]);
        this->feature_map.insert({counter, map_pointer});
        this->AddFrame(counter, temp_vector, 9.65 , pnet->getctrl("SoundFileSource/src/mrs_natural/pos")->to<mrs_natural>(), hop_size);
        counter = counter +1;
        // if we need to get the Spectrum and modify it, here is the way
        // to do it.  Notice that we must open a new scope using curly
        // brackets so that MarControlAccessor is automatically destroyed
        // when we are finished modifing the realvec control.
    }
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
    delete pnet;
}

void AudioOracle::AddState(int first_state){
    this->states_[first_state].state_ = first_state;
}


void AudioOracle::CreateState(int m) {
    State newstate;
    newstate.state_ = m;
    this->states_.push_back(newstate);
    //cout << "state: " << this->states_[m].state_ << endl;
}
void AudioOracle::AddTransition(int first_state, int last_state, vector <Marsyas::mrs_real> vector_real, int feature_state, int starting_frame) {
    SingleTransition transition_i;
    transition_i.first_state_ = first_state;
    transition_i.last_state_ = last_state;
    transition_i.vector_real_ = vector_real;
    transition_i.corresponding_state_ = feature_state;
    transition_i.starting_frame_ = starting_frame;
    this->states_[first_state].transition_.push_back(transition_i);
}
/*
string AudioOracle::FOGenerate( int& i, string v, float q)
{
    //! A normal member taking four arguments and returning a string value.
    /*!
      \param i an integer argument.
      \param v a string argument.
      \param q a float argument.
      \return The factor oracle improvisation
    */
/*
    std::random_device rd;  ///Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); ///Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    float u = dis(gen);
    /// float u = (float)rand() / RAND_MAX;
    if (u < q) //Preguntar si debe iniciar en 1 o en 0
    {
        i = state_i_plus_one;
        int len = this->states_.size();
        if (i == len)
            i = len - 1;
        char w = this->states_[i].transition_[0].vector_real_;
        string s(1,w);
        v = v + s;
    }
    else
    {
        int lenSuffix = this->states_[this->states_[i].suffix_transition_].transition_.size() - 1;
        std::random_device rd;  ///Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); ///Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis_int(0, lenSuffix);
        int rand_alpha = dis_int(gen);
        char alpha = this->states_[this->states_[i].suffix_transition_].transition_[rand_alpha].vector_real_;
        i = this->states_[this->states_[i].suffix_transition_].transition_[rand_alpha].last_state_;
        if (i == -1)
        {
            i = 0;
        }
        v = v + alpha;
    }
    return v;
}
*/


void AudioOracle::FindBetter(int state_i_plus_one, double threshold, vector <mrs_real> vector_real)
{
    //! A normal member taking five arguments and returning an integer value.
    /*!
      \param T a reference to a vector of vector of integers.
      \param i an integer argument.
      \param alpha a char argument.
      \param word a string argument.
      \return A better state
    */

    int iter = 0;
    double min_distance = INFINITY;
    vector <FilteredTransition> filtered_transitions;
    while (iter < this->states_[k].transition_.size()) {
        double *v1_pointer = &(vector_real[0]);
        double *v2_pointer = &(this->states_[k].transition_[iter].vector_real_[0]);
       // cout << "inside lst: " << *v1_pointer << " " << *v2_pointer << endl;
        double euclidean_result = vectorDistance(v1_pointer, (v1_pointer + 4095), v2_pointer);
       // cout << "euc result1: " << euclidean_result << endl;
        if (euclidean_result < threshold) {
          //  cout << "inside euc res " << endl;
            FilteredTransition current_filtered_trans;
            current_filtered_trans.current_transition_ = this->states_[k].transition_[iter];
            current_filtered_trans.current_lrs_ = this->states_[this->states_[k].transition_[iter].last_state_].lrs_;
            filtered_transitions.push_back(current_filtered_trans);
        }
        iter++;
    }
    typedef std::function<bool(FilteredTransition transition_1, FilteredTransition transition_2)> Comparator;
    // Defining a lambda function to compare two lrs
    Comparator compFunctor =
            [](FilteredTransition transition_1, FilteredTransition transition_2)
            {
                return transition_1.current_lrs_ < transition_2.current_lrs_;
            };
    sort(filtered_transitions.begin(),filtered_transitions.end(), compFunctor);
    for (int w = 0; w < filtered_transitions.size(); w++)
    {
        this->states_[state_i_plus_one].suffix_transition_ = filtered_transitions[w].current_transition_.last_state_; //preguntar a jaime
     //   cout << "last: " <<  filtered_transitions[w].current_transition_.last_state_ << endl;
        this->T[filtered_transitions[w].current_transition_.last_state_].push_back(state_i_plus_one);
    }

}
int AudioOracle::LengthCommonSuffix( int pi_1, int pi_2)
{
    if (pi_2 == this->states_[pi_1].suffix_transition_)
    {
    //    cout << "pi_2 == pi_1: " << endl << pi_2 << this->states_[pi_1].suffix_transition_ << this->states_[pi_1].lrs_ << endl;
       return this->states_[pi_1].lrs_;
    }
    else
    {
        while (this->states_[pi_1].suffix_transition_ != this->states_[pi_2].suffix_transition_)
        {
            pi_2 = this->states_[pi_2].suffix_transition_;
        }
    }
    return min(this->states_[pi_1].lrs_,this->states_[pi_2].lrs_) + 1;
}
void AudioOracle::AddFrame(int i, vector <mrs_real> vector_real, double threshold, int start_frame, int hop_size) {
    //! A normal member taking four arguments and returning no value.
    /*!
      \param i an integer argument.
      \param vector_real a vector of mrs_real (aka double) values.
      \param threshold a double value which determines the level of similarity between vectors.
    */
    //char alpha = word[i-1];
    cout << "inside AddFrame, state: " << i << endl;
    this->CreateState(i + 1);
    int state_i_plus_one = i + 1;
    this->T.push_back({});
    this->AddTransition(i, state_i_plus_one, vector_real,i,(state_i_plus_one + 1) * hop_size);
    k = this->states_[i].suffix_transition_; /*!< k = S[i] */
    this->states_[state_i_plus_one].suffix_transition_ = 0;
    this->states_[state_i_plus_one].lrs_ = 0;
    this->states_[state_i_plus_one].starting_frame_ = start_frame;
    pi_1 = i; /*!< phi_one = i */
    int flag = 0, iter = 0, counter = 0, s;
    while (k > -1 && flag == 0) {
       // cout << "entro k > -1" << endl;
        iter = 0;

        while (iter < this->states_[k].transition_.size() && k > -1) {
            double *v2_pointer = &(this->states_[k].transition_[iter].vector_real_[0]);
            double *v1_pointer = &(vector_real[0]);
            iter++;
            double euclidean_result = vectorDistance(v1_pointer, (v1_pointer + 4095), v2_pointer);
           // cout << "euc result: " << euclidean_result << endl;
            if (euclidean_result < threshold) {
                AddTransition(k, state_i_plus_one, vector_real,i,(state_i_plus_one + 1) * hop_size);
               // cout << this->states_[k].transition_[1].last_state_ << endl;
             //   cout << "k: " << k << endl;
                pi_1 = k;
                k = this->states_[k].suffix_transition_;
              //  cout << "k after: " << k << endl;
               // cout << "entro" << k << endl;
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
        /* this->states_[statemplusone].suffix_transition_ = 0;
         this->states_[statemplusone].lrs_ = 0;*/
       // cout << "entro a  k == -1 " << endl;
        this->states_[state_i_plus_one].suffix_transition_ = 0;
        this->states_[state_i_plus_one].lrs_ = 0;
    }
    else {
       // FindBetter(state_i_plus_one,threshold,vector_real);
        s = 0;
        flag = 0, iter = 0;
        double min_distance = INFINITY;
        while (iter < this->states_[k].transition_.size()) {

            double *v1_pointer = &(vector_real[0]);
            double *v2_pointer = &(this->states_[k].transition_[iter].vector_real_[0]);
            //cout << "inside last: " << *v1_pointer << " " << *v2_pointer << endl;
            double euclidean_result = vectorDistance(v1_pointer, (v1_pointer + 4095), v2_pointer);

            if (euclidean_result < min_distance) {
                s = this->states_[k].transition_[iter].last_state_;
             //   cout << "s prev: " << s << " k: " << k << endl;
               // cout << "min: " << min_distance << " euc r: " << euclidean_result <<  endl;
                min_distance = euclidean_result;
            }
            iter++;
        }
        this->states_[state_i_plus_one].suffix_transition_ = s;
        this->states_[state_i_plus_one].lrs_ = this->LengthCommonSuffix(pi_1,this->states_[state_i_plus_one].suffix_transition_ - 1);
        //cout << "LRS INSIDE:" << state_i_plus_one << "-- "<< this->states_[state_i_plus_one].lrs_ << endl;
    }
    /*if (k != 0)
    {
        this->states_[state_i_plus_one].lrs_ = this->states_[state_i_plus_one].lrs_ + 1;
        this->states_[state_i_plus_one].suffix_transition_ = k;
    }*/
    this->T[this->states_[state_i_plus_one].suffix_transition_].push_back(state_i_plus_one);
}


void AudioOracle::AudioOracleStart(string word)
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
    this->T.resize(len+1);
    if (len+1 != 1)
    {
        for (int i = 1; i <= len; i++)
        {
            /*!< for i <- 1 to m
            * do AddFrame(i)
            */
            this->AddFrame(i, {}, 0.05, 0, 4096);
        }
    }
    
    for (int i = 0; i < len+1; i++){

        cout << "STATE[" << i << "]:\n" << "LRS: "<< this->states_[i].lrs_ << "\n";
        cout << "Suffix: " << this->states_[i].suffix_transition_ << "\n";
        cout << "Transitions: " << "\n";
        for (int w = 0; w < this->states_[i].transition_.size(); w++)
        {
            cout << this->states_[i].transition_[w].first_state_ << " " << this->states_[i].transition_[w].last_state_ << " "  << this->states_[i].transition_[w].vector_real_[0] << "\n";
        }
        cout << "\n";

    }

    string oracle = "";
    fo_iter = 1;
    int q = 0;
    cout << "Input the q value: ";
    cin >> q;
   /* for (int x = 0; x < len; x++)
    {
        oracle = this->FOGenerate(fo_iter,oracle,q);
        if (fo_iter == len)
            fo_iter = len-1;
        cout << "Factor Oracle Sequence: " << oracle << "\n";

    }*/

}

/*
void AudioOracle::CallGenerate(int len, float q)
{
    vector<T> oracle = {};
    fo_iter = 1;
    // int q = 0;
    // cout << "Input the q value: ";
    // cin >> q;
    for (int x = 0; x < len; x++)
    {
        oracle = this->AOGenerate(fo_iter,oracle,q);
        if (fo_iter == len)
            fo_iter = len-1;
        for (int w = 0; w < oracle.size(); w++)
            cout << oracle[w] << " ";
        cout << endl;
    }

};
*/
