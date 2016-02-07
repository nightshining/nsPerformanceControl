#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class nsOsc {
    
public:
    nsOsc();
    ~nsOsc();
    void setup(int port);
    void update();
    void setMessageName(string uniqueName);
    float getFloatMessage(int getIndex); //This is to set local variables to incoming float connected to whatever name I set
    
    float getKnob(int index);
    float getSlider(int index);
    float getPad(int index);
    
    int getTotalPads();
    int getTotalKnobs();
    int getTotalSliders();
    
    void debugSliders();
    void debugKnobs();
    void debugPads();

private:
    
    ofxOscReceiver receiver;
    vector <string> messageName;
    vector <float> receiveMessage;
    
    vector <float> knobMessage;
    vector <float> sliderMessage;
    vector <int> padMessage;
    
    int totalPad, totalKnob, totalSlider;
    
};
