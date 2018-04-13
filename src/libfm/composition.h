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
	 * Returns the composition metrics being used at the given position in the composition.
	 *
	 * @param pos The position in the composition from which to retrieve composition metrics.
	 * @return The composition metrics used at the position.
	 */
	CompositionMetrics* getCompositionMetricsAtPosition(int pos) {
		for (int i = metrics.size() - 1; i >= 0; i--) {
			printf("%d\n", metrics[i]->position);
			if (pos >= metrics[i]->position) {
				printf("hello\n");
				printf("%d\n", metrics[i]->key.getTonic());
				return metrics[i];
			}
		}
		return NULL;
	}
	
	/**
	 * Sets the composition metrics at position 0 to the given composition metrics.
	 *
	 * @param The composition metrics to use at the start of the composition.
	 */
	void setInitialCompositionMetrics(CompositionMetrics *mets) {
		if (mets->position != 0) {
			mets->position = 0;
		}
		if (metrics.size() == 0) {
			metrics.push_back(mets);
		}
		else {
			metrics[0] = mets;
		}
	}
	
	/**
	 * Sets the key at position 0 of this composition to the given key.
	 *
	 * @param initKey The initial key of the composition.
	 */
	void setInitialKey(Key initKey) {
		if (metrics.size() == 0) {
			CompositionMetrics m;
			printf("about to set metrics key\n");
			m.key = initKey;
			m.position = 0;
			metrics.push_back(&m);
			printf("pushing back initial key\n");
			printf("%d\n", metrics[0]->key.getTonic());
			printf("%d\n", metrics[0]->position);
		}
		else {
			printf("in metrics size != 0\n");
			printf("%d\n", metrics[0]->key.getTonic());
			metrics[0]->key = initKey;
		}
	}
	
	/**
	 * Sets the tempo at position 0 of this composition to the given tempo.
	 *
	 * @param initTempo The initial tempo of the composition.
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
	 * Sets the time signature at position 0 of this composition to the given
	 * time signature.
	 *
	 * @param initTimeSig The initial time signature of the composition.
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
		if (metrics.size() == 0) {
			return false;
		}
		
	}
	
	/**
	 *
	 */
	bool addTempoChange(int newTempo, int pos) {
		if (metrics.size() == 0) {
			return false;
		}
	}
	
	/**
	 *
	 */
	bool addTimeSignatureChange(TimeSignature newTimeSig, int pos) {
		if (metrics.size() == 0) {
			return false;
		}
	}
	
	/**
	 * Adds a new set of composition metrics to the composition at the given position.
	 * If the composition has no composition metrics, the new set of composition metrics
	 * will instead be inserted at position 0.
	 *
	 * @param mets A pointer to the composition metrics to be added.
	 * @return whether the composition metrics were added.
	 */
	bool addNewCompositionMetrics(CompositionMetrics *mets) {
		if (metrics.size() == 0) {
			mets->position = 0;
			metrics.push_back(mets);
			return true;
		}
		else {
			std::vector<CompositionMetrics*>::iterator it = metrics.begin();
			while (it != metrics.end()) {
				if ((*it)->position == mets->position) {
					(*it)->key = mets->key;
					(*it)->timeSignature = mets->timeSignature;
					(*it)->tempo = mets->tempo;
					return true;
				}
				else if ((*it)->position > mets->position) {
					if ((*it)->key.getTonic() == mets->key.getTonic() &&
							(*it)->key.getScale() == mets->key.getScale() &&
							(*it)->timeSignature.num == mets->timeSignature.num &&
							(*it)->timeSignature.denom == mets->timeSignature.denom &&
							(*it)->tempo == mets->tempo) {
						return false;		
					}
					metrics.insert(it, mets);
					return true;
				}
				it++;
			}
			metrics.push_back(mets);
			return true;
		}
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
	bool addToPattern(std::string name) {
		
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
	int compositionMetricsAtPosition(int pos) {
		for (int i = 0; i < metrics.size(); i++) {
			if (metrics[i]->position == pos) {
				return i;
			}
		}
		return -1;
	}
	std::vector<CompositionMetrics*> metrics;
	std::vector<Part*> parts;
	std::vector<PatternSegment*> patternSegments;
	std::vector<std::string> pattern;
	Part chordProgression;
};


#endif /* COMPOSITION_H */
 