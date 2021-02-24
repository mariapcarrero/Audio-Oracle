//
// Created by MARIA PAULA CARRERO on 2/12/21.
//

#include <iostream>
#include <new>
#include <string>
#include <vector>
#include <variant>
#include <random>
#include <algorithm>
#include <cmath>
#include <map>
#include "../3rd-party/AudioFile.h"
#include <math.h>

using namespace std;

int main(){
    double outp;
    AudioFile<double> audioFile;
    audioFile.load ("/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/BlueJay2.wav");

    int sampleRate = audioFile.getSampleRate();
    int bitDepth = audioFile.getBitDepth();

    int numSamples = audioFile.getNumSamplesPerChannel();
    double lengthInSeconds = audioFile.getLengthInSeconds();

    int numChannels = audioFile.getNumChannels();
    bool isMono = audioFile.isMono();
    bool isStereo = audioFile.isStereo();

    cout << "sampleRate: "<< sampleRate << " bitDepth: " << bitDepth << " numSamples: " << numSamples << " lengthInSeconds: " << lengthInSeconds << endl;
    cout << "numChannels: " << numChannels << " isMono: " << isMono << " isStereo: " << isStereo << endl;
/*    int channel = 0;
    //int numSamples = audioFile.getNumSamplesPerChannel();
    double currentSample;
    for (int i = 0; i < numSamples; i++)
    {
        currentSample = audioFile.samples[channel][i];
        cout << currentSample  << endl;
    }*/

    AudioFile<double>::AudioBuffer buffer;

    // 2. Set to (e.g.) two channels
        buffer.resize (2);

    // 3. Set number of samples per channel
        buffer[0].resize (419225);
        buffer[1].resize (419225);

     numChannels = 2;
    int numSamplesPerChannel = 419225;
     sampleRate = 44100.f;
    float frequency = 440.f;

/*    for (int i = 0; i < numSamplesPerChannel; i++)
    {
        float sample = audioFile.samples[0][numSamplesPerChannel-i] ;

        for (int channel = 0; channel < numChannels; channel++)
            buffer[channel][i] = sample;
    }*/
    int repetitions = 50;
    repetitions = repetitions * 4096;
    int i = 0;
    int j = 0;
    int x = 1;
    while (i < repetitions)
    {
        std::random_device rd;  ///Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); ///Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis_int(0, 415128);
        int rand_alpha = dis_int(gen);
        j = x * rand_alpha;
        int w = j+4095;
        cout << "rand: "<<  rand_alpha << " j: " << j << " w: " << w << endl;
        while (j < w)
        {
            float sample = audioFile.samples[0][j];
            for (int channel = 0; channel < numChannels; channel++)
                buffer[channel][i] = sample;
            j++;
            i++;
        }
    }
    cout << "i: " << i << endl;
// 5. Put into the AudioFile object
    bool ok = audioFile.setAudioBuffer (buffer);
    cout << ok << endl;
    audioFile.save ("/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/audioFile.wav", AudioFileFormat::Wave);
    return 0;
}