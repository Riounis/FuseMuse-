/* 
 * File:   part.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef PART_H
#define PART_H
 
#include <vector>
#include <iostream>
#include "constants.h"
#include "event.h"
#include "note.h"
#include "chord.h"
#include "dynamics.h"

class Part {
public:
    auto begin() { return events.begin(); }
	auto end() { return events.end(); }
	auto erase(auto it) { 
	    length -= it->duration;
		return events.erase(it);
	}
	void insert(Event e) {
		events.insert(it, e);
	}
	void appendNote(Note n) { events.push_back(n); length += n.duration; }
	void appendChord(Chord c) { events.push_back(c); length += c.duration; }
	void appendDynamic(Dynamics d) { events.push_back(d); }
	Dynamics getDynamicsAtPosition(int pos) {
		int currentPosition = 0;
		auto it = begin();
		auto it2 = begin();
		auto iter = end();
		while (currentPosition <= pos && it != iter) {
			currentPosition += it->duration;
			it++;
		}
		it--;
		while (it->duration != 0 && it != it2) {
		    it--;
		}
		return it*;
	}
	std::vector<char> getPitchesAtPosition(int pos) {
		int currentPosition = 0;
		auto it = begin();
		auto iter = end();
		while (currentPosition <= pos && it != iter) {
			currentPosition += it->duration;
			it++;
		}
		it--;
		Note n = dynamic_cast<Note>(it*);
		if (!n) {
			Chord c = dynamic_cast<Chord>(it*);
			return c.pitches;
		}
		else {
			std::vector<char> pitches;
			pitches.push_back(n.pitch);
			return pitches;
		}
		return NULL;
	}
	int getLength() { return length; }
private:
	std::vector<Event> events;
	int length;
}

#endif /* PART_H */
