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

/*
int main()
{
    string fileName;
    cout << "Please enter filename: " << endl;
    cin >> fileName;
    if (fileName.size() == 0)
    {
        cout<<"Please enter filename."<<endl;
        exit(1);
    }
    cout << "Processing file " << fileName << endl;

    recognize(fileName);
    exit(0);
}
*/

int main()
{
    AudioOracle audio_oracle;
    audio_oracle.AnalyseAudio("BlueJayCall.wav");
   // exit(0);
}