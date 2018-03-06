/* 
 * File:   chord.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef CHORD_H
#define CHORD_H

#include <vector>
#include "constants.h"
#include "event.h"

struct Chord: public Event {
	Chord(): pitches({c4, e4, g4}), duration(quarter_note), triplet(0),
			dotted(0), double_dotted(0), staccato(0), tenuto(0), 
            accent(0), fermata(0), tied(0), slurred(0){}
    Chord(std::vector<char> pitches, int duration, int triplet = 0,
			int dotted = 0, int double_dotted = 0, int staccato = 0,
			int tenuto = 0, int accent = 0, int fermata = 0,
			int tied = 0, int slurred = 0) : pitches(pitches),
			duration(duration), triplet(triplet), dotted(dotted),
			double_dotted(double_dotted), staccato(staccato),
			tenuto(tenuto), accent(accent), fermata(fermata),
			tied(tied), slurred(slurred){}
	bool dot() { 
        if (!dotted) {
			if (duration == one_twenty_eighth_note) {
				return false;	
			} else {
				dotted = true;
				duration *= 1.5;
			}
			return true;
		} else if (dotted && !double_dotted) {
			if (duration == dotted_sixty_fourth_note) {
				return false;
			} else {
				double_dotted = true;
				duration /= 6;
				duration *= 7;
			}
			return true;
		} else if (dotted && double_dotted) {
			return false;
		}
    }
	bool doubledot() {
		if (dotted) {
			return false;
		} else if (duration == one_twenty_eighth_note ||
			duration == sixty_fourth_note) {
			return false;	
		} else {
			dotted = true;
			double_dotted = true;
			duration /= 4;
			duration *= 7;
		}
		return true;
	}
	bool putInTriplet() {
		if (triplet) {
			return false;
		} else {
			triplet = true;
			duration /= 3;
			duration *= 2;
		}
		return true;
	}
	bool addOctave() {
		if (pitches.size() == 0 || pitches[pitches.size()-1] + 12 > 126) {
			return false;
		}
		for (int i = 0; i < pitches.size(); i++) {
			pitches[i] += 12;
		}
		return true;
	}
	bool dropOctave() {
		if (pitches.size() == 0 || pitches[0] - 12 < 0) {
			return false;
		}
		for (int i = 0; i < pitches.size(); i++) {
			pitches[i] -= 12;
		}
		return true;
	}
	bool invert() {
		if (pitches.size() < 2 || pitches[0] + 12 > 126) {
			return false;
		}
		pitches.push_back(pitches[0] + 12);
		pitches.erase(pitches.begin());
		return true;
	}
    std::vector<char> pitches;
    unsigned int duration : 10;
	unsigned int triplet : 1;
	unsigned int dotted : 1;
	unsigned int double_dotted : 1;
    unsigned int staccato : 1;
    unsigned int tenuto : 1;
    unsigned int accent : 1;
    unsigned int fermata : 1;
    unsigned int tied : 1;
    unsigned int slurred : 1;
};

#endif /* CHORD_H */
