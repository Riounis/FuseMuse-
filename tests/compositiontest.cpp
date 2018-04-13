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
	Key key(cs3, major_intervals);
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
	printf("haven't set initial key yet\n");
	comp.setInitialKey(key);
	printf("testing initial key\n");
	ASSERT_EQ(key.getTonic(),
			comp.getCompositionMetricsAtPosition(0)->key.getTonic());
	// Test change in initial key
	Key key2(g3, major_intervals);
	printf("testing initial key change\n");
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
	Key key2(a3, minor_intervals);
	// Test with no initial key
	ASSERT_FALSE(comp.addKeyChange(key2, 5));
	comp.setInitialKey(key);
	// Test at position of a CompositionMetrics
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
	// Test with no initial tempo
	ASSERT_FALSE(comp.addTempoChange(35, 5));
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
	TimeSignature timeSig2(15, 2);
	// Test with no initial time signature
	ASSERT_FALSE(comp.addTimeSignatureChange(timeSig2, 5));
	comp.setInitialTimeSignature(timeSig);
	// Test at position of a CompositionMetrics
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
	TimeSignature timeSig(6, 4);
	Key key(af3, minor_intervals);
	CompositionMetrics mets;
	mets.key = key;
	mets.timeSignature = timeSig;
	mets.tempo = 65;
	mets.position = 0;
	comp.setInitialCompositionMetrics(&mets);
	// Test at position of a CompositionMetrics
	TimeSignature timeSig2(8, 8);
	Key key2(gf3, major_intervals);
	CompositionMetrics mets2;
	mets2.key = key2;
	mets2.timeSignature = timeSig2;
	mets2.tempo = 99;
	mets2.position = 0;
	comp.addNewCompositionMetrics(&mets2);
	ASSERT_EQ(timeSig2.num,
			comp.getCompositionMetricsAtPosition(0)->timeSignature.num);
	// Test with same metrics as previous composition metrics
	CompositionMetrics mets3;
	mets3.key = key2;
	mets3.timeSignature = timeSig2;
	mets3.tempo = 99;
	mets3.position = 48;
	comp.addNewCompositionMetrics(&mets3);
	ASSERT_EQ(0, comp.getCompositionMetricsAtPosition(50)->position);
	// Test at new location
	CompositionMetrics mets4;
	mets4.key = key2;
	mets4.timeSignature = timeSig2;
	mets4.position = 48;
	mets4.tempo = 120;
	comp.addNewCompositionMetrics(&mets4);
	ASSERT_EQ(120, comp.getCompositionMetricsAtPosition(51)->tempo);
}

TEST(compositionTest, updateCompositionMetricsAtPositionTest) {
	Composition comp;
	Key key(a5, major_intervals);
	TimeSignature timeSig(5, 4);
	CompositionMetrics mets;
	mets.key = key;
	mets.timeSignature = timeSig;
	mets.tempo = 80;
	mets.position = 0;
	comp.setInitialCompositionMetrics(&mets);
	Key key2(a3, minor_intervals);
	TimeSignature timeSig2(6, 8);
	CompositionMetrics mets2;
	mets2.key = key2;
	mets2.timeSignature = timeSig2;
	mets2.tempo = 85;
	mets2.position = 90;
	comp.addNewCompositionMetrics(&mets2);
	Key key3(fs3, dorian_intervals);
	TimeSignature timeSig3(3, 4);
	comp.updateCompositionMetricsAtPositionTest(90, key3, 86, timeSig3);
	ASSERT_EQ(fs3, comp.getCompositionMetricsAtPosition(90)->key.getTonic());
	ASSERT_EQ(3, comp.getCompositionMetricsAtPosition(90)->timeSignature.num);
	ASSERT_EQ(86, comp.getCompositionMetricsAtPosition(90)->tempo);
}

TEST(compositionTest, getAllCompositionMetricsTest) {
	// I kinda don't feel the need to write this one right now cause it just
	// returns a field of the composition.
}

