#pragma once

#include "ofMain.h"
#include "nsOsc.h"
#include "ofxAssimpModelLoader.h"


class nsVisuals {
    
public:
    nsVisuals();
    ~nsVisuals();
    
    void setup(int portNumber);
    void update();
    
    //visual content
    void background();
    
    void triSquares(ofVec2f position);
    void sineCircles();
    void scanLines();
    void sines();
    void verticalCircles();
    void noiseSquares(ofVec2f position);
    void waves(float posX, float posY);
    void generativeSphere(ofVec2f position);
    void deformedMesh();
    void organismDraw(ofVec2f pos, float scale);
    void videoPlayback();
    
private:
    
    void dynamicPositioning();
    
    nsOsc osc;
    void panel(ofPoint position); //background

    //global vars
    int width, height;
    float scale;
    ofPoint left, center, right;
    ofColor objectColor;
    
    //video
    ofVideoPlayer vid;
    float videoAlpha;
    
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
    float sphereCounter, boxAlpha;
    vector <float> sphereAlpha;

    
    //deformedMesh
    ofxAssimpModelLoader model;
    vector<ofPoint> modelPosition;
    int randomMeshPosition;
    float meshAlpha, meshRumble;

    //Organism
    int nCurveVertices;
    vector<ofVec2f> curveVertices;
    void organism(ofPoint& pos, ofColor& c, float scale, float rotation, float noiseAmt);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

};
