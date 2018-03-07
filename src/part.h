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
	void insertNote(std::vector<Event>::iterator it, Note n) {
		events.insert(it, n);
		length += n.duration;
	}
	void insertChord(std::vector<Event>::iterator it, Chord c) {
		events.insert(it, c);
		length += c.duration;
	}
	void insertDynamic(std::vector<Event>::iterator it, Dynamics d) {
		events.insert(it, d);
	}
	void appendNote(Note n) { events.push_back(n); length += n.duration; }
	void appendChord(Chord c) { events.push_back(c); length += c.duration; }
	void appendDynamic(Dynamics d) { events.push_back(d); }
	Dynamics getCurrentDynamics(std::vector<Event>::iterator it) {
		std::vector<Event>::iterator start = begin();
		while (true) {
			printf("iterator position: %d\n", it);
			Event *e = &*it;
			Dynamics *d = nullptr;
			printf("attempt to dynamic cast to Dynamics*\n");
			if (d = dynamic_cast<Dynamics*>(e)) {
				printf("success casting element to Dynamics*\n");
				return *d;
			}
			printf("failed to cast element to Dynamics*\n");
			if (it == start) {
				printf("at start of vector with no Dynamics, return defaule Dynamic\n");
				Dynamics dynamics;
				return dynamics;
			}
			it--;
		}
	}
	int getLength() { return length; }
	int getNumEvents() { return events.size(); }
private:
	std::vector<Event> events;
	int length;
};

#endif /* PART_H */