TEST(compositionTest, getPartTest) {
	Composition comp;
	Part p("drumline");
	comp.addPart(p);
	// Test no part with name
	Part *p2 = comp.getPart("bass");
	ASSERT_EQ(NULL, p2);
	// Test part with name
	Part *p3 = comp.getPart("drumline");
	ASSERT_EQ("drumline", p3->getName());
}

TEST(compositionTest, getPartsTest) {
	Composition comp;
	Part p("drumline");
	Part p2("bass");
	Part p3("guitar");
	comp.addPart(p);
	comp.addPart(p2);
	comp.addPart(p3);
	std::vector<Part*> parts = comp.getParts();
	ASSERT_EQ(3, parts.size());
	ASSERT_EQ("drumline", parts[0]->getName());
	ASSERT_EQ("bass", parts[1]->getName());
	ASSERT_EQ("guitar", parts[2]->getName());
}

TEST(compositionTest, addPartTest) {
	Composition comp;
	Part p("drumline");
	// Test that part gets added
	comp.addPart(p);
	ASSERT_EQ("drumline", comp.getPart("drumline")->getName());
	// Test that part with same name won't be added
	Part p2("drumline");
	ASSERT_FALSE(comp.addPart(p2));
}

TEST(compositionTest, registerPatternSegmentTest) {
	PatternSegment p("verse", 3084);
	Composition comp;
	comp.registerPatternSegment(&p);
	ASSERT_EQ("verse", comp.getPatternSegment("verse")->getName());
	PatternSegment p2("verse", 3084);
	ASSERT_FALSE(comp.registerPatternSegment(&p2));
}

TEST(compositionTest, editPatternSegmentTest) {
	PatternSegment p("verse", 3084);
	Composition comp;
	comp.registerPatternSegment(&p);
	PatternSegment p2("verse", 1024);
	comp.editPatternSegment(&p2);
	ASSERT_EQ(1024, comp.getPatternSegment("verse")->getDuration());
	PatternSegment p3("vorse", 2048);
	ASSERT_FALSE(comp.editPatternSegment(&p3));
}

TEST(compositionTest, getPatternSegmentTest) {
	PatternSegment p("verse", 3084);
	Composition comp;
	comp.registerPatternSegment(&p);
	ASSERT_EQ("verse", comp.getPatternSegment("verse")->getName());
}

TEST(compositionTest, addToPatternTest) {
	Composition comp;
	// Test with no corresponding pattern segment
	ASSERT_FALSE(comp.addToPattern("verse"));
	// Test with corresponding pattern segment
	PatternSegment p("verse", 3084);
	comp.registerPatternSegment(&p);
	comp.addToPattern("verse");
	ASSERT_EQ("verse", comp.getPattern()[0]);
}

TEST(compositionTest, getPatternTest) {
	Composition comp;
	PatternSegment p("verse", 3084);
	PatternSegment p2("chorus", 1024);
	comp.registerPatternSegment(&p);
	comp.registerPatternSegment(&p2);
	for (int i = 0; i < 3; i++) {
		comp.addToPattern("verse");
		comp.addToPattern("chorus");
	}
	std::vector<std::string> pattern = comp.getPattern();
	for (int i = 0; i < pattern.size(); i++) {
		if (i % 2 == 0) {
			ASSERT_EQ("verse", pattern[i]);
		}
		else {
			ASSERT_EQ("chorus", pattern[i]);
		}
	}
}

TEST(compositionTest, resetPatternTest) {
	Composition comp;
	PatternSegment p("verse", 3084);
	PatternSegment p2("chorus", 1024);
	comp.registerPatternSegment(&p);
	comp.registerPatternSegment(&p2);
	for (int i = 0; i < 3; i++) {
		comp.addToPattern("verse");
		comp.addToPattern("chorus");
	}
	comp.resetPattern();
	ASSERT_EQ(0, comp.getPattern().size());
}

TEST(compositionTest, getChordProgressionTest) {
	// Should be what the chord progression is
}

// Test tree functionality
