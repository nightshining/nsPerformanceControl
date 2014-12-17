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

  
private:
    
    ofxOscReceiver receiver;
    vector <string> messageName;
    vector <float> receiveMessage;
};
