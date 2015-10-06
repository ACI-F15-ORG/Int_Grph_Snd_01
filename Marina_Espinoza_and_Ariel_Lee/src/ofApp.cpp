#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetRectMode(OF_RECTMODE_CENTER);
    bubbleImage.loadImage("bubble_img.png");
    popSound.loadSound("pop_sound.mp3");
    popSound.setMultiPlay(true);
    ofEnableAlphaBlending();

    bgColor1 = ofColor(30,30,30);
    bgColor2 = ofColor::black;
    lerpInterval = 50;
    currentLerpTime = 0;
    currentLerpDirection = 1;

    int number_ofBubbles = 30;
    for (int i = 0; i < number_ofBubbles; i++){
        container.push_back(Bubble(bubbleImage, popSound));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // Lerp background color (ping-pong between the two colors)
    currentLerpTime = currentLerpTime + currentLerpDirection;
    if(currentLerpTime >= lerpInterval ||
       currentLerpTime <= 0 ) {
        currentLerpDirection *= -1;
    }

    for (int i = 0; i < container.size(); ++i){
        container[i].update();
        if (container[i].isOffScreen()){
            container.erase (container.begin()+i);
            container.push_back(Bubble(bubbleImage, popSound));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor currentBgColor = bgColor1;
    currentBgColor.lerp(bgColor2, float(currentLerpTime) / lerpInterval);
    ofBackground(currentBgColor);
    for (int i = 0; i < container.size(); ++i){
        container[i].draw();
    }
}

//--------------------------------------------------------------
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
    for (int i = 0; i < container.size(); i++){
        if (container[i].onClick(x,y)){
            container.erase (container.begin()+i);
            container.push_back(Bubble(bubbleImage, popSound));
        }
    }
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
