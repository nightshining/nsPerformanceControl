#include "nsVisuals.h"

nsVisuals::nsVisuals() {
    
}

nsVisuals::~nsVisuals() {
    
}

void nsVisuals::setup(int portNumber) {
    
    /////SETUP GLOBAL VARIABLES/////
    scale = .5;
    objectColor.set(240, 240, 230);
    dynamicPositioning();
    
    /////SETUP LOCAL VARIABLES/////
    
    triAlpha = 255.0;
    blend = 0;
    scanLinesAlpha = 255.0;
    scanLinesColor.set(0, 255, 250, 150);
    sinesFade = 0.0;
    sinesAlpha = 0.0;
    squareNoise = 0.0;
    wavesMax = 100;
    wavesFreq = 0.0;
    wavesAlpha = 0.0;
    sphereAlpha = 0.0;
    sphereCounter = 0.003;
    
    float verticalCircleSize = width * height;
    
    verticalAlpha.resize(verticalCircleSize);
    
    for (int i = 0; i < verticalAlpha.size(); i++) {
        
        verticalAlpha[i] = 0.0;
    }
    
    model.loadModel("3d/rock.3ds");
    model.setPosition(0,0,0);

    modelPosition.resize(3);
    modelPosition[0] = .25;
    modelPosition[1] = .50;
    modelPosition[2] = .75;
    
    
    /////SETUP OSC/////
    
    osc.setup(portNumber);
    osc.setMessageName("/triSquares"); //index 0
    osc.setMessageName("/sineCircles"); //index 1
    osc.setMessageName("/scanLines"); //index 2
    osc.setMessageName("/sines"); //index 3
    osc.setMessageName("/verticalCircles"); //index 4
    osc.setMessageName("/noiseSquares"); //index 5
    osc.setMessageName("/waves"); //index 6
    osc.setMessageName("/generativeSphere"); //index 7
    
}

void nsVisuals::update() {
    
    osc.update();
    
    dynamicPositioning();
  
}

void nsVisuals::triSquares(ofVec2f position) {
    
    int squareAmt = 3;
    
    
   for (int i = 0; i < squareAmt; i++) {

//        if ( osc.getFloatMessage(0) == 1.0 ) {
       if ( osc.getPad(1) == 1){
            float speed = 5;
       
           triAlpha = ofMap(sin(i + ofGetElapsedTimef() * speed) * 255, -255, 255, 0, 255);
        
       }

        ofPushStyle(); {

        ofPushMatrix(); {
            
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofTranslate(position.x * 0.89, position.y);
        ofSetColor(objectColor, triAlpha);
        ofRect(i * 59, 0, 50, 100);
        
            } ofPopMatrix();
        
        } ofPopStyle();
        
    }
    
    triAlpha -= 5;
}

void nsVisuals::sineCircles() {
    
    int patternInc = 50;
    
    for (int i = 0; i < width; i += patternInc) {
        
        for (int j = 0; j < height; j += patternInc) {
            
            float sineCirclesAlpha = 0;
            float sineCirclesRadius = 0;
            
            if ( osc.getFloatMessage(1) == 1.0 ) {
                
                sineCirclesAlpha = ofMap( sin(i + ofGetElapsedTimef() * 5 ) * 255, -255, 255, 0, 255);
                sineCirclesRadius = ofMap(sin(i + ofGetElapsedTimef() * 5 ) * 25, -25, 25, 0, 25);
            } else {
                sineCirclesAlpha = 0;
            }
            
            ofPushStyle();
            ofPushMatrix();
            ofTranslate(left);
            ofScale(scale, scale);
            ofSetColor(objectColor, sineCirclesAlpha);
            ofCircle(i, j, sineCirclesRadius, sineCirclesRadius);
            ofPopMatrix();
            ofPopStyle();
        }
    }
    
}

