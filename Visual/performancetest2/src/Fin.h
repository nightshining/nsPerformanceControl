#pragma once

#include "ofMain.h"

class Fin {
    
private:
    
    float x, y, easing;
    float timeX, timeY, noise;
    float setMovementX, setMovementY;
    ofMesh mesh;
    ofPoint pos;
    
public:
    
    Fin() {
        
        mesh.setMode(OF_PRIMITIVE_POINTS);
        glPointSize(.50);
        noise = 0.0;
        easing = 0.005;
        
    }
    
    void draw() {
        
        //Begin Mesh Total Size
        ofSetSphereResolution(8);
        
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
        
        int meshAmt = 180;
        
        for (float u = 0.0; u < TWO_PI; u += PI / meshAmt) {
            
            for (float v = 0.0; v < PI; v += PI / meshAmt) {
                
                float size = 150 + meshAmt * 0.25;
                float x = sin(timeX + u) * size;
                float y = sin(v + u) * ofNoise(u + timeY) * size + cos(timeY * u) * 25;
                float z = sin(u * cos(v)) * size;
                
                ofFloatColor c = ofFloatColor(1.,1.,1., u * 0.10);
                mesh.addColor(c);
                
                ofVec3f vec = ofVec3f(x,y,z);
                mesh.addVertex(vec);
                
            }
        }
        
        float r = ofGetElapsedTimef() * .05;
        
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateX(r);
        ofRotateY(r);
        ofRotateZ(r);
        mesh.draw();
        ofPopMatrix();
        
    }
    
    void setMovement(float _setX, float _setY) {
        
        setMovementX = _setX;
        setMovementY = _setY;
    }
    
    void setPos(ofPoint set) {
        
        pos = set;
    }
    
    
    
};
