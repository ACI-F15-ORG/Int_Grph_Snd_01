#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    font.loadFont("franklinGothic.otf", 14);
    color1 = (ofColor::white);
    fontColor = (ofColor::black);

    bgImage.loadImage("SoundFriendEdit.jpg");
    bgImage.resize(ofGetWidth(), ofGetHeight());

	ofSetLogLevel(OF_LOG_VERBOSE);

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	int baud = 9600;
	serial.setup("/dev/ttyACM0", baud);

	memset(bytesReadString, 0, 4);

    ofAddListener( timer1.TIMER_COMPLETE , this, &ofApp::timer1CompleteHandler ) ;
    ofAddListener( timer1.TIMER_STARTED , this, &ofApp::timer1StartedHandler ) ;

    bTimerComplete=false;

}

//--------------------------------------------------------------
void ofApp::update(){

 	    timer1.update( ) ;

        unsigned char bytesReturned[5];

        memset(bytesReadString, 0, 6);
        memset(bytesReturned, 0, 5);

        serial.readBytes(bytesReturned, 5);

        string serialData = (char*) bytesReturned; // cast to char
        memcpy(bytesReadString, bytesReturned, 3); //


        int serialInt = ofToInt(serialData);

        if(serialInt == 6){
        timer1.setup(1000 ) ;
        timer1.start(true);
        }

        if(serialInt != 0){
        cout << "serial data" <<serialInt << endl;
        }

        if(bTimerComplete){
        bTimerComplete=false;
        color1 = ofColor::fromHsb( ofRandom(255) , 255 , 255 ) ;
        pitchRandom= (ofRandom(0,1023));
        pitchValue = ofToString(pitchRandom) + "  Pitch Value";
            if(ofGetFrameNum() % 4 == 0) {
            //dont send data every frame
            serial.writeByte(pitchRandom);
            }
        }
}
//--------------------------------------------------------------
void ofApp::draw(){


    bgImage.draw(0,0);

    ofEnableAlphaBlending();
    ofSetColor(color1);
    ofRect(0, 0, ofGetWidth(), 70);
    ofDisableAlphaBlending();


    ofSetColor(fontColor);
    font.drawString("Press Button to Detect Pitch", 30, 40);
    font.drawString(pitchValue + "\n", 400, 40);
    ofSetColor(255, 255, 255);


}
//--------------------------------------------------------------


void ofApp::timer1CompleteHandler( int &args ){
     //timer1.bIsPaused;
     cout << "5 seconds passed" << endl;
     bTimerComplete=true;
     timer1.reset();

    }


void ofApp::timer1StartedHandler(int &args){


}

void ofApp::keyPressed(int key){

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
