#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(ofColor::black);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetFullscreen(false);
    
    visuals.setup(7400);

    bDebug = true;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    visuals.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if ( bDebug == true ) {
        
    visuals.background();
    
    
    }
    
    visuals.triSquares();
//    visuals.sineCircles();
//    visuals.scanLines();
//    visuals.sines();
//    visuals.verticalCircles();
//    visuals.noiseSquares();
//    visuals.waves();
//   visuals.generativeSphere();

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if ( key == 'd' ) {
        
        bDebug = !bDebug;
        
    }
    
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
