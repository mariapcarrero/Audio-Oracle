//
// Created by MARIA PAULA CARRERO on 3/20/21.
//

#ifndef FACTORORACLESTRING_GIST_PLAY_FILE_H
#define FACTORORACLESTRING_GIST_PLAY_FILE_H

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


#endif //FACTORORACLESTRING_GIST_PLAY_FILE_H
