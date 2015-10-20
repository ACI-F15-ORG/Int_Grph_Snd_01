#pragma once

#include "ofMain.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "metronome.h"
#include "notelookup.h"

class Tracker {
	public:
		Tracker() {reference = 440., y = ofGetHeight(), accuracy = 0.;}
		Tracker(float _reference) {reference = _reference, y = ofGetHeight(), accuracy = 0.;}
		void draw(float target, float freq) {
			if (accuracy < 0.5)
				ofSetColor(0,255,0);
			else if (accuracy < 1)
				ofSetColor(255,255,0);
			else if (accuracy < 3)
				ofSetColor(255,0,0);
			else
				ofSetColor(255,255,255);

			// ofDrawBitmapString(ofToString(accuracy) + " , " + ofToString(target) + " , " + ofToString((3986. * log10(target/freq))),0,ofGetHeight()/2);
			// ofLine(ofGetWidth()/3,0,ofGetWidth()/3,(3986. * log10(target/freq))/100 * ofGetHeight()/12.   );
			// ofLine(ofGetWidth()/3,0,ofGetWidth()/3,(3986. * log10(target/880))/100 * ofGetHeight()/12.   );

			ofFill();
			ofSetCircleResolution(3);
			ofCircle(ofGetWidth()/3, y, 12);
		}
		void update(float freq, float target, float difficulty) {
			float diff = (reference - freq)/1760.;
			diff = diff < 0.5 ? diff : 0.5;
			diff = diff > -0.5 ? diff : -0.5;
			y = ofGetHeight()*(0.5 + diff);

			// accuracy = (3986. * log10(target/freq)) / (((ofGetHeight()/8.)) * difficulty);
			// accuracy = ((3986. * log10(target/freq)) / 100) * (ofGetHeight()/12.)  ;
			accuracy = ((3986. * log10(target/880)) / 100) * (ofGetHeight()/12.)  ;
			accuracy = (y - accuracy)/ofGetHeight() * 8./difficulty;
			accuracy = accuracy < 0 ? -accuracy : accuracy;
		}
		float getAccuracy() {return accuracy;}

	private:
		float reference;
		float y;
		float accuracy;
};