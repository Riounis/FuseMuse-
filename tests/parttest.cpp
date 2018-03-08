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
	part.appendNote(&note);
	ASSERT_EQ(eighth_note, part.getLength());
	Event *e = *part.begin();
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
	else {
		FAIL();
	}
	ASSERT_EQ(eighth_note, part.getLength());
}

TEST(partTest, appendChordTest) {
	Part part;
	Chord chord(gs_minor_7_chord, half_note);
	part.appendChord(&chord);
	ASSERT_EQ(half_note, part.getLength());
	Event *e = *part.begin();
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
	else {
		FAIL();
	}
	ASSERT_EQ(half_note, part.getLength());
}

TEST(partTest, appendDynamicTest) {
	Part part;
	Dynamics dynamic(mf);
	part.appendDynamic(&dynamic);
	ASSERT_EQ(0, part.getLength());
	Event *e = *part.begin();
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
	else {
		FAIL();
	}
	ASSERT_EQ(0, part.getLength());
}

TEST(partTest, appendAllEventsTest) {
	Part part;
	Note note(cs3, half_note);
	Chord chord(g_major_chord, quarter_note);
	Dynamics dynamic(mf, false, false);
	part.appendChord(&chord);
	ASSERT_EQ(quarter_note, part.getLength());
	part.appendDynamic(&dynamic);
	ASSERT_EQ(quarter_note, part.getLength());
	part.appendNote(&note);
	ASSERT_EQ(dotted_half_note, part.getLength());
	std::vector<Event*>::iterator it = part.begin();
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = *it;
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
		else {
			FAIL();
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
	part.appendDynamic(&dynamic);
	part.appendNote(&note);
	part.appendNote(&note2);
	part.appendNote(&note3);
	part.appendDynamic(&dynamic2);
	part.appendNote(&note4);
	part.appendNote(&note5);
	part.appendDynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = *it;
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
		else {
			FAIL();
		}
		it++;
	}
}

TEST(partTest, iteratorEraseTest) {
	Part part;
	Note note(fs3, quarter_note);
	Note note2(ds3, quarter_note);
	Note note3(cs2, quarter_note);
	part.appendNote(&note);
	part.appendNote(&note2);
	part.appendNote(&note3);
	ASSERT_EQ(3*quarter_note, part.getLength());
	ASSERT_EQ(3, part.getNumEvents());
	std::vector<Event*>::iterator it = part.begin();
	it++;
	part.erase(it);
	it--;
	ASSERT_EQ(2*quarter_note, part.getLength());
	ASSERT_EQ(2, part.getNumEvents());
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = *it;
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
		else {
			FAIL();
		}
		it++;
	}
}

TEST(partTest, insertIntoEmptyListTest) {
	Part part;
	Note note;
	ASSERT_EQ(0, part.getNumEvents());
	part.insertNote(part.begin(), &note);
	ASSERT_EQ(1, part.getNumEvents());
}

TEST(partTest, insertNoteTest) {
	Part part;
	Note note(fs3, quarter_note);
	Note note2(ds3, quarter_note);
	Note note3(cs2, quarter_note);
	part.appendNote(&note);
	part.appendNote(&note3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	part.insertNote(it, &note2);
	it = part.begin();
	ASSERT_EQ(3, part.getNumEvents());
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			if (i == 0) {
				ASSERT_EQ(fs3, n->pitch);
			}
			else if (i == 1) {
				ASSERT_EQ(ds3, n->pitch);
			}
			else if (i == 2) {
				ASSERT_EQ(cs2, n->pitch);
			}
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			FAIL();
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			FAIL();
		}
		else {
			FAIL();
		}
		it++;
	}
}

