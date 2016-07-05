
#include "ofMain.h"
#include "ofxMeshUtils.h"
#include "ofxControlUtils.h"

class OrganicShape {
    
public:
    
    OrganicShape(){
        
        stepvalue = 0.07f;
        
        a1value = 2.65381;
        a2value = 1.64623;
        n1value = 10.8462;
        n2value = 2.25662;
        n3value = 0.937191;
        n4value = 1.37344;
            
        a1target = a1value;
        a2target = a2value;
        n1target = n1value;
        n2target = n2value;
        n3target = n3value;
        n4target = n4value;
        
        size = 150.0f;
        
        bToggleWire = true;
        bAlpha = false;
        
        alpha = 0.0f;
        alphaVel = 0.05f;
        
    }
    
    void draw(){
    
    ofPushStyle();
    ofPushMatrix();
        
    glShadeModel(GL_FLAT);
    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
    
    float targetSpeed = 0.08f;
    a1value = moveTowards(a1value, a1target, targetSpeed);
    a2value = moveTowards(a2value, a2target, targetSpeed);
    n1value = moveTowards(n1value, n1target, targetSpeed);
    n2value = moveTowards(n2value, n2target, targetSpeed);
    n3value = moveTowards(n3value, n3target, targetSpeed);
    n4value = moveTowards(n4value, n4target, targetSpeed);
    
    
    mesh.clear();
    int N_X = ceil((2.0*PI) / stepvalue);
    int N_Y = ceil(1.0*PI / stepvalue);
    
    for(int x = 0; x < N_X; x++) {
        for(int y = 0; y < N_Y; y++) {
            
            c.a = y*alpha;
            mesh.addVertex(sf3d(x,y));
            mesh.addColor(c);
        }
    }
    
    
    lastRow.clear();
    
    for(int x = 0; x < N_X; x++) {
        for(int y = 0; y < N_Y-1; y++) {
            
            if(x == N_X-1) {
                
                int idx1 = x*N_Y+y;
                int idx2 = x*N_Y+y+1;
                
                int idx3 = y+1;
                int idx4 = y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
            } else {
                int idx1 = x*N_Y+y;
                int idx2 = x*N_Y+y+1;
                
                int idx3 = (x+1)*N_Y+y+1;
                int idx4 = (x+1)*N_Y+y;
                
                mesh.addTriangle(idx1, idx2, idx3);
                mesh.addTriangle(idx1, idx3, idx4);
                
                if(y == N_Y-2) {
                    lastRow.push_back(idx2);
                }
            }
            
        }
    }
    
    int lastVertex = mesh.getNumVertices()-1;
    
    for(int i=0;i<lastRow.size()-1;i++) {
        mesh.addTriangle(lastRow[i], lastRow[i+1], lastVertex);
    }
    mesh.addTriangle(lastRow[0],lastRow[lastRow.size()-1], lastVertex);
    
    ofxMeshUtils::calcNormals(mesh);

    

        if (bToggleWire) {
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        
        } else {
            
            mesh.setMode(OF_PRIMITIVE_POINTS);
        }
    
    ofTranslate(pos.x, pos.y);
        ofRotateX(ofGetElapsedTimef()*5.0f);
        ofRotateY(ofGetElapsedTimef()*5.0f);
        
    mesh.drawWireframe();
    
    glDisable(GL_DEPTH_TEST);
    
    ofPopMatrix();
    ofPopStyle();
    
    
        if (bAlpha){
            
            alpha+=alphaVel;
        }
        
    
        if(alpha >= 3.0f){
            bAlpha = false;
            alpha = 0.0f;
    }
       
}

    void setColor(ofColor color){
        
        c = color;
    }
    
    void setPos(ofPoint position){
        
        pos = position;
    }
    
    void toggleWireFrame(bool toggle){
        
        bToggleWire = toggle;
    }
    
    
    void keyPressed(int key){
        
        
        if(key == '1') {
            a1value = 0.1;

        }
        if(key == '2') {
            a2value = 0.4;

        }
        if(key == '3') {
            n1value = 0.5;

        }

        triggerAlpha();

    }

    void triggerAlpha(){
        
        alpha = 0.0f;
        bAlpha = true;
        
        //Gives nice shape//
        n1value = 0.5;
    }
    
//    void triggerRandomShape(int r){
//
//        if(r==0) { a1value = 0.1; }
//        if(r==1) { a2value = 0.4; }
//        if(r==2) { n1value = 0.5; }
//    }
    
  
    
    
private:
    
    float moveTowards(float current, float target, float step) {
        
        if(abs(current-target) < step) {
            current = target;
        } else {
            
            if(current > target) {
                current -= step;
            } else if(current < target) {
                current += step;
            }
        }
        
        return current;
    }
    
    ofVec3f sf3d(float x, float y) {
        
        float i = -PI + x*stepvalue;
        
        float j = -PI/2.0f + y*stepvalue;
        
        float raux1 = pow(abs(1/a1value*abs(cos(sin(n1value) * i/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*i/4))),n4value);
        
        float r1=pow(abs(raux1),(-1/n2value));
        float raux2=pow(abs(1/a1value*abs(cos(n1value*j/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*j/4))),n4value);
        float r2=pow(abs(raux2),(-1/n2value));
//        float xx=r1*cos(i)*r2*cos(j)*100.0f;
        float xx=r1*cos(i)*r2*cos(j)* ofNoise(j+i*a1value*0.05f)*size;
        float yy=r1*sin(i)*r2*cos(j)* ofNoise(j)*size;
        float zz=r2*sin(j)*size;
        //float zz=r2*sin(j)*100.0f;
        
        return ofVec3f(xx,yy,zz);
    }
    
    float a1value;
    float a2value;
    float n1value;
    float n2value;
    float n3value;
    float n4value;
    float stepvalue;
    float size;
    bool drawWire;
    bool drawPoints;
    
    
    
    float n1target, n2target, n3target, n4target,a1target,a2target;
    
    
    ofMesh mesh;
    ofPoint pos;
    ofColor c;
    float alpha, alphaVel;
    bool bToggleWire, bAlpha;
    
    vector<int> lastRow;
    
};