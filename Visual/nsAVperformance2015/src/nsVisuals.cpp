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
    squareNoise = 0.0;
    wavesMax = 100;
    wavesFreq = 0.0;
    wavesAlpha = 0.0;
    boxAlpha = 0.0;
    sphereCounter = 0.003;
    sphereAlpha.resize(50);
    
    
    model.loadModel("3d/rock.3ds");
    model.setPosition(0,0,0);

    modelPosition.resize(3);
    meshAlpha = 255;
    meshRumble = 0.0;
    randomMeshPosition = 0;
    
    
    texOrgImg.loadImage("Texture/oak.jpg");
    
    ofPushStyle();
    texOrgSphere.setResolution(6);
    texOrgSphere.setPosition(0, 0, 0);
    
    texOrgMesh.setMode(OF_PRIMITIVE_POINTS);
    texOrgMesh.setupIndicesAuto();
    texOrgMesh = texOrgSphere.getMesh();
    ofPopStyle();
    
    
    texOrgScale = 5.0;
    texOrgSpinX = 0.0;
    texOrgSpinY = 0.0;
    
    counterIndex = 0;
    
    ofPushStyle();
    sphereHUD.setResolution(45);
    sphereHUD.setPosition(0,0,0);
    sphereHUD.setScale(50);
    
    meshHUD.setupIndicesAuto();
    meshHUD = sphereHUD.getMesh();
    meshHUD.setMode(OF_PRIMITIVE_POINTS);
    
    for (int i = 0; i < 200; i++){
        
        meshHUD.removeVertex(ofRandom(400, 600));
        
    }
    
    ofPopStyle();
    
    //Organic Mesh
    genMesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    genMeshNoise = 0.0;
    genMeshSize = 0.0;
    genMeshCoords = ofVec3f(0.0,0.0,0.0);
    genMeshRotate = ofVec3f(0.0,0.0,0.0);
    genMeshColor = ofColor(0.0,0.0,0.0);
    genMeshTime = 0.0;
    
    int exprAmt = 5;
    genMeshExpr.resize(exprAmt);
    
    /////SETUP OSC/////
    
    osc.setup(portNumber);
    osc.setMessageName("/triSquares"); //index 0
    osc.setMessageName("/deformedMesh"); //index 1
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

void nsVisuals::organicMesh(ofVec2f position, nsShapeTitle nsName ) {
    
    genMesh.clear();
    genMesh.clearColors();
    

    for (float u = 0.0; u < 2 * PI; u += PI / 75) {
        for (float v = 0.0; v < 2 * PI; v += 2 * PI / 75) {
            
            switch (nsName) {
                    
                case NS_SINE:
                    
                    genMeshNoise = ofMap(ofGetMouseX(),0,ofGetWidth(),0.0,5.0,true);
                    genMeshSize = 200;
                    genMeshCoords.x = sin(u) * sin(v) * genMeshSize;
                    genMeshCoords.y = ofSignedNoise(u + ofGetElapsedTimef() * genMeshNoise)* ofSignedNoise(v + ofGetElapsedTimef() * genMeshNoise) * ofMap(ofGetMouseY(),0,ofGetHeight(),0.0,300.0);
                    genMeshCoords.z = sin(v) * cos(v) * genMeshSize;

                    genMeshColor = ofFloatColor(0.80,0.80,0.70, u * 0.05);
                    genMeshRotate.set(0, 0, 0);
                    break;
                    
                case NS_MESH_MOLD:
                    
                    genMeshSize = 150;
                    genMeshTime = ofGetElapsedTimef() * 2.0;
                    genMeshCoords.set(sin(u) * cos(v + genMeshTime) * genMeshSize, cos(u) * sin(v) * genMeshSize, sin(v) * cos(v) * genMeshSize );
                    
                    genMeshColor = ofFloatColor(0.25,0.80,0.70, u * 0.05);
                    genMeshRotate.set(0, 0, 0);
                    break;
                    
                case NS_NOISE_WAVE:
                    
                    genMeshTime = ofGetElapsedTimef() * 5.0f;
                    genMeshNoise =  ofNoise(genMeshTime * .05);
                    genMeshSize = 150;
                    genMeshCoords.x = sin(v) * cos(u) * ofMap(ofGetMouseX(),0,ofGetWidth(),0.0,5.0,true) * genMeshSize;
                    genMeshCoords.y = cos(v * sin(v)) * sin(v) * genMeshSize;
                    genMeshCoords.z = sin(u + genMeshTime + genMeshNoise * cos(v + genMeshTime)) * genMeshSize;
                    genMeshColor = ofFloatColor(0.95,0.06,0.30, u * 0.05);
                    genMeshRotate.set(genMeshTime, genMeshTime, genMeshTime);
                    break;
                    
                case NS_APPLE:
                    genMeshTime = ofGetElapsedTimef() * 1.0f;
                    genMeshNoise = ofSignedNoise(v + cos(genMeshTime)) * 5.0f;
                    genMeshSize = 100;
                    
                    //coords color
                    genMeshCoords.x = sin(v) * cos(u) * genMeshSize;
                    genMeshCoords.y = genMeshNoise + cos(v + u) * genMeshSize;
                    genMeshCoords.z = sin(u + genMeshTime + genMeshNoise * cos(v + genMeshTime)) * genMeshSize;
                    genMeshColor = ofFloatColor(0.10,0.8,0.50, u * 0.05);
                    genMeshRotate.set(0, 0, 0);

                    break;
                    
                case NS_GHOST:
                    genMeshTime = ofGetElapsedTimef() * 1.0f;
                    genMeshNoise = cos(v)+ ofNoise(genMeshTime) * 5.0f;
                    genMeshSize = 100;
                    genMeshCoords.x = sin(v) * genMeshSize;
                    genMeshCoords.y = cos(u) * genMeshSize;
                    genMeshCoords.z = sin(u + genMeshTime) * cos(genMeshNoise) * genMeshSize;
                    genMeshColor = ofFloatColor(.85,0.9,0.90, u * 0.08);
                    genMeshRotate.set(genMeshTime*15.0,genMeshTime*10.0,genMeshTime*5.0);
                    break;
                    
                default:
                    
                    //genMeshRotate.set(1.0,1.0,1.0);
                    break;
            }
            
            genMesh.addColor(genMeshColor);
            ofVec3f vec = ofVec3f(genMeshCoords);
            genMesh.addVertex(vec);
            
        }
    }
 
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(position);
    ofRotateX(genMeshRotate.x);
    ofRotateY(genMeshRotate.y);
    ofRotateZ(genMeshRotate.z);
    genMesh.draw();
    ofPopMatrix();
    ofPopStyle();


}

