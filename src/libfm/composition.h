/* 
 * File:   composition.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */
 
 #ifndef COMPOSITION_H
#define COMPOSITION_H

#include <vector>
#include <string>
#include "composition_metrics.h"
#include "part.h"

class PatternSegment {
public:
	PatternSegment(): name(), duration(), chordProgression(){}
    PatternSegment(std::string name, int duration) : name(name), duration(duration),
			chordProgression(){}
	Part getChordProgression() { return chordProgression; }
	void setChordProgression(Part *p) { chordProgression = *p; }
	std::string getName() { return name; }
	void setName(std::string n) { name = n; }
	int getDuration() { return duration; }
	void setDuration(int d) { duration = d; }
private:
	std::string name;
	int duration;
	Part chordProgression;
};

class Composition {
public:
    bool addKeyChange(int measure);
	bool addTimeSigChange(int measure);
	bool addTempoChange(int measure);
	bool addPart(Part *p) { parts.push_back(p); }
	std::vector<char> getPitchesAtPosition(int pos) {
		std::vector<char> pitches;
		for (int i = 0; i < parts.size(); i++) {
			
		}
	}
private:
	std::vector<CompositionMetrics*> metrics;
	std::vector<Part*> parts;
	std::vector<std::string> pattern;
	std::vector<PatternSegment*> patternSegments;
	Part chordProgression;
};


#endif /* COMPOSITION_H */
 