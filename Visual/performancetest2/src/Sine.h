#pragma once

#include "ofMain.h"
#include "ofxTween.h"

class Sine {
    
private:
    
    ofMesh mesh;
    ofxEasingSine tweenEasing;
    ofxTween animateSize, animateNoise;
    
    float time, noise, size, sizeY;
    ofFloatColor color;
    ofVec3f coords, rotate;
    ofPoint pos;
    bool bAnimate;
    
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
        bAnimate = false;

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
        
        for (float u = 0.0; u < 2 * PI; u += PI / 100) {
            for (float v = 0.0; v < 2 * PI; v += 2 * PI / 100) {
                
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
    
    void fadeUp() {
        int maxSpeed = 5.0;
        int maxSize = 550;
        
        noise += 0.05;
        sizeY += 30.0;
        
        if (sizeY >= maxSize) {
            
            sizeY = maxSize;
        }
        
        if (noise >= maxSpeed) {
            
            noise = maxSpeed;
        }
        
        
        setMovementX += 0.008;
        
        if (setMovementX >= 0.02) {
            
            setMovementX = 0.02;
        }

    }
    
    void fadeDown() {
        
        int min = 0.0;
        
        noise -= 0.05;
        sizeY -= 45.0;
        
        if (sizeY <= min) {
            
            sizeY = min;
        }
        
        if (noise <= min) {
            
            noise = min;
        }
        
        setMovementX -= 0.01;
        
        if (setMovementX <= min) {
            
            setMovementX = min;
        }
        
    }
    
    
    
    
};