void nsVisuals::scanLines() {
    
    ofPushStyle();
    
    
    blend += 5.0;
    
    if (blend >= height - 5) {
        blend = 0.0;
    }
    
    ofPushMatrix();
    ofScale(scale, scale);
    ofTranslate(center);
  
    ofSetColor(scanLinesColor, 150);
    ofRect(0, blend, width, 5);
    ofPopMatrix();
    
    for (int j = 0; j < height; j+=30) {
        
        scanLinesAlpha -= 0.50;
        
        if ( scanLinesAlpha <= 10.0 ) {
            
            scanLinesAlpha = 0;
        }
        
        
        if ( osc.getFloatMessage(2) ) {
            scanLinesAlpha = 255;
        }
        
        ofPushMatrix();
        ofScale(scale, scale);
        ofTranslate(center);
        
        ofSetColor(objectColor, scanLinesAlpha);
        ofRect(0,0, width, j);
        ofPopMatrix();
        
        }
    
    for (int h = 0; h < height; h+=15) {
        
        ofPushMatrix();
        ofScale(scale, scale);
        ofTranslate(center);
        
        ofSetColor(objectColor);
        ofLine(0, h, width, h);
        ofPopMatrix();

    }
    
    ofPopStyle();
    
}

void nsVisuals::sines() {

    sinesFade -= 5.0;
    
    if(sinesFade <= 20.0) {
        sinesFade = 20.0;
    }
    
    if(osc.getFloatMessage(3)) {
        sinesFade = 255;
    }
    
    ofPushMatrix();

    ofTranslate(left);
    ofScale(scale, scale);


    ofSetColor(objectColor);
    ofRect(0,0,width,height);
    ofPopMatrix();
    
    for(int w = 0; w < width; w+=5){
        
        float sine = sin(w + ofGetElapsedTimef() * 5) * sinesFade;
        sinesAlpha = cos(w) * 255;
        float size = ofMap( sin(w + ofGetElapsedTimef()), -1.0, 1.0, 10, 20);
        
        ofPushMatrix();
        ofTranslate(left);
        ofScale(scale, scale);

        ofSetColor(ofColor::black, sinesAlpha);
        ofCircle(w, sine, size, size);
        ofPopMatrix();
    }
    
}

void nsVisuals::verticalCircles() {
    
    ofPushMatrix();
    ofTranslate(center);
    for(int i = 0; i < width; i+=50) {
        for (int j = 0; j < height; j+=25) {
          
            float size = cos(i  + ofGetElapsedTimef() * 5) * 25;
            float yPos = sin(j  + ofGetElapsedTimef() * 7) * 150;
            
            verticalAlpha[i] -= ofNoise(i) + 0.20;
            
            if ( verticalAlpha[i] <= 1.0 ) {
                
                verticalAlpha[i] = 0.0;
            }
            
            if (osc.getFloatMessage(4)) {
                
                verticalAlpha[i] = 255.0;
                
            }
            
            
            ofSetColor(objectColor, verticalAlpha[i]);
            ofCircle( i, yPos, size, size );

        }
    }
    ofPopMatrix();
    
}

void nsVisuals::noiseSquares( ofVec2f position ) {
    
    for (int j = 0; j < height; j+=100) {
        
        squareNoise -= .40;
        
        if (squareNoise <= 0.0) {
            
            squareNoise = 0.0;
        }
        
        
        if ( osc.getPad(0) ) {
            
            squareNoise = ofRandom(0, 255);
            
        }
        
        ofPushStyle();
        ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofTranslate(position.x, position.y * .75);
        ofScale(scale * .4, scale * .55);
        ofSetColor(objectColor, squareNoise);
        ofRect(0, j, width, 75);
        ofPopMatrix();
        ofPopStyle();
    }
    
}

