#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"

class NoiseWave : public ofxControlUtils {
    
private:
    
    ofMesh mesh;
    float sendNoise, amp;
    float time, noise, size, alpha, boxAlpha, trigger;
    float randomRotate;
    int randomTrigger;
    ofFloatColor color;
    ofPoint pos;
    ofVec3f coords, rotate;
    ofxControlUtils noiseCtrl;
    
    
public:
    
    NoiseWave() {
        
        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        noise = 0.0;
        size = 0.0;
        coords = ofVec3f(0.0,0.0,0.0);
        rotate = ofVec3f(0.0,0.0,0.0);
        color = ofColor(0.0,0.0,0.0);
        time = 0.0;
        sendNoise = 0;
        amp = 0;
        randomTrigger = 0.0;
        
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
    void flashBox(){
        
        ofPushStyle();
        ofPushMatrix();
        //ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(255, boxAlpha);
        ofFill();
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        ofPopMatrix();
        ofPopStyle();
        
        if ( trigger == 1.0 && ofRandomf() > .35) {
            
            boxAlpha = ofRandom(50, 255);
            
        }
        
        boxAlpha -= 5.0;
        
        
        if (boxAlpha <= 0.0 ) {
            
            boxAlpha = 0.0;
        }
        
    }

    void draw() {

        pos = ofPoint(ofGetWidth() * .70, ofGetHeight() * .5);

        mesh.clear();
        mesh.clearColors();
        
        int spacing = 130;
      
        for (float u = 0.0; u < TWO_PI; u += PI / spacing) {
            for (float v = 0.0; v < TWO_PI; v += PI / spacing) {
                
                time = ofGetElapsedTimef() * .25;
                noise =  ofNoise(time * .05);
                size = 150;
                
                float coordX;
                float coordY;
                
                switch (randomTrigger) {
                    case 0:
                        coordX = sin(v * time) + cos(u + v)  * size;
                        coordY = sin(v) * size;
                        break;
                    case 1:
                        coordX = cos(v * time) + sin(u + v)  * size;
                        coordY = sin(v) * size;
                        break;
                    case 2:
                        coordX = cos(v + u * noise) * size;
                        coordY = sin(noise * v + time) * size;
                        break;
                    case 3:
                        coordX = cos(v + u * noise) * size;
                        coordY = cos(noise * v + time) + sin(u * noise) * size;
                        break;
                    default:
                        coordX = cos(v + u) * size;
                        coordY = cos(noise * v + time) + sin(u * noise) * size;
                        break;
                }
                
                coords.x = coordX;
                coords.y = coordY;
                coords.z = sin(u + time + noise * cos(v + time)) * size;
            
                //rotate.set(time * .9, time * 5.0, time);

//                color = ofFloatColor(0.86,0.2,0.50, u * alpha);
                color = ofFloatColor(1.0f,1.0f,1.0f, u * alpha);

                //Create
                mesh.addColor(color);
                ofVec3f vec = ofVec3f(coords);
                mesh.addVertex(vec);
            }
        }
        
        addNoise();
        
        //Flashing box draw
        flashBox();
        
        
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateZ(randomRotate);
        ofRotateX(rotate.x);
        ofRotateY(rotate.y);
        ofRotateZ(rotate.z);
        mesh.draw();
        ofPopMatrix();
        ofPopStyle();
        

    }
    void setFlashTrigger(int toggle) {
        
        trigger = toggle;
        
    }
    
    void setAlpha(float amt) {
        
        alpha = ofMap(rampToggle(amt, 0.7, 0.8), 0.0, 1.0, 0.0, 0.1, true);
    }
    
    void setRandomTrigger() {
        
        randomTrigger = ofRandom(4);
        randomRotate = ofRandomf();
        
    }
    
    void setNoise(float value) {
        
        amp = ofMap(noiseCtrl.rampToggle(value, 0.06, 0.05), 0.0, 1.0, 0, 1000 / 2, true);
    }
    
    
    
};
