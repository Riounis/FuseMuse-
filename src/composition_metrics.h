/* 
 * File:   CompositionMetrics.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 * Created on January 5, 2018, 5:03 PM
 */

#ifndef COMPOSITIONMETRICS_H
#define COMPOSITIONMETRICS_H

#include <string>
#include <vector>
#include "Constants.h"

class Key {
public:
    //Key() : tonic(c3), intervals(0), scale(0) {}
    Key(int tonic = c3, std::vector<char> intervals = major_intervals) :
            tonic(tonic), intervals(intervals) {
        char pitch = tonic;
        scale.push_back(pitch);
        for (std::vector<char>::size_type i = 0; i < intervals.size()-1; i++) {
            pitch += intervals[i];
            scale.push_back(pitch);
        }
    }
private:
    char tonic;
    std::vector<char> intervals;
    std::vector<char> scale;
};

struct CompositionMetrics {
    CompositionMetrics() : key(), timeSignature(), tempo(80) {}
    CompositionMetrics();
    Key key;
    TimeSignature timeSignature;
    unsigned int tempo;
};

#endif /* COMPOSITIONMETRICS_H */

