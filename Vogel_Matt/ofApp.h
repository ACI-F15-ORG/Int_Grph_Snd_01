#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#define N_SOUNDS 8

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    //declare image and font
    ofImage beemo;
    ofTrueTypeFont font;
    
    //create arduino object
    ofArduino   arduino;
    // lets you know if arduino is set up from the arduino side
    bool bSetupArduino; //I put b infront of the variable name to remind myself that it's a bool, not necessary
    int flexPin1;
    int flexPin2;
    int oldFlexPositionX;
    int oldFlexPositionY;
    int flexPositionY;
    int flexPositionX;
    int sec0;
    int sec1;
    int sec2;
    int sec3;
    int sec4;
    int sec5;
    int sec6;
    int sec7;
    
    //polyline
    ofPolyline flexPath;
    
    // when the ball hits we play this sound
    ofSoundPlayer  sound[N_SOUNDS];

private:
    //when arduino create new event callback, if you want to create your own events you need this
    //when arduino has a change tell OF what is happening
    void setupArduino(const int & version);//parameters that are going in (taken directly from example)
    void analogPinChanged(const int & pinNum);
    void updateArduino();
    
    //accessor functions to make grabbing stuff easier to draw on screen
    string potValue;//grab value from potentionator sensor
    
    
    
		
};
