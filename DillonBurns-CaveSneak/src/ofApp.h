#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void setupStage();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVideoGrabber 		vidGrabber;
		int 				camWidth;
		int 				camHeight;

        int windowHeight;
        int windowWidth;

		bool diff = false;

		int framediff;

		int threshold = 2800;

		ofPixels      holdingframe;
        ofImage       holdingImage;

		deque<ofPixels> frames;
		int qsize =0;
		int numslice =0;

        string asciiCharacters;
        ofTrueTypeFont  font;

        vector<ofVec2f> circles;
        ofPoint temp;
        int circlessize =0;


        bool clearscreen=false;

        //Audio Stuff
        void audioIn(float * input, int bufferSize, int nChannels);

		vector <float> left;
		vector <float> right;
		vector <float> volHistory;

		int 	bufferCounter;
		int 	drawCounter;

		float smoothedVol;
		float scaledVol;

		float volmod;

		ofSoundStream soundStream;


};
