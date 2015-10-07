#pragma once

#include <iostream>
#include <map>

class NoteLookup {
	public:
		NoteLookup()
		{
			// notes = std::map <std::string,float>();
			notes.push_back(std::pair<std::string, float> ("C0", 16.35));
			notes.push_back(std::pair<std::string, float> ("Cs0", 17.32));
			notes.push_back(std::pair<std::string, float> ("Db0", 17.32));
			notes.push_back(std::pair<std::string, float> ("D0", 18.35));
			notes.push_back(std::pair<std::string, float> ("Ds0", 19.45));
			notes.push_back(std::pair<std::string, float> ("Eb0", 19.45));
			notes.push_back(std::pair<std::string, float> ("E0", 20.60));
			notes.push_back(std::pair<std::string, float> ("F0", 21.83));
			notes.push_back(std::pair<std::string, float> ("Fs0", 23.12));
			notes.push_back(std::pair<std::string, float> ("Gb0", 23.12));
			notes.push_back(std::pair<std::string, float> ("G0", 24.50));
			notes.push_back(std::pair<std::string, float> ("Gs0", 25.96));
			notes.push_back(std::pair<std::string, float> ("Ab0", 25.96));
			notes.push_back(std::pair<std::string, float> ("A0", 27.50));
			notes.push_back(std::pair<std::string, float> ("As0", 29.14));
			notes.push_back(std::pair<std::string, float> ("Bb0", 29.14));
			notes.push_back(std::pair<std::string, float> ("B0", 30.87));

			notes.push_back(std::pair<std::string, float> ("C1", 32.70));
			notes.push_back(std::pair<std::string, float> ("Cs1", 34.65));
			notes.push_back(std::pair<std::string, float> ("Db1", 34.65));
			notes.push_back(std::pair<std::string, float> ("D1", 36.71));
			notes.push_back(std::pair<std::string, float> ("Ds1", 38.89));
			notes.push_back(std::pair<std::string, float> ("Eb1", 38.89));
			notes.push_back(std::pair<std::string, float> ("E1", 41.20));
			notes.push_back(std::pair<std::string, float> ("F1", 43.65));
			notes.push_back(std::pair<std::string, float> ("Fs1", 46.25));
			notes.push_back(std::pair<std::string, float> ("Gb1", 46.25));
			notes.push_back(std::pair<std::string, float> ("G1", 49.00));
			notes.push_back(std::pair<std::string, float> ("Gs1", 51.91));
			notes.push_back(std::pair<std::string, float> ("Ab1", 51.91));
			notes.push_back(std::pair<std::string, float> ("A1", 55.00));
			notes.push_back(std::pair<std::string, float> ("As1", 58.27));
			notes.push_back(std::pair<std::string, float> ("Bb1", 58.27));
			notes.push_back(std::pair<std::string, float> ("B1", 61.74));

			notes.push_back(std::pair<std::string, float> ("C2", 65.41));
			notes.push_back(std::pair<std::string, float> ("Cs2", 69.30));
			notes.push_back(std::pair<std::string, float> ("Db2", 69.30));
			notes.push_back(std::pair<std::string, float> ("D2", 73.42));
			notes.push_back(std::pair<std::string, float> ("Ds2", 77.78));
			notes.push_back(std::pair<std::string, float> ("Eb2", 77.78));
			notes.push_back(std::pair<std::string, float> ("E2", 82.41));
			notes.push_back(std::pair<std::string, float> ("F2", 87.31));
			notes.push_back(std::pair<std::string, float> ("Fs2", 92.50));
			notes.push_back(std::pair<std::string, float> ("Gb2", 92.50));
			notes.push_back(std::pair<std::string, float> ("G2", 98.00));
			notes.push_back(std::pair<std::string, float> ("Gs2", 103.83));
			notes.push_back(std::pair<std::string, float> ("Ab2", 103.83));
			notes.push_back(std::pair<std::string, float> ("A2", 110.00));
			notes.push_back(std::pair<std::string, float> ("As2", 116.54));
			notes.push_back(std::pair<std::string, float> ("Bb2", 116.54));
			notes.push_back(std::pair<std::string, float> ("B2", 123.47));

			notes.push_back(std::pair<std::string, float> ("C3", 130.81));
			notes.push_back(std::pair<std::string, float> ("Cs3", 138.59));
			notes.push_back(std::pair<std::string, float> ("Db3", 138.59));
			notes.push_back(std::pair<std::string, float> ("D3", 146.83));
			notes.push_back(std::pair<std::string, float> ("Ds3", 155.56));
			notes.push_back(std::pair<std::string, float> ("Eb3", 155.56));
			notes.push_back(std::pair<std::string, float> ("E3", 164.81));
			notes.push_back(std::pair<std::string, float> ("F3", 174.61));
			notes.push_back(std::pair<std::string, float> ("Fs3", 185.00));
			notes.push_back(std::pair<std::string, float> ("Gb3", 185.00));
			notes.push_back(std::pair<std::string, float> ("G3", 196.00));
			notes.push_back(std::pair<std::string, float> ("Gs3", 207.65));
			notes.push_back(std::pair<std::string, float> ("Ab3", 207.65));
			notes.push_back(std::pair<std::string, float> ("A3", 220.00));
			notes.push_back(std::pair<std::string, float> ("As3", 233.08));
			notes.push_back(std::pair<std::string, float> ("Bb3", 233.08));
			notes.push_back(std::pair<std::string, float> ("B3", 246.94));

			notes.push_back(std::pair<std::string, float> ("C4", 261.63));
			notes.push_back(std::pair<std::string, float> ("Cs4", 277.18));
			notes.push_back(std::pair<std::string, float> ("Db4", 277.18));
			notes.push_back(std::pair<std::string, float> ("D4", 293.66));
			notes.push_back(std::pair<std::string, float> ("Ds4", 311.13));
			notes.push_back(std::pair<std::string, float> ("Eb4", 311.13));
			notes.push_back(std::pair<std::string, float> ("E4", 329.63));
			notes.push_back(std::pair<std::string, float> ("F4", 349.23));
			notes.push_back(std::pair<std::string, float> ("Fs4", 369.99));
			notes.push_back(std::pair<std::string, float> ("Gb4", 369.99));
			notes.push_back(std::pair<std::string, float> ("G4", 392.00));
			notes.push_back(std::pair<std::string, float> ("Gs4", 415.30));
			notes.push_back(std::pair<std::string, float> ("Ab4", 415.30));
			notes.push_back(std::pair<std::string, float> ("A4", 440.00));
			notes.push_back(std::pair<std::string, float> ("As4", 466.16));
			notes.push_back(std::pair<std::string, float> ("Bb4", 466.16));
			notes.push_back(std::pair<std::string, float> ("B4", 493.88));

			notes.push_back(std::pair<std::string, float> ("C5", 523.25));
			notes.push_back(std::pair<std::string, float> ("Cs5", 554.37));
			notes.push_back(std::pair<std::string, float> ("Db5", 554.37));
			notes.push_back(std::pair<std::string, float> ("D5", 587.33));
			notes.push_back(std::pair<std::string, float> ("Ds5", 622.25));
			notes.push_back(std::pair<std::string, float> ("Eb5", 622.25));
			notes.push_back(std::pair<std::string, float> ("E5", 659.25));
			notes.push_back(std::pair<std::string, float> ("F5", 698.46));
			notes.push_back(std::pair<std::string, float> ("Fs5", 739.99));
			notes.push_back(std::pair<std::string, float> ("Gb5", 739.99));
			notes.push_back(std::pair<std::string, float> ("G5", 783.99));
			notes.push_back(std::pair<std::string, float> ("Gs5", 830.61));
			notes.push_back(std::pair<std::string, float> ("Ab5", 830.61));
			notes.push_back(std::pair<std::string, float> ("A5", 880.00));
			notes.push_back(std::pair<std::string, float> ("As5", 932.33));
			notes.push_back(std::pair<std::string, float> ("Bb5", 932.33));
			notes.push_back(std::pair<std::string, float> ("B5", 987.77));

			notes.push_back(std::pair<std::string, float> ("C6", 1046.50));
			notes.push_back(std::pair<std::string, float> ("Cs6",1108.73));
			notes.push_back(std::pair<std::string, float> ("Db6",1108.73));
			notes.push_back(std::pair<std::string, float> ("D6", 1174.66));
			notes.push_back(std::pair<std::string, float> ("Ds6",1244.51));
			notes.push_back(std::pair<std::string, float> ("Eb6",1244.51));
			notes.push_back(std::pair<std::string, float> ("E6", 1318.51));
			notes.push_back(std::pair<std::string, float> ("F6", 1396.91));
			notes.push_back(std::pair<std::string, float> ("Fs6",1479.98));
			notes.push_back(std::pair<std::string, float> ("Gb6", 1479.98));
			notes.push_back(std::pair<std::string, float> ("G6", 1567.98));
			notes.push_back(std::pair<std::string, float> ("Gs6",1661.22));
			notes.push_back(std::pair<std::string, float> ("Ab6", 1661.22));
			notes.push_back(std::pair<std::string, float> ("A6", 1760.00));
			notes.push_back(std::pair<std::string, float> ("As6",1864.66));
			notes.push_back(std::pair<std::string, float> ("Bb6", 1864.66));
			notes.push_back(std::pair<std::string, float> ("B6", 1975.53));

			notes.push_back(std::pair<std::string, float> ("C7", 2093.00));
			notes.push_back(std::pair<std::string, float> ("Cs7",2217.46));
			notes.push_back(std::pair<std::string, float> ("Db7",2217.46));
			notes.push_back(std::pair<std::string, float> ("D7", 2349.32));
			notes.push_back(std::pair<std::string, float> ("Ds7",2489.02));
			notes.push_back(std::pair<std::string, float> ("Eb7",2489.02));
			notes.push_back(std::pair<std::string, float> ("E7", 2637.02));
			notes.push_back(std::pair<std::string, float> ("F7", 2793.83));
			notes.push_back(std::pair<std::string, float> ("Fs7",2959.96));
			notes.push_back(std::pair<std::string, float> ("Gb7", 2959.96));
			notes.push_back(std::pair<std::string, float> ("G7", 3135.96));
			notes.push_back(std::pair<std::string, float> ("Gs7",3322.44));
			notes.push_back(std::pair<std::string, float> ("Ab7", 3322.44));
			notes.push_back(std::pair<std::string, float> ("A7", 3520.00));
			notes.push_back(std::pair<std::string, float> ("As7",3729.31));
			notes.push_back(std::pair<std::string, float> ("Bb7", 3729.31));
			notes.push_back(std::pair<std::string, float> ("B7", 3951.07));

			notes.push_back(std::pair<std::string, float> ("C8", 4186.01));
			notes.push_back(std::pair<std::string, float> ("Cs8",4434.92));
			notes.push_back(std::pair<std::string, float> ("Db8",4434.92));
			notes.push_back(std::pair<std::string, float> ("D8", 4698.63));
			notes.push_back(std::pair<std::string, float> ("Ds8",4978.03));
			notes.push_back(std::pair<std::string, float> ("Eb8",4978.03));
			notes.push_back(std::pair<std::string, float> ("E8", 5274.04));
			notes.push_back(std::pair<std::string, float> ("F8", 5587.65));
			notes.push_back(std::pair<std::string, float> ("Fs8",5919.91));
			notes.push_back(std::pair<std::string, float> ("Gb8", 5919.91));
			notes.push_back(std::pair<std::string, float> ("G8", 6271.93));
			notes.push_back(std::pair<std::string, float> ("Gs8",6644.88));
			notes.push_back(std::pair<std::string, float> ("Ab8", 6644.88));
			notes.push_back(std::pair<std::string, float> ("A8", 7040.00));
			notes.push_back(std::pair<std::string, float> ("As8",7458.62));
			notes.push_back(std::pair<std::string, float> ("Bb8", 7458.62));
			notes.push_back(std::pair<std::string, float> ("B8", 7902.13));
		}

		std::string lookup(float frequency)
		{
			vector<std::pair<std::string, float> >::iterator i = notes.begin();
			vector<std::pair<std::string, float> >::iterator j;
			while (frequency > i->second && i != notes.end()) {
				j = i;
				i++;
			}
			if (i == notes.end()) return "?";
			if (i == notes.begin()) return i->first;
			if (frequency > (i->second + j->second) / 2.)
				return i->first;
			else
				return j->first;
		}

	private:
		vector <std::pair<std::string, float> > notes;
};