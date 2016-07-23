
#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"

class FadeShape {
    
private:
    
    ofxControlUtils fade;
    ofColor c, c2;
    ofPoint p;
    ofMesh mesh;
    

    float sendNoise, amp, destroy;
    ofxControlUtils noiseCtrl, noiseCtrl2;
    
    
    ofxTween pulse;
    ofxEasingLinear easing;
    float minSize, maxSize;
    
public:
    
    FadeShape() {
    
        mesh.setMode(OF_PRIMITIVE_POINTS);
        minSize = 90;
        maxSize = 125;
        pulse.setParameters(easing, ofxTween::easeInOut, maxSize, minSize, 20000, 0);

    }
    
    void addNoise() {
    
        float liquidness = 50;
        
        float amplitude = amp / destroy;
        float speedDampen = 5;
        
        
        vector<ofVec3f>& verts = mesh.getVertices();
        
        for(unsigned int i = 0; i < verts.size(); i++){
            
            float liquidMesh = ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen) * amplitude;
            
            sendNoise = ofSignedNoise(verts[i].x/liquidness, verts[i].y * ofGetElapsedTimef() * 50, verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen) * amplitude;
            
            verts[i].x += liquidMesh;
            verts[i].y += sendNoise;
            verts[i].z += liquidMesh;
            
            mesh.setVertex(i, verts[i]);
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
        ofRotateX(ofGetElapsedTimef() * 5.0f);
        ofRotateY(ofGetElapsedTimef() * 15.0f);
        ofRotateZ(ofGetElapsedTimef() * 20.0f);
        mesh.draw();
        ofPopMatrix();
        ofPopStyle();
        
        
        mesh.clear();
        float tweenVal = pulse.update();
        float size = tweenVal;
        float alpha = 0.08;
        
        int total = 5000;
        float azimuth = 128.0f * PI / total;
        float inclination = PI / total;
        float radius = tweenVal;
        
        ofVec3f center = ofVec3f(ofGetWidth()*0.5f, ofGetHeight()*0.5f, 0.0);
        
        for (int i = 0; i < total; ++i) {
            
            float x = radius * sin( inclination * i ) * cos( azimuth * i );
            float y = radius * cos( inclination * i );
            float z = radius * sin( inclination * i ) * sin( azimuth * i );
            
            ofVec3f vec = ofVec3f(x,y,z);
            mesh.addVertex(vec);
            c2.a = ofMap(i, 0, total, 0, 255, true);
            mesh.addColor(c2);
            
        }
        
        addNoise();
        
        if (pulse.isCompleted() && pulse.update() > minSize) {
            
            pulse.setParameters(easing, ofxTween::easeInOut, maxSize, minSize, 200, 0);
            
        }
    }
    
    void triggerFade(bool trigger){
        
        float cFade = fade.rampToggle(trigger, 0.08f, 0.07f) * 225;
        c = ofColor(cFade);
        c2 = ofColor(ofMap(cFade, 255,0,0,255));
        
        int verts = mesh.getVertices().size();
        
        for (int i = 0; i < verts; i++){
            
            c2.a = ofMap(i, 0, verts, 25, 255, true);
            mesh.setColor(i, c2);
        }
        
    }
    
    void setPos(ofPoint pos){
        
        p = pos;
        
    }
    
    void triggerPulse(){
        
        pulse.setParameters(easing, ofxTween::easeInOut, minSize, maxSize, 50, 0);
       
    }
    
    void setNoise(float value) {
        
        float n = noiseCtrl.rampToggle(value, 0.05, 0.03);
        amp = ofMap(n, 0.0, 1.0, 0, 200, true);
        float n2 = noiseCtrl2.rampToggle(value, 0.4, 1.0);
        destroy = ofMap(n2, 0.0, 1.0, 5.0, 10.0, true);
        
        

    }
};