#pragma once

#include "ofMain.h"
#include "Sphere.h"
#include "Waves.h"
#include "Apple.h"
#include "Ghost.h"
#include "MiniNoise.h"
#include "Sine.h"
#include "Mold.h"
#include "Fin.h"
#include "DeformedSphere.h"
#include "OrganicShape.h"
#include "NoiseSphere.h"
#include "FadeShape.h"

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
    OrganicShape _orgL, _orgR;
    MiniNoise _miniL;
    Sine _sine;
    Mold _moldL, _moldR;
    Fin _fin;
    DeformedSphere _dSphereL, _dSphereR;
    NoiseSphere _nSphere;
    FadeShape _fadeL, _fadeR;
    
// UNUSED
//    NoiseWave _noisewave;
//    LongWave _longL, _longR;
//    Jelly _jelly;
    
    nsOsc osc;
    

    int counter;
    bool bDebug;
    
    //Effects//
    ofShader effect, effect2;
    ofFbo fbo;
    

};
