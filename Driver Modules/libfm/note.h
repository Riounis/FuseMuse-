/* 
 * File:   note.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef NOTE_H
#define NOTE_H

#include "constants.h"
#include "event.h"

/**
 * A Note is an object that represents a music note with pitch and duration.
 */
struct Note: public Event {
	
	/**
	 * Constructs a Note object with the pitch c4 and the duration of a quarter note.
	 */
    Note(): pitch(c4), duration(quarter_note), triplet(0),
			dotted(0), double_dotted(0), staccato(0), tenuto(0), 
            accent(0), fermata(0), tied(0), slurred(0){}
			
	/**
	 * Constructs a Note object with specified pitch and duration. Pitch and Duration
	 * parameters are required, others are optional.
	 *
	 * @param pitch The pitch of the note.
	 * @param duration The duration of the note.
	 * @param triplet Whether the note is in a triplet or not.
	 * @param dotted Whether the note is dotted or not.
	 * @param double_dotted Whether the note is double dotted or not.
	 * @param staccato Whether the note is staccato or not.
	 * @param tenuto Whether the note is tenuto or not.
	 * @param accent Whether the note is accented or not.
	 * @param fermata Whether the note is to be held or not.
	 * @param tied Whether the note is tied to the next note.
	 * @param slurred Whether the note is slurred to the next note.
	 */
    Note(int pitch, int duration, int triplet = 0, int dotted = 0,
			int double_dotted = 0, int staccato = 0, int tenuto = 0,
			int accent = 0, int fermata = 0, int tied = 0,
			int slurred = 0) : pitch(pitch), duration(duration),
			triplet(triplet), dotted(dotted),
			double_dotted(double_dotted), staccato(staccato),
			tenuto(tenuto), accent(accent), fermata(fermata),
			tied(tied), slurred(slurred){}
	
	/**
	 * Adds a dot to the note (which turns on the dotted flag and increases the duration
	 * of the note by 1/2 of its original duration, unless it is already dotted, in which
	 * case, it double dots the note by increasing its duration by 7/6 its original duration.
	 *
	 * @return Whether the note was dotted.
	 */
	bool dot() { 
        if (!dotted) {
			if (duration == one_twenty_eighth_note) {
				return false;	
			} else {
				dotted = true;
				duration *= 1.5;
			}
		} else if (dotted && !double_dotted) {
			if (duration == dotted_sixty_fourth_note) {
				return false;
			} else {
				double_dotted = true;
				duration /= 6;
				duration *= 7;
			}
		} else if (dotted && double_dotted) {
			return false;
		}
    }
	
	/**
	 * Adds two dots to the note, turning its duration into 7/4 its original duration.
	 *
	 * @return Whether the note was double dotted.
	 */
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
	}
	
	/**
	 * Puts the note in a triplet by turning on the triplet flag and making the note's
	 * duration 2/3 its original duration.
	 *
	 * @return Whether the note was added to a triplet.
	 */
	bool putInTriplet() {
		if (triplet) {
			return false;
		} else {
			triplet = true;
			duration /= 3;
			duration *= 2;
		}
	}
	
    unsigned int pitch : 7;
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


#endif /* NOTE_H */

