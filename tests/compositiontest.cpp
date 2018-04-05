/* 
 * File:   compositiontest.cpp
 * Author: Sam Rappl
 *
 */
 
#include "composition.h"
#include "gtest/gtest.h"

TEST(compositionTest, getCompositionMetricsAtPositionTest) {
	Composition comp;
	// Test with no composition metrics
	ASSERT_EQ(NULL, comp.getCompositionMetricsAtPosition(0));
	// Test with compsition metrics
	CompositionMetrics mets;
	Key key;
	TimeSignature timeSignature;
	mets.key = key;
	mets.timeSignature = timeSignature;
	comp.setInitialCompositionMetrics(&mets);
	ASSERT_EQ(mets.key.getTonic(),
			comp.getCompositionMetricsAtPosition(0)->key.getTonic());
	// Test with multiple composition metrics
	CompositionMetrics met2;
	Key key2(fs3, minor_intervals);
	TimeSignature timeSignature2;
	met2.key = key2;
	met2.timeSignature = timeSignature2;
	met2.position = 58;
	comp.addNewCompositionMetrics(&met2);
	ASSERT_EQ(mets.key.getTonic(),
			comp.getCompositionMetricsAtPosition(15)->key.getTonic());
	ASSERT_EQ(met2.key.getTonic(),
			comp.getCompositionMetricsAtPosition(58)->key.getTonic());
	ASSERT_EQ(met2.key.getTonic(),
			comp.getCompositionMetricsAtPosition(65)->key.getTonic());
}

TEST(compositionTest, setInitialKeyTest) {
	Composition comp;
	Key key(fs3, minor_intervals);
	comp.setInitialKey(key);
	ASSERT_EQ(key.getTonic(),
			comp.getCompositionMetricsAtPosition(0)->key.getTonic());
	// Test change in initial key
	Key key2(g3, major_intervals);
	comp.setInitialKey(key2);
	ASSERT_EQ(key2.getTonic(),
			comp.getCompositionMetricsAtPosition(0)->key.getTonic());
}

TEST(compositionTest, setInitialTempoTest) {
	Composition comp;
	comp.setInitialTempo(65);
	ASSERT_EQ(65, comp.getCompositionMetricsAtPosition(0)->tempo);
	// Test change in initial tempo
	comp.setInitialTempo(45);
	ASSERT_EQ(45, comp.getCompositionMetricsAtPosition(0)->tempo);
}

TEST(compositionTest, setInitialTimeSignatureTest) {
	Composition comp;
	TimeSignature timeSig(5, 4);
	comp.setInitialTimeSignature(timeSig);
	ASSERT_EQ(timeSig.num,
			comp.getCompositionMetricsAtPosition(0)->timeSignature.num);
	// Test change in initial time signature
	TimeSignature timeSig2(6, 4);
	comp.setInitialTimeSignature(timeSig2);
	ASSERT_EQ(timeSig2.num,
			comp.getCompositionMetricsAtPosition(0)->timeSignature.num);
	
}

TEST(compositionTest, addKeyChangeTest) {
	Composition comp;
	Key key;
	comp.setInitialKey(key);
	// Test at position of a CompositionMetrics
	Key key2(a3, minor_intervals);
	comp.addKeyChange(key2, 0);
	ASSERT_EQ(key2.getTonic(),
			comp.getCompositionMetricsAtPosition(0)->key.getTonic());
	// Test with same key as previous composition metrics
	comp.addKeyChange(key2, 18);
	ASSERT_EQ(0, comp.getCompositionMetricsAtPosition(78)->position);
	// Test at new location
	Key key3(g5, major_intervals);
	comp.addKeyChange(key3, 13);
	ASSERT_EQ(key3.getTonic(),
			comp.getCompositionMetricsAtPosition(14)->key.getTonic());
}

TEST(compositionTest, addTempoChangeTest) {
	Composition comp;
	comp.setInitialTempo(65);
	// Test at position of a CompositionMetrics
	comp.addTempoChange(35, 0);
	ASSERT_EQ(35, comp.getCompositionMetricsAtPosition(0)->tempo);
	// Test with same tempo as previous composition metrics
	comp.addTempoChange(35, 444);
	ASSERT_EQ(0, comp.getCompositionMetricsAtPosition(480)->position);
	// Test at new location
	comp.addTempoChange(121, 130);
	ASSERT_EQ(121, comp.getCompositionMetricsAtPosition(135)->tempo);
}

TEST(compositionTest, addTimeSignatureChangeTest) {
	Composition comp;
	TimeSignature timeSig;
	comp.setInitialTimeSignature(timeSig);
	// Test at position of a CompositionMetrics
	TimeSignature timeSig2(15, 2);
	comp.addTimeSignatureChange(timeSig2, 0);
	ASSERT_EQ(timeSig2.num,
			comp.getCompositionMetricsAtPosition(0)->timeSignature.num);
	// Test with same time signature as previous composition metrics
	comp.addTimeSignatureChange(timeSig2, 14);
	ASSERT_EQ(0, comp.getCompositionMetricsAtPosition(154)->position);
	// Test at new location
	TimeSignature timeSig3(6, 8);
	comp.addTimeSignatureChange(timeSig3, 7);
	ASSERT_EQ(timeSig3.num,
			comp.getCompositionMetricsAtPosition(9)->timeSignature.num);
}

TEST(compositionTest, addNewCompositionMetricsTest) {
	Composition comp;
	
	// Test at position of a CompositionMetrics
	
	// Test with same metrics as previous composition metrics
	
	// Test at new location
}

TEST(compositionTest, updateCompositionMetricsAtPositionTest) {
	
}

TEST(compositionTest, getAllCompositionMetricsTest) {
	
}

TEST(compositionTest, getPartTest) {
	// Test no part with name
	
	// Test part with name
}

TEST(compositionTest, getPartsTest) {
	
}

TEST(compositionTest, addPartTest) {
	// Test that part gets added
	
	// Test that part with same name won't be added
}

TEST(compositionTest, registerPatternSegmentTest) {
	
}

TEST(compositionTest, editPatternSegmentTest) {
	
}

TEST(compositionTest, getPatternSegmentTest) {
	
}

TEST(compositionTest, addToPatternTest) {
	// Test with no corresponding pattern segment
	
	// Test with corresponding pattern segment
}

TEST(compositionTest, getPatternTest) {
	
}

TEST(compositionTest, resetPatternTest) {
	
}

TEST(compositionTest, getChordProgressionTest) {
	
}

// Test tree functionality
