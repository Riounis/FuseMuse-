/* 
 * File:   parttest.cpp
 * Author: Sam Rappl
 *
 */

#include "part.h"
#include "gtest/gtest.h"

TEST(partTest, setNameTest) {
	Part part;
	part.set_name("name");
	ASSERT_EQ("name", part.get_name());
}

TEST(partTest, emptyPartTest) {
	Part part;
	ASSERT_EQ(0, part.get_length());
}

TEST(partTest, appendNoteTest) {
	Part part;
	Note note(e4, eighth_note);
	part.append_note(&note);
	ASSERT_EQ(eighth_note, part.get_length());
	Event *e = *part.begin();
	Note *n = nullptr;
	Chord *c = nullptr;
	Dynamic *d = nullptr;
	if (n = dynamic_cast<Note*>(e)) {
		ASSERT_EQ(note.pitch, n->pitch);
	}
	else if (c = dynamic_cast<Chord*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (d = dynamic_cast<Dynamic*>(e)) {
		ASSERT_FALSE(true);
	}
	else {
		FAIL();
	}
	ASSERT_EQ(eighth_note, part.get_length());
}

TEST(partTest, appendChordTest) {
	Part part;
	Chord chord(gs_minor_7_chord, half_note);
	part.append_chord(&chord);
	ASSERT_EQ(half_note, part.get_length());
	Event *e = *part.begin();
	Note *n = nullptr;
	Chord *c = nullptr;
	Dynamic *d = nullptr;
	if (n = dynamic_cast<Note*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (c = dynamic_cast<Chord*>(e)) {
		ASSERT_EQ(gs_minor_7_chord, c->pitches);
	}
	else if (d = dynamic_cast<Dynamic*>(e)) {
		ASSERT_FALSE(true);
	}
	else {
		FAIL();
	}
	ASSERT_EQ(half_note, part.get_length());
}

TEST(partTest, appendDynamicTest) {
	Part part;
	Dynamic dynamic(mf);
	part.append_dynamic(&dynamic);
	ASSERT_EQ(0, part.get_length());
	Event *e = *part.begin();
	Note *n = nullptr;
	Chord *c = nullptr;
	Dynamic *d = nullptr;
	if (n = dynamic_cast<Note*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (c = dynamic_cast<Chord*>(e)) {
		ASSERT_FALSE(true);
	}
	else if (d = dynamic_cast<Dynamic*>(e)) {
		ASSERT_EQ(mf, d->volume);
	}
	else {
		FAIL();
	}
	ASSERT_EQ(0, part.get_length());
}

TEST(partTest, appendAllEventsTest) {
	Part part;
	Note note(cs3, half_note);
	Chord chord(g_major_chord, quarter_note);
	Dynamic dynamic(mf, false, false);
	part.append_chord(&chord);
	ASSERT_EQ(quarter_note, part.get_length());
	part.append_dynamic(&dynamic);
	ASSERT_EQ(quarter_note, part.get_length());
	part.append_note(&note);
	ASSERT_EQ(dotted_half_note, part.get_length());
	std::vector<Event*>::iterator it = part.begin();
	for (int i = 0; i < part.get_num_events(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamic *d = nullptr;
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
		else if (d = dynamic_cast<Dynamic*>(e)) {
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
	Dynamic dynamic(mp, true, false);
	Note note(fs3, quarter_note);
	Note note2(ds3, quarter_note);
	Note note3(cs2, quarter_note);
	Dynamic dynamic2(mp, true, false);
	Note note4(ds3, quarter_note);
	Note note5(gs3, quarter_note);
	Dynamic dynamic3(ff, true, false);
	part.append_dynamic(&dynamic);
	part.append_note(&note);
	part.append_note(&note2);
	part.append_note(&note3);
	part.append_dynamic(&dynamic2);
	part.append_note(&note4);
	part.append_note(&note5);
	part.append_dynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	for (int i = 0; i < part.get_num_events(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamic *d = nullptr;
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
		else if (d = dynamic_cast<Dynamic*>(e)) {
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
	Dynamic dynamics;
	part.append(&note);
	part.append(&chord);
	part.append(&dynamics);
	ASSERT_EQ(3, part.get_num_events());
	std::vector<Event*>::iterator it = part.begin();
	for (int i = 0; i < part.get_num_events(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamic *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			ASSERT_EQ(0, i);
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			ASSERT_EQ(1, i);
		}
		else if (d = dynamic_cast<Dynamic*>(e)) {
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
	part.append_note(&note);
	part.append_note(&note2);
	part.append_note(&note3);
	ASSERT_EQ(3*quarter_note, part.get_length());
	ASSERT_EQ(3, part.get_num_events());
	std::vector<Event*>::iterator it = part.begin();
	it++;
	part.erase(it);
	it--;
	ASSERT_EQ(2*quarter_note, part.get_length());
	ASSERT_EQ(2, part.get_num_events());
	for (int i = 0; i < part.get_num_events(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamic *d = nullptr;
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
		else if (d = dynamic_cast<Dynamic*>(e)) {
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
	ASSERT_EQ(0, part.get_num_events());
	part.insert_note(part.begin(), &note);
	ASSERT_EQ(1, part.get_num_events());
}

TEST(partTest, insertNoteTest) {
	Part part;
	Note note(fs3, quarter_note);
	Note note2(ds3, quarter_note);
	Note note3(cs2, quarter_note);
	part.append_note(&note);
	part.append_note(&note3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	part.insert_note(it, &note2);
	it = part.begin();
	ASSERT_EQ(3, part.get_num_events());
	for (int i = 0; i < part.get_num_events(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamic *d = nullptr;
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
		else if (d = dynamic_cast<Dynamic*>(e)) {
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
	part.append_chord(&chord);
	part.append_chord(&chord3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	part.insert_chord(it, &chord2);
	it = part.begin();
	ASSERT_EQ(3, part.get_num_events());
	for (int i = 0; i < part.get_num_events(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamic *d = nullptr;
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
		else if (d = dynamic_cast<Dynamic*>(e)) {
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
	Dynamic dynamic(mp);
	Dynamic dynamic2(mf);
	Dynamic dynamic3(f);
	part.append_dynamic(&dynamic);
	part.append_dynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	part.insert_dynamic(it, &dynamic2);
	it = part.begin();
	ASSERT_EQ(3, part.get_num_events());
	for (int i = 0; i < part.get_num_events(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamic *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			FAIL();
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			FAIL();
		}
		else if (d = dynamic_cast<Dynamic*>(e)) {
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
	Dynamic dynamic(mf);
	Note note(c4, eighth_note);
	Note note2(d4, eighth_note);
	Note note3(e4, eighth_note);
	Note note4(f4, eighth_note);
	Note note5(g4, eighth_note);
	Note note6(a4, eighth_note);
	Note note7(b4, eighth_note);
	part.append_dynamic(&dynamic);
	part.append_note(&note);
	part.append_note(&note2);
	part.append_note(&note3);
	part.append_note(&note4);
	part.append_note(&note5);
	part.append_note(&note7);
	std::vector<Event*>::iterator it = part.begin();
	// Increment to note 7, to insert note 6 before it.
	for (int i = 0; i < 6; i++) { it++; }
	part.insert_note(it, &note6);
	it = part.begin();
	for (int i = 0; i < part.get_num_events(); i++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamic *d = nullptr;
		if (n = dynamic_cast<Note*>(e)) {
			if (i < 1 || i > 7) {
				FAIL();
			}
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			FAIL();
		}
		else if (d = dynamic_cast<Dynamic*>(e)) {
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

TEST(partGetDynamicTest, emptyListTest) {
	Part part;
	ASSERT_EQ(mp, part.get_current_dynamics(part.begin()).volume);
}

TEST(partGetDynamicTest, noDynamicTest) {
	Part part;
	Note note;
	Chord chord;
	Note note2;
	part.append_note(&note);
	part.append_chord(&chord);
	part.append_note(&note2);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	ASSERT_EQ(mp, part.get_current_dynamics(it).volume);
}

TEST(partGetDynamicTest, onDynamicTest) {
	Part part;
	Dynamic dynamics(mf);
	Note note;
	Dynamic dynamics2(f);
	Dynamic dynamics3(pp);
	part.append_dynamic(&dynamics);
	part.append_note(&note);
	part.append_dynamic(&dynamics2);
	part.append_dynamic(&dynamics3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	ASSERT_EQ(f, part.get_current_dynamics(it).volume);
	it++;
	ASSERT_EQ(pp, part.get_current_dynamics(it).volume);
}

TEST(partGetDynamicTest, postDynamicTest) {
	Part part;
	Dynamic dynamics(p);
	Note note;
	Note note2;
	part.append_dynamic(&dynamics);
	part.append_note(&note);
	part.append_note(&note2);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	ASSERT_EQ(p, part.get_current_dynamics(it).volume);
	it++;
	ASSERT_EQ(p, part.get_current_dynamics(it).volume);
}

TEST(partGetDynamicPositionTest, outOfBoundsTest) {
	Part part;
	Dynamic dynamics(p);
	Note note;
	Chord chord;
	Dynamic dynamics2(mf);
	Chord chord2;
	part.append_dynamic(&dynamics);
	part.append_note(&note);
	part.append_chord(&chord);
	part.append_dynamic(&dynamics2);
	part.append_chord(&chord2);
	ASSERT_EQ(p, part.get_dynamics_at_position(-45).volume);
	ASSERT_EQ(mf, part.get_dynamics_at_position(381).volume);
}

TEST(partGetDynamicPositionTest, boundaryValueTest) {
	Part part;
	Dynamic dynamics(p);
	Note note;
	Chord chord;
	Dynamic dynamics2(mf);
	Dynamic dynamics3(ff);
	Chord chord2;
	part.append_dynamic(&dynamics);
	part.append_note(&note);
	part.append_chord(&chord);
	part.append_dynamic(&dynamics2);
	part.append_dynamic(&dynamics3);
	part.append_chord(&chord2);
	ASSERT_EQ(p, part.get_dynamics_at_position(0).volume);
	ASSERT_EQ(p, part.get_dynamics_at_position(192).volume);
	ASSERT_EQ(ff, part.get_dynamics_at_position(193).volume);
}

TEST(partGetDynamicPositionTest, normalCaseTest) {
	Part part;
	Dynamic dynamics(p);
	Note note;
	Chord chord;
	Dynamic dynamics2(mf);
	Chord chord2;
	part.append_dynamic(&dynamics);
	part.append_note(&note);
	part.append_chord(&chord);
	part.append_dynamic(&dynamics2);
	part.append_chord(&chord2);
	ASSERT_EQ(p, part.get_dynamics_at_position(15).volume);
	ASSERT_EQ(mf, part.get_dynamics_at_position(197).volume);
}

TEST(partGetPitchesTest, emptyListTest) {
	Part part;
	std::vector<Event*>::iterator it = part.begin();
	std::vector<int> pitches;
	ASSERT_EQ(pitches, part.get_current_pitches(it));
}

TEST(partGetPitchesTest, noPitchesTest) {
	Part part;
	Dynamic dynamic;
	Dynamic dynamic2;
	Dynamic dynamic3;
	part.append_dynamic(&dynamic);
	part.append_dynamic(&dynamic2);
	part.append_dynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	std::vector<int> pitches;
	ASSERT_EQ(pitches, part.get_current_pitches(it));
}

TEST(partGetPitchesTest, onDynamicTest) {
	Part part;
	Dynamic dynamic;
	Note note(g5, quarter_note);
	Dynamic dynamic2;
	Dynamic dynamic3;
	part.append_dynamic(&dynamic);
	part.append_note(&note);
	part.append_dynamic(&dynamic2);
	part.append_dynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	std::vector<int> pitches;
	pitches.push_back(g5);
	ASSERT_EQ(pitches, part.get_current_pitches(it));
}

TEST(partGetPitchesTest, postDynamicTest) {
	Part part;
	Dynamic dynamic;
	Note note(g5, quarter_note);
	Note note2(g4, quarter_note);
	Dynamic dynamic3;
	part.append_dynamic(&dynamic);
	part.append_note(&note);
	part.append_note(&note2);
	part.append_dynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	std::vector<int> pitches;
	pitches.push_back(g4);
	ASSERT_EQ(pitches, part.get_current_pitches(it));
}

TEST(partGetPitchesTest, onDynamicChordTest) {
	Part part;
	Dynamic dynamic;
	Chord chord(gs_major_7_chord, quarter_note);
	Dynamic dynamic2;
	Dynamic dynamic3;
	part.append_dynamic(&dynamic);
	part.append_chord(&chord);
	part.append_dynamic(&dynamic2);
	part.append_dynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	ASSERT_EQ(gs_major_7_chord, part.get_current_pitches(it));
}

TEST(partGetPitchesTest, postDynamicChordTest) {
	Part part;
	Dynamic dynamic;
	Chord chord(f_sus2_chord, quarter_note);
	Chord chord2(b_minor_chord, quarter_note);
	Dynamic dynamic3;
	part.append_dynamic(&dynamic);
	part.append_chord(&chord);
	part.append_chord(&chord2);
	part.append_dynamic(&dynamic3);
	std::vector<Event*>::iterator it = part.begin();
	it++;
	it++;
	ASSERT_EQ(b_minor_chord, part.get_current_pitches(it));
}

TEST(partGetPitchesPositionTest, outOfBoundsTest) {
	Part part;
	Dynamic dynamic;
	Chord chord(f_sus2_chord, quarter_note);
	Chord chord2(b_minor_chord, quarter_note);
	Dynamic dynamic3;
	part.append_dynamic(&dynamic);
	part.append_chord(&chord);
	part.append_chord(&chord2);
	part.append_dynamic(&dynamic3);
	ASSERT_EQ(f_sus2_chord, part.get_pitches_at_position(-45));
	ASSERT_EQ(b_minor_chord, part.get_pitches_at_position(1023));
}

TEST(partGetPitchesPositionTest, borderTest) {
	Part part;
	Dynamic dynamic;
	Chord chord(f_sus2_chord, quarter_note);
	Chord chord2(b_minor_chord, quarter_note);
	Dynamic dynamic3;
	part.append_dynamic(&dynamic);
	part.append_chord(&chord);
	part.append_chord(&chord2);
	part.append_dynamic(&dynamic3);
	ASSERT_EQ(f_sus2_chord, part.get_pitches_at_position(0));
	ASSERT_EQ(f_sus2_chord, part.get_pitches_at_position(96));
	ASSERT_EQ(b_minor_chord, part.get_pitches_at_position(97));
}

TEST(partGetPitchesPositionTest, normalCaseTest) {
	Part part;
	Dynamic dynamic;
	Chord chord(f_sus2_chord, quarter_note);
	Chord chord2(b_minor_chord, quarter_note);
	Dynamic dynamic3;
	part.append_dynamic(&dynamic);
	part.append_chord(&chord);
	part.append_chord(&chord2);
	part.append_dynamic(&dynamic3);
	ASSERT_EQ(f_sus2_chord, part.get_pitches_at_position(15));
	ASSERT_EQ(b_minor_chord, part.get_pitches_at_position(105));
}

TEST(partGetPositionIteratorTest, getPositionIteratorTest) {
	Part part;
	Note note;
	Chord chord(a_major_chord, eighth_note);
	Note note2(c3, sixteenth_note);
	part.append_note(&note);
	part.append_chord(&chord);
	part.append_note(&note2);
	std::vector<Event*>::iterator it = part.begin();
	ASSERT_EQ(0, part.get_position_of(it));
	ASSERT_EQ(quarter_note, part.get_position_after(it));
	it++;
	ASSERT_EQ(quarter_note, part.get_position_of(it));
	ASSERT_EQ(dotted_quarter_note, part.get_position_after(it));
	it++;
	ASSERT_EQ(dotted_quarter_note, part.get_position_of(it));
	ASSERT_EQ(double_dotted_quarter_note, part.get_position_after(it));
}
