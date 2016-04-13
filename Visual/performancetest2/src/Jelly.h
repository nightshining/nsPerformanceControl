#pragma once

#include "ofMain.h"


class Jelly {
    
private:
    
    ofVec3f pos;
    ofMesh tempMesh;
    
    
    float size;
    float alpha;
    float time;
    
    
public:
    
    Jelly() {
        
        //Create a temporary mesh with a for loop//
        
        tempMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        
        pos = ofVec3f(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f);
        size = 100;
        
        alpha = 0.08;
        
        for (float u = 0.0; u < TWO_PI; u += PI / 50) {
            
            for (float v = 0.0; v < TWO_PI; v += 2 * PI / 50) {
                
                
                ofVec3f vec = ofVec3f( sin(u) * size, sin(v + u) * size, sin(-u * cos(v)) * size);
                tempMesh.addVertex(vec);
                ofFloatColor c = ofFloatColor(abs(sin(v)),1.0,0.9, u * alpha);
                tempMesh.addColor(c);
                
            }
        }
        
        
    }
    
    void draw() {
        
        //Now make a local mesh that you can control better//
        
        ofVboMesh mesh = tempMesh;
        
        float amplitude = 10;
        float liquid = 100;
        
        vector<ofVec3f>& verts = mesh.getVertices();
        
        for(unsigned int i = 0; i < verts.size(); i++){
            //
            verts[i].x += ofSignedNoise(verts[i].x/liquid, verts[i].y/liquid,verts[i].z/liquid, ofGetElapsedTimef() * 5.0) * amplitude;
            verts[i].y += ofSignedNoise(verts[i].z/liquid, verts[i].x/liquid,verts[i].y/liquid, ofGetElapsedTimef() * 1.0) * amplitude;
            verts[i].z += ofSignedNoise(verts[i].y/liquid, verts[i].z/liquid,verts[i].x/liquid, ofGetElapsedTimef() * 5.0) * amplitude;
            
            //verts[i].x += sin(verts[i].x * ofGetElapsedTimef() * 0.4) * amplitude;
            
        }
        
        
        
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateX(207);
        ofRotateY(191);
        ofRotateZ(207);
        ofScale(ofGetMouseX() * 0.1, ofGetMouseY() * 0.1);
        mesh.draw();
        ofPopMatrix();
        ofPopStyle();
        
    }
    
    
    
    
};