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

/**
 * A TimeSignature represents the number of beats per measure and which note
 * gets the beat.
 */
struct TimeSignature {
	
	/**
	 * Constructs a TimeSignature with the given number of beats per measure
	 * and which note gets the beat. By default, they are 4 beats per measure,
	 * and the quarter note gets the beat.
	 *
	 * @param num The number of beats per measure.
	 * @param denom Which note gets the beat (4 for quarter note, 8 for eighth
	 * 		note, etc...)
	 */
    TimeSignature(char num = 4, char denom = 4) : num(num), denom(denom) {
		// If the denominator is not a power of 2
		if ((denom & (denom - 1)) != 0) {
			// Eventually throw error; for now, set to 4
			this->denom = 4;
		}
	}
	
	/**
	 * Returns the duration of one measure in FuseMuse position units
	 *
	 * @return The duration of one measure in FuseMuse position units
	 */
	int durationOfMeasure() {
		return (384 * num) / denom;
	}
	
    char num;
    char denom;
};

/**
 * A Key represents a scale, or group of pitches, which makes up the pitches used
 * in a song. This Key object contains the key quality (whether it's major or minor),
 * the key signature (number of sharps or flats in conventional western music), but it
 * can also contain arbitrarily constructed scales.
 */
class Key {
public:

	/**
	 * Constructs a Key which defaults to C major.
	 *
	 * @param tonic The tonic note of the scale.
	 * @param intervals A vector filled with numbers of half steps between steps in
	 * 		the scale.
	 */
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
	
	/**
	 * Returns a list of notes in the scale in this Key.
	 *
	 * @return A vector containing the pitches in this scale.
	 */
	std::vector<char> getScale() const { return scale; }
	
	/**
	 * Returns a list of intervals in between notes in the scale in this Key.
	 *
	 * @return A vector containing the intervals in this scale.
	 */
	std::vector<char> getIntervals() const { return intervals; }
	
	bool setIntervals(std::vector<char> i) {
		intervals = i;
		return true;
	}
	
