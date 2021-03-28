//
// Created by MARIA PAULA CARRERO on 8/25/19.
//
/*
#include "MarSystemManager.h"
using namespace std;
using namespace Marsyas;

void sfplay(string sfName, float gain)
{
    MarSystemManager mng;

    MarSystem* playbacknet = mng.create("Series", "playbacknet");

    playbacknet->addMarSystem(mng.create("SoundFileSource", "src")); // mng.create(TYPE, NAME)
    playbacknet->addMarSystem(mng.create("Gain", "gt"));
    playbacknet->addMarSystem(mng.create("AudioSink", "dest"));

    playbacknet->updctrl("SoundFileSource/src/mrs_string/filename", sfName);
    playbacknet->updctrl("Gain/gt/mrs_real/gain", gain);
    playbacknet->updctrl("AudioSink/dest/mrs_bool/initAudio", true);

    while ( playbacknet->getctrl("SoundFileSource/src/mrs_bool/hasData")->to<mrs_bool>() )
    {
        playbacknet->tick();
    }
    delete playbacknet;
}*/

//
// Created by MARIA PAULA CARRERO on 8/26/19.
//
#include "AudioOracle.h"
#include "AudioOracleGist.h"
#include <iostream>
#include <fstream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <vector>
#include "../3rd-party/AudioFile.h"
#define USE_ACCELERATE_FFT
#include "Gist.h"


using namespace std;


/*
void recognize(string sfName)
{
    MarSystemManager mng;
    MarSystem* pnet = mng.create("Series", "pnet");
    // standard network
    pnet->addMarSystem(mng.create("SoundFileSource", "src"));
    pnet->updctrl("SoundFileSource/src/mrs_string/filename", sfName);
 //   pnet->addMarSystem(mng.create("Spectrum","spk"));
 //   pnet->addMarSystem(mng.create("Gain", "g2"));
 //   pnet->addMarSystem(mng.create("Spectrum/spk"));
    pnet->addMarSystem(mng.create("PowerSpectrum/pspk"));
    pnet->addMarSystem(mng.create("Centroid","cntd"));
    pnet->addMarSystem(mng.create("Gain", "gain"));
    pnet->addMarSystem(mng.create("Windowing/ham"));
    pnet->addMarSystem(mng.create("Rolloff/rolloff"));

    //pnet->updControl("mrs_natural/inSamples", 256);
    vector <vector <double>> vector_real;
    int counter = 0;
    while ( pnet->getctrl("SoundFileSource/src/mrs_bool/hasData")->to<mrs_bool>() )
    {
        pnet->tick();
        // gets data from the Spectrum for read only!
        //const realvec& processedData =
         //       pnet->getctrl("Spectrum/spk/mrs_realvec/processedData")->to<mrs_realvec>();
        const realvec& processedData =
                pnet->getctrl("Centroid/cntd/mrs_realvec/processedData")->to<mrs_realvec>();
        //cout << "Original Spectrum = " << processedData << endl;
        //cout << processedData << endl;
        mrs_real * real_pointer;
        real_pointer = processedData.getData();
        //cout << "val pointer: "<< *real_pointer << endl;
        vector <mrs_real> temp_vector;
        for (int temp_counter = 0; temp_counter < 511; temp_counter ++ )
        {
            temp_vector.push_back(*(real_pointer+temp_counter));
        }
       // cout <<"getData: " << *processedData.getData() << endl;
        vector_real.push_back(temp_vector);
        counter = counter +1;
        // if we need to get the Spectrum and modify it, here is the way
        // to do it.  Notice that we must open a new scope using curly
        // brackets so that MarControlAccessor is automatically destroyed
        // when we are finished modifing the realvec control.
    }
    cout << "COUNTER IS:" << counter << endl;
    delete pnet;
}
*/
/*
int main()Am
{
    string fileName;
    string gain_string;
    cout << "Enter filename: " << endl;
    cin >> fileName;
    cout << "Enter gain: " << endl;
    cin >> gain_string;
    float gain = stof(gain_string);

    if (fileName.size() == 0)
    {
        cout<<"Please enter filename."<<endl;
        exit(1);
    }
    cout << "Playing file " << fileName << " at volume " <<
         gain << endl;

    sfplay(fileName,gain);
    exit(0);
}*/
string printElement(AudioOracle audioOracle, int nodeNumber){
    string DOT;
    DOT = "\\node[initial,state,accepting] (0)      {$0$};\n";
    //int size = audioOracle->states_.size();
    int size = audioOracle.states_.size();
    for(int i = 1; i < size; i++)
    {
        DOT += "\\node[state]         (" + to_string(i) + ") [right of="+ to_string(i - 1) +"]  {$"+ to_string(i) +"$};\n";
    }
    for(int i = 0; i < size; i++)
    {
        int transition_size = audioOracle.states_[i].transition_.size();
        for(int j = 0; j < transition_size; j++)
        {
            if(transition_size > 1 && j > 0) DOT += "\\path[->] (" + to_string(audioOracle.states_[i].transition_[j].first_state_) +")  edge  [bend right, below]  node {" + to_string(audioOracle.states_[i].transition_[j].corresponding_state_) + "} (" + to_string(audioOracle.states_[i].transition_[j].last_state_) +");\n";
            else DOT += "\\path[->] (" + to_string(audioOracle.states_[i].transition_[j].first_state_) +")  edge           node {" + to_string(audioOracle.states_[i].transition_[j].corresponding_state_) + "} (" + to_string(audioOracle.states_[i].transition_[j].last_state_) +");\n";
        }

    }
    for(int i = 0; i < size; i++)
    {
        if (!audioOracle.T[i].empty()) {
            for (int x : audioOracle.T[i]) {
                DOT += "\\path[->, dashed] (" + to_string(x) +")  edge   [bend right, above]  node {" + to_string(x) + "} (" + to_string(i) +");\n";
            }
        }
    }
    return DOT;
   /* DOT+= to_string(audioOracle->states_[0].state_)+"\"]\n";
    //int size = audioOracle->states_.size();
    for (int i = 0; i < size; i++){
        DOT += "n" + to_string(nodeNumber) + "->";
        DOT += "n" + to_string(nodeNumber+1) + "\n";
        //printElement(to_string(audioOracle->states_[0].state_), nodeNumber+1);
    }*/
    cout << DOT;

}

