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

/**
 * A PatternSegment is an object that represents a piece of a song (such as a chorus or
 * a verse).
 */
class PatternSegment {
public:

	/**
	 * Constructs a PatternSegment object with no name and no chord progression
	 */
	PatternSegment(): name(), duration(), chordProgression(){}
	
	/**
	 * Constructs a PatternSegment with a name and a duration
	 *
	 * @param name The name of the PatternSegment.
	 * @param duration The length of the PatternSegment in FuseMuse duration units.
	 */
    PatternSegment(std::string name, int duration) : name(name), duration(duration),
			chordProgression(){}
			
	/**
	 * Returns the chord progression of this PatternSegment.
	 *
	 * @return The chord progression of this PatternSegment.
	 */
	Part getChordProgression() { return chordProgression; }
	
	/**
	 * Sets the chord progression of this PatternSegment.
	 *
	 * @param p A pointer to the chord progression to be set for this PatternSegment.
	 */
	void setChordProgression(Part *p) { chordProgression = *p; }
	
	/**
	 * Returns the name of this PatternSegment.
	 *
	 * @return The name of this PatternSegment.
	 */
	std::string getName() { return name; }
	
	/**
	 * Sets the name of this PatternSegment.
	 *
	 * @param n The new name for this PatternSegment.
	 */
	void setName(std::string n) { name = n; }
	
	/**
	 * Returns the duration of this PatternSegment.
	 *
	 * @return The duration of this PatternSegment.
	 */
	int getDuration() { return duration; }
	
	/**
	 * Sets the duration of this PatternSegment.
	 *
	 * @param d The new duration of this PatternSegment.
	 */
	void setDuration(int d) { duration = d; }
private:
	std::string name;
	int duration;
	Part chordProgression;
};

class Composition {
public:
	Composition(): metrics(), parts(), pattern(), patternSegments(), chordProgression(){}
	
	/**
	 *
	 */
	CompositionMetrics* getCompositionMetricsAtPosition(int pos) {
		return NULL;
	}
	
	/**
	 *
	 */
	void setInitialCompositionMetrics(CompositionMetrics *mets) {
		
	}
	
	/**
	 *
	 */
	void setInitialKey(Key initKey) {
		if (metrics.size() == 0) {
			CompositionMetrics m;
			m.key = initKey;
			m.position = 0;
			metrics.push_back(&m);
		}
		else {
			metrics[0]->key = initKey;
		}
	}
	
	/**
	 *
	 */
	void setInitialTempo(int initTempo) {
		if (metrics.size() == 0) {
			CompositionMetrics m;
			m.tempo = initTempo;
			m.position = 0;
			metrics.push_back(&m);
		}
		else {
			metrics[0]->tempo = initTempo;
		}
	}
	
	/**
	 *
	 */
	void setInitialTimeSignature(TimeSignature initTimeSig) {
		if (metrics.size() == 0) {
			CompositionMetrics m;
			m.timeSignature = initTimeSig;
			m.position = 0;
			metrics.push_back(&m);
		}
		else {
			metrics[0]->timeSignature = initTimeSig;
		}
	}
	
	/**
	 *
	 */
	bool addKeyChange(Key newKey, int pos) {
		
	}
	
	/**
	 *
	 */
	bool addTempoChange(int newTempo, int pos) {
		
	}
	
	/**
	 *
	 */
	bool addTimeSignatureChange(TimeSignature newTimeSig, int pos) {
		
	}
	
	/**
	 *
	 */
	bool addNewCompositionMetrics(CompositionMetrics *mets) {
		/**if (metrics.size() == 0) {
			mets.position = 0;
			metrics.push_back(&mets);
		}
		else {
			std::vector<CompositionMetrics*>::iterator it = metrics.begin();
			while (it != metrics.end()) {
				if (it->position == mets.position) {
					*it->key = mets.key;
					*it->timeSignature = mets.timeSignature;
					*it->tempo = mets.tempo;
					return true;
				}
				else if (*it->position > mets.position) {
					metrics.insert(it, &mets);
					return true;
				}
				it++;
			}
			metrics.push_back(&mets);
			return true;
		}*/
		return true;
	}
	
	/**
	 *
	 */
	bool updateCompositionMetricsAtPositionTest(int pos, Key newKey, int newTempo,
			TimeSignature newTimeSig) {
		return true;
	}
	
	/**
	 *
	 */
	std::vector<CompositionMetrics*> getAllCompositionMetrics() {
		return metrics;
	}
	
	/**
	 *
	 */
	Part* getPart(std::string name) {
		/**for (int i = 0; i < parts.size(); i++) {
			if (parts[i]->name == name) {
				return parts[i];
			}
		}*/
		return NULL;
	}
	
	/**
	 *
	 */
	std::vector<Part*> getParts() {
		return parts;
	}
	
	/**
	 *
	 */
	bool addPart(Part p) {
		/**for (int i = 0; i < parts.size(); i++) {
			if (parts[i]->name == p.name) {
				return false;
			}
		}
		parts.push_back(&p);*/
		return true;
	}
	
	/**
	 *
	 */
	bool registerPatternSegment(PatternSegment *p) {
		/**for (int i = 0; i < patternSegments.size(); i++) {
			if (patternSegments[1]->name == p.name) {
				return false;
			}
		}
		patternSegments.push_back(&p);*/
		return true;
	}
	
	/**
	 *
	 */
	bool editPatternSegment(PatternSegment *p) {
		
	}
	
	/**
	 *
	 */
	PatternSegment* getPatternSegment(std::string name) {
		/**for (int i = 0; i < patternSegments.size(); i++) {
			if (patternSegments[i]->name == name) {
				return patternSegments[i];
			}
		}*/
	}
	
	/**
	 *
	 */
	void addToPattern(std::string name) {
		
	}
	
	/**
	 *
	 */
	std::vector<std::string> getPattern() { return pattern; }
	
	/**
	 *
	 */
	void resetPattern() {
		
	}
	
	/**
	 *
	 */
	Part getChordProgression() { return chordProgression; }
	
	// Add tree of PacketParts
private:
	std::vector<CompositionMetrics*> metrics;
	std::vector<Part*> parts;
	std::vector<PatternSegment*> patternSegments;
	std::vector<std::string> pattern;
	Part chordProgression;
};


#endif /* COMPOSITION_H */
 