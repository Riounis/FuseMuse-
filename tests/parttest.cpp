/* 
 * File:   parttest.cpp
 * Author: Sam Rappl
 *
 */

#include "part.h"
#include "gtest/gtest.h"

TEST(partTest, emptyPartTest) {
	Part part;
	ASSERT_EQ(0, part.getLength());
}

TEST(partTest, appendNoteTest) {
	Part part;
	Note note(e4, eighth_note);
	part.appendNote(note);
	ASSERT_EQ(eighth_note, part.getLength());
	Event *e = &*part.begin();
	Note *n = nullptr;
	Chord *c = nullptr;
	Dynamics *d = nullptr;
	if (n = dynamic_cast<Note*>(e)) {
		ASSERT_EQ(note.pitch, n->pitch);
	}
	else if (c = dynamic_cast<Chord*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (d = dynamic_cast<Dynamics*>(e)) {
		ASSERT_FALSE(true);
	}
	ASSERT_EQ(eighth_note, part.getLength());
}

TEST(partTest, appendChordTest) {
	Part part;
	Chord chord(gs_minor_7_chord, half_note);
	part.appendChord(chord);
	ASSERT_EQ(half_note, part.getLength());
	Event *e = &*part.begin();
	Note *n = nullptr;
	Chord *c = nullptr;
	Dynamics *d = nullptr;
	if (n = dynamic_cast<Note*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (c = dynamic_cast<Chord*>(e)) {
		ASSERT_EQ(gs_minor_7_chord, c->pitches);
	}
	else if (d = dynamic_cast<Dynamics*>(e)) {
		ASSERT_FALSE(true);
	}
	ASSERT_EQ(half_note, part.getLength());
}

TEST(partTest, appendDynamicTest) {
	Part part;
	Dynamics dynamic(mf);
	part.appendDynamic(dynamic);
	ASSERT_EQ(0, part.getLength());
	Event *e = &*part.begin();
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
		ASSERT_EQ(mf, d->volume);
	}
	ASSERT_EQ(0, part.getLength());
}

TEST(partTest, appendAllEventsTest) {
	Part part;
	Note note(cs3, half_note);
	Chord chord(g_major_chord, quarter_note);
	Dynamics dynamic(mf, false, false);
	part.appendChord(chord);
	ASSERT_EQ(quarter_note, part.getLength());
	part.appendDynamic(dynamic);
	ASSERT_EQ(quarter_note, part.getLength());
	part.appendNote(note);
	ASSERT_EQ(dotted_half_note, part.getLength());
	std::vector<Event>::iterator it = part.begin();
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = &*it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			ASSERT_EQ(2, i);
			ASSERT_EQ(cs3, n->pitch);
			ASSERT_EQ(half_note, n->duration);
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			ASSERT_EQ(0, i);
			ASSERT_EQ(g_major_chord, c->pitches);
			ASSERT_EQ(quarter_note, c->duration);
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			ASSERT_EQ(1, i);
			ASSERT_EQ(mf, d->volume);
		}
		it++;
	}
}

TEST(partTest, appendMultiNoteDynamicTest) {
	Part part;
	Dynamics dynamic(mp, true, false);
	Note note(fs3, quarter_note);
	Note note2(ds3, quarter_note);
	Note note3(cs2, quarter_note);
	Dynamics dynamic2(mp, true, false);
	Note note4(ds3, quarter_note);
	Note note5(gs3, quarter_note);
	Dynamics dynamic3(ff, true, false);
	part.appendDynamic(dynamic);
	part.appendNote(note);
	part.appendNote(note2);
	part.appendNote(note3);
	part.appendDynamic(dynamic2);
	part.appendNote(note4);
	part.appendNote(note5);
	part.appendDynamic(dynamic3);
	std::vector<Event>::iterator it = part.begin();
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = &*it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			if (i == 1 || i == 2 || i == 3 || i == 5 || i == 6) {
				ASSERT_EQ(quarter_note, n->duration);
			}
			else {
				FAIL();
			}
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			FAIL();
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			if (i == 0 || i == 4 || i == 7) {
				ASSERT_EQ(true, d->cresc);
			}
			else {
				FAIL();
			}
		}
		it++;
	}
}

TEST(partTest, iteratorEraseTest) {
	Part part;
	Note note(fs3, quarter_note);
	Note note2(ds3, quarter_note);
	Note note3(cs2, quarter_note);
	part.appendNote(note);
	part.appendNote(note2);
	part.appendNote(note3);
	std::vector<Event>::iterator it = part.begin();
	it++;
	part.erase(it);
	it--;
	ASSERT_EQ(2, part.getNumEvents());
	for(int i = 0; i < part.getNumEvents(); i++) {
		Event *e = &*it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			if (i == 0) {
				ASSERT_EQ(fs3, n->pitch);
			}
			else if (i == 1) {
				ASSERT_EQ(cs2, n->pitch);
			}
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			FAIL();
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			FAIL();
		}
		it++;
	}
}

TEST(partTest, insertNoteTest) {
	FAIL();
}

TEST(partTest, insertChordTest) {
	FAIL();
}

TEST(partTest, insertDynamicTest) {
	FAIL();
}

TEST(partTest, getCurrentDynamicsTest) {
	FAIL();
}

TEST(partTest, getDynamicsAtPositionTest) {
	FAIL();
}

TEST(partTest, getPitchesAtPositionTest) {
	FAIL();
}

TEST(partTest, getCurrentPitchesTest) {
	FAIL();
}

TEST(partTest, typeCurrentElementTest) {
	FAIL();
}
