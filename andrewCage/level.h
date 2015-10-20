#pragma once

#include "ofMain.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "metronome.h"
#include "notelookup.h"

class Wall {
	public:
		Wall(int _note, float _x) {note = _note, x = _x, width = 1;}
		Wall(int _note, float _x, float _width) {note = _note, x = _x, width = _width;}

		float x;
		int note;
		float width;
};

class Level {
	public:
		Level() {};
		Level(Metronome metronome){
			totalTime = 0;
			strobe = false;
			strobeTimer = 0;
			difficulty = 4;
			target = 0;
			float noteWidth = (ofGetWidth()*2/3.)/metronome.getUpper();
			for (int i=0; i < 100; i++) {
				int note;
				if (i==0)
					note = (int) ofRandom(0,7);
				else
					note = max(min(walls[i-1].note + (int) ofRandom(-difficulty,difficulty),int(8-difficulty/2)),int(difficulty/2));
				walls.push_back(Wall(note,i*noteWidth + ofGetWidth()*5/3));
			}
		}
		void update(float dt, Metronome metronome) {
			totalTime += dt;
			strobeTimer += dt;
			// width/3 is where the playhead is. A measure should be from
			// the playhead to the edge of the screen.
			float noteWidth = (ofGetWidth()*2/3.)/metronome.getUpper();
			for (vector<Wall>::iterator i=walls.begin(); i != walls.end(); i++){
				i->x -= metronome.getSecondsPerBeat()*noteWidth*dt;
				if (i->x <= ofGetWidth()/3 && i->x + i->width*noteWidth >= ofGetWidth()/3)
					target = 880. * pow(2.,i->note*100./1200.);
				if (i->x + i->width*noteWidth < -noteWidth*3 ) {
					walls.erase(i);
					int note = max(min(walls.back().note + (int) ofRandom(-difficulty,difficulty),int(8-difficulty/2)),int(difficulty/2));
					walls.push_back(Wall(note,
						walls.back().x + (walls.back().width*noteWidth)));
				}
			}

			if (strobeTimer > 1)
				strobeTimer = fmodf(strobeTimer, 1.0);

			difficulty -= 0.0002;
			difficulty = difficulty < 0.5 ? 0.5 : difficulty;

			strobe = (totalTime > 30 && totalTime < 60);

		}
		void draw(Metronome metronome) {
			float noteWidth = (ofGetWidth()*2/3.)/metronome.getUpper();
			float noteHeight = 80;
			// let's show two octaves at a time! that means from the centre
			// note, we need to go both up and down 8 whole steps!!
			// so let's just hard code this. we'll centre around D6(1174.66)
			// so D5 is 587.33 and D7 is 2349.32 ... 1761.99. BUT OUR SCREEN
			// IS ONLY 720 TALL! That works out to... 2.4 pixels per note...
			// okay new plan, just do one octave. Ohp, class is over, gtg
			ofSetColor(255,0,0);
			ofBeginShape();
				// ofVertex(0,-noteHeight);
			bool first = true;
			vector<Wall>::iterator j = walls.end();
			for (vector<Wall>::iterator i=walls.begin(); i != walls.end(); i++){
				if (i->x + i->width*noteWidth >= -noteWidth*3 && i->x - (i->width*noteWidth) <= ofGetWidth() + noteWidth*3) {
					if (first) {
						ofVertex(i->x,-noteHeight);
						first = false;
					}
					ofCurveVertex(i->x,(i->note - (difficulty/2))*noteHeight );
					j = i;
				}
			}
			if (j != walls.end())
				ofCurveVertex(j->x + j->width*noteWidth,(j->note - (difficulty/2))*noteHeight );
			ofVertex(ofGetWidth(),-noteHeight);
			ofSetColor(255);
			ofEndShape(true);


			ofBeginShape();
				// ofVertex(0,ofGetHeight()+noteHeight);
			first = true;
			for (vector<Wall>::iterator i=walls.begin(); i != walls.end(); i++){
				if (first) {
					ofVertex(i->x,ofGetHeight()+noteHeight);
					first = false;
				}
				if (i->x + i->width*noteWidth >= -noteWidth*3 && i->x - (i->width*noteWidth) <= ofGetWidth() + noteWidth*3) {
					ofCurveVertex(i->x,(i->note + (difficulty/2))*noteHeight );
					j = i;
				}
			}
			if (j != walls.end())
				ofCurveVertex(j->x + j->width*noteWidth,(j->note + (difficulty/2))*noteHeight );
			ofVertex(ofGetWidth(),ofGetHeight()+noteHeight);
			ofEndShape(true);

			// if (strobe && strobeTimer > 0.5 ) {
			if (strobe && metronome.getBeat(totalTime) % 2 ) {
				ofSetColor(0,0,0,255);
				ofRect(0,0,ofGetWidth(),ofGetHeight());
			}

			ofSetColor(255,0,0);
		}
		float getDifficulty() {return difficulty;}
		float getTarget() {return target;}

	private:
		vector <Wall> walls;
		float difficulty;
		bool strobe;
		float strobeTimer;
		float totalTime;
		float target;
};