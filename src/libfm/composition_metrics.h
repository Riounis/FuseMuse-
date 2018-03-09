/* 
 * File:   composition_metrics.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef COMPOSITIONMETRICS_H
#define COMPOSITIONMETRICS_H

#include <string>
#include <vector>
#include "constants.h"

struct TimeSignature {
    TimeSignature(char num = 4, char denom = 4) : num(num), denom(denom) {
		// If the denominator is not a power of 2
		if ((denom & (denom - 1)) != 0) {
			// Eventually throw error; for now, set to 4
			this->denom = 4;
		}
	}
    char num;
    char denom;
};

class Key {
public:
    Key(int tonic = c3, std::vector<char> intervals = major_intervals) :
            tonic(tonic), intervals(intervals) {
        char pitch = tonic;
		if (pitch >= 102) {
			pitch = pitch % 12 + 36;
		}
        scale.push_back(pitch);
        for (std::vector<char>::size_type i = 0; i < intervals.size(); i++) {
            pitch += intervals[i];
            scale.push_back(pitch);
        }
    }
	std::vector<char> getScale() { return scale; }
	std::vector<char> getIntervals() { return intervals; }
	int getKeySignature() {
		if (intervals != major_intervals && intervals != minor_intervals) {
			return 0;
		}
		else if (intervals == major_intervals) {
			int currentValue = 0;
			for (int i = 0; i < 12; i++) {
				if (tonic % 12 == i) {
					return currentValue;
				}
				if (currentValue >= 0) {
					currentValue -= 5;
				}
				else {
					currentValue += 7;
				}
			}
		}
		else {
			int currentValue = -3;
			for (int i = 0; i < 12; i++) {
				if (tonic % 12 == i) {
					return currentValue;
				}
				if (currentValue >= 0) {
					currentValue -= 5;
				}
				else {
					currentValue += 7;
				}
			}
		}
	}
	int getKeyQuality() {
		if (tonic + 4 == scale[2]) {
			return 0;
		}
		else if (tonic + 3 == scale[2]) {
			return 1;
		}
		else {
			return 2;
		}
	}
	bool isInScale(char pitch) {
		char pmod = pitch % 12;
		for (int i = 0; i < scale.size(); i++) {
			if (pmod == scale[i] % 12) {
				return true;
			}
		}
		return false;
	}
	int positionInScale(char pitch) {
		char pmod = pitch % 12;
		for (int i = 0; i < scale.size(); i++) {
			if (pmod == scale[i] % 12) {
				return i + 1;
			}
		}
		return -1;
	}
	int nextPitchInScale(char pitch) {
		char numOctaves = pitch / 12;
		char pmod = pitch % 12;
		int indexOfNext = -1;
		for (int i = 0; i < scale.size(); i++) {
			if (pmod == scale[i] % 12) {
				indexOfNext = i+1;
			}
		}
		if (indexOfNext == -1) {
			for (int i = 0; i < scale.size() - 1; i++) {
				if (pmod > scale[i] % 12 && pmod < scale[i+1] % 12) {
					indexOfNext = i + 1;
				}
			}
		}
		return scale[indexOfNext] % 12 + numOctaves * 12;
	}
	char getNthPitch(int n) {
		if (n < scale.size() && n >= 0) {
			return scale[n-1];
		}
		else {
			return -1;
		}
	}
	char getTonic() { return tonic; }
	char get2nd() {
		if (scale.size() >= 2) {
			return scale[1];
		}
		else {
			return -1;
		}
	}
	char get3rd() {
		if (scale.size() >= 3) {
			return scale[2];
		}
		else {
			return -1;
		}
	}
	char get4th() {
		if (scale.size() >= 4) {
			return scale[3];
		}
		else {
			return -1;
		}
	}
	char get5th() {
		if (scale.size() >= 5) {
			return scale[4];
		}
		else {
			return -1;
		}
	}
	char get6th() {
		if (scale.size() >= 6) {
			return scale[5];
		}
		else {
			return -1;
		}
	}
	char get7th() {
		if (scale.size() >= 7) {
			return scale[6];
		}
		else {
			return -1;
		}
	}
	char get8th() {
		if (scale.size() >= 8) {
			return scale[7];
		}
		else {
			return -1;
		}
	}
	char get9th() {
		if (scale.size() >= 9) {
			return scale[8];
		}
		else {
			return -1;
		}
	}
	char get10th() {
		if (scale.size() >= 10) {
			return scale[9];
		}
		else {
			return -1;
		}
	}
	char get11th() {
		if (scale.size() >= 11) {
			return scale[10];
		}
		else {
			return -1;
		}
	}
	char get12th() {
		if (scale.size() >= 12) {
			return scale[11];
		}
		else {
			return -1;
		}
	}
private:
    char tonic;
    std::vector<char> intervals;
    std::vector<char> scale;
};

struct CompositionMetrics {
    CompositionMetrics() : key(), timeSignature(), tempo(80), measure(0) {}
    Key key;
    TimeSignature timeSignature;
    unsigned int tempo;
	int measure;
};

#endif /* COMPOSITIONMETRICS_H */

