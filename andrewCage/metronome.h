#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

class Metronome {

	public:
		Metronome() {upper = 4, lower = 4, bpm = 120;}
		Metronome(unsigned char u, unsigned char l) {upper = u, lower = l;}
		Metronome(unsigned char u, unsigned char l, short b) {upper = u, lower = l, bpm = b;}
		void setMeter(unsigned char u, unsigned char l) {upper = u, lower = l;}
		void setBPM(short b) {bpm = b;}
		unsigned char getUpper() {return upper;}
		unsigned char getLower() {return lower;}
		short getBPM() {return bpm;}
		unsigned char getBeat(float t) {return (unsigned char) fmodf(t * (120./60.),upper) + 1;}
		float getSecondsPerBeat() {return (float) (1.*upper/bpm) * 60.;}
	private:
		unsigned char upper;
		unsigned char lower;
		short bpm;

};