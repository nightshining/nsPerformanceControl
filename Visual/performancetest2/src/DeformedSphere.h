
#pragma once

#include "ofMain.h"
#include "ofxControlUtils.h"
#include "ofxTween.h"



class DeformedSphere : public ofxControlUtils {
    
private:
    
    ofMesh mesh;
    ofFloatColor c;
    ofVec3f coords;
    ofColor color;
    ofPoint pos;
    float alpha, addNoise;
    int size, maxSize, minSize;
    
    ofxTween move, distort;
    ofxEasingLinear easing;
    
public:
    
DeformedSphere() {
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    alpha = 0.12;
    addNoise = 0.0;
    size = 150;
    maxSize = 300;
    minSize = size;
    c = ofFloatColor(.05,0.95,0.8);
    move.setParameters(easing, ofxTween::easeInOut, maxSize, minSize, 80, 0);
    
}

void draw(){
    
    if (move.isCompleted() && move.update() > minSize) {
        
        move.setParameters(easing, ofxTween::easeInOut, maxSize, minSize, 80, 0);
        distort.setParameters(easing, ofxTween::easeInOut, 0.0, 1.0, 800, 0);
        
    }
    
    mesh.clear();
    mesh.clearColors();
    
    
    addNoise += 0.01;
    
    
    int res = 80;
    for (float u = 0.0; u < TWO_PI; u += PI / res ) {
        for (float v = 0.0; v < PI; v += PI / res ) {
            
            size = move.update();
            coords.x = sin(sin(sin(v) * cos(u))) * ofNoise(v + cos(u) + addNoise) * size;
            coords.y = sin(sin(sin(v) * sin(u))) * ofNoise(distort.update() * u + sin(v) + addNoise) * size / 1;
            coords.z = sin(sin(cos(v))) * size / 1;
            color = ofFloatColor(c, u * alpha);
            
            
            glPointSize(1.0);
            //Create
            mesh.addColor(color);
            ofVec3f vec = ofVec3f(coords);
            mesh.addVertex(vec);
        }
    }
    
    
    float r = ofGetElapsedTimef() * 5.0;
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(pos);
    
    ofRotateY(r);
    ofRotateZ(r);
    mesh.draw();
    ofPopMatrix();
    ofPopStyle();
    
    
}
    
void setPosition(ofPoint _pos) {
    
    pos = _pos;
}

void keyPressed(int key){
    
    
    move.setParameters(easing, ofxTween::easeInOut, minSize, maxSize, 200, 0);
    distort.setParameters(easing, ofxTween::easeInOut, 0.0, 1.0, 100, 0);
    
}
};

