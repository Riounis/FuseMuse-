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
	std::vector<Event*>::iterator begin() { return events.begin(); }
	std::vector<Event*>::iterator end() { return events.end(); }
	std::vector<Event*>::iterator erase(std::vector<Event*>::iterator it) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			length -= n->duration;
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			length -= c->duration;
		}
		return events.erase(it);
	}
	void insertNote(std::vector<Event*>::iterator it, Note *n) {
		events.insert(it, n);
		length += n->duration;
	}
	void insertChord(std::vector<Event*>::iterator it, Chord *c) {
		events.insert(it, c);
		length += c->duration;
	}
	void insertDynamic(std::vector<Event*>::iterator it, Dynamics *d) {
		events.insert(it, d);
	}
	void append(Event *e) {
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			appendNote(n);
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			appendChord(c);
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			appendDynamic(d);
		}
	}
	void appendNote(Note *n) { events.push_back(n); length += n->duration; }
	void appendChord(Chord *c) { events.push_back(c); length += c->duration; }
	void appendDynamic(Dynamics *d) { events.push_back(d); }
	int getLength() { return length; }
	int getNumEvents() { return events.size(); }
	Dynamics getCurrentDynamics(std::vector<Event*>::iterator it) {
		if (events.size() == 0) {
			Dynamics dynamics;
			return dynamics;
		}
		std::vector<Event*>::iterator start = begin();
		while (true) {
			Event *e = *it;
			Dynamics *d = nullptr;
			if (d = dynamic_cast<Dynamics*>(e)) {
				return *d;
			}
			if (it == start) {
				Dynamics dynamics;
				return dynamics;
			}
			it--;
		}
	}
	Dynamics getDynamicsAtPosition(int pos) {
		return getCurrentDynamics(getIteratorAtPosition(pos));
	}
	std::vector<char> getCurrentPitches(std::vector<Event*>::iterator it) {
		if (events.size() == 0) {
			std::vector<char> drop;
			return drop;
		}
		bool up = false;
		while (true) {
			Event *e = *it;
			Dynamics *d = nullptr;
			if (d = dynamic_cast<Dynamics*>(e)) {
				if (it == begin() && !listContainsPitches()) {
					std::vector<char> drop;
					return drop;
				}
				else if (it == begin()) {
					up = true;
				}
				if (up) {
					it++;
				}
				else {
					it--;
				}
			}
			else {
				Note *n = nullptr;
				Chord *c = nullptr;
				if (n = dynamic_cast<Note*>(e)) {
					std::vector<char> ret;
					ret.push_back(n->pitch);
					return ret;
				}
				else if (c = dynamic_cast<Chord*>(e)) {
					return c->pitches;
				}
			}
		}
	}
	std::vector<char> getPitchesAtPosition(int pos) {
		return getCurrentPitches(getIteratorAtPosition(pos));
	}
	int getPositionOf(std::vector<Event*>::iterator it) {
		int pos = 0;
		while (it != begin()) {
			it--;
			Event *e = *it;
			Note *n = nullptr;
			Chord *c = nullptr;
			if (n = dynamic_cast<Note*>(e)) {
				pos += n->duration;
			}
			else if (c = dynamic_cast<Chord*>(e)) {
				pos += c->duration;
			}
		}
		return pos;
	}
	int getPositionAfter(std::vector<Event*>::iterator it) {
		int pos = 0;
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			pos += n->duration;
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			pos += c->duration;
		}
		while (it != begin()) {
			it--;
			Event *e = *it;
			Note *n = nullptr;
			Chord *c = nullptr;
			if (n = dynamic_cast<Note*>(e)) {
				pos += n->duration;
			}
			else if (c = dynamic_cast<Chord*>(e)) {
				pos += c->duration;
			}
		}
		return pos;
	}
private:
	std::vector<Event*> events;
	int length;
	std::vector<Event*>::iterator getIteratorAtPosition(int pos) {
		if (pos <= 0) {
			return begin();
		}
		else if (pos >= length) {
			std::vector<Event*>::iterator it = begin();
			while (it != end()) { it++; }
			it --;
			return it;
		}
		else {
			std::vector<Event*>::iterator it = begin();
			int tempPos = 0;
			while (tempPos < pos) {
				Event *e = *it;
				Note *n = nullptr;
				Chord *c = nullptr;
				if (n = dynamic_cast<Note*>(e)) {
					tempPos += n->duration;
				}
				else if (c = dynamic_cast<Chord*>(e)) {
					tempPos += c->duration;
				}
				if (tempPos >= pos) {
					return it;
				}
				it++;
			}
		}
	}
	bool listContainsPitches() {
		if (length > 0) {
			return true;
		}
		return false;
	}
};

#endif /* PART_H */
