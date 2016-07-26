#pragma once
#include "ofMain.h"


class PngSequence {
    
private:
    
    int   appFPS;
    float sequenceFPS;
    bool  bFrameIndependent;
    int   frameIndex;
    ofColor fullColor;
    
    vector <ofImage> images;
    
public:
    PngSequence(){
        
        bFrameIndependent = true;
        sequenceFPS = 24;
        frameIndex = 0;
        fullColor = ofColor(255,255,255);

    }
    void setup(string directory){
      
        ofDirectory dir;
        
        int nFiles = dir.listDir(directory);
        
        if(nFiles) {
            
            for(int i=0; i<dir.numFiles(); i++) {
                
                // add the image to the vector
                string filePath = dir.getPath(i);
                images.push_back(ofImage());
                images.back().allocate(640,480,OF_IMAGE_COLOR_ALPHA);
                images.back().loadImage(filePath);
                
            }
        }
        
    }
    
    void update(){
        
        
        frameIndex = 0;
        
        if(bFrameIndependent) {
            // calculate the frame index based on the app time
            // and the desired sequence fps. then mod to wrap
            frameIndex = (int)(ofGetElapsedTimef() * sequenceFPS) % images.size();
        }
        else {
            // set the frame index based on the app frame
            // count. then mod to wrap.
            frameIndex = ofGetFrameNum() % images.size();
        }
        
    }
    
    void draw(ofPoint pos){
        
        ofPushStyle();
        ofPushMatrix();
        
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        images[frameIndex].setAnchorPercent(0.5f,0.5f);
        ofSetColor(fullColor);
        images[frameIndex].draw(pos);
        
        ofDisableBlendMode();
        ofPopMatrix();
        ofPopStyle();
    }
    
    void setAlphaChannel(int alpha){
        
        fullColor.a = alpha;
    }

};