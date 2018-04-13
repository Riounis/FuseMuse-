/* 
 * File:   part.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef PART_H
#define PART_H
 
#include <vector>
#include <string>
#include <iostream>
#include "constants.h"
#include "event.h"
#include "note.h"
#include "chord.h"
#include "dynamics.h"

/**
 * A Part is an object that represents a single line of music played by a single
 * instrument.
 */
class Part {
public:
	
	/** 
	 * Constructs a Part object with no name and no music.
	 */
	Part(): name(), events(0), length(0) {}
	
	/**
	 * Constructs a Part object with a name and no music.
	 *
	 * @param name The name of the Part.
	 */
	Part(std::string name): name(name), events(0), length(0) {}
	
	/**
	 * Sets the name of the Part to the given name.
	 *
	 * @param n The new name of the Part.
	 */
	void setName(std::string n) { name = n; }
	
	/**
	 * Returns the name of the Part.
	 *
	 * @return The name of the Part.
	 */
	std::string getName() { return name; }
	
	/**
	 * Returns an iterator indexed to the beginning of the list of music notes,
	 * chords, and dynamics in this Part. The ++ operator advances this iterator,
	 * the -- operator moves this iterator back, and the * operator when used to
	 * dereference the iterator gives the contents of the list at the location of
	 * the iterator.
	 *
	 * @return An iterator indexed to the beginning of the list of music notes,
	 * 		chords, and dynamics in this Part.
	 */
	std::vector<Event*>::iterator begin() { return events.begin(); }
	
	/**
	 * Returns an iterator indexed to the end of the list of music notes, chords,
	 * and dynamics in this Part. The ++ operator advances this iterator,
	 * the -- operator moves this iterator back, and the * operator when used to
	 * dereference the iterator gives the contents of the list at the location of
	 * the iterator.
	 *
	 * @return An iterator indexed to the end of the list of music notes, chords,
	 * 		and dynamics in this Part.
	 */
	std::vector<Event*>::iterator end() { return events.end(); }
	
	/**
	 * Erases the music note, chord, or dynamic event at the location of the
	 * iterator passed in and returns an iterator pointing to the location following
	 * the removed music event. If the removed event was the end of the list, it
	 * returns the end iterator.
	 *
	 * @param it An iterator pointing to the music event to be removed from the Part.
	 * @return An iterator indexed to the music event after the one which was removed,
	 * 		or an iterator indexed to the end of the list if the removed event was the
	 * 		last event.
	 */
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
	
	/**
	 * Inserts a Note event at the position in the Part before the given iterator.
	 *
	 * @param it An iterator pointing to the music event after the Note that is
	 * 		to be inserted.
	 * @param n A pointer to the Note to be inserted at the position before the iterator.
	 */
	void insertNote(std::vector<Event*>::iterator it, Note *n) {
		events.insert(it, n);
		length += n->duration;
	}
	
	/**
	 * Inserts a Chord event at the position in the Part before the given iterator.
	 *
	 * @param it An iterator pointing to the music event after the Chord that is
	 * 		to be inserted.
	 * @param n A pointer to the Chord to be inserted at the position before the iterator.
	 */
	void insertChord(std::vector<Event*>::iterator it, Chord *c) {
		events.insert(it, c);
		length += c->duration;
	}
	
	/**
	 * Inserts a Dynamics event at the position in the Part before the given iterator.
	 *
	 * @param it An iterator pointing to the music event after the Dynamic that is
	 * 		to be inserted.
	 * @param n A pointer to the Note to be inserted at the position before the iterator.
	 */
	void insertDynamic(std::vector<Event*>::iterator it, Dynamics *d) {
		events.insert(it, d);
	}
	
	/**
	 * Appends a music event (a Note, Chord, or Dynamics object) to the end of the Part.
	 *
	 * @param e A pointer to the Note, Chord, or Dynamics to be appended to the Part.
	 */
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
	
	/**
	 * Appends a Note to the end of the Part.
	 *
	 * @param n A pointer to the Note to be appended to the Part.
	 */
	void appendNote(Note *n) { events.push_back(n); length += n->duration; }
	
