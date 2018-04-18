/* 
 * File:   parttest.cpp
 * Author: Sam Rappl
 *
 */

#include "part.h"
#include "gtest/gtest.h"

TEST(partTest, setNameTest) {
	Part part;
	part.setName("name");
	ASSERT_EQ("name", part.getName());
}

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

TEST(partTest, appendTest) {
	Part part;
	Note note;
	Chord chord;
	Dynamics dynamics;
	part.append(&note);
	part.append(&chord);
	part.append(&dynamics);
	ASSERT_EQ(3, part.getNumEvents());
	std::vector<Event*>::iterator it = part.begin();
	for (int i = 0; i < part.getNumEvents(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			ASSERT_EQ(0, i);
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			ASSERT_EQ(1, i);
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			ASSERT_EQ(2, i);
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

TEST(partGetDynamicsTest, emptyListTest) {
	Part part;
	ASSERT_EQ(mp, part.getCurrentDynamics(part.begin()).volume);
}

TEST(partGetDynamicsTest, noDynamicsTest) {
	Part part;
	Note note;
	Chord chord;
	Note note2;
	part.appendNote(&note);
	part.appendChord(&chord);
	part.appendNote(&note2);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	ASSERT_EQ(mp, part.getCurrentDynamics(it).volume);
}

TEST(partGetDynamicsTest, onDynamicsTest) {
	Part part;
	Dynamics dynamics(mf);
	Note note;
	Dynamics dynamics2(f);
	Dynamics dynamics3(pp);
	part.appendDynamic(&dynamics);
	part.appendNote(&note);
	part.appendDynamic(&dynamics2);
	part.appendDynamic(&dynamics3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	ASSERT_EQ(f, part.getCurrentDynamics(it).volume);
	it++;
	ASSERT_EQ(pp, part.getCurrentDynamics(it).volume);
}

TEST(partGetDynamicsTest, postDynamicsTest) {
	Part part;
	Dynamics dynamics(p);
	Note note;
	Note note2;
	part.appendDynamic(&dynamics);
	part.appendNote(&note);
	part.appendNote(&note2);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	ASSERT_EQ(p, part.getCurrentDynamics(it).volume);
	it++;
	ASSERT_EQ(p, part.getCurrentDynamics(it).volume);
}

TEST(partGetDynamicsPositionTest, outOfBoundsTest) {
	Part part;
	Dynamics dynamics(p);
	Note note;
	Chord chord;
	Dynamics dynamics2(mf);
	Chord chord2;
	part.appendDynamic(&dynamics);
	part.appendNote(&note);
	part.appendChord(&chord);
	part.appendDynamic(&dynamics2);
	part.appendChord(&chord2);
	ASSERT_EQ(p, part.getDynamicsAtPosition(-45).volume);
	ASSERT_EQ(mf, part.getDynamicsAtPosition(381).volume);
}

TEST(partGetDynamicsPositionTest, boundaryValueTest) {
	Part part;
	Dynamics dynamics(p);
	Note note;
	Chord chord;
	Dynamics dynamics2(mf);
	Dynamics dynamics3(ff);
	Chord chord2;
	part.appendDynamic(&dynamics);
	part.appendNote(&note);
	part.appendChord(&chord);
	part.appendDynamic(&dynamics2);
	part.appendDynamic(&dynamics3);
	part.appendChord(&chord2);
	ASSERT_EQ(p, part.getDynamicsAtPosition(0).volume);
	ASSERT_EQ(p, part.getDynamicsAtPosition(192).volume);
	ASSERT_EQ(ff, part.getDynamicsAtPosition(193).volume);
}

TEST(partGetDynamicsPositionTest, normalCaseTest) {
	Part part;
	Dynamics dynamics(p);
	Note note;
	Chord chord;
	Dynamics dynamics2(mf);
	Chord chord2;
	part.appendDynamic(&dynamics);
	part.appendNote(&note);
	part.appendChord(&chord);
	part.appendDynamic(&dynamics2);
	part.appendChord(&chord2);
	ASSERT_EQ(p, part.getDynamicsAtPosition(15).volume);
	ASSERT_EQ(mf, part.getDynamicsAtPosition(197).volume);
}

TEST(partGetPitchesTest, emptyListTest) {
	Part part;
	std::vector<Event*>::iterator it = part.begin();
	std::vector<int> pitches;
	ASSERT_EQ(pitches, part.getCurrentPitches(it));
}

TEST(partGetPitchesTest, noPitchesTest) {
	Part part;
	Dynamics dynamic;
	Dynamics dynamic2;
	Dynamics dynamic3;
	part.appendDynamic(&dynamic);
	part.appendDynamic(&dynamic2);
	part.appendDynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	std::vector<int> pitches;
	ASSERT_EQ(pitches, part.getCurrentPitches(it));
}

TEST(partGetPitchesTest, onDynamicsTest) {
	Part part;
	Dynamics dynamic;
	Note note(g5, quarter_note);
	Dynamics dynamic2;
	Dynamics dynamic3;
	part.appendDynamic(&dynamic);
	part.appendNote(&note);
	part.appendDynamic(&dynamic2);
	part.appendDynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	std::vector<int> pitches;
	pitches.push_back(g5);
	ASSERT_EQ(pitches, part.getCurrentPitches(it));
}

TEST(partGetPitchesTest, postDynamicsTest) {
	Part part;
	Dynamics dynamic;
	Note note(g5, quarter_note);
	Note note2(g4, quarter_note);
	Dynamics dynamic3;
	part.appendDynamic(&dynamic);
	part.appendNote(&note);
	part.appendNote(&note2);
	part.appendDynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	std::vector<int> pitches;
	pitches.push_back(g4);
	ASSERT_EQ(pitches, part.getCurrentPitches(it));
}

TEST(partGetPitchesTest, onDynamicsChordTest) {
	Part part;
	Dynamics dynamic;
	Chord chord(gs_major_7_chord, quarter_note);
	Dynamics dynamic2;
	Dynamics dynamic3;
	part.appendDynamic(&dynamic);
	part.appendChord(&chord);
	part.appendDynamic(&dynamic2);
	part.appendDynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	ASSERT_EQ(gs_major_7_chord, part.getCurrentPitches(it));
}

TEST(partGetPitchesTest, postDynamicsChordTest) {
	Part part;
	Dynamics dynamic;
	Chord chord(f_sus2_chord, quarter_note);
	Chord chord2(b_minor_chord, quarter_note);
	Dynamics dynamic3;
	part.appendDynamic(&dynamic);
	part.appendChord(&chord);
	part.appendChord(&chord2);
	part.appendDynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	ASSERT_EQ(b_minor_chord, part.getCurrentPitches(it));
}

TEST(partGetPitchesPositionTest, outOfBoundsTest) {
	Part part;
	Dynamics dynamic;
	Chord chord(f_sus2_chord, quarter_note);
	Chord chord2(b_minor_chord, quarter_note);
	Dynamics dynamic3;
	part.appendDynamic(&dynamic);
	part.appendChord(&chord);
	part.appendChord(&chord2);
	part.appendDynamic(&dynamic3);
	ASSERT_EQ(f_sus2_chord, part.getPitchesAtPosition(-45));
	ASSERT_EQ(b_minor_chord, part.getPitchesAtPosition(1023));
}

TEST(partGetPitchesPositionTest, borderTest) {
	Part part;
	Dynamics dynamic;
	Chord chord(f_sus2_chord, quarter_note);
	Chord chord2(b_minor_chord, quarter_note);
	Dynamics dynamic3;
	part.appendDynamic(&dynamic);
	part.appendChord(&chord);
	part.appendChord(&chord2);
	part.appendDynamic(&dynamic3);
	ASSERT_EQ(f_sus2_chord, part.getPitchesAtPosition(0));
	ASSERT_EQ(f_sus2_chord, part.getPitchesAtPosition(96));
	ASSERT_EQ(b_minor_chord, part.getPitchesAtPosition(97));
}

TEST(partGetPitchesPositionTest, normalCaseTest) {
	Part part;
	Dynamics dynamic;
	Chord chord(f_sus2_chord, quarter_note);
	Chord chord2(b_minor_chord, quarter_note);
	Dynamics dynamic3;
	part.appendDynamic(&dynamic);
	part.appendChord(&chord);
	part.appendChord(&chord2);
	part.appendDynamic(&dynamic3);
	ASSERT_EQ(f_sus2_chord, part.getPitchesAtPosition(15));
	ASSERT_EQ(b_minor_chord, part.getPitchesAtPosition(105));
}

TEST(partGetPositionIteratorTest, getPositionIteratorTest) {
	Part part;
	Note note;
	Chord chord(a_major_chord, eighth_note);
	Note note2(c3, sixteenth_note);
	part.appendNote(&note);
	part.appendChord(&chord);
	part.appendNote(&note2);
	std::vector<Event*>::iterator it = part.begin();
	ASSERT_EQ(0, part.getPositionOf(it));
	ASSERT_EQ(quarter_note, part.getPositionAfter(it));
	it++;
	ASSERT_EQ(quarter_note, part.getPositionOf(it));
	ASSERT_EQ(dotted_quarter_note, part.getPositionAfter(it));
	it++;
	ASSERT_EQ(dotted_quarter_note, part.getPositionOf(it));
	ASSERT_EQ(double_dotted_quarter_note, part.getPositionAfter(it));
}