	/**
	 * Returns the number of sharps or flats in this key signature.
	 *
	 * @return The number of sharps or flats in this key signature (- for flats,
	 * 		+ for sharps)
	 */
	int getKeySignature() const {
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
	
	/**
	 * Returns whether the key is major or minor.
	 *
	 * @return 0 for Major, 1 for Minor.
	 */
	int getKeyQuality() const {
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
	
	/**
	 * Returns whether the given pitch is in the scale.
	 *
	 * @param pitch The pitch to compare to the pitches in the scale.
	 * @return Whether the pitch is in the scale.
	 */
	bool isInScale(char pitch) const {
		char pmod = pitch % 12;
		for (int i = 0; i < scale.size(); i++) {
			if (pmod == scale[i] % 12) {
				return true;
			}
		}
		return false;
	}
	
	/**
	 * Returns whether the pitch given is the tonic, 2nd, 3rd, etc... in the
	 * scale.
	 *
	 * @param pitch The pitch to find the position of in the scale.
	 * @return The position of the pitch in the scale. (1 if tonic, 2nd, 3rd, etc.)
	 */
	int positionInScale(char pitch) const {
		char pmod = pitch % 12;
		for (int i = 0; i < scale.size(); i++) {
			if (pmod == scale[i] % 12) {
				return i + 1;
			}
		}
		return -1;
	}
	
	/**
	 * Returns the next pitch up in the scale above the given pitch.
	 *
	 * @param pitch The pitch to get the pitch above on the scale.
	 * @return The next pitch up in the scale.
	 */
	int nextPitchInScale(char pitch) const {
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
	
	/**
	 * Returns the nth pitch in the scale.
	 *
	 * @param n The index of the pitch in the scale (1 is tonic, 2 is 2nd etc)
	 * @return The pitch in the scale at the given index, or -1 if there is no
	 * 		pitch at the given index.
	 */
	char getNthPitch(int n) const {
		if (n < scale.size() && n >= 0) {
			return scale[n-1];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the tonic pitch of the scale.
	 *
	 * @return The tonic pitch of the scale.
	 */
	char getTonic() const { return tonic; }
	
	bool setTonic(char t) {
		tonic = t;
		return true;
	}
	
	std::vector<int> getSimpleChord(int i) {
		std::vector<int> pitches;
		int st = i % scale.size();
		pitches.push_back(scale[st]);
		int mid = (st + 2) % scale.size();
		if (mid < st) {
			pitches.push_back(scale[mid] + 12);
		}
		else {
			pitches.push_back(scale[mid]);
		}
		int top = (mid + 2) % scale.size();
		if (top < mid) {
			pitches.push_back(scale[top] + 12);
		}
		else {
			pitches.push_back(scale[top]);
		}
		return pitches;
	}
	
	/**
	 * Returns the second pitch of the scale.
	 *
	 * @return The second pitch of the scale, or -1 if the scale has 1 or fewer
	 * 		notes.
	 */
	char get2nd() const {
		if (scale.size() >= 2) {
			return scale[1];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the third pitch of the scale.
	 *
	 * @return The third pitch of the scale, or -1 if the scale has 2 or fewer
	 * 		notes.
	 */
	char get3rd() const {
		if (scale.size() >= 3) {
			return scale[2];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the fourth pitch of the scale.
	 *
	 * @return The fourth pitch of the scale, or -1 if the scale has 3 or fewer
	 * 		notes.
	 */
	char get4th() const {
		if (scale.size() >= 4) {
			return scale[3];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the fifth pitch of the scale.
	 *
	 * @return The fifth pitch of the scale, or -1 if the scale has 4 or fewer
	 * 		notes.
	 */
	char get5th() const {
		if (scale.size() >= 5) {
			return scale[4];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the sixth pitch of the scale.
	 *
	 * @return The sixth pitch of the scale, or -1 if the scale has 5 or fewer
	 * 		notes.
	 */
	char get6th() const {
		if (scale.size() >= 6) {
			return scale[5];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the seventh pitch of the scale.
	 *
	 * @return The seventh pitch of the scale, or -1 if the scale has 6 or fewer
	 * 		notes.
	 */
	char get7th() const {
		if (scale.size() >= 7) {
			return scale[6];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the eighth pitch of the scale.
	 *
	 * @return The eighth pitch of the scale, or -1 if the scale has 7 or fewer
	 * 		notes.
	 */
	char get8th() const {
		if (scale.size() >= 8) {
			return scale[7];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the ninth pitch of the scale.
	 *
	 * @return The ninth pitch of the scale, or -1 if the scale has 8 or fewer
	 * 		notes.
	 */
	char get9th() const {
		if (scale.size() >= 9) {
			return scale[8];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the tenth pitch of the scale.
	 *
	 * @return The tenth pitch of the scale, or -1 if the scale has 9 or fewer
	 * 		notes.
	 */
	char get10th() const {
		if (scale.size() >= 10) {
			return scale[9];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the eleventh pitch of the scale.
	 *
	 * @return The eleventh pitch of the scale, or -1 if the scale has 10 or fewer
	 * 		notes.
	 */
	char get11th() const {
		if (scale.size() >= 11) {
			return scale[10];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns the twelfth pitch of the scale.
	 *
	 * @return The twelfth pitch of the scale, or -1 if the scale has 11 or fewer
	 * 		notes.
	 */
	char get12th() const {
		if (scale.size() >= 12) {
			return scale[11];
		}
		else {
			return -1;
		}
	}
	
	/**
	 * Returns whether the key is the same as the key passed in.
	 *
	 * @param key The key to be tested against this key
	 * @return Whether the key is the same as the given key
	 */
	bool equals(Key key) const {
		if (key.getTonic() != tonic) {
			return false;
		}
		else if (key.getIntervals().size() != intervals.size()) {
			return false;
		}
		else {
			for (int i = 0; i < intervals.size(); i++) {
				if (key.getIntervals()[i] != intervals[i]) {
					return false;
				}
			}
			return true;
		}
	}
private:
    char tonic;
    std::vector<char> intervals;
    std::vector<char> scale;
};

/**
 * A CompositionMetric is a simple structure to hold Key, TimeSignature, and Tempo
 * data, as well as a FuseMuse position signifying the CompositionMetrics' position
 * in its respective Composition.
 */
struct CompositionMetrics {
    CompositionMetrics() : key(), timeSignature(), tempo(80), position(0) {}
    Key key;
    TimeSignature timeSignature;
    unsigned int tempo;
	int position;
};

#endif /* COMPOSITIONMETRICS_H */

