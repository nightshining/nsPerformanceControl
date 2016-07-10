#pragma once
#include "ofMain.h"
#include "ofxControlUtils.h"

class NoiseSphere {
    
private:
    
    float radious;
    float noiseScale;
    float timeScale;
    float scale;
    ofColor c;
    ofxControlUtils ctrl;

    
    float x, easing;
    
public:
    
NoiseSphere(){
    
    radious = 250;
    noiseScale = 0.009f;
    timeScale = 0.6f;
    scale = 0.5f;
    c = ofColor::white;
    easing = 0.09f;
    
}
float addEase(float valSmooth) {
        
        float targetX = valSmooth;
        float deltaX = targetX - x;
        x += deltaX * easing;
        return x;
        
}
void draw(){

    ofPushStyle();
    ofPushMatrix();

    ofTranslate(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f);
    ofScale(scale, scale);
    float timeZ = ofGetElapsedTimef() * 15.0f;
    float timeX = ofGetElapsedTimef() * 25.0f;
    ofRotateZ(scale + timeZ);
    ofRotateX(scale + timeX);
    
    ofSetColor(c);
    ofNoFill();
    
    //Multiple Shapes
    
    int holes = 3;
    
    for(float y = -radious * 2.0 / holes; y <= radious * 2.0 / holes; y+=4){
        
        c.a = y * 0.5f;
        
        //Individual Shape
        
        float r = radious * asin(abs(y / radious));
        
        
        ofBeginShape();
        
        int resolution = 128;
        
        for(float radian = 0; radian < TWO_PI; radian += TWO_PI / resolution){
            
            float x = r * cos(radian);
            float z = r * sin(radian);
            
            //float noise =  ofMap(ofNoise(x * noiseScale, ofGetElapsedTimef() * timeScale, z * noiseScale), 0, 1, -radious / 3, scale + radious / 3);
            float noise =  ofMap(ofNoise(x * noiseScale + scale * 5.0f + timeScale, scale, noiseScale), 0, 1, -radious / 3, scale + radious / 3);
            
            float yy = scale * y + noise;

                if( yy > radious ){
            
                    yy = radious;

                }
            
            float rr = radious * cos(sin(abs(yy / radious)));
            float xx = rr * cos(radian) * scale;
            float zz = rr * sin(radian) * scale;
            
            ofVertex(xx, yy, zz);
            }
        ofEndShape();
        }
    ofPopMatrix();
    ofPopStyle();
    
    }
    
    void triggerScale(bool toggle){
        
        float valToScale = addEase(ofMap(ctrl.rampToggle(toggle, 0.6f, 0.8f), 0.0f, 1.0f, 0.5f, 0.8f));
        
        scale = valToScale;
    }

};