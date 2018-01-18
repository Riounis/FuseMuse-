#include "note.h"
#include "constants.h"
#include "gtest/gtest.h"

TEST(noteTest, noteDefaultConstructorTest) {
	// Test Default constructor
	Note note;
	ASSERT_EQ(c4, note.pitch);
	ASSERT_EQ(quarter_note, note.duration);
	ASSERT_FALSE(note.triplet);
	ASSERT_FALSE(note.dotted);
	ASSERT_FALSE(note.double_dotted);
	ASSERT_FALSE(note.staccato);
	ASSERT_FALSE(note.tenuto);
	ASSERT_FALSE(note.accent);
	ASSERT_FALSE(note.fermata);
	ASSERT_FALSE(note.tied);
	ASSERT_FALSE(note.slurred);
}

TEST(noteTest, noteConstructorPitchDurationTest) {
	// Test pitch and duration constructor
	Note note(c4, quarter_note);
	ASSERT_EQ(c4, note.pitch);
	ASSERT_EQ(quarter_note, note.duration);
	ASSERT_FALSE(note.triplet);
	ASSERT_FALSE(note.dotted);
	ASSERT_FALSE(note.double_dotted);
	ASSERT_FALSE(note.staccato);
	ASSERT_FALSE(note.tenuto);
	ASSERT_FALSE(note.accent);
	ASSERT_FALSE(note.fermata);
	ASSERT_FALSE(note.tied);
	ASSERT_FALSE(note.slurred);
}

TEST(noteTest, noteConstructorPitchDurationTripDotDoubleTest) {
	Note note(c4, dotted_quarter_note, false, true, false);
	ASSERT_FALSE(note.triplet);
	ASSERT_TRUE(note.dotted);
	ASSERT_FALSE(note.double_dotted);
}

TEST(noteTest, noteAllArgsConstructorTest) {
	// Test all argument constructor
	Note note(c4, quarter_note, false, false, false, true,
		false, false, false, false, true);
	ASSERT_EQ(c4, note.pitch);
	ASSERT_EQ(quarter_note, note.duration);
	ASSERT_FALSE(note.triplet);
	ASSERT_FALSE(note.dotted);
	ASSERT_FALSE(note.double_dotted);
	ASSERT_TRUE(note.staccato);
	ASSERT_FALSE(note.tenuto);
	ASSERT_FALSE(note.accent);
	ASSERT_FALSE(note.fermata);
	ASSERT_FALSE(note.tied);
	ASSERT_TRUE(note.slurred);
}

TEST(noteTest, dotTest) {
	Note note(c4, quarter_note);
	
	// Test dot function
	note.dot();
	ASSERT_EQ(dotted_quarter_note, note.duration);
	
	// Test dotting a second time
	note.dot();
	ASSERT_EQ(double_dotted_quarter_note, note.duration);
	
	// Test dotting a third time
	ASSERT_FALSE(note.dot());
	
	// Test double dotting
	Note note2(c4, quarter_note);
	note2.doubledot();
	ASSERT_EQ(double_dotted_quarter_note, note2.duration);
	
	// Test double dotting a dotted note
	Note note3(c4, dotted_quarter_note, false, true, false);
	ASSERT_FALSE(note3.doubledot());
}

TEST(noteTest, tripletTest) {
	Note note(c4, quarter_note);
	Note note2(c4, dotted_eighth_note, false, true, false);
	Note note3(c4, triplet_eighth_note, true, false, false);
	
	// Test putInTriplet function
	note.putInTriplet();
	ASSERT_EQ(triplet_quarter_note, note.duration);
	ASSERT_FALSE(note.putInTriplet());
	note2.putInTriplet();
	ASSERT_EQ(triplet_dotted_eighth_note, note2.duration);
	ASSERT_FALSE(note2.putInTriplet());
	ASSERT_FALSE(note3.putInTriplet());
}

TEST(noteTest, pitchBitFieldTest) {
	Note note;
	
	// Lowest Supported Constant
	note.pitch = c0;
	ASSERT_EQ(c0, note.pitch);
	
	// Highest Supported Pitch
	note.pitch = f10;
	ASSERT_EQ(f10, note.pitch);
	
	// Highest Supported Constant
	note.pitch = rest;
	ASSERT_EQ(rest, note.pitch);
	
	// Common Value
	note.pitch = c4;
	ASSERT_EQ(c4, note.pitch);
	
	// OOB test for 7 bit field
	note.pitch = 128;
	EXPECT_NE(128, note.pitch) << "If this fails, the size of the bit"
	<< " field for pitch has been increased.";
}

TEST(noteTest, durationBitFieldTest) {
	Note note;
	
	// Lowest Supported Duration
	note.duration = 0;
	ASSERT_EQ(0, note.duration);
	
	// Lowest Supported Constant
	note.duration = triplet_one_twenty_eighth_note;
	ASSERT_EQ(triplet_one_twenty_eighth_note, note.duration);
	
	// Highest Supported Constant
	note.duration = double_dotted_whole_note;
	ASSERT_EQ(double_dotted_whole_note, note.duration);
	
	// Highest Supported Duration
	note.duration = 1023;
	ASSERT_EQ(1023, note.duration);
	
	// Common Value
	note.duration = quarter_note;
	ASSERT_EQ(quarter_note, note.duration);
	
	// OOB test for 10 bit field.
	note.duration = 1024;
	EXPECT_NE(1024, note.duration) << "If this fails, the size of the bit"
	<< "field for duration has been increased.";
}