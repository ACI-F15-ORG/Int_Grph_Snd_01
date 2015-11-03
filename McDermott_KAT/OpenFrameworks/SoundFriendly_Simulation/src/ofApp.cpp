#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //ofSetVerticalSync(true);
    ofSetFrameRate(60);
    font.loadFont("franklinGothic.otf", 14);
    color1 = (ofColor::white);
    fontColor = (ofColor::black);

    bgImage.loadImage("SoundFriendEdit.jpg");
    bgImage.resize(ofGetWidth(), ofGetHeight());

    std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();

    ofLogNotice("ofApp::setup") << "Connected Devices: ";

    for (std::size_t i = 0; i < devicesInfo.size(); ++i)
    {
        ofLogNotice("ofApp::setup") << "\t" << devicesInfo[i];
    }

    if (!devicesInfo.empty())
    {
        // Connect to the first matching device.
        bool success = device.setup(devicesInfo[0], 115200);

        if(success)
        {
            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[0];
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[0];
        }
    }
    else
    {
        ofLogNotice("ofApp::setup") << "No devices connected.";
    }

    ofAddListener( timer1.TIMER_COMPLETE , this, &ofApp::timer1CompleteHandler ) ;
    ofAddListener( timer1.TIMER_STARTED , this, &ofApp::timer1StartedHandler ) ;
}

//--------------------------------------------------------------
void ofApp::update(){

 	    timer1.update();
        uint8_t buffer[1024];

        while (device.available() > 0)
        {
            std::size_t sz = device.readBytes(buffer, 1024);

            for (int i = 0; i < sz; ++i)
            {
                std::cout << buffer[i];
                if(buffer[i] == 'L'){
                    timer1.setup(5000);
                    timer1.start(true);
                }
            }
        }
     pitchValue = ofToString(pitchRandom) + "  Pitch Value";
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
     cout << "5 seconds passed" << endl;
     color1 = ofColor::fromHsb( ofRandom(255) , 255 , 255 ) ;
     pitchRandom= (ofRandom(0,1023));
     std::string text = ofToString(pitchRandom);
     ofx::IO::ByteBuffer textBuffer(text); //get ofxIO from githubpage
     device.writeBytes(textBuffer);
     device.writeByte('\n');
     timer1.reset();

    }


void ofApp::timer1StartedHandler(int &args){


}


