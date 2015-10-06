#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofHideCursor();//if you hide the cursor and then show it on mouse moved it's a workaround for the invisible cursor bug
    ofSetFrameRate(150); //important because it may accidentally read data from arduino faster than the arduino can access
    arduino.connect("/dev/tty.usbmodem1411", 57600);//to get the port of the arduino search in terminal using ls /dev/tty.*
    //create a listener (arduino
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);//(who has access to call, which class is the reciever, who is the function within the class that will recieve this message) also & sends the address of the function since you can't pass the function
    bSetupArduino = false;
    
    //declare the pins and positions for the flex sensors
    flexPin1 = 0;
    flexPin2 = 1;
    oldFlexPositionX = 0;
    oldFlexPositionY = 0;
    flexPositionY = 0;
    flexPositionX = 0;
    
    // load the 8 sfx soundfile
    for (int i=0; i<N_SOUNDS; i++) {
        sound[i].loadSound("sfx/"+ofToString(i)+".mp3");
        sound[i].setMultiPlay(true);
        sound[i].setLoop(false);
    }
    int noteDivision = ofGetWindowWidth()/8;
    sec0 = 0 + noteDivision;
    sec1 = sec0 + noteDivision;
    sec2 = sec1 + noteDivision;
    sec3 = sec2 + noteDivision;
    sec4 = sec3 + noteDivision;
    sec5 = sec4 + noteDivision;
    sec6 = sec5 + noteDivision;
    sec7 = sec6 + noteDivision;
    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();
    
    //There's an easier way of doing this but I don't know it
    //Play notes in X direction
    if (flexPositionX<sec1){
        sound[0].play();
    }
    if (flexPositionX>sec1 & flexPositionX<sec2){
        sound[1].play();
    }
    if (flexPositionX>sec2 & flexPositionX<sec3){
        sound[2].play();
    }
    if (flexPositionX>sec3 & flexPositionX<sec4){
        sound[3].play();
    }
    if (flexPositionX>sec4 & flexPositionX<sec5){
        sound[4].play();
    }
    if (flexPositionX>sec5 & flexPositionX<sec6){
        sound[5].play();
    }
    if (flexPositionX>sec6 & flexPositionX<sec7){
        sound[6].play();
    }
    if (flexPositionX>sec7){
        sound[7].play();
    };
    
    //Play notes in Y direction
    if (flexPositionY<sec1){
        sound[0].play();
    }
    if (flexPositionY>sec1 & flexPositionY<sec2){
        sound[1].play();
    }
    if (flexPositionY>sec2 & flexPositionY<sec3){
        sound[2].play();
    }
    if (flexPositionY>sec3 & flexPositionY<sec4){
        sound[3].play();
    }
    if (flexPositionY>sec4 & flexPositionY<sec5){
        sound[4].play();
    }
    if (flexPositionY>sec5 & flexPositionY<sec6){
        sound[5].play();
    }
    if (flexPositionY>sec6 & flexPositionY<sec7){
        sound[6].play();
    }
    if (flexPositionY>sec7){
        sound[7].play();
    };
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version){
   //create a remove listener to stop listening for if the arduino is setup
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;
    
    //start listening on a pin and outputting on another pin
    arduino.sendAnalogPinReporting(flexPin1, ARD_ANALOG);
    arduino.sendAnalogPinReporting(flexPin2, ARD_ANALOG);
    
    //tell arduino that new data has come in and to deal with it
    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged); //& sends the address of the function since you can't pass the function

    
}
//--------------------------------------------------------------

void ofApp::analogPinChanged(const int & pinNum){

}

void ofApp::updateArduino(){
    arduino.update();
    
    //check to see if arduino has been set up
    if (bSetupArduino){
        //flexPositionX = arduino.getAnalog(flexPin2);
        flexPositionX = ofMap(arduino.getAnalog(flexPin2), 730, 900, 0, ofGetWindowWidth());
        flexPositionY = ofMap(arduino.getAnalog(flexPin1), 690, 850, 0, ofGetWindowHeight());
        
        //add points to line
        flexPath.curveTo(flexPositionX, flexPositionY);
        
        //print to console
        //cout << flexPositionX << endl;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetLineWidth(10);
    //ofNoFill();
    //ofSetColor(ofColor::royalBlue);

    if (ofGetFrameNum()%25==0){
        oldFlexPositionX = flexPositionX;
        oldFlexPositionY = flexPositionY;
    };
    
    if (ofGetFrameNum()%100==0){
        ofSetColor(0,0,0,150);
        ofRect(0,0,ofGetWidth(),ofGetHeight());
        
        //ofBackground(ofColor::black);redraw background
        ofSetColor(ofRandom(20, 220),ofRandom(20, 220),ofRandom(20, 220),50);
        flexPath.clear();
    };
    
    flexPath.draw();
    //ofLine(oldFlexPositionX, oldFlexPositionY, flexPositionX, flexPositionY);

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    ofShowCursor();
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
