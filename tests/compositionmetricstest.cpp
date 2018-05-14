/* 
 * File:   compositionmetricstest.cpp
 * Author: Sam Rappl
 *
 */

#include "composition_metrics.h"
#include "constants.h"
#include "gtest/gtest.h"
#include <vector>

TEST(timeSigTest, timeSigDefaultConstructorTest) {
	TimeSignature timeSig;
	ASSERT_EQ(4, timeSig.num);
	ASSERT_EQ(4, timeSig.denom);
}

TEST(timeSigTest, timeSigConstructorTest) {
	TimeSignature timeSig(6,8);
	ASSERT_EQ(6, timeSig.num);
	ASSERT_EQ(8, timeSig.denom);
	//TimeSignature timeSig2(5,7);
	//ASSERT_EQ(5, timeSig2.num);
	//ASSERT_EQ(4, timeSig2.denom);
}

TEST(compositionMetricsTest, keyDefaultConstructorTest) {
	Key key;
	std::vector<int> scale;
	scale.push_back(c3);
	scale.push_back(d3);
	scale.push_back(e3);
	scale.push_back(f3);
	scale.push_back(g3);
	scale.push_back(a3);
	scale.push_back(b3);
	scale.push_back(c4);
	ASSERT_EQ(c3, key.get_tonic());
	ASSERT_EQ(scale, key.get_scale());
	ASSERT_EQ(major_intervals, key.get_intervals());
}

TEST(keyTest, keyConstructorTest) {
	Key key(ds3, minor_intervals);
	std::vector<int> scale;
	scale.push_back(ds3);
	scale.push_back(f3);
	scale.push_back(fs3);
	scale.push_back(gs3);
	scale.push_back(as3);
	scale.push_back(b3);
	scale.push_back(cs4);
	scale.push_back(ds4);
	ASSERT_EQ(ds3, key.get_tonic());
	ASSERT_EQ(scale, key.get_scale());
	ASSERT_EQ(minor_intervals, key.get_intervals());
}

TEST(keyTest, keySignatureTest) {
	Key key(g4, major_intervals);
	switch (key.get_tonic() % 12) {
		case 0:
			ASSERT_EQ(0, key.get_key_signature());
			break;
		case 1:
			ASSERT_EQ(-5, key.get_key_signature());
			break;
		case 2:
			ASSERT_EQ(2, key.get_key_signature());
			break;
		case 3:
			ASSERT_EQ(-3, key.get_key_signature());
			break;
		case 4:
			ASSERT_EQ(4, key.get_key_signature());
			break;
		case 5:
			ASSERT_EQ(-1, key.get_key_signature());
			break;
		case 6:
			ASSERT_EQ(6, key.get_key_signature());
			break;
		case 7:
			ASSERT_EQ(1, key.get_key_signature());
			break;
		case 8:
			ASSERT_EQ(-4, key.get_key_signature());
			break;
		case 9:
			ASSERT_EQ(3, key.get_key_signature());
			break;
		case 10:
			ASSERT_EQ(-2, key.get_key_signature());
			break;
		case 11:
			ASSERT_EQ(3, key.get_key_signature());
			break;
	}
	Key key2(cs3, minor_intervals);
	switch (key2.get_tonic() % 12) {
		case 0:
			ASSERT_EQ(-3, key2.get_key_signature());
			break;
		case 1:
			ASSERT_EQ(4, key2.get_key_signature());
			break;
		case 2:
			ASSERT_EQ(-1, key2.get_key_signature());
			break;
		case 3:
			ASSERT_EQ(6, key2.get_key_signature());
			break;
		case 4:
			ASSERT_EQ(1, key2.get_key_signature());
			break;
		case 5:
			ASSERT_EQ(-4, key2.get_key_signature());
			break;
		case 6:
			ASSERT_EQ(3, key2.get_key_signature());
			break;
		case 7:
			ASSERT_EQ(-2, key2.get_key_signature());
			break;
		case 8:
			ASSERT_EQ(5, key2.get_key_signature());
			break;
		case 9:
			ASSERT_EQ(0, key2.get_key_signature());
			break;
		case 10:
			ASSERT_EQ(-5, key2.get_key_signature());
			break;
		case 11:
			ASSERT_EQ(2, key2.get_key_signature());
			break;
	}
	Key key3(gf3, mixolydian_intervals);
	ASSERT_EQ(0, key3.get_key_signature());
}

TEST(keyTest, keyQualityTest) {
	Key key(gs2, minor_intervals);
	ASSERT_EQ(1, key.get_key_quality());
	Key key2(c3, major_intervals);
	ASSERT_EQ(0, key2.get_key_quality());
	Key key3(d3, dorian_intervals);
	ASSERT_EQ(1, key3.get_key_quality());
}

TEST(keyTest, inScaleTest) {
	Key key(c3, major_intervals);
	ASSERT_EQ(false, key.is_in_scale(gs3));
	ASSERT_EQ(true, key.is_in_scale(b3));
	ASSERT_EQ(true, key.is_in_scale(d5));
}

TEST(keyTest, positionInScaleTest) {
	Key key(c3, lydian_intervals);
	ASSERT_EQ(4, key.position_in_scale(fs3));
	ASSERT_EQ(2, key.position_in_scale(d6));
	ASSERT_EQ(1, key.position_in_scale(c0));
	ASSERT_EQ(-1, key.position_in_scale(cs4));
}

TEST(keyTest, nextPitchInScaleTest) {
	Key key(c3, lydian_intervals);
	ASSERT_EQ(fs3, key.next_pitch_in_scale(e3));
	ASSERT_EQ(fs3, key.next_pitch_in_scale(f3));
	ASSERT_EQ(g4, key.next_pitch_in_scale(fs4));
}

TEST(keyTest, nthPitchTest) {
	Key key(c3, lydian_intervals);
	ASSERT_EQ(c3, key.get_tonic());
	ASSERT_EQ(fs3, key.get_nth_pitch(4));
}

TEST(keyTest, keyEqualsTest) {
	Key key(fs3, minor_intervals);
	Key key2(fs3, minor_intervals);
	Key key3(fs3, dorian_intervals);
	Key key4(g3, minor_intervals);
	ASSERT_TRUE(key.equals(&key2));
	ASSERT_FALSE(key.equals(&key3));
	ASSERT_FALSE(key.equals(&key4));
}

TEST(compositionMetricsTest, compositionMetricsDefaultConstructorTest) {
	CompositionMetrics comp;
	std::vector<int> scale;
	scale.push_back(c3);
	scale.push_back(d3);
	scale.push_back(e3);
	scale.push_back(f3);
	scale.push_back(g3);
	scale.push_back(a3);
	scale.push_back(b3);
	scale.push_back(c4);
	// Test the key
	ASSERT_EQ(c3, comp.key.get_tonic());
	ASSERT_EQ(scale, comp.key.get_scale());
	ASSERT_EQ(major_intervals, comp.key.get_intervals());
	// Test the time signature
	ASSERT_EQ(4, comp.time_signature.num);
	ASSERT_EQ(4, comp.time_signature.denom);
	// Test the tempo
	ASSERT_EQ(80, comp.tempo);
	// Test the position
	ASSERT_EQ(0, comp.position);
}

