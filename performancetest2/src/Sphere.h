#pragma once

#include "ofMain.h"

class Sphere {
    
private:
    
    vector<float> alpha;
    float counter, boxAlpha, scale;
    float trigger;
    ofPoint pos;

public:
    
    Sphere() {
        int colorAmt = 50;
        alpha.resize(colorAmt);
        scale = 0.4;
        counter = 0.003;
        boxAlpha = 0.0;
        trigger = 1.0;
        pos = ofPoint(ofGetWidth() * .5, ofGetHeight() * .5);
        
    }
    
    void draw() {
        
        
        for (int i = 0; i < 50; i++) {
            
            ofPushStyle();
            ofSetCircleResolution(60);
            ofPushMatrix();
            ofTranslate(pos);
            ofScale(scale, scale);
            float move = counter * (i + 20);
            ofRotateX(move);
            ofRotateY(move);
            
            if (trigger == 1.0) {
                
                float makeSphereLines = 1.0;
                counter = ofNoise(ofGetElapsedTimef() * ofRandom(3, 5)) * makeSphereLines * 3.0;
                
                for (int a = 0; a < alpha.size(); a++ ) {
                    alpha[a] = ofNoise(a) * 200;
                }
        
            } else {
               
                for (int a = 0; a < alpha.size(); a++ ) {
                   
                    ofSetColor(255, alpha[i]);
                    ofNoFill();
                    
                    if ( i == 45 ) {
                        ofSetColor(0,255,200, alpha[i]);
                        ofNoFill();
                    }
               }
            
                ofCircle(0, 0, ofGetWidth() * .25);
                ofPopMatrix();
                ofPopStyle();
                
                for (int a = 0; a < alpha.size(); a++) {
                    
                    alpha[a] -= move * .005;
                    
                    if ( alpha[a] <= 0.0 ) {
                        
                        alpha[a] = 0.0;
                        
                    }
                }
                
            }
        }
        
        ofPushStyle();
        ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(255, boxAlpha);
        ofFill();
        ofTranslate(pos);
        ofRect(0, 0, ofGetWidth() * .4, ofGetHeight() * .65 );
        ofPopMatrix();
        ofPopStyle();
        
        if ( trigger == 1.0 && ofRandomf() > .95) {
            
            boxAlpha = ofRandom(50, 255);
            
        }
        
        boxAlpha -= 5.0;
        
        
        if (boxAlpha <= 0.0 ) {
            
            boxAlpha = 0.0;
        }
        
        pos = ofPoint(ofGetWidth() * .5, ofGetHeight() * .5);

        
    }
    
    void setTrigger(int value) {
        
        trigger = value;
        
    }
    
};
