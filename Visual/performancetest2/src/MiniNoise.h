#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"

class MiniNoise : public ofxControlUtils {
    
private:
    
    ofMesh mesh;
    float sendNoise, amp, liquid;
    float time, noise, size, alpha;
    float randomRotate, rotateTime;
    int randomTrigger;
    ofFloatColor color;
    ofPoint pos;
    ofVec3f coords, rotate;
    
    float x, y, easing;
    float timeX, timeY;
    float setMovementX, setMovementY;
    
public:
    
    MiniNoise() {
        
        glPointSize(.50);
        mesh.setMode(OF_PRIMITIVE_POINTS);
        noise = 0.0;
        size = 0.0;
        coords = ofVec3f(0.0,0.0,0.0);
        rotate = ofVec3f(0.0,0.0,0.0);
        color = ofColor(0.0,0.0,0.0);
        time = 0.0;
        sendNoise = 0;
        amp = 0;
        alpha = 0.20; //0.25
        
        easing = 0.005;

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
            verts[i].y += 0;
            verts[i].z += liquidMesh;
            
            mesh.setVertex(i, verts[i]);
        }
    }
    void draw() {
        
        mesh.clear();
        mesh.clearColors();
        
        addMovement();

        int spacing = 150;
        
        for (float u = 0.0; u < PI; u += PI / spacing) {
            for (float v = 0.0; v < PI; v += PI / spacing) {
                
                time = ofGetElapsedTimef() * 0.5;
                noise =  ofNoise(time * .25);
                size = 150;
                  
                coords.x = sin(time + u) * size;
                coords.y = sin(v + u) * ofNoise(u + timeX + timeY) * size;
                coords.z = sin(u) * cos(v) * size;
                
                rotate.set(time * 0.1, time * 0.5, time);
                
                color = ofFloatColor(.9,.95, 1.0, u * alpha);

                
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
        ofRotateX(rotate.x);
        ofRotateY(rotate.y);
        ofRotateZ(rotate.z);
        mesh.draw();
        ofPopMatrix();
        ofPopStyle();
        
    }
    
    void setMovement(float _setX, float _setY) {
        
        setMovementX = ofMap(_setX, 0,1,0,100);
        setMovementY = ofMap(_setY,0,1,0,100);
    }
    
    
    void setNoise(float value) {
        
//        float amt = rampToggle(value, 0.01, 0.01);
        float amt = rampToggle(value, 0.08, 0.1);
        amp = ofMap(amt, 0.0, 1.0, 0, 20);
        liquid = ofMap(amt, 0.0, 1.0, -50, 50);
        
        
    }
    
    void setPos(ofPoint position) {
        
        pos = position;
    }
    
};
