/* 
 * File:   chordtest.cpp
 * Author: Sam Rappl
 *
 */

#include <vector>
#include "chord.h"
#include "constants.h"
#include "gtest/gtest.h"

TEST(chordTest, chordDefaultConstructorTest) {
	// Test Default constructor
	std::vector<char> defvec = {c4, e4, g4};
	Chord chord;
	ASSERT_EQ(defvec, chord.pitches);
	ASSERT_EQ(quarter_note, chord.duration);
	ASSERT_FALSE(chord.triplet);
	ASSERT_FALSE(chord.dotted);
	ASSERT_FALSE(chord.double_dotted);
	ASSERT_FALSE(chord.staccato);
	ASSERT_FALSE(chord.tenuto);
	ASSERT_FALSE(chord.accent);
	ASSERT_FALSE(chord.fermata);
	ASSERT_FALSE(chord.tied);
	ASSERT_FALSE(chord.slurred);
}

TEST(chordTest, chordConstructorPitchDurationTest) {
	// Test pitch and duration constructor
	std::vector<char> invec;
	invec.push_back(d4);
	invec.push_back(fs4);
	invec.push_back(a4);
	Chord chord(invec, quarter_note);
	ASSERT_EQ(invec, chord.pitches);
	ASSERT_EQ(quarter_note, chord.duration);
	ASSERT_FALSE(chord.triplet);
	ASSERT_FALSE(chord.dotted);
	ASSERT_FALSE(chord.double_dotted);
	ASSERT_FALSE(chord.staccato);
	ASSERT_FALSE(chord.tenuto);
	ASSERT_FALSE(chord.accent);
	ASSERT_FALSE(chord.fermata);
	ASSERT_FALSE(chord.tied);
	ASSERT_FALSE(chord.slurred);
}

TEST(chordTest, chordConstructorPitchDurationTripDotDoubleTest) {
	std::vector<char> invec;
	invec.push_back(d4);
	invec.push_back(fs4);
	invec.push_back(a4);
	Chord chord(invec, dotted_quarter_note, false, true, false);
	ASSERT_FALSE(chord.triplet);
	ASSERT_TRUE(chord.dotted);
	ASSERT_FALSE(chord.double_dotted);
}

TEST(chordTest, chordAllArgsConstructorTest) {
	// Test all argument constructor
	std::vector<char> invec;
	invec.push_back(d4);
	invec.push_back(fs4);
	invec.push_back(a4);
	Chord chord(invec, quarter_note, false, false, false, true,
		false, false, false, false, true);
	ASSERT_EQ(invec, chord.pitches);
	ASSERT_EQ(quarter_note, chord.duration);
	ASSERT_FALSE(chord.triplet);
	ASSERT_FALSE(chord.dotted);
	ASSERT_FALSE(chord.double_dotted);
	ASSERT_TRUE(chord.staccato);
	ASSERT_FALSE(chord.tenuto);
	ASSERT_FALSE(chord.accent);
	ASSERT_FALSE(chord.fermata);
	ASSERT_FALSE(chord.tied);
	ASSERT_TRUE(chord.slurred);
}

TEST(chordTest, dotTest) {
	std::vector<char> invec;
	invec.push_back(d4);
	invec.push_back(fs4);
	invec.push_back(a4);
	Chord chord(invec, quarter_note);
	
	// Test dot function
	chord.dot();
	ASSERT_EQ(dotted_quarter_note, chord.duration);
	
	// Test dotting a second time
	chord.dot();
	ASSERT_EQ(double_dotted_quarter_note, chord.duration);
	
	// Test dotting a third time
	ASSERT_FALSE(chord.dot());
	
	// Test double dotting
	Chord chord2(invec, quarter_note);
	chord2.doubledot();
	ASSERT_EQ(double_dotted_quarter_note, chord2.duration);
	
	// Test double dotting a dotted chord
	Chord chord3(invec, dotted_quarter_note, false, true, false);
	ASSERT_FALSE(chord3.doubledot());
}

TEST(chordTest, tripletTest) {
	std::vector<char> invec;
	invec.push_back(d4);
	invec.push_back(fs4);
	invec.push_back(a4);
	Chord chord(invec, quarter_note);
	Chord chord2(invec, dotted_eighth_note, false, true, false);
	Chord chord3(invec, triplet_eighth_note, true, false, false);
	
	// Test putInTriplet function
	chord.putInTriplet();
	ASSERT_EQ(triplet_quarter_note, chord.duration);
	ASSERT_FALSE(chord.putInTriplet());
	chord2.putInTriplet();
	ASSERT_EQ(triplet_dotted_eighth_note, chord2.duration);
	ASSERT_FALSE(chord2.putInTriplet());
	ASSERT_FALSE(chord3.putInTriplet());
}
