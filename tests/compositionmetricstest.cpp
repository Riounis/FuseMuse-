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
	TimeSignature timeSig2(5,7);
	ASSERT_EQ(5, timeSig2.num);
	ASSERT_EQ(4, timeSig2.denom);
}

TEST(compositionMetricsTest, keyDefaultConstructorTest) {
	Key key;
	std::vector<char> scale;
	scale.push_back(c3);
	scale.push_back(d3);
	scale.push_back(e3);
	scale.push_back(f3);
	scale.push_back(g3);
	scale.push_back(a3);
	scale.push_back(b3);
	scale.push_back(c4);
	ASSERT_EQ(c3, key.getTonic());
	ASSERT_EQ(scale, key.getScale());
	ASSERT_EQ(major_intervals, key.getIntervals());
}

TEST(keyTest, keyConstructorTest) {
	Key key(ds3, minor_intervals);
	std::vector<char> scale;
	scale.push_back(ds3);
	scale.push_back(f3);
	scale.push_back(fs3);
	scale.push_back(gs3);
	scale.push_back(as3);
	scale.push_back(b3);
	scale.push_back(cs4);
	scale.push_back(ds4);
	ASSERT_EQ(ds3, key.getTonic());
	ASSERT_EQ(scale, key.getScale());
	ASSERT_EQ(minor_intervals, key.getIntervals());
}

TEST(keyTest, keySignatureTest) {
	Key key(g4, major_intervals);
	switch (key.getTonic() % 12) {
		case 0:
			ASSERT_EQ(0, key.getKeySignature());
			break;
		case 1:
			ASSERT_EQ(-5, key.getKeySignature());
			break;
		case 2:
			ASSERT_EQ(2, key.getKeySignature());
			break;
		case 3:
			ASSERT_EQ(-3, key.getKeySignature());
			break;
		case 4:
			ASSERT_EQ(4, key.getKeySignature());
			break;
		case 5:
			ASSERT_EQ(-1, key.getKeySignature());
			break;
		case 6:
			ASSERT_EQ(6, key.getKeySignature());
			break;
		case 7:
			ASSERT_EQ(1, key.getKeySignature());
			break;
		case 8:
			ASSERT_EQ(-4, key.getKeySignature());
			break;
		case 9:
			ASSERT_EQ(3, key.getKeySignature());
			break;
		case 10:
			ASSERT_EQ(-2, key.getKeySignature());
			break;
		case 11:
			ASSERT_EQ(3, key.getKeySignature());
			break;
	}
	Key key2(cs3, minor_intervals);
	switch (key2.getTonic() % 12) {
		case 0:
			ASSERT_EQ(-3, key2.getKeySignature());
			break;
		case 1:
			ASSERT_EQ(4, key2.getKeySignature());
			break;
		case 2:
			ASSERT_EQ(-1, key2.getKeySignature());
			break;
		case 3:
			ASSERT_EQ(6, key2.getKeySignature());
			break;
		case 4:
			ASSERT_EQ(1, key2.getKeySignature());
			break;
		case 5:
			ASSERT_EQ(-4, key2.getKeySignature());
			break;
		case 6:
			ASSERT_EQ(3, key2.getKeySignature());
			break;
		case 7:
			ASSERT_EQ(-2, key2.getKeySignature());
			break;
		case 8:
			ASSERT_EQ(5, key2.getKeySignature());
			break;
		case 9:
			ASSERT_EQ(0, key2.getKeySignature());
			break;
		case 10:
			ASSERT_EQ(-5, key2.getKeySignature());
			break;
		case 11:
			ASSERT_EQ(2, key2.getKeySignature());
			break;
	}
	Key key3(gf3, mixolydian_intervals);
	ASSERT_EQ(0, key3.getKeySignature());
}

TEST(keyTest, keyQualityTest) {
	Key key(gs2, minor_intervals);
	ASSERT_EQ(1, key.getKeyQuality());
	Key key2(c3, major_intervals);
	ASSERT_EQ(0, key2.getKeyQuality());
	Key key3(d3, dorian_intervals);
	ASSERT_EQ(1, key3.getKeyQuality());
}

TEST(keyTest, inScaleTest) {
	Key key(c3, major_intervals);
	ASSERT_EQ(false, key.isInScale(gs3));
	ASSERT_EQ(true, key.isInScale(b3));
	ASSERT_EQ(true, key.isInScale(d5));
}

TEST(keyTest, positionInScaleTest) {
	Key key(c3, lydian_intervals);
	ASSERT_EQ(4, key.positionInScale(fs3));
	ASSERT_EQ(2, key.positionInScale(d6));
	ASSERT_EQ(1, key.positionInScale(c0));
	ASSERT_EQ(-1, key.positionInScale(cs4));
}

TEST(keyTest, nextPitchInScaleTest) {
	Key key(c3, lydian_intervals);
	ASSERT_EQ(fs3, key.nextPitchInScale(e3));
	ASSERT_EQ(fs3, key.nextPitchInScale(f3));
	ASSERT_EQ(g4, key.nextPitchInScale(fs4));
}

TEST(keyTest, nthPitchTest) {
	Key key(c3, lydian_intervals);
	ASSERT_EQ(c3, key.getTonic());
	ASSERT_EQ(d3, key.get2nd());
	ASSERT_EQ(e3, key.get3rd());
	ASSERT_EQ(fs3, key.get4th());
	ASSERT_EQ(g3, key.get5th());
	ASSERT_EQ(a3, key.get6th());
	ASSERT_EQ(b3, key.get7th());
	ASSERT_EQ(fs3, key.getNthPitch(4));
}

TEST(keyTest, keyEqualsTest) {
	Key key(fs3, minor_intervals);
	Key key2(fs3, minor_intervals);
	Key key3(fs3, dorian_intervals);
	Key key4(g3, minor_intervals);
	ASSERT_TRUE(key.equals(key2));
	ASSERT_FALSE(key.equals(key3));
	ASSERT_FALSE(key.equals(key4));
}

TEST(compositionMetricsTest, compositionMetricsDefaultConstructorTest) {
	CompositionMetrics comp;
	std::vector<char> scale;
	scale.push_back(c3);
	scale.push_back(d3);
	scale.push_back(e3);
	scale.push_back(f3);
	scale.push_back(g3);
	scale.push_back(a3);
	scale.push_back(b3);
	scale.push_back(c4);
	// Test the key
	ASSERT_EQ(c3, comp.key.getTonic());
	ASSERT_EQ(scale, comp.key.getScale());
	ASSERT_EQ(major_intervals, comp.key.getIntervals());
	// Test the time signature
	ASSERT_EQ(4, comp.timeSignature.num);
	ASSERT_EQ(4, comp.timeSignature.denom);
	// Test the tempo
	ASSERT_EQ(80, comp.tempo);
	// Test the position
	ASSERT_EQ(0, comp.position);
}