void nsVisuals::waves() {
    
    wavesMax -= 10;
    
    if ( wavesMax <= 0 ) {
        wavesMax = 0;
    }

    ofPushStyle(); {

    
    for (int j = 0; j < 50; j+=2){
        
        wavesFreq = sin(ofGetElapsedTimef() * 5) * wavesMax - sin(ofGetElapsedTimef() * 5) * 20;
        
        if (osc.getFloatMessage(6)) {
            wavesMax = 255;
        }
        
        
        ofPushMatrix();
        wavesAlpha = ofNoise(j) * 200;
       
        
        ofTranslate(left);
        ofScale(scale, scale);
        ofTranslate(0, -j);

        ofSetColor(objectColor, wavesAlpha);
        ofNoFill();
        
        ofBeginShape();
        {
        ofCurveVertex(0, 0);
        ofCurveVertex(0, 0);
        
        if (j == 4) {
            ofSetColor(255, 0, 100, 200);
        }
        
        for(int i = 0; i < 50; i++) {
            ofCurveVertex(width * .1 + i * 10, ofNoise(i + ofGetElapsedTimef() * 5) * cos(ofGetElapsedTimef() * 5) * wavesFreq);
        }
        ofCurveVertex(width * .5, 0);
        ofCurveVertex(width * .5, 0);
        
        }
        
        ofEndShape(false);
        ofPopMatrix();
    }
    
    } ofPopStyle();
    

    
}

void nsVisuals::generativeSphere() {
    
    for (int i = 0; i < 50; i++) {
        ofPushStyle();
        ofSetCircleResolution(60);
        ofPushMatrix();
        ofTranslate(center);
        ofScale(scale, scale);
        float move = sphereCounter * (i + 20);
        ofSetColor(255, move);
        ofNoFill();
        if(i == 25) {
        ofSetColor(0, 200, 200, 80);
        ofRotateX(ofGetElapsedTimef() * 5);
        }
        
        ofRotateX(move);
        ofRotateY(move);
        ofCircle(0, 0, 200);
        ofPopMatrix();
        ofPopStyle();
    }
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofSetColor(255, sphereAlpha);
    ofFill();
    ofTranslate(center);
    //ofScale(scale, scale);
    ofRect(0, 0, 200, 200);
    ofPopMatrix();
    ofPopStyle();
    
    sphereAlpha -= 3.0;
    
    if ( osc.getFloatMessage(7) ) {
        
        sphereAlpha = ofRandom(50, 255);
        sphereCounter = ofNoise(ofGetElapsedTimef() * 3);
        
    }

}

void nsVisuals::deformedMesh() {

    //get the model attributes we need
    ofVec3f scale = model.getScale();
    ofVec3f position = ofVec3f(center);
    
    float normalizedScale = model.getNormalizedScale() * .45;
    ofVboMesh mesh = model.getMesh(0);

    ofxAssimpMeshHelper& meshHelper = model.getMeshHelper( 0 );
    
    ofPushMatrix();
    ofPushMatrix();
    
    if ( osc.getPad(0) == 1) {
        
        ofTranslate(position.x * modelPosition[ofRandom(3)], position.y);

    } else {
        
        ofTranslate(position);

    }
    ofRotate(ofMap(osc.getKnob(0), 0.0, 1.0, 0, ofGetWidth()), 1, 1, 1);
    ofRotate(90,1,1,1);
    
    
    ofScale(normalizedScale, normalizedScale, normalizedScale);
    ofScale(scale.x,scale.y,scale.z);
    
    //modify mesh with some noise
    float liquidness = 5;
    float amplitude = 5 / 100.0;
    float speedDampen = 5;
    
    vector<ofVec3f>& verts = mesh.getVertices();
    
    for(unsigned int i = 0; i < verts.size(); i++){
        verts[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        verts[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
        

    }
    ofSetColor(ofColor::white, 100);

    mesh.drawWireframe();
    
    ofPopMatrix();
    ofPopStyle();

    
}


//// THIS IS CODE FOR THE THREE BACKGROUND PANELS ////

void nsVisuals::background() {
    
    panel(left);
    panel(center);
    panel(right);
    
    osc.debugPads();
    osc.debugKnobs();
    osc.debugSliders();
    
}

void nsVisuals::panel(ofPoint position){
    
    int size = 200;
    
    ofPushStyle();
    ofPushMatrix();
    ofSetLineWidth(0.01);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    ofSetColor(ofColor::white, 255);
    ofRect(position, size, size);
    ofPopMatrix();
    ofPopStyle();
    
    
}

void nsVisuals::dynamicPositioning() {
    
    ///GLOBAL POSITION///
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    left.set(width * .25, height * .5);
    center.set(width * .50, height * .5);
    right.set(width * .75, height * .5);
    
    
}