void nsVisuals::triSquares(ofVec2f position) {

   ofEnableSmoothing();

   int squareAmt = 8;

   for (int i = 0; i < squareAmt; i++) {
       for (int j = 0; j < squareAmt; j++) {
       
      // if ( osc.getPad(1) == 1){
           
            float speed = 5;
       
           triAlpha = ofMap(sin(j + ofGetElapsedTimef() * speed) * 255, -255, 255, 0, 255);
        
      //  }

        ofPushStyle(); {
        ofPushMatrix(); {
            
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofTranslate(position.x * 0.83, position.y * 0.75);
        if(i == 5 && j == 3){
            ofSetColor(10,250,215, triAlpha);
        } else {
            ofSetColor(objectColor, 255);
        }
            ofCircle(i * 25, j * 25, 10);
            } ofPopMatrix();
        
        } ofPopStyle();
       
       }
    }
    
    triAlpha -= 5;
    
    ofDisableSmoothing();
}


void nsVisuals::noiseSquares( ofVec2f position ) {
    
    for (int j = 0; j < height; j+=50) {
        
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

void nsVisuals::waves(float posX, float posY) {
    
    wavesMax -= 10;
    
    if ( wavesMax <= 0 ) {
        wavesMax = 0;
    }

    ofPushStyle(); {
        ofSetLineWidth(.05);
        
    for (int j = 0; j < 75; j++){
        
        //Move waves
        wavesMax = osc.getKnob(6) * 500;
        wavesFreq = sin(ofGetElapsedTimef() * 5) * wavesMax - sin(ofGetElapsedTimef() * 5) * 25;
    
        
        wavesAlpha = ofMap(sin(j) * 255, -255, 255, 230, 255);
        
        ofPushMatrix();
        ofTranslate(posX, posY);
        ofScale(scale, 1.0);
        ofTranslate(0, -j * 3);

        ofSetColor(objectColor, wavesAlpha);
        ofNoFill();
        
        ofBeginShape();
        {
        ofCurveVertex(0, 0);
        ofCurveVertex(0, 0);
        
        if (j == 2) {
            ofSetColor(255, 0, 100, 200);
        }
        
        for(int i = 0; i < 25; i++) {
            ofCurveVertex( width * .1 + i * 15, ofNoise(i + ofGetElapsedTimef() * ofMap(osc.getKnob(7), 0.0, 1.0, 5.0, 200.0)) * cos(ofGetElapsedTimef() * 5) * wavesFreq);
        }
        ofCurveVertex(width * .5, 0);
        ofCurveVertex(width * .5, 0);
        
        }
        
        ofEndShape(false);
        ofPopMatrix();

    }
    
    } ofPopStyle();
    

    
}

void nsVisuals::generativeSphere(ofVec2f position) {
    
    for (int i = 0; i < 50; i++) {
        
        ofPushStyle();
        ofSetCircleResolution(60);
        ofPushMatrix();
        ofTranslate(center);
        ofScale(scale, scale);
        
        float move = sphereCounter * (i + 20);
        ofRotateX(move);
        ofRotateY(move);
        
        if (osc.getFloatMessage(7) == 1.0) {
        sphereCounter = ofNoise(ofGetElapsedTimef() * ofRandom(3, 5)) * osc.getFloatMessage(7) * 3.0;
        
        for (int a = 0; a < sphereAlpha.size(); a++ ) {
            sphereAlpha[a] = ofNoise(a) * 200;
        }

        } else {
      
        for (int a = 0; a < sphereAlpha.size(); a++ ) {
            
        ofSetColor(255, sphereAlpha[a]);
        ofNoFill();
            
            if ( i == 45 ) {
                ofSetColor(0, 255, 200, sphereAlpha[a]);
                ofNoFill();
            }
            
        }
            
       
        ofCircle(0, 0, width * .25);
        ofPopMatrix();
        ofPopStyle();
            
            for (int a = 0; a < sphereAlpha.size(); a++) {
                
                sphereAlpha[a] -= move * .005;
                
                if ( sphereAlpha[a] <= 0.0 ) {
                    
                    sphereAlpha[a] = 0.0;
                    
                }
            }

        }
    }
    
    ofPushStyle();
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(255, boxAlpha);
    ofFill();
    ofTranslate(center);
    ofRect(0, 0, width * .3, height * .45 );
    ofPopMatrix();
    ofPopStyle();
    
    if ( osc.getFloatMessage(7) == 1 && osc.getSlider(5) == 0.0 && ofRandomf() > .5) {

    boxAlpha = ofRandom(50, 255);
        
    }
    
    boxAlpha -= 5.0;
    
  
    if (boxAlpha <= 0.0 ) {
        
        boxAlpha = 0.0;
    }

}

void nsVisuals::deformedMesh() {

    modelPosition[0] = left;
    modelPosition[1] = center;
    modelPosition[2] = right;
    
    //get the model attributes we need
    ofVec3f scale = model.getScale();
    
    float normalizedScale = model.getNormalizedScale() * .45;
    ofVboMesh mesh = model.getMesh(0);

    ofxAssimpMeshHelper& meshHelper = model.getMeshHelper( 0 );
    
    ofPushStyle();
    ofPushMatrix();
   
    
    if ( osc.getFloatMessage(1) == 1.0 ) {
        
        randomMeshPosition = ofRandom(3);
        
        ofTranslate(modelPosition[randomMeshPosition]);
        meshAlpha = 255;
        
    } else {
        
        ofTranslate(modelPosition[randomMeshPosition]);
        
    }
    
    ofRotate(ofMap(osc.getKnob(0), 0.0, 1.0, 0, ofGetWidth()) + ofGetElapsedTimef() * 5.0, 1, 1, 1);
    ofRotate(90,1,1,1);
    
    
    ofScale(normalizedScale, normalizedScale, normalizedScale);
    ofScale(scale.x,scale.y,scale.z);
    
   
    //modify mesh with some noise
    float liquidness = 5;
    float amplitude = ofMap(osc.getKnob(3), 0.0, 1.0, 10.0, 300.0) / 100.0;
    float speedDampen = 5;
    
    
    vector<ofVec3f>& verts = mesh.getVertices();
    
    for(unsigned int i = 0; i < verts.size(); i++){
        
        float liquidMesh = ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen) * amplitude;
        
        if ( osc.getPad(12) == 1 || osc.getPad(13) == 1 || osc.getPad(14) == 1 || osc.getPad(15) == 1) {
            
            meshRumble = ofSignedNoise(verts[i].x/liquidness, verts[i].y * ofGetElapsedTimef() * 200,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen) * amplitude;
            
        } else {
            
            meshRumble = liquidMesh;
            
        }
        
        verts[i].x += liquidMesh;
        verts[i].y += meshRumble;
        verts[i].z += liquidMesh;
        
        ofColor c = ofColor::white;
        //c.a = ofMap(i, 0, verts.size(), 50, 180) + meshAlpha;
        c.a = ofNoise(i) * meshAlpha;
        //c.a = ofMap(i, 0, verts.size(), 50, 180);
        mesh.addColor(c);
        
        ofPushStyle();
        ofPushMatrix();
        ofSetColor(ofColor::crimson, 200);
        ofDrawSphere(verts[i], .005);
        ofPopMatrix();
        ofPopStyle();
    }

    mesh.drawWireframe();

    
    ofPopMatrix();
    ofPopStyle();

    meshAlpha -= 5.0;
    
    if ( meshAlpha <= 0 ) {
        
        meshAlpha = 0;
    }
}


void nsVisuals::texOrgDraw(ofVec2f position) {
    
    
    texOrgSpinX = ofGetElapsedTimef() * 7.0f;
    texOrgSpinY = ofGetElapsedTimef() * 10.0f;
    
    ofEnableDepthTest(); //important to enable and disable here bc it effects everything else otherwise
    
    ofPushMatrix();
    
    ofTranslate(position);
    ofScale(texOrgScale, texOrgScale);
    ofRotateX(texOrgSpinX);
    ofRotateY(texOrgSpinY);
    ofSetColor(ofColor::black);
    //texOrgImg.bind();
    texOrgMesh.drawWireframe();
    //texOrgImg.unbind();
    
    
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(position);
    ofScale(texOrgScale, texOrgScale);
    ofRotateX(texOrgSpinX);
    ofRotateY(texOrgSpinY);
    //texOrgImg.bind();
    ofSetColor(ofColor::whiteSmoke, 200);
    texOrgMesh.drawWireframe();
    //texOrgImg.unbind();
    
    ofPopMatrix();
    
    texOrgMovement();
    HUD(texOrgSpinX * 2.0, texOrgSpinY * 6.0);

    ofDisableDepthTest();
}

void nsVisuals::texOrgMovement() {
    
    vector<ofVec3f>& verts = texOrgMesh.getVertices();
    
    for(unsigned int i = 0; i < verts.size(); i++){
        
        
        float liquidness = 25.0;
        float amplitude = 0.05;
        float speedDampen = 8.0;
        float noise = ofSignedNoise(verts[i].x / liquidness, verts[i].y / liquidness,verts[i].z / liquidness, ofGetElapsedTimef() * speedDampen) * amplitude;
        verts[i].x += noise;
        verts[i].y += noise;
        verts[i].z += noise;
        
        
    }
    
    int meshSize = texOrgMesh.getVertices().size();
    
    for (int i = 0; i < meshSize; i++) {
        
        float posX = texOrgMesh.getVertices().at(i).x;
        float posY = texOrgMesh.getVertices().at(i).y;
        float posZ = texOrgMesh.getVertices().at(i).z;
        
        
        
        ofPushStyle();
        ofPushMatrix();
        ofSetCircleResolution(60);
        ofTranslate(ofGetWidth() * .5, ofGetHeight() * .5);
        ofScale(texOrgScale, texOrgScale);
        ofRotateX(texOrgSpinX);
        ofRotateY(texOrgSpinY);
        //float alpha = ofMap(sin(i + ofGetElapsedTimef() * 10.0) * 255, -255, 255, 0, 255);
        ofSetColor(ofColor::white);
        ofDrawSphere(posX, posY, posZ, .25);
        ofPopMatrix();
        ofPopStyle();
        
        
    }
    
}

void nsVisuals::HUD(float rotateX, float rotateY){
    
    
    ofPushStyle();
    ofPushMatrix();
    ofSetColor(255);
    ofTranslate(center);
    ofScale(11, 13);
    ofRotateX(rotateX);
    ofRotateY(rotateY);
    meshHUD.drawWireframe();
    ofPopMatrix();
    ofPopStyle();
    
    for (int i = 0; i < 50; i++) {
        
        ofPushStyle();
        ofPushMatrix();
        ofSetColor(ofColor::hotPink);
        ofTranslate(center);
        ofScale(11, 13);
        ofRotateX(i * 500 + rotateX * .05);
        ofRotateY(i * 1000 + rotateY * .30);
        
        for (float pos = 0; pos < 5.0; pos+=.85) {
            ofDrawSphere(22 + pos, 0, .09);
        }
        ofSetColor(ofColor::white, 240);
        ofLine(20,0, 21,0);
        ofNoFill();
        ofSetCircleResolution(60);
        ofRotateY(450);
        ofCircle(0,0,20, .5);
        
        ofPopMatrix();
        ofPopStyle();
    }
    
    
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
