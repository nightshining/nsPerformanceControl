#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(ofColor::black);
    ofDisableArbTex();
    
    bDebug = false;
    
    counter = 0;
    
    //Setup OSC
    osc.setup(7400);
    osc.setMessageName("/object1"); //index 0
    osc.setMessageName("/object2"); //index 1

    //Setup Effect
    effect.load("shaders/tv");
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    fbo.begin();
    ofClear(0);
    fbo.end();
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    //OSC//
    osc.update();
    

    if (counter == 1) {
        
    //Waves//
    _sphere.setTrigger(osc.getFloatMessage(0));
    _waveL.setPos(ofPoint(0, ofGetHeight() * .65));
    _waveR.setPos(ofPoint(ofGetWidth() * .75, ofGetHeight() * .65));
        
        if (ofGetKeyPressed(' ')) {
            
            _waveL.setNoise();
            _waveR.setNoise();
        }

    } //end 1
    
    if (counter == 2) {
    
    //Apple//
        
        if (osc.getPad(0) == 1 || osc.getPad(4) == 1 || osc.getPad(7) == 1 || osc.getPad(9) || osc.getPad(11) == 1 || osc.getFloatMessage(1)) {
            
            _apple.triggerAlphaSlow(1);
            _apple.setNoise(1);
            
        } else {
            
            _apple.triggerAlphaSlow(0);
            _apple.setNoise(0);
        }
    
        //_apple2.triggerAlpha(osc.getFloatMessage(0));

        
    //Ghost//
    
    _ghostL.setPos(ofPoint(ofGetWidth() * .15, ofGetHeight() * .5));
    _ghostR.setPos(ofPoint(ofGetWidth() * .85, ofGetHeight() * .5));
    
        float triggerGhost = osc.getFloatMessage(0);
        _ghostL.triggerAlpha(triggerGhost);
        _ghostR.triggerAlpha(triggerGhost);
        
    }
     //end2
    
    if (counter == 3) {

    //Noise Wave//
    
        _noisewave.setNoise(osc.getPad(3));
        
        float triggerNoiseWave = osc.getFloatMessage(0);
    
        _noisewave.setAlpha(triggerNoiseWave);
        _noisewave.setFlashTrigger(triggerNoiseWave);
        
        if (triggerNoiseWave == 1.0) {
            _noisewave.setRandomTrigger();
        }
    
    _miniL.setPos(ofPoint(ofGetWidth()*.35, ofGetHeight()*0.5));

    _miniL.setNoise(osc.getPad(3));
        
    _miniL.setMovement(osc.getKnob(5), osc.getKnob(5));
    
        
    } //end 3
    
    if (counter == 4) {

    //Sine//
        
        
        if (osc.getPad(4) == 1.0 || osc.getPad(6) == 1.0 || osc.getPad(8) == 1.0 || osc.getPad(9) == 1.0 || osc.getPad(11) == 1.0) {
         
            _sine.fadeUp();
            
        } else {
            
            _sine.fadeDown();
        }
        
    //Mold//

    float triggerMoldL = osc.getFloatMessage(0);
    float triggerMoldR = osc.getFloatMessage(1);
    
        if (triggerMoldL == 1.0) {
            
            _moldL.setAlpha();
            
        }
        if (triggerMoldR == 1.0) {
            
            _moldR.setAlpha();
        }
        
    _moldL.setPos(ofPoint(ofGetWidth()*.18, ofGetHeight()*0.5));
    _moldR.setPos(ofPoint(ofGetWidth()*.80, ofGetHeight()*0.5));
        
    _moldL.setTrigger(triggerMoldL);
    _moldR.setTrigger(triggerMoldR);
    
    } //end 4
    
    
    if (counter == 5) {
        
        //Fin//
        _fin.setNoise(osc.getSlider(0));
        
        if (osc.getPad(0) == 1.0 || osc.getPad(3) == 1.0 || osc.getPad(8) == 1.0 || osc.getPad(10)) {
            
            _fin.setMovement(osc.getKnob(3) * 5.0);
            
        }
        _fin.setPos(ofPoint(ofGetWidth() * .5, ofGetHeight() * .5));
        
        //Deformed Sphere//
        
        
        _dSphereL.setDeform(osc.getKnob(3));
        _dSphereR.setDeform(osc.getKnob(3));
        
        _dSphereL.setPosition(ofPoint(ofGetWidth() * .15, ofGetHeight() * .5));
        _dSphereR.setPosition(ofPoint(ofGetWidth() * .85, ofGetHeight() * .5));
        
        if (osc.getFloatMessage(0) == 1.0) {
        
            _dSphereL.setPulse();
            _dSphereR.setPulse();
        }
        
    } //end 5
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.begin();
    ofClear(0);
    
    switch (counter) {
        case 1:
            _sphere.draw();
            _waveL.draw();
            _waveR.draw();

            break;
        case 2:
            _apple.draw();
            _apple2.draw();
            _ghostL.draw();
            _ghostR.draw();
            break;
        case 3:
            _noisewave.draw();
            _miniL.draw();
            //_miniR.draw();
            break;
        case 4:
            _sine.draw();
            _moldL.draw();
            _moldR.draw();
            break;
        case 5:
            _fin.draw();
            _dSphereL.draw();
            _dSphereR.draw();
            break;
            
        default:
            break;
    }
    fbo.end();
    
    float sliderEffectParam1 = ofMap(osc.getSlider(2), 0.0, 1.0, 0.0, 0.01, true);
    float sliderEffectParam2 = ofMap(osc.getSlider(3), 0.0, 1.0, 0.0, 0.01, true);
    
    effect.begin();
    effect.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(), 0.0);
    effect.setUniform1f("iGlobalTime", ofGetElapsedTimef());
    effect.setUniform4f("iMouse", sliderEffectParam1, sliderEffectParam2, 0.0, 0.0);
    effect.setUniformTexture("iChannel0", fbo, 0);
    effect.setUniform4f("iDate", ofGetYear(), ofGetMonth(), ofGetDay(), ofGetSeconds());
    
    ofRect(0,0, ofGetWidth(), ofGetHeight());
    effect.end();
    
    
    if (bDebug) {
    
    osc.debugKnobs();
    osc.debugPads();
    osc.debugSliders();
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(ofGetWidth() * .75, ofGetHeight() * .10));
        
    }
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_UP) {
        counter++;
        counter %= 8;
    }

    if (key == OF_KEY_DOWN) {
        counter--;
        
        if (counter < 0) {
            counter = 0;
        }
    }
    

    if (key == '1') {
        
        ofSetFullscreen(true);
        
        
        fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
        
        fbo.begin();
        ofClear(0);
        fbo.end();
        
    }
    
    if (key == '2') {
        ofSetFullscreen(false);
        
        
        fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
        
        fbo.begin();
        ofClear(0);
        fbo.end();
        

    }
    
    if (key == 'd') {
        
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
    
    /*     Ghost tempGhost;
     _ghost.push_back(tempGhost);
     }
     if (_ghost.size() > 10) {
     _ghost.erase(_ghost.begin(), _ghost.begin()+1);
     }
     
     for (auto it = _ghost.begin(); it != _ghost.end(); ++it){
     it->draw();
     }
     */
