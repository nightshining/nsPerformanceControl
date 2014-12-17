#include "nsOsc.h"


nsOsc::nsOsc() {
    
    
}

nsOsc::~nsOsc() {
    

}

//--------------------------------------------------------------
void nsOsc::setup(int port){
  
    receiver.setup(port);
    
    int totalPad = 16;
    int totalKnob = 8;
    int totalSlider = 6;
    
    
    knobMessage.resize(totalKnob);
    sliderMessage.resize(totalSlider);
    padMessage.resize(totalPad);
    
    
    
}

void nsOsc::update() {
    
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage message;
        
        receiver.getNextMessage(&message);
        
        for(int i = 0; i < messageName.size(); i++ ) {
        
            if( message.getAddress() == messageName[i] ) {
            
            receiveMessage[i] = message.getArgAsFloat(0);
            
            }
        }
        
        
        ofxOscMessage knob;
        
        receiver.getNextMessage(&knob);
        
        for ( int j = 0; j < knobMessage.size(); j++ ) {
            
        if ( knob.getAddress() == "/knob/" + ofToString(j)) {
            
            knobMessage[j] = knob.getArgAsFloat(0);
            
            }
        }
        
        ofxOscMessage slider;
        
        receiver.getNextMessage(&slider);
        
        for ( int k = 0; k < knobMessage.size(); k++ ) {
            
            if ( slider.getAddress() == "/slider/" + ofToString(k)) {
                
                sliderMessage[k] = slider.getArgAsFloat(0);
                
            }
        }
        
        ofxOscMessage pad;
        
        receiver.getNextMessage(&pad);
        
        for ( int l = 0; l < padMessage.size(); l++ ) {
            
            if ( pad.getAddress() == "/pad/" + ofToString(l)) {
                
                padMessage[l] = pad.getArgAsFloat(0);
                
            }
        }
        
        
    }

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



