/* 
 * File:   composition.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */
 
 #ifndef COMPOSITION_H
#define COMPOSITION_H

#include <vector>
#include "composition_metrics.h"
#include "part.h"

class Composition {
public:
    bool addKeyChange(int measure);
	bool addTimeSigChange(int measure);
	bool addTempoChange(int measure);
	bool addPart(Part p) { parts.push_back(p); }
	std::vector<char> getPitchesAtPosition(int pos) {
		std::vector<char> pitches;
		for (int i = 0 i < parts.size(); i++) {
			
		}
	}
private:
	std::vector<CompositionMetrics> metrics;
	std::vector<Part> parts;
};


#endif /* COMPOSITION_H */
 