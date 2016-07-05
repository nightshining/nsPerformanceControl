#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"

class MiniNoise : public ofxControlUtils {
    
private:
    
    ofMesh mesh;
    float sendNoise, amp, liquid;
    float time, noise, size, alpha;
    ofFloatColor color;
    ofPoint pos;
    ofVec3f coords;
    
    float x, y, easing;
    float timeX, timeY;
    float setMovementX, setMovementY;
    
public:
    
    MiniNoise() {
        
        glPointSize(0.50f);
        mesh.setMode(OF_PRIMITIVE_POINTS);
        noise = 0.0;
        size = 0.0;
        coords = ofVec3f(0.0,0.0,0.0);
        color = ofColor(0.0,0.0,0.0);
        time = 0.0;
        sendNoise = 0;
        amp = 0;
        alpha = 0.20; //0.25
        
        easing = 0.5 / 10;

    }
    
    void addMovement() {
    
        float targetX = setMovementX;
        float deltaX = targetX - x;
        x += deltaX * easing;
        timeX = x;
        
        float targetY = setMovementY;
        float deltaY = targetY - y;
        y += deltaY * easing;
        timeY = y;
        
    }
    
    void addNoise() {
        
        float liquidness = liquid;
        float amplitude = amp;
        float speedDampen = 5;
        float slowSpeed = ofGetElapsedTimef() * 1.0;
        
        vector<ofVec3f>& verts = mesh.getVertices();
        
        for(unsigned int i = 0; i < verts.size(); i++){
            
            float liquidMesh = ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, slowSpeed/speedDampen) * amplitude;
            
            sendNoise = ofSignedNoise(verts[i].x/liquidness, verts[i].y * slowSpeed, verts[i].z/liquidness, slowSpeed/speedDampen) * amplitude;
            
            verts[i].x += liquidMesh;
            verts[i].y += 0.0f;
            verts[i].z += liquidMesh;
            
            mesh.setVertex(i, verts[i]);
        }
    }
    void draw() {
        
        mesh.clear();
        mesh.clearColors();
        
        addMovement();

        int spacing = 125;
        
        for (float u = 0.0; u < PI; u += PI / spacing) {
            for (float v = 0.0; v < PI; v += PI / spacing) {
                
                time = ofGetElapsedTimef() * 0.5;
                noise =  ofNoise(time * .25);
                size = 200;
                  
                coords.x = sin(time + u) * size;
                coords.y = sin(v * u) * ofNoise(u + timeY) * size;
                coords.z = sin(u) * cos(v) * size;
                
                color = ofFloatColor(0.9f,.95f, 1.0f, u * alpha);

                //Create
                mesh.addColor(color);
                ofVec3f vec = ofVec3f(coords);
                mesh.addVertex(vec);
            }
        }

        addNoise();
        
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(pos);
        int vel = 250;
        ofRotateX(timeX * vel);
        ofRotateY(timeY * vel);
        ofRotateZ(timeY * vel);
        mesh.draw();
        ofPopMatrix();
        ofPopStyle();
        
    }
    
    void setMovement(float _setX, float _setY) {
        
        setMovementX = _setX;
        setMovementY = _setY;
    }
    
    
    void setNoise(float value) {
        
        float amt = rampToggle(value, 0.08, 0.1);
        amp = ofMap(amt, 0.0, 1.0, 0, 20);
        liquid = ofMap(amt, 0.0, 1.0, -50, 50);
        
        
    }
    
    void setPos(ofPoint position) {
        
        pos = position;
    }
    
};
