//
// Created by MARIA PAULA CARRERO on 2/8/21.
//

#include "../src/AudioOracle.h"
using namespace std;

#include <marsyas/system/MarSystem.h>
#include <marsyas/system/MarSystemManager.h>


int main()
{

    string sfName = ("/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/BlueJay2.wav");
    string sfName1 = ("/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/BlueJay.wav");
    Marsyas::MarSystemManager mng;
    Marsyas::MarSystem* pnet = mng.create("Series", "pnet");
    // standard network
    pnet->addMarSystem(mng.create("SoundFileSource", "src"));
   // pnet->addMarSystem(mng.create("Gain", "gt"));
  //  pnet->addMarSystem(mng.create("AudioSink", "desti"));
  //  pnet->updctrl("AudioSink/desti/mrs_bool/initAudio", true);
    pnet->addMarSystem(mng.create("SoundFileSink", "dest"));
    pnet->updctrl("SoundFileSource/src/mrs_string/filename", sfName);
    pnet->updControl("mrs_natural/inSamples", 4096);
   int counter = 0;
    /*  while ( pnet->getctrl("SoundFileSource/src/mrs_bool/hasData")->to<mrs_bool>() ) {
         pnet->tick();
         counter++;
     }*/
   // cout << counter << endl;
    pnet->updctrl("SoundFileSink/dest/mrs_string/filename","/Users/mariapaulacarrero/Documents/GitHub/Audio-Oracle/BlueJay3.wav");
    mrs_natural pos = pnet->updctrl("SoundFileSource/src/mrs_natural/pos", 8192);
    cout << pos << endl;
    while ( pnet->getctrl("SoundFileSource/src/mrs_bool/hasData")->to<mrs_bool>() ) {
        pnet->tick();
        counter++;
    }
    cout << counter << endl;


/*    pnet->tick();
    mrs_natural nat = pnet->getctrl("SoundFileSource/src/mrs_natural/pos")->to<mrs_natural>();
    cout << nat << endl;
    pnet->tick();
    nat = pnet->getctrl("SoundFileSource/src/mrs_natural/pos")->to<mrs_natural>();
    cout << nat << endl;
    pnet->tick();
    nat = pnet->getctrl("SoundFileSource/src/mrs_natural/pos")->to<mrs_natural>();
    cout << nat << endl;*/

    // exit(0);
}