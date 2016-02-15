
#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"
#include "ofxTween.h"



class DeformedSphere : public ofxControlUtils {
    
private:
    
    ofVboMesh mesh;
    ofFloatColor c;
    ofVec3f coords;
    ofColor color;
    ofPoint pos;
    float alpha, addNoise, m;
    int size, maxSize, minSize;

    
    ofxTween pulse;
    ofxEasingLinear easing;

public:
    
DeformedSphere() {
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    //alpha = 0.12;
    alpha = 0.15;
    addNoise = 0.0;
    size = 170;
    maxSize = 300;
    minSize = size;
    c = ofFloatColor(.05,0.95,0.8);
    pulse.setParameters(easing, ofxTween::easeInOut, maxSize, minSize, 80, 0);
    
    
}

void draw(){
    
    alpha -= 0.03;
    
    if (alpha <= 0.0) {
        
        alpha = 0.0;
    }
    
    if (pulse.isCompleted() && pulse.update() > minSize) {
        
        pulse.setParameters(easing, ofxTween::easeInOut, maxSize, minSize, 80, 0);
        
    }
    
    mesh.clear();
    mesh.clearColors();
    
    
    addNoise += 0.05;

    
    int res = 80;
    for (float u = 0.0; u < TWO_PI; u += PI / res ) {
        for (float v = 0.0; v < PI; v += PI / res ) {
            //size = pulse.update();
            coords.x = sin(sin(sin(v) * cos(u))) * ofNoise(v + cos(u) + addNoise) * ofNoise(m * sin(u + v)) * size * 2;
            coords.y = sin(sin(sin(v) * sin(u))) * ofNoise(u + sin(v) + addNoise) * ofNoise(m * sin(u + v)) * size;
            coords.z = sin(sin(cos(v))) * size / 1;
            color = ofFloatColor(c, u * alpha);
            
            
            glPointSize(1.0);
            //Create
            mesh.addColor(color);
            ofVec3f vec = ofVec3f(coords);
            mesh.addVertex(vec);

        }
    }
    
    
    float r = ofGetElapsedTimef() * 35.0;
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(pos);
    ofRotateY(r);
    ofRotateZ(r);
    mesh.draw();
    ofPopMatrix();
    ofPopStyle();
    
}
void setDeform(float val) {

    m = ofMap(val, 0.0, 1.0, -3.0, 3.0, true);
}
    
void setPosition(ofPoint _pos) {
    
    pos = _pos;
}

void setPulse() {
    
    alpha = 0.15;
    //pulse.setParameters(easing, ofxTween::easeInOut, minSize, maxSize, 200, 0);
 
}
    
    

};

