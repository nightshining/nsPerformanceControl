#pragma once

#include "ofMain.h"
#include "nsVisuals.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    //nsOsc osc;
    nsVisuals visuals;
    
    //Debug
    bool bDebug;
    
    ofVec2f getLeft();
    ofVec2f getCenter();
    ofVec2f getRight();
    
    int counter, counterMax;
    
    void dCounter() {
        
        ofPushStyle();
        ofSetColor(0, 255, 255);
        ofDrawBitmapString("Counter: " + ofToString(counter), 25, 25);
        ofPopStyle();
        
    }
};
