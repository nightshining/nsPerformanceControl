#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(5);
    ofEnableAlphaBlending();
    ofSetFullscreen(false);
    ofEnableNormalizedTexCoords();
    ofDisableArbTex();
    
    
    visuals.setup(7400);

    bDebug = true;
    
    counter = 0;
    counterMax = 10;
    
    
  
}

//--------------------------------------------------------------
void ofApp::update(){
    
    visuals.update();
    
  
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
  
    ///DEBUG///
    
    if ( bDebug == true ) {
        visuals.background();
        dCounter();
        
    }
    
    ///CONTROL///
    
    switch (counter) {
        case 1:
            visuals.triSquares(getCenter());
            visuals.noiseSquares(getLeft());
            visuals.noiseSquares(getRight());
            break;
        case 2:
            visuals.deformedMesh();
            break;
        case 3: {
            float centerWaves = 1.25;
            visuals.waves(getLeft().x * 0.0, getLeft().y * centerWaves);
            visuals.waves(getRight().x, getRight().y * centerWaves);
            visuals.generativeSphere(getCenter());
            break;
        }
        case 4:
            visuals.texOrgDraw(getCenter());
            break;
        case 5:
            visuals.organicMesh(getCenter(), NS_SINE );
            //visuals.organicMesh(getRight(), NS_MESH_MOLD );
            //visuals.organicMesh(getLeft(), NS_MESH_MOLD );
            break;
        case 6:
            visuals.organicMesh(getCenter(), NS_NOISE_WAVE);
            break;

        default:
            break;
    }
    

    

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if ( key == 'd' ) {
        
        bDebug = !bDebug;
        
    }
    
    if ( key == OF_KEY_UP ) {
        
        counter++;
        
    }
    
    if ( key == OF_KEY_DOWN ) {
        
        counter--;
    
    }
    
    if ( counter < 0 ) {
        
        counter = 0;
        
    }
    
    if ( counter >= counterMax ) {
        
        counter = counterMax;
        
    }
}

ofVec2f ofApp::getLeft() {
    
    ofVec2f setLeft = ofVec2f(ofGetWidth() * .25, ofGetHeight() * .5);
    
    return setLeft;
    
}

ofVec2f ofApp::getCenter() {
    
    ofVec2f setCenter = ofVec2f(ofGetWidth() * .5, ofGetHeight() * .5);
    
    return setCenter;
}

ofVec2f ofApp::getRight() {
    
    ofVec2f setRight = ofVec2f(ofGetWidth() * .75, ofGetHeight() * .5);

    return setRight;
    
}

void ofApp::dCounter() {
    
    ofPushStyle();
    ofPushMatrix();
    ofSetColor(0, 255, 255);
    ofDrawBitmapString("Counter: " + ofToString(counter), 25, 25);
    ofPopMatrix();
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
