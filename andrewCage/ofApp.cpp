#include "ofApp.h"
#include "metronome.h"
#include "notelookup.h"
#include "level.h"
#include "tracker.h"
#include <math.h>
#include <algorithm>

//--------------------------------------------------------------
void ofApp::setup(){
	width = ofGetWidth();
	height = ofGetHeight();

	volumeBufferMax = 20;
	freqBufferMax = 10;
	micSamplesMax = 256;
	volume = freq = 0.0;
	averageFreq = averageVol = 0.0;
	micSamples.assign(micSamplesMax, 0.0);
	zeroIndices.assign(micSamplesMax, 0.0);
	curveVertecies.assign(micSamplesMax, 0.0);
	volumeBuffer.assign(volumeBufferMax, 0.0);
	freqBuffer.assign(freqBufferMax, 0.0);

	//in my setup, 4 is the default audio device
	soundStream.listDevices();
	soundStream.setDeviceID(4);

	soundStream.setup(this, 0, 1, 44100, micSamplesMax, 4);

	startTime = lastTime = ofGetElapsedTimef();
	timer = 0.0;

	metronome = Metronome(4,4,100);
	notelookup = NoteLookup();
	level = Level(metronome);
	tracker = Tracker(1174.66);

	count[0] = count[1] = count[2] = 0;

	ofBackground(0);
}

void ofApp::audioIn(float* input, int bufferSize, int nChannels) {
	float sampleVolume = 0.;

	for (int i=0; i < bufferSize; i++) {
		// Store the mic samples for future frequency detection
		micSamples[i] = input[i];
		sampleVolume += input[i];
	}

	if (sampleVolume > 0.0)
		sampleVolume = sqrt( sampleVolume / ((float)bufferSize) );

	volume *= 0.93;
	volume += 0.07 * sampleVolume;
	volume = ofMap(volume, 0.0, 0.32, 0.0, 1.0, true);
}

//--------------------------------------------------------------
void ofApp::update() {
	float dt = ofGetElapsedTimef() - lastTime;
	lastTime = ofGetElapsedTimef();

	volumeBuffer.push_back(volume);

	if (volumeBuffer.size() > volumeBufferMax)
		volumeBuffer.erase(volumeBuffer.begin(),volumeBuffer.begin()+1);
	if (freqBuffer.size() > freqBufferMax)
		freqBuffer.erase(freqBuffer.begin(),freqBuffer.begin()+1);

	// frequency detection
	float f = 0.;
	curveVertecies.clear();
	double half = micSamples.size()/2.;
	for (unsigned int i=0; i < micSamples.size(); i++) {
		if (i > 0 && micSamples[i] * micSamples[i-1] < 0)
			zeroIndices.push_back(i);
		curveVertecies.push_back(micSamples[i]*pow(i/half,2)*pow((i-half*2.)/half,2) * averageVol);
	}

	f = 0.;
	for (unsigned int i=1; i < zeroIndices.size(); i++)
		f += zeroIndices[i] - zeroIndices[i-1];
	if (zeroIndices.size() > 2)
		freq = 44100. / ((f*2.)/(zeroIndices.size()-1));
	else
		freq = 0;
	freqBuffer.push_back(freq);
	zeroIndices.clear();

	f = 0.;
	for (unsigned int i=0; i < freqBuffer.size(); i++)
		f += freqBuffer[i];
	averageFreq = f / ((float) freqBuffer.size());

	// end frequency detection

	f = 0.;
	for (unsigned int i=0; i < volumeBuffer.size(); i++)
		f += volumeBuffer[i];
	averageVol = f / ((float) volumeBuffer.size());

	count[1] = count[0];
	count[0] = (int) metronome.getBeat(timer);
	count[2] = max(count[2]-1,0);
	if (count[0] != count[1])
		count[2] = 10;

	level.update(dt, metronome);
	tracker.update(averageFreq, level.getTarget(), level.getDifficulty());

	timer = ofGetElapsedTimef() - startTime;
	timer = fmodf(timer, 60.0);
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofPushMatrix();
	ofTranslate(0,height/2);

	ofSetLineWidth(4);
		// ofSetColor(255,255,255,96*averageVol);
		if (tracker.getAccuracy() < 0.5)
			ofSetColor(0,255,0,96*averageVol);
		else if (tracker.getAccuracy() < 1)
			ofSetColor(255,255,0,96*averageVol);
		else if (tracker.getAccuracy() < 3)
			ofSetColor(255,0,0,96*averageVol);
		else
			ofSetColor(255,255,255,96*averageVol);
		ofFill();
		ofBeginShape();
		for (unsigned int i=0; i < curveVertecies.size(); i++)
			ofCurveVertex(i*width/curveVertecies.size(), curveVertecies[i]*96);
		for (unsigned int i=curveVertecies.size()-1; i > 3; i-= 4)
			ofCurveVertex(i*width/curveVertecies.size(), curveVertecies[i]*32);
		ofCurveVertex(0,0);
		ofEndShape(true);

	ofPopMatrix();

	level.draw(metronome);
	tracker.draw(level.getTarget(), averageFreq);

	ofSetColor(255,255,0,(int) 128 * (count[2]/10.) );
	ofNoFill();
	// ofLine(ofGetWidth()/3,0,ofGetWidth()/3,ofGetHeight());
	ofRect(2,2,width-4,height-4);

	// Counter
	ofFill();
	ofSetCircleResolution(32);
	for (int i=0; i < metronome.getUpper(); i++) {
		if (i+1 == count[0]) {
			ofSetColor(255,0,0);
			ofCircle(24 + 16*i,height-24,6);
		} else {
			ofSetColor(255,0,0,128);
			ofCircle(24 + 16*i,height-24,3);
		}
	}

	ofSetColor(128);
	ofDrawBitmapString("volume: " + ofToString(averageVol*100., 3), width-164, height-40);
	ofDrawBitmapString("Frequency: " + notelookup.lookup(averageFreq) + " " + ofToString(averageFreq, 0)  + "Hz", width-256, height-20);
	ofDrawBitmapString("BPM: " + ofToString(metronome.getBPM(), 0), width/2 - 40, 12);
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
