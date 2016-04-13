#pragma once

#include "ofMain.h"


class LongWave {
    
private:
    
    ofVec3f pos;
    
    ofFloatColor c;
    float size;
    float alpha;
    float time;
    
    float xstep = 5;
    float ystep = 4;
    float y = 0;
    
    ofVec3f n;
    
    //Easing//
    float ease1 = 0.0;
    float ease2 = 0.0;
    float easing = 0.1; // easing percentage
    
    
public:
    
    LongWave() {
        
        n = ofVec3f(ofRandom(100),ofRandom(100),ofRandom(1000));
        
        //Create a temporary mesh with a for loop//
        
        pos = ofVec3f(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f);
        
        alpha = 0.08;
        
        
    }
    
    void draw() {
        
        float parameter1 = ofNormalize(ofGetMouseX(), 0, ofGetWidth()) * 5.0;
        float parameter2 = ofNormalize(ofGetMouseY(), ofGetHeight(), 0);
        float mx = ease1 += (parameter1 - ease1) * easing;
        float my = ease2 += (parameter2 - ease2) * easing;
        
        ofNoFill();
        
        ofTranslate(0, ofGetHeight() * 0.5f);
        ofScale(1.0, my);
        for (float j = 0; ofGetHeight() + ystep > j; j+= ystep) {
            
            if (j < ofGetWidth() * 0.5) {
                c = ofFloatColor(1.0, 1.0, 1.0, ofNormalize(j, 0,ofGetHeight()));
                
            } else {
                
                c = ofFloatColor(0.8, 0.97, 1.0, ofNormalize(j, ofGetHeight(),0));
                
            }
            
            ofSetColor(c);
            
            ofBeginShape();
            ofVertex(-100, ofGetHeight() * 0.5f);
            
            for (float i = 0; i < ofGetWidth() + xstep; i+=xstep) {
                
                n.x = i / 250;
                n.y = j / 250;
                y = ofMap(ofNoise(n.x,n.y, n.z), 0, 1, -50, 50) + sin(j);
                
                ofCurveVertex(i, y);
                
            }
            
            ofVertex(ofGetWidth() + 100, ofGetHeight() * 0.5f);
            ofEndShape();
        }
        
        
        n.z = mx;
        
        
    }
    
    
};