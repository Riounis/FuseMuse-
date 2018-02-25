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
	std::vector<char> getPitchesAtPosition(int pos);
private:
	std::vector<CompositionMetrics> metrics;
	std::vector<Part> parts;
};


#endif /* COMPOSITION_H */
 