#include "nsOsc.h"


nsOsc::nsOsc() {
    
    
}

nsOsc::~nsOsc() {
    

}

//--------------------------------------------------------------
void nsOsc::setup(int port){
  
    receiver.setup(port);

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




