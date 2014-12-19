#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(ofColor::black);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetFullscreen(false);
    
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
    
    if ( bDebug == true ) {
        
    visuals.background();
    dCounter();
    
    
    }
    
    if (counter == 0) {
    
        visuals.triSquares(getCenter());
        visuals.noiseSquares(getLeft());
        visuals.noiseSquares(getRight());


    }
    
//    visuals.sineCircles();
//    visuals.scanLines();
//    visuals.sines();
//    visuals.verticalCircles();
//    visuals.waves();
//   visuals.generativeSphere();

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if ( key == 'd' ) {
        
        bDebug = !bDebug;
        
    }
    
    if ( key == OF_KEY_UP ) {
        
        counter++;
        
    } else if ( key == OF_KEY_DOWN ) {
        
        counter--;
    
    }
    
    if ( counter <= 0 ) {
        
        counter = 0;
        
    } else if ( counter >= counterMax ) {
        
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