	/**
	 * Appends a Chord to the end of the Part.
	 *
	 * @param c A pointer to the Chord to be appended to the Part.
	 */
	void appendChord(Chord *c) { events.push_back(c); length += c->duration; }
	
	/**
	 * Appends a Dynamics object to the end of the Part.
	 *
	 * @param d A pointer to the Dynamics to be appended to the Part.
	 */
	void appendDynamic(Dynamics *d) { events.push_back(d); }
	
	/**
	 * Returns the length of the Part in FuseMuse duration units.
	 * (see libfm/constants.h for help understanding FuseMuse duration units)
	 *
	 * @return The length of the Part in FuseMuse duration units.
	 */
	int getLength() { return length; }
	
	/**
	 * Returns the number of music events in the Part.
	 *
	 * @return The number of music events in the Part.
	 */
	int getNumEvents() { return events.size(); }
	
	/**
	 * Returns the Dynamics that are applied to the music event pointed to
	 * by the iterator passed in.
	 *
	 * @param it An iterator pointing to the music event to have its Dynamics
	 * 		retrieved.
	 * @return The Dynamics that are used at the position of the music event
	 * 		pointed to by the iterator.
	 */
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
	
	/**
	 * Returns the Dynamics that are applied to the music event at the
	 * given position.
	 *
	 * @param pos The position at which to retrieve Dynamics.
	 * @return The Dynamics used at the given position.
	 */
	Dynamics getDynamicsAtPosition(int pos) {
		return getCurrentDynamics(getIteratorAtPosition(pos));
	}
	
	/**
	 * Returns the pitches that are played by the music event pointed to
	 * by the iterator passed in or at the position of that iterator if the
	 * music event pointed to by the iterator is a Dynamics object.
	 *
	 * @param it An iterator pointing to the music event at the position to
	 * 		check for pitches being played.
	 * @return The pitches that are played at the position of the music event
	 * 		pointed to by the iterator.
	 */
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
	
	/**
	 * Returns the pitches that are played at the given position.
	 *
	 * @param pos The position at which to retrieve pitches.
	 * @return The pitches played at the given position.
	 */
	std::vector<char> getPitchesAtPosition(int pos) {
		return getCurrentPitches(getIteratorAtPosition(pos));
	}
	
	/**
	 * Returns the FuseMuse position at the beginning of the music event pointed to
	 * by the iterator passed in. (see libfm/utilities.h for help understanding
	 * FuseMuse duration units)
	 *
	 * @param it An iterator pointing to the music event of which to get the
	 * 		starting position.
	 * @return The FuseMuse position at which the music event pointed to by the
	 * 		iterator begins.
	 */
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
	
	/**
	 * Returns the FuseMuse position after the music event pointed to by
	 * the iterator passed in. (see libfm/utilities.h for help understanding
	 * FuseMuse duration units)
	 *
	 * @param it An iterator pointing to the music event of which to get the
	 * 		ending position.
	 * @return The FuseMuse position at which the music event pointed to by the
	 * 		iterator ends.
	 */
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
	
	/** The name of the Part. */
	std::string name;
	
	/** 
	 * An ordered list of the music events (Notes, Chords, and Dynamics) in the Part.
	 */
	std::vector<Event*> events;
	
	/** 
	 * The FuseMuse duration of the entire Part. (see libfm/utilities.h for help
	 * understanding FuseMuse duration units)
	 */
	int length;
	
	/**
	 * A private helper method to get an iterator for a music event at a specific
	 * FuseMuse position. see libfm/utilities.h for help understanding FuseMuse
	 * duration units)
	 *
	 * @param pos The position at which the music event the iterator will point to
	 * 		resides.
	 * @return An iterator to the music event at the given position.
	 */
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
	
	/**
	 * A private helper method to see if there are any pitches (Notes or Chords) in
	 * the Part.
	 *
	 * @return Whether the Part contains any pitches.
	 */
	bool listContainsPitches() {
		if (length > 0) {
			return true;
		}
		return false;
	}
};

#endif /* PART_H */