TEST(partTest, insertChordTest) {
	Part part;
	Chord chord(fs_major_chord, quarter_note);
	Chord chord2(ds_minor_chord, quarter_note);
	Chord chord3(cs_sus4_chord, quarter_note);
	part.appendChord(&chord);
	part.appendChord(&chord3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	part.insertChord(it, &chord2);
	it = part.begin();
	ASSERT_EQ(3, part.getNumEvents());
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			FAIL();
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			if (i == 0) {
				ASSERT_EQ(fs_major_chord, c->pitches);
			}
			else if (i == 1) {
				ASSERT_EQ(ds_minor_chord, c->pitches);
			}
			else if (i == 2) {
				ASSERT_EQ(cs_sus4_chord, c->pitches);
			}
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			FAIL();
		}
		else {
			FAIL();
		}
		it++;
	}
}

TEST(partTest, insertDynamicTest) {
	Part part;
	Dynamics dynamic(mp);
	Dynamics dynamic2(mf);
	Dynamics dynamic3(f);
	part.appendDynamic(&dynamic);
	part.appendDynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	part.insertDynamic(it, &dynamic2);
	it = part.begin();
	ASSERT_EQ(3, part.getNumEvents());
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			FAIL();
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			FAIL();
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			if (i == 0) {
				ASSERT_EQ(mp, d->volume);
			}
			else if (i == 1) {
				ASSERT_EQ(mf, d->volume);
			}
			else if (i == 2) {
				ASSERT_EQ(f, d->volume);
			}
		}
		else {
			FAIL();
		}
		it++;
	}
}

TEST(partTest, insertMixedListTest) {
	Part part;
	Dynamics dynamic(mf);
	Note note(c4, eighth_note);
	Note note2(d4, eighth_note);
	Note note3(e4, eighth_note);
	Note note4(f4, eighth_note);
	Note note5(g4, eighth_note);
	Note note6(a4, eighth_note);
	Note note7(b4, eighth_note);
	part.appendDynamic(&dynamic);
	part.appendNote(&note);
	part.appendNote(&note2);
	part.appendNote(&note3);
	part.appendNote(&note4);
	part.appendNote(&note5);
	part.appendNote(&note7);
	std::vector<Event*>::iterator it = part.begin();
	// Increment to note 7, to insert note 6 before it.
	for (int i = 0; i < 6; i++) { it++; }
	part.insertNote(it, &note6);
	it = part.begin();
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			if (i < 1 || i > 7) {
				FAIL();
			}
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			FAIL();
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			if (i == 0) {
				ASSERT_EQ(mf, d->volume);
			}
		}
		else {
			FAIL();
		}
		it++;
	}
}

TEST(partTest, getCurrentDynamicsValidTest) {
	Part part;
	Dynamics dynamic(mf);
	Note note(c4, eighth_note);
	Note note2(d4, eighth_note);
	Note note3(e4, eighth_note);
	Note note4(f4, eighth_note);
	Note note5(g4, eighth_note);
	Dynamics dynamic2(f);
	Note note6(a4, eighth_note);
	Note note7(b4, eighth_note);
	part.appendDynamic(&dynamic);
	part.appendNote(&note);
	part.appendNote(&note2);
	part.appendNote(&note3);
	part.appendNote(&note4);
	part.appendNote(&note5);
	part.appendDynamic(&dynamic2);
	part.appendNote(&note6);
	part.appendNote(&note7);
	std::vector<Event*>::iterator it = part.begin();
	// increment a few notes into part.
	for (int i = 0; i < 3; i++) { it++; }
	ASSERT_EQ(mf, part.getCurrentDynamics(it).volume);
	// increment past the second Dynamics object in the part.
	for (int i = 0; i < 4; i++) { it++; }
	ASSERT_EQ(f, part.getCurrentDynamics(it).volume);
}

TEST(partTest, getCurrentDynamicsInvalidTest) {
	Part part;
	Note note(c4, eighth_note);
	Note note2(d4, eighth_note);
	Note note3(e4, eighth_note);
	Note note4(f4, eighth_note);
	Note note5(g4, eighth_note);
	part.appendNote(&note);
	part.appendNote(&note2);
	part.appendNote(&note3);
	part.appendNote(&note4);
	part.appendNote(&note5);
	
	std::vector<Event*>::iterator it = part.begin();
	// increment a few notes into part.
	for (int i = 0; i < 3; i++) { it++; }
	ASSERT_EQ(mp, part.getCurrentDynamics(it).volume);
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
