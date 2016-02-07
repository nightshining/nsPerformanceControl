#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"

class Sine : public ofxControlUtils {
    
private:
    
    ofMesh mesh;
    
    float time, noise, size, sizeY;
    ofFloatColor color;
    ofVec3f coords, rotate;
    ofPoint pos;
    ofxControlUtils ctrlNoise, ctrlScale;
    
    float x, easing;
    float timeX;
    float setMovementX;
    
public:
    
    Sine() {
        
        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        noise = 0.0;
        size = 0.0;
        coords = ofVec3f(0.0,0.0,0.0);
        rotate = ofVec3f(0.0,0.0,0.0);
        color = ofFloatColor(0.0,0.0,0.0);
        time = 0.0;
        sizeY = 0.0;
        pos = ofPoint(0,0);
        
        easing = 0.005;

    }
    
    void addMovement() {
        
        float targetX = setMovementX;
        float deltaX = targetX - x;
        x += deltaX * easing;
        timeX = x;

        
    }
    
    void draw() {
        
        mesh.clear();
        mesh.clearColors();
        
        addMovement();
        
        for (float u = 0.0; u < 2 * PI; u += PI / 75) {
            for (float v = 0.0; v < 2 * PI; v += 2 * PI / 75) {
                
                //noise = ofMap(ofGetMouseX(),0,ofGetWidth(),0.0,5.0,true);
                size = 200;
                coords.x = sin(u) * sin(v) * size;
                coords.y = ofSignedNoise(u + ofGetElapsedTimef() * timeX * noise) * ofSignedNoise(v + ofGetElapsedTimef() * timeX * noise) * sizeY;
                coords.z = sin(v) * cos(v) * size;
                
                color = ofFloatColor(0.80,0.80,0.70, u * 0.05);
                rotate.set(0, 0, 0);
                
                //create
                mesh.addColor(color);
                ofVec3f vec = ofVec3f(coords);
                mesh.addVertex(vec);
            }
        }
        
        pos = ofPoint(ofGetWidth() * .5, ofGetHeight() * .5);
        
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateX(rotate.x);
        ofRotateY(rotate.y);
        ofRotateZ(rotate.z);
        mesh.draw();
        ofPopMatrix();
        ofPopStyle();
        
    }
    
    void setNoise(float value) {
        
        noise = ofMap(ctrlNoise.rampToggle(value, 0.10, 0.08), 0.0, 1.0, 0.0, 2.0);
    }
    
    void setScale(float value) {
        
        sizeY = ofMap(ctrlScale.rampToggle(value, 0.05, 0.01), 0.0, 1.0, 0.0,300.0);
    }
    
    void setMovement(float _setX) {
        
        setMovementX = ofMap(_setX, 0,1,0.05, .8);

    }
    
    
};
