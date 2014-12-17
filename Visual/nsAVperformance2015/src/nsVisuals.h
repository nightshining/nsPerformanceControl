#pragma once

#include "ofMain.h"
#include "nsOsc.h"

class nsVisuals {
    
public:
    nsVisuals();
    ~nsVisuals();
    
    void setup(int portNumber);
    void update();
    
    //visual content
    void background();
    
    void triSquares();
    void sineCircles();
    void scanLines();
    void sines();
    void verticalCircles();
    void noiseSquares();
    void waves();
    void generativeSphere();
    
private:
    
    void dynamicPositioning();
    
    nsOsc osc;
    void panel(ofPoint position); //background

    //global vars
    int width, height;
    float scale;
    ofPoint left, center, right;
    ofColor objectColor;
    
    //triSquare Vars
    float triAlpha;
    
    //sineCircles Vars
    //float sineCirclesAlpha;
    
    //scanLines Vars
    float blend, scanLinesAlpha;
    ofColor scanLinesColor;
    
    //sines Vars
    float sinesFade, sinesAlpha;
    
    //verticalCircles
    vector<float> verticalAlpha;
    
    
    //noiseSquares
    float squareNoise;
    
    //waves
    float wavesAlpha, wavesFreq, wavesMax, counter;
    
    //generativeSphere
    float sphereCounter, sphereAlpha;

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

};
