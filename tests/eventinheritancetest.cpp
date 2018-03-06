/* 
 * File:   eventinheritancetest.cpp
 * Author: Sam Rappl
 *
 */

#include "dynamics.h"
#include "note.h"
#include "chord.h"
#include "event.h"
#include "constants.h"
#include "gtest/gtest.h"
#include <vector>

TEST(eventInheritanceTest, dynamicsInheritanceTest) {
	std::vector<Event> events;
	Dynamics dynamic;
	events.push_back(dynamic);
	Event *e = &events[0];
	Note *n = nullptr;
	Chord *c = nullptr;
	Dynamics *d = nullptr;
	if (n = dynamic_cast<Note*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (c = dynamic_cast<Chord*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (d = dynamic_cast<Dynamics*>(e)) {
		ASSERT_TRUE(true);
	}
}

TEST(eventInheritanceTest, noteInheritanceTest) {
	std::vector<Event> events;
	Note note;
	events.push_back(note);
	Event *e = &events[0];
	Note *n = nullptr;
	Chord *c = nullptr;
	Dynamics *d = nullptr;
	if (n = dynamic_cast<Note*>(e)) {
		ASSERT_TRUE(true);
	}
	else if (c = dynamic_cast<Chord*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (d = dynamic_cast<Dynamics*>(e)) {
		ASSERT_FALSE(true);
	}
}

TEST(eventInheritanceTest, chordInheritanceTest) {
	std::vector<Event> events;
	Chord chord;
	events.push_back(chord);
	Event *e = &events[0];
	Note *n = nullptr;
	Chord *c = nullptr;
	Dynamics *d = nullptr;
	if (n = dynamic_cast<Note*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (c = dynamic_cast<Chord*>(e)) {
		ASSERT_TRUE(true);
	}
	else if (d = dynamic_cast<Dynamics*>(e)) {
		ASSERT_FALSE(true);
	}
}

TEST(eventInheritanceTest, mixedListInheritanceTest) {
	std::vector<Event> events;
	Dynamics dynamic(ff, false, true);
	events.push_back(dynamic);
	Note note(gs7, half_note);
	events.push_back(note);
	std::vector<char> invec;
	invec.push_back(fs3);
	invec.push_back(ef4);
	invec.push_back(b5);
	invec.push_back(cs6);
	Chord chord(invec, eighth_note);
	events.push_back(chord);
	for (int i = 0; i < events.size(); i++) {
		Event *e = &events[i];
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			ASSERT_EQ(gs7, n->pitch);
			ASSERT_EQ(half_note, n->duration);
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			ASSERT_EQ(invec, c->pitches);
			ASSERT_EQ(eighth_note, c->duration);
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			ASSERT_EQ(ff, d->volume);
			ASSERT_EQ(false, d->cresc);
			ASSERT_EQ(true, d->decresc);
		}
	}
}
