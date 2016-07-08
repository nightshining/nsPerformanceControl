
#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"

class FadeShape {
    
private:
    
    ofxControlUtils fade;
    ofColor c, c2;
    ofPoint p;
    ofMesh mesh;
    
public:
    
    FadeShape() {
        
        mesh.setMode(OF_PRIMITIVE_POINTS);
        
        const float size = 100;
        const float alpha = 0.08;
        
        const int total = 5000;
        const float azimuth = 128.0 * PI / total;
        const float inclination = PI / total;
        const float radius = 100.0f;
        
        ofVec3f center = ofVec3f(ofGetWidth()*0.5, ofGetHeight()*0.5, 0.0);
        
        for (int i = 0; i < total; ++i) {
            
            float x = radius * sin( inclination * i ) * cos( azimuth * i );
            float y = radius * cos( inclination * i );
            float z = radius * sin( inclination * i ) * sin( azimuth * i );
            
            ofVec3f vec = ofVec3f(x,y,z);
            mesh.addVertex(vec);
            c2 = ofFloatColor::black;
            c2.a = ofMap(i, 0, total, 50, 255, true);
            mesh.addColor(c2);
            
        }

        
    }
    
    void draw() {
        
        ofPushStyle();
        ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofTranslate(p);
        int w = ofGetWidth() * 0.35f;
        int h = ofGetHeight() * 0.5f;
        ofSetColor(c);
        ofRect(0,0,w,h);
//        ofSetColor(c2);
//        ofCircle(0,0,10,10);
        ofRotateX(ofGetElapsedTimef() * 5.0f);
        ofRotateY(ofGetElapsedTimef() * 15.0f);
        ofRotateZ(ofGetElapsedTimef() * 20.0f);
        mesh.draw();
        ofPopMatrix();
        ofPopStyle();
        
    }
    
    void triggerFade(bool trigger){
        
        float cFade = fade.rampToggle(trigger, 0.08f, 0.07f) * 225;
        c = ofColor(cFade);
        c2 = ofColor(ofMap(cFade, 255,0,0,255));
        
        for (int i = 0; i < mesh.getVertices().size(); i++){
            
            mesh.setColor(i, c2);
        }
        
    }
    
    void setPos(ofPoint pos){
        
        p = pos;
        
    }
};