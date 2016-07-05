#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"

class Ghost : public ofxControlUtils {
    
private:
    
    ofMesh mesh ;
    
    float time, noise, size;
    ofFloatColor color;
    ofVec3f coords, rotate;
    ofPoint pos;
    float timer, alpha;
    
    
public:
    
    Ghost() {
        
        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        noise = 0.0;
        size = 0.0;
        coords = ofVec3f(0.0,0.0,0.0);
        float r = ofRandomf();
        rotate = ofVec3f(r,r,r);
        color = ofColor(0.0,0.0,0.0);
        time = 0.0;
        
//        if (ofRandomf() > .5) {
//            
//            pos = ofPoint(ofGetWidth() * .15, ofGetHeight() * .5);
//            
//        } else {
//        
//            pos = ofPoint(ofGetWidth() * .85, ofGetHeight() * .5);
//        
//        }
        
        timer = 0.0;
        alpha = 0.08;
    }
    
    void draw() {
        
        mesh.clear();
        mesh.clearColors();
        
        for (float u = 0.0; u < 2 * PI; u += PI / 75) {
            for (float v = 0.0; v < 2 * PI; v += 2 * PI / 75) {
                
                time = ofGetElapsedTimef() * 1.0f;
                noise = cos(v)+ ofNoise(time) * 5.0f;
                size = 100;
                coords.x = sin(v) * size;
                coords.y = cos(u) * size;
                coords.z = sin(u + time) * cos(noise) * size;
                color = ofFloatColor(.85,0.9,0.90, u * alpha);
                rotate.set(time*15.0,time*10.0,time*5.0);
                
                
                //Create
                mesh.addColor(color);
                ofVec3f vec = ofVec3f(coords);
                mesh.addVertex(vec);
            }
        }
        
        
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateX(rotate.x);
        ofRotateY(rotate.y);
        ofRotateZ(rotate.z);
        mesh.draw();
        ofPopMatrix();
        ofPopStyle();
        
        
//        timer+=0.5;
//        
//        if (timer >= 1.0) {
//            
//            alpha-=0.05;
//            
//            if (alpha < 0) {
//                alpha = 0;
//            }
//        }
        

    }
    
    void triggerAlpha(float value) {
        
        alpha = ofMap(rampToggle(value, .75, .5), 0.0, 1.0, 0.0, 0.1);
        
    }
    
    void setPos(ofPoint set) {
        
        pos = set;
    }
    

};
