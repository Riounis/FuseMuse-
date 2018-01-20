/* 
 * File:   composition_metrics.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef COMPOSITIONMETRICS_H
#define COMPOSITIONMETRICS_H

#include <string>
#include <vector>
#include "Constants.h"

struct TimeSignature {
    TimeSignature(int num = 4, int denom = 4) : num(num), denom(denom) {
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
        scale.push_back(pitch);
        for (std::vector<char>::size_type i = 0; i < intervals.size(); i++) {
            pitch += intervals[i];
            scale.push_back(pitch);
        }
    }
	std::vector<char> getScale() { return scale; }
	std::vector<char> getIntervals() { return intervals; }
	char getTonic() { return tonic; }
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

