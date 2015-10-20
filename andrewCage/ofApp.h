#pragma once

#include "ofMain.h"
#include "metronome.h"
#include "notelookup.h"
#include "level.h"
#include "tracker.h"

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

		void audioIn(float* input, int bufferSize, int nChannels);

		vector <float> micSamples;
		vector <int> zeroIndices;
		vector <float> volumeBuffer;
		vector <float> freqBuffer;
		vector <float> curveVertecies;

		float volume;
		float freq;
		float averageVol;
		float averageFreq;
		float timer;
		float startTime;
		float lastTime;
		unsigned int volumeBufferMax;
		unsigned int freqBufferMax;
		unsigned int micSamplesMax;
		int width;
		int height;
		int count [3];

		Metronome metronome;
		NoteLookup notelookup;
		Level level;
		Tracker tracker;

		ofSoundStream soundStream;

};
