#pragma once

#include "ofMain.h"
#include "ofxTween.h"

class Waves {
    
private:
    
    int total;
    float freq, alpha, scale, noiseAmt;
    ofColor c;
    ofPoint pos;
    ofxTween tween;
    ofxEasingLinear ease;
    int duration;
    
    
public:
    
    Waves() {
        
        scale = .5;
        total = 100;
        freq = 0.0;
        alpha = 0.0;
        c = ofColor(240, 240, 230);
        pos = ofPoint(0,0);
        duration = 2000;
    }
    
void draw() {

    if (tween.isCompleted()) {
        
        total -= 10;
        
        if (total <= 0.0) {
            
            total = 0.0;
        }
        
    } else {
        
        total = ofMap(tween.update(), 0, 1, 5, 850);
    }
    
    ofPushStyle(); {
    ofSetLineWidth(.05);
        
        for (int j = 0; j < 75; j++){
            
            //Move waves
            //total = ofMap(noiseAmt, 0,1,5,250);

            freq = sin(ofGetElapsedTimef() * 5) * total - sin(ofGetElapsedTimef() * 5) * 25;
            
            
            alpha = ofMap(sin(j) * 255, -255, 255, 230, 255);
            
            ofPushMatrix();
            ofTranslate(pos);
            ofScale(scale, 1.0);
            ofTranslate(0, -j * 3);
            
            ofSetColor(c, alpha);
            ofNoFill();
            
            ofBeginShape();
            {
                ofCurveVertex(0, 0);
                ofCurveVertex(0, 0);
                
                if (j == 2) {
                    ofSetColor(255, 0, 100, 200);
                }
                
                for(int i = 0; i < 25; i++) {
                    ofCurveVertex( ofGetWidth() * .1 + i * 15, ofNoise(i + ofGetElapsedTimef() * ofMap(noiseAmt, 0.0, 1.0, 5.0, 250.0)) * cos(ofGetElapsedTimef() * 5) * freq);
                }
                ofCurveVertex(ofGetWidth() * .5, 0);
                ofCurveVertex(ofGetWidth() * .5, 0);
                
            }
            
            ofEndShape(false);
            ofPopMatrix();
            
        }
        
    } ofPopStyle();
    
    }
    
//    void setNoise(float amt) {
//        
//        noiseAmt = amt;
//    }
    
    void setNoise() {
            
        tween.setParameters(0,ease,ofxTween::easeInOut,0.01,1.0,duration,0);

    }

    void setPos(ofPoint position) {
        
        pos = position;
    }
    
};
