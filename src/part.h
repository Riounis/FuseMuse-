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
	Part() : events(0), length(0) {}
	std::vector<Event>::iterator begin() { return events.begin(); }
	std::vector<Event>::iterator end() { return events.end(); }
	std::vector<Event>::iterator erase(std::vector<Event>::iterator it) {
		Event *e = &*it;
		Note *n = nullptr;
		Chord *c = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			length -= n->duration;
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			length -= n->duration;
		}
		return events.erase(it);
	}
	void appendNote(Note n) { events.push_back(n); length += n.duration; }
	void appendChord(Chord c) { events.push_back(c); length += c.duration; }
	void appendDynamic(Dynamics d) { events.push_back(d); }
	int getLength() { return length; }
	int getNumEvents() { return events.size(); }
private:
	std::vector<Event> events;
	int length;
};

#endif /* PART_H */
