#pragma once

#include "ofMain.h"
#include "nsOsc.h"
#include "ofxAssimpModelLoader.h"

enum nsShapeTitle {
    
    NS_SINE, NS_NOISE_WAVE, NS_MESH_MOLD
    
};

class nsVisuals {
    
public:
    nsVisuals();
    ~nsVisuals();
    
    void setup(int portNumber);
    void update();
    
    //visual content
    void background();
    
    void triSquares(ofVec2f position);
    void noiseSquares(ofVec2f position);
    void waves(float posX, float posY);
    void generativeSphere(ofVec2f position);
    void deformedMesh();
    void texOrgDraw(ofVec2f position);
    void organicMesh(ofVec2f position, nsShapeTitle nsName);

    
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

    //texturedOrg
    
    ofSpherePrimitive texOrgSphere;
    ofMesh texOrgMesh;
    ofColor texOrgC;
    ofImage texOrgImg;
    
    float texOrgScale, texOrgSpinX, texOrgSpinY;
    int counterIndex;
    
    void texOrgMovement();
    
    ofSpherePrimitive sphereHUD;
    ofMesh meshHUD;
    void HUD(float rotateX, float rotateY);
    
    //Mesh Objects
    ofMesh genMesh;
    float genMeshNoise, genMeshSize, genMeshTime;
    ofVec3f genMeshCoords;
    ofFloatColor genMeshColor;
};
