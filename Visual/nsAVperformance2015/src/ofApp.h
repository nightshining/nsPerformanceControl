#pragma once

#include "ofMain.h"
#include "nsVisuals.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		
		
    //nsOsc osc;
    nsVisuals visuals;
    
    //Debug
    bool bDebug;
    
    ofVec2f getLeft();
    ofVec2f getCenter();
    ofVec2f getRight();
    
    int counter, counterMax;
    void dCounter();

};
