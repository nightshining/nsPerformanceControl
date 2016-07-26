#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"
#include "PngSequence.h"

class Mold : public ofxControlUtils {
    
private:
    
    ofMesh mesh;
    
    float time, noise, size, alpha, boxAlpha;
    float trigger;
    ofFloatColor color;
    ofVec3f coords, rotate;
    ofPoint pos;
    PngSequence png;
    
public:
    
    Mold() {
        
        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        noise = 0.0;
        size = 0.0;
        coords = ofVec3f(0.0,0.0,0.0);
        rotate = ofVec3f(0.0,0.0,0.0);
        color = ofColor(0.0,0.0,0.0);
        time = 0.0;
        trigger = 0.0;

        //PNG//
        png.setup("images/MoldPNG");

        
    }
    
    void draw() {
        
        alpha -= 0.01;
        
        if (alpha <= 0.0) {
        
            alpha = 0.0;
        }
        
        mesh.clear();
        mesh.clearColors();
        
        for (float u = 0.0; u < 2 * PI; u += PI / 75) {
            for (float v = 0.0; v < 2 * PI; v += 2 * PI / 75) {
                
                size = 150;
                time = ofGetElapsedTimef() * 2.0;
                coords.set(sin(u) * cos(v + time) * size, cos(u) * sin(v) * size, sin(v) * cos(v) * size);
                
//                color = ofFloatColor(0.65,0.90,0.95, u * alpha);
                color = ofFloatColor(1.0,1.0,1.0, u * alpha);
                
              
                
                //Create
                mesh.addColor(color);
                ofVec3f vec = ofVec3f(coords);
                mesh.addVertex(vec);
            }
        }
        
        //Flashing box draw
        flashBox();
        
        
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(pos);
        mesh.draw();
        ofPopMatrix();
        ofPopStyle();
        
        png.update();
        
        //PNG//
        
        
        
        if (boxAlpha < 5) {
            
            png.draw(pos);
        }
        
    }
    
    void setAlpha() {
        
        alpha = .09;

    }
    
    void setPos(ofPoint set) {
        
        pos = set;
    }
    
    void setTrigger(int toggle) {
        
        trigger = toggle;
        
    }
    void flashBox(){
        
        ofPushStyle();
        ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(255, boxAlpha);
        ofFill();
        ofTranslate(pos);
        ofRect(0, 0, ofGetWidth() * .4, ofGetHeight() * .6 );
        ofPopMatrix();
        ofPopStyle();
        
        if ( trigger == 1.0 && ofRandomf() > .95) {
            
            boxAlpha = ofRandom(50, 255);
            
        }
        
        boxAlpha -= 5.0;
        
        
        if (boxAlpha <= 0.0 ) {
            
            boxAlpha = 0.0;
        }

    }
    
    
};