string printData()
{
    string DOT;
    DOT = "\\node[initial,state,accepting] (0)      {$0$};\n";
    //int size = audioOracle->states_.size();
    int size = 100;
    for(int i = 1; i < size; i++)
    {
        DOT += "\\node[state]         (" + to_string(i) + ") [right of="+ to_string(i - 1) +"]  {$"+ to_string(i) +"$};\n";
    }
    return DOT;
}
void createFile(AudioOracle audioOracle)
{
    ofstream MyFile("/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/graph.tex");
    MyFile << "\\documentclass[border=0.2cm]{standalone}\n"
              "\\usepackage[all]{xy}\n"
              "\\usepackage{tikz}\n"
              "\\usetikzlibrary{arrows,positioning,automata}\n"
              "\n"
              "\\begin{document}\n"
              "\\begin{tikzpicture}[>=stealth',shorten >=1pt,auto,node distance=15mm]\n"
              "\\tikzstyle {vertex}=[circle,fill=black!25,minimum size=17pt,inner sep=0pt]";
   // printElement()
    string dot = printElement(audioOracle,0);
    MyFile << dot;
    MyFile << "\\end{tikzpicture}\n"
              "\\end{document}";
    MyFile.close();
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

int main()
{
    int frameSize = 8192;
    int sampleRate = 44100;
    auto start = chrono::steady_clock::now();
    Gist<double> gist (frameSize, sampleRate);
    //vector<double> audioFrame;
    vector<vector<double>> audioFrame = GenerateAudioFrames("/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/driverslicense.wav",8192,8192);
    auto end = chrono::steady_clock::now();
    cout << "gen: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
    cout << "len: " << audioFrame.size() << endl;
    cout << "int_len: " << audioFrame[0].size() << endl;
    gist.processAudioFrame(audioFrame[10]);

    float rms = gist.rootMeanSquare();
    end = chrono::steady_clock::now();
    cout << "rms1: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
    float zcr = gist.zeroCrossingRate();
    end = chrono::steady_clock::now();
    cout << "zcr1: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
    float specCent = gist.spectralCentroid();
    end = chrono::steady_clock::now();
    cout << "cent1: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
    float pitch = gist.pitch();
    end = chrono::steady_clock::now();
    cout << "pitch: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
    cout << "rms: " << rms << " zcr: " << zcr << " specCent: " << specCent << " pitch: " << pitch <<  endl;


    AudioOracleGist audio_oracle;
    audio_oracle.AnalyseAudio("/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/driverslicense.wav",16384, "centroid");
    vector<int> vector_final;
    //createFile(audio_oracle);
    //vector_final = audio_oracle.AOGenerate(0,200,0.7,0);
    /*for(int i = 0; i < 200; i++)
        cout << vector_final[i] << " "; 8192  16384 32768
    cout << endl*/;
   // audio_oracle.GenerateAudio(500,1200,0.8,0,8192,16384,"/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/driverslicense.wav","/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/3rd-party/audios/driversRms.wav");

    /*MarSystem* mar = audio_oracle.RealTimeInitialize(true);
    this_thread::sleep_for (std::chrono::seconds(10));
    audio_oracle.RealTimeStop(mar,true);*/
    /*    vector<double> vector_doubles;
    vector_doubles = audio_oracle.MakeWindow(200);
    for(int i = 0; i < 200; i++)
        cout << vector_doubles[i] << " ";
    cout << endl;*/
    //audio_oracle.AOGenerate(0,200,0.8,0,"/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/Faded.wav","/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/FadedOne.wav");
   // exit(0);
}