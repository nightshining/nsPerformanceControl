#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"

class Apple {

private:
    
    ofMesh mesh;
    float time, noise, size, alpha;
    float sendNoise, amp;
    ofFloatColor color;
    ofVec3f coords, rotate;
    ofPoint pos;
    ofxControlUtils noiseCtrl, alphaCtrl, slowAlphaCtrl;
    
    
public:
 
    Apple() {
        
        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        noise = 0.0;
        size = 150.0;
        coords = ofVec3f(0.0,0.0,0.0);
        rotate = ofVec3f(0.0,0.0,0.0);
        color = ofColor(0.0,0.0,0.0);
        time = 0.0;
        sendNoise = 0.0;
        amp = 0.0;
        alpha = 0.0;
        pos = ofPoint(ofGetWidth() * .5, ofGetHeight() * .5);
    }

    void draw() {
            
            mesh.clear();
            mesh.clearColors();
            
            for (float u = 0.0; u < 2 * PI; u += PI / 75) {
                for (float v = 0.0; v < 2 * PI; v += 2 * PI / 75) {
                    
                    //Math
                    time = ofGetElapsedTimef() * 1.0;
                    noise = ofSignedNoise(v + cos(time)) * 5.0f;
                    //size = 100;
                    
                    //coords color
                    coords.x = sin(v) * cos(u) * size;
                    coords.y = noise + cos(v + u) * size;
                    coords.z = sin(u + time + noise * cos(v + time)) * size;
                    color = ofFloatColor(0.10,0.8,0.50, u * alpha);
                    rotate.set(0, 0, 0);
                    
                    //Vertices
                    mesh.addColor(color);
                    ofVec3f vec = ofVec3f(coords);
                    mesh.addVertex(vec);
                }
            }

            addNoise();
        
            ofPushStyle();
            ofPushMatrix();
            ofTranslate(pos);
            ofRotateX(rotate.x);
            ofRotateY(rotate.y);
            ofRotateZ(rotate.z);
            mesh.draw();
            ofPopMatrix();
            ofPopStyle();
            
        pos = ofPoint(ofGetWidth() * .5, ofGetHeight() * .5);
        
//        alpha-=0.5;
//        
//        if (alpha < 0) {
//            alpha = 0;
//        }

        }
    
    void addNoise() {
        
        float liquidness = 50;
        float amplitude = amp / 50;
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
    
    void triggerAlpha(float value) {
        
        alpha = ofMap(alphaCtrl.rampToggle(value, 0.8, .5), 0.0, 1.0, 0.0, 0.08);
        
    }
    
    void triggerAlphaSlow(float value) {
    
        alpha = ofMap(slowAlphaCtrl.rampToggle(value, 0.8, 0.25), 0.0, 1.0, 0.0, 0.05);

    }

    void setNoise(float value) {
        
        amp = ofMap(noiseCtrl.rampToggle(value, 0.06, 0.05), 0.0, 1.0, 0, 1000 / 2, true);
    
    }
    
    void setScale(float value) {
        
        size = value;
    }
    
};
