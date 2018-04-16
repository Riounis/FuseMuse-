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
#include "packetpart.h"

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
	Part getChordProgression() const { return chordProgression; }
	
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
	std::string getName() const { return name; }
	
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
	int getDuration() const { return duration; }
	
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
	Composition(): metrics(), parts(), pattern(), patternSegments(), chordProgression(),
		root(NULL){};
	
	/**
	 * Returns the composition metrics being used at the given position in the composition.
	 *
	 * @param pos The position in the composition from which to retrieve composition metrics.
	 * @return The composition metrics used at the position.
	 */
	CompositionMetrics* getCompositionMetricsAtPosition(int pos) const {
		for (int i = metrics.size() - 1; i >= 0; i--) {
			if (pos >= metrics[i]->position) {
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
			CompositionMetrics *m = new CompositionMetrics();
			m->key = initKey;
			m->position = 0;
			metrics.push_back(m);
		}
		else {
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
			CompositionMetrics *m = new CompositionMetrics();
			m->tempo = initTempo;
			m->position = 0;
			metrics.push_back(m);
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
      CompositionMetrics *m = new CompositionMetrics();
      m->timeSignature = initTimeSig;
			m->position = 0;
			metrics.push_back(m);
		}
		else {
			metrics[0]->timeSignature = initTimeSig;
		}
	}
	
	/**
	 * Adds a key change to the given key at the given position in the composition.
	 *
	 * @param newKey The key that should be changed to at the given position.
	 * @param pos The position the key change should occur.
	 * @return Whether the key was changed.
	 */
	bool addKeyChange(Key newKey, int pos) {
		if (metrics.size() == 0) {
			return false;
		}
		int index = compositionMetricsAtPosition(pos);
		if (index > -1) {
			metrics[index]->key = newKey;
			return true;
		}
		else {
			CompositionMetrics *mets = getCompositionMetricsAtPosition(pos);
			if (mets->key.equals(newKey)) {
				return false;
			}
			else {
				CompositionMetrics *keyChange = new CompositionMetrics();
				keyChange->position = pos;
				keyChange->key = newKey;
				keyChange->tempo = mets->tempo;
				keyChange->timeSignature = mets->timeSignature;
				for (std::vector<CompositionMetrics*>::iterator it = metrics.begin();
						it != metrics.end(); ++it) {
					if ((*it)->position > pos) {
						metrics.insert(it, keyChange);
						return true;
					}
				}
				metrics.push_back(keyChange);
				return true;
			}
		}
	}
	
	/**
	 * Adds a tempo change at the given position in the composition.
	 *
	 * @param newTempo The tempo that should be changed to at the given position.
	 * @param pos The position the tempo change should occur.
	 * @return Whether the tempo was changed.
	 */
	bool addTempoChange(int newTempo, int pos) {
		if (metrics.size() == 0) {
			return false;
		}
		int index = compositionMetricsAtPosition(pos);
		if (index > -1) {
			metrics[index]->tempo = newTempo;
		}
		else {
			CompositionMetrics *mets = getCompositionMetricsAtPosition(pos);
			if (mets->tempo == newTempo) {
				return false;
			}
			else {
				CompositionMetrics *tempoChange = new CompositionMetrics();
				tempoChange->position = pos;
				tempoChange->tempo = newTempo;
				tempoChange->key = mets->key;
				tempoChange->timeSignature = mets->timeSignature;
				for (std::vector<CompositionMetrics*>::iterator it = metrics.begin();
						it != metrics.end(); ++it) {
					if ((*it)->position > pos) {
						metrics.insert(it, tempoChange);
						return true;
					}
				}
				metrics.push_back(tempoChange);
				return true;
			}
		}
	}
	
	/**
	 * Adds a time signature change at the given position in the composition.
	 *
	 * @param newTimeSig The time signature that should be changed to at the given position.
	 * @param pos The position the time signature change should occur.
	 * @return Whether the time signature was changed.
	 */
	bool addTimeSignatureChange(TimeSignature newTimeSig, int pos) {
		if (metrics.size() == 0) {
			return false;
		}
		int index = compositionMetricsAtPosition(pos);
		if (index > -1) {
			metrics[index]->timeSignature = newTimeSig;
		}
		else {
			CompositionMetrics *mets = getCompositionMetricsAtPosition(pos);
			if (mets->timeSignature.num == newTimeSig.num &&
					mets->timeSignature.denom == newTimeSig.denom) {
				return false;
			}
			else {
				CompositionMetrics *timeSigChange = new CompositionMetrics();
				timeSigChange->position = pos;
				timeSigChange->key = mets->key;
				timeSigChange->tempo = mets->tempo;
				timeSigChange->timeSignature = newTimeSig;
				for (std::vector<CompositionMetrics*>::iterator it = metrics.begin();
						it != metrics.end(); ++it) {
					if ((*it)->position > pos) {
						metrics.insert(it, timeSigChange);
						return true;
					}
				}
				metrics.push_back(timeSigChange);
				return true;
			}
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
					it--;
					if ((*it)->key.equals(mets->key) &&
							(*it)->timeSignature.num == mets->timeSignature.num &&
							(*it)->timeSignature.denom == mets->timeSignature.denom &&
							(*it)->tempo == mets->tempo) {
						return false;		
					}
					it++;
					metrics.insert(it, mets);
					return true;
				}
				it++;
			}
			it--;
			if ((*it)->key.equals(mets->key) &&
					(*it)->timeSignature.num == mets->timeSignature.num &&
					(*it)->timeSignature.denom == mets->timeSignature.denom &&
					(*it)->tempo == mets->tempo) {
				return false;		
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
		CompositionMetrics *mets = getCompositionMetricsAtPosition(pos);
		if (mets != NULL) {
			mets->key = newKey;
			mets->tempo = newTempo;
			mets->timeSignature = newTimeSig;
			return true;
		}
		else {
			return false;
		}
	}
	
	/**
	 *
	 */
	std::vector<CompositionMetrics*> getAllCompositionMetrics() const {
		return metrics;
	}
	
	/**
	 *
	 */
	Part* getPart(std::string name) const {
		for (int i = 0; i < parts.size(); i++) {
			if (parts[i]->getName() == name) {
				return parts[i];
			}
		}
		return NULL;
	}
	
	/**
	 *
	 */
	std::vector<Part*> getParts() const {
		return parts;
	}
	
	/**
	 *
	 */
	bool addPart(Part p) {
		for (int i = 0; i < parts.size(); i++) {
			if (parts[i]->getName() == p.getName()) {
				return false;
			}
		}
		parts.push_back(&p);
		return true;
	}
	
	/**
	 *
	 */
	bool registerPatternSegment(PatternSegment *p) {
		for (int i = 0; i < patternSegments.size(); i++) {
			if (patternSegments[i]->getName() == p->getName()) {
				return false;
			}
		}
		patternSegments.push_back(p);
		return true;
	}
	
	/**
	 *
	 */
	bool editPatternSegment(PatternSegment *p) {
		for (int i = 0; i < patternSegments.size(); i++) {
			if (patternSegments[i]->getName() == p->getName()) {
				patternSegments[i] = p;
				return true;
			}
		}
		return false;
	}
	
	/**
	 *
	 */
	PatternSegment* getPatternSegment(std::string name) const {
		for (int i = 0; i < patternSegments.size(); i++) {
			if (patternSegments[i]->getName() == name) {
				return patternSegments[i];
			}
		}
		return NULL;
	}
	
	/**
	 *
	 */
	bool addToPattern(std::string name) {
		if (getPatternSegment(name) != NULL) {
			pattern.push_back(name);
			return true;
		}
		return false;
	}
	
	/**
	 *
	 */
	std::vector<std::string> getPattern() const { return pattern; }
	
	std::vector<PatternSegment*> getPatternSegments() const { return patternSegments; }
	
	/**
	 *
	 */
	void resetPattern() {
		pattern.clear();
	}
	
	/**
	 *
	 */
	Part getChordProgression() const { return chordProgression; }
	
	PacketPart* getPacketTreeRoot() const { return root; }
	
	void setPacketTreeRoot(PacketPart *r) { root = r; }
	
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
	PacketPart *root;
};


#endif /* COMPOSITION_H */
 
