/* 
 * File:   compositionmetricstest.cpp
 * Author: Sam Rappl
 *
 */

#include "composition_metrics.h"
#include "constants.h"
#include "gtest/gtest.h"
#include <vector>

TEST(compositionMetricsTest, timeSigDefaultConstructorTest) {
	TimeSignature timeSig;
	ASSERT_EQ(4, timeSig.num);
	ASSERT_EQ(4, timeSig.denom);
}

TEST(compositionMetricsTest, timeSigConstructorTest) {
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

TEST(compositionMetricsTest, keyConstructorTest) {
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
	// Test the measure position
	ASSERT_EQ(0, comp.measure);
}
