#pragma once

#include "ofMain.h"
#include "PngSequence.h"

class Fin {
    
private:
    
    float x, y, easing;
    float timeX, timeY, noise;
    float setMovementX, setMovementY;
    float sendNoise, amp, counter;
    ofVboMesh mesh;
    ofPoint pos;
    PngSequence png;
    
    
public:
    
    Fin() {
        
        mesh.setMode(OF_PRIMITIVE_POINTS);
        glPointSize(.8);
        noise = 0.0;
        easing = 0.05;
        
        //PNG//
        png.setup("images/MicroPNG");

    }
    
    void draw() {
        
        //Begin Mesh Total Size
        
        mesh.clearVertices();
        mesh.clearColors();
        
        float targetX = setMovementX;
        float deltaX = targetX - x;
        x += deltaX * easing;
        timeX = x;
        
        float targetY = setMovementY;
        float deltaY = targetY - y;
        y += deltaY * easing;
        timeY = y;
        
        int meshAmt = 100;
        
        for (float u = 0.0; u < TWO_PI; u += PI / meshAmt) {
            
            for (float v = 0.0; v < PI; v += PI / meshAmt) {
                
                float size = 175 + meshAmt * 0.25;
                float x = sin(timeX + u) * size;
                float y = sin(v + u) * ofNoise(u + timeY) * size + cos(timeY * u) * 25;
                float z = sin(ofGetElapsedTimef() + u * cos(v)) * size;
                
                ofFloatColor c = ofFloatColor(1.,1.,1., u * 0.15);
                mesh.addColor(c);
                
                ofVec3f vec = ofVec3f(x,y,z);
                mesh.addVertex(vec);
                
            }
        }
        
        addNoise();
        
        float r = ofGetElapsedTimef() * 0.05;
        
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateX(r);
        ofRotateY(r);
        ofRotateZ(r);
        mesh.draw();
        ofPopMatrix();
        
        
        /// PNG //
        png.update();
        png.draw(pos);
        
        
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
    
    void setNoise(float amt) {
        
       // amp = ofMap(noiseCtrl.rampToggle(value, 0.06, 0.05), 0.0, 1.0, 0, 1000 / 2, true);
        
        amp = ofMap(amt, 0.0, 1.0, 0.0, 1000, true);
    }
    
    
    void setMovement(float val) {

        setMovementX = ofGetElapsedTimef() * 3.0;
        setMovementY = val;
    }
    
    void setPos(ofPoint set) {
        
        pos = set;
    }
    
    
    
};
