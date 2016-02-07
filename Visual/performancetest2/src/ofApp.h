#pragma once

#include "ofMain.h"
#include "Sphere.h"
#include "Waves.h"
#include "Apple.h"
#include "Ghost.h"
#include "NoiseWave.h"
#include "MiniNoise.h"
#include "Sine.h"
#include "Mold.h"
#include "Fin.h"
#include "DeformedSphere.h"
#include "nsOsc.h"



class ofApp : public ofBaseApp {

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
		
    Sphere _sphere;
    Waves _waveL, _waveR;
    Apple _apple, _apple2;
    Ghost _ghostL, _ghostR;
    NoiseWave _noisewave;
    MiniNoise _miniL, _miniR;
    Sine _sine;
    Mold _moldL, _moldR;
    Fin _fin;
    DeformedSphere dSphereL, dSphereR;
    nsOsc osc;
    

    int counter;

    


};
