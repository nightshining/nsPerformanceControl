#include "nsOsc.h"


nsOsc::nsOsc() {
    
    
}

nsOsc::~nsOsc() {
    

}

//--------------------------------------------------------------
void nsOsc::setup(int port){
  
    receiver.setup(port);
    
    totalPad = 16;
    totalKnob = 8;
    totalSlider = 8;
    
    
    knobMessage.resize(totalKnob);
    sliderMessage.resize(totalSlider);
    padMessage.resize(totalPad);
    
    for (int i = 0; i < knobMessage.size(); i++) {
    
        knobMessage[i] = 0.0;
        
    }
    
    for (int i = 0; i < padMessage.size(); i++) {
        padMessage[i] = 0.0;
    }
    
    for (int i = 0; i < sliderMessage.size(); i++) {
        sliderMessage[i] = 0.0;
    }
    
    
}

void nsOsc::update() {
    
    while(receiver.hasWaitingMessages()) {
        
        ofxOscMessage message;
        
        receiver.getNextMessage(&message);
        
        //cout << "Message: " << message.getArgAsInt32(0) << endl;
        
        for(int i = 0; i < messageName.size(); i++ ) {
        
            if( message.getAddress() == messageName[i] ) {
            
            receiveMessage[i] = message.getArgAsInt32(0);
            
            }
        }
        
        for ( int k = 0; k < sliderMessage.size(); k++ ) {
            
            if ( message.getAddress() == "/slider/" + ofToString(k)) {
                
                sliderMessage[k] = message.getArgAsFloat(0);
                
            }
        }
        
        for ( int j = 0; j < knobMessage.size(); j++ ) {
            
        if ( message.getAddress() == "/knob/" + ofToString(j)) {
            
            knobMessage[j] = message.getArgAsFloat(0);
            
            }
        }
        
        for ( int l = 0; l < padMessage.size(); l++ ) {
            
            if ( message.getAddress() == "/pad/" + ofToString(l)) {
                
                padMessage[l] = message.getArgAsInt32(0);
                
            }
        }

        
    } //ending bracket for while loop

}

void nsOsc::setMessageName(string uniqueName) {
    
    messageName.push_back(uniqueName);
    
    for(int i = 0; i < messageName.size(); i++){
        receiveMessage.push_back(i);
    }

}


float nsOsc::getFloatMessage(int getIndex) {
    
    return receiveMessage[getIndex]; //Index corresponds to order of setMessageName() in setup function
    
}

float nsOsc::getKnob(int index) {
    
    return knobMessage[index];
}


float nsOsc::getSlider(int index) {
    
    return sliderMessage[index];
}

float nsOsc::getPad(int index) {
    
    return padMessage[index];
}


int nsOsc::getTotalKnobs() {
    
    return totalKnob;
}

int nsOsc::getTotalSliders() {
    
    return totalSlider;
}

int nsOsc::getTotalPads() {
    
    return totalPad;
}

void nsOsc::debugSliders() {
    

    for (int i = 0; i < sliderMessage.size(); i++) {
        
        ofPushMatrix();
        ofDrawBitmapString("Sliders: " + ofToString(i) + " " + ofToString(sliderMessage[i]), ofGetWidth() * .05, i * 10 + ofGetHeight() * .10);
        ofPopMatrix();
        
    }

    
}


void nsOsc::debugKnobs() {
   
    for (int i = 0; i < knobMessage.size(); i++) {
        
        ofPushMatrix();
        ofDrawBitmapString("Knobs: " + ofToString(i) + " " + ofToString(knobMessage[i]), ofGetWidth() * .20, i * 10 + ofGetHeight() * .10);
        ofPopMatrix();
        
    }
  
}

void nsOsc::debugPads() {
    
    ofPushMatrix();
    for (int i = 0; i < padMessage.size(); i++) {
        
        ofDrawBitmapString("Pads: " + ofToString(i) + " " + ofToString(padMessage[i]), ofGetWidth() * .40, i * 10 + ofGetHeight() * .10);
        
    }
    ofPopMatrix();
    
}



