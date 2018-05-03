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
	ASSERT_EQ(NULL, comp.get_composition_metrics_at_position(0));
	// Test with compsition metrics
	CompositionMetrics mets;
	Key key(cs3, major_intervals);
	TimeSignature time_signature;
	mets.key = key;
	mets.time_signature = time_signature;
	comp.set_initial_composition_metrics(&mets);
	ASSERT_EQ(mets.key.get_tonic(),
			comp.get_composition_metrics_at_position(0)->key.get_tonic());
	// Test with multiple composition metrics
	CompositionMetrics met2;
	Key key2(fs3, minor_intervals);
	TimeSignature time_signature2;
	met2.key = key2;
	met2.time_signature = time_signature2;
	met2.position = 58;
	comp.add_new_composition_metrics(&met2);
	ASSERT_EQ(mets.key.get_tonic(),
			comp.get_composition_metrics_at_position(15)->key.get_tonic());
	ASSERT_EQ(met2.key.get_tonic(),
			comp.get_composition_metrics_at_position(58)->key.get_tonic());
	ASSERT_EQ(met2.key.get_tonic(),
			comp.get_composition_metrics_at_position(65)->key.get_tonic());
}

TEST(compositionTest, setIntialKeyTest) {
	Composition comp;
	Key key(fs3, minor_intervals);
	comp.set_initial_key(key);
	ASSERT_EQ(key.get_tonic(),
			comp.get_composition_metrics_at_position(0)->key.get_tonic());
	// Test change in initial key
	Key key2(g3, major_intervals);
	comp.set_initial_key(key2);
	ASSERT_EQ(key2.get_tonic(),
			comp.get_composition_metrics_at_position(0)->key.get_tonic());
}

TEST(compositionTest, setInitialTempoTest) {
	Composition comp;
	comp.set_initial_tempo(65);
	ASSERT_EQ(65, comp.get_composition_metrics_at_position(0)->tempo);
	// Test change in initial tempo
	comp.set_initial_tempo(45);
	ASSERT_EQ(45, comp.get_composition_metrics_at_position(0)->tempo);
}

TEST(compositionTest, setInitialTimeSignatureTest) {
	Composition comp;
	TimeSignature timeSig(5, 4);
	comp.set_initial_time_signature(timeSig);
	ASSERT_EQ(timeSig.num,
			comp.get_composition_metrics_at_position(0)->time_signature.num);
	// Test change in initial time signature
	TimeSignature timeSig2(6, 4);
	comp.set_initial_time_signature(timeSig2);
	ASSERT_EQ(timeSig2.num,
			comp.get_composition_metrics_at_position(0)->time_signature.num);
	
}

TEST(compositionTest, addKeyChangeTest) {
	Composition comp;
	Key key;
	Key key2(a3, minor_intervals);
	// Test with no initial key
	ASSERT_FALSE(comp.add_key_change(key2, 5));
	comp.set_initial_key(key);
	// Test at position of a CompositionMetrics
	comp.add_key_change(key2, 0);
	ASSERT_EQ(key2.get_tonic(),
			comp.get_composition_metrics_at_position(0)->key.get_tonic());
	// Test with same key as previous composition metrics
	comp.add_key_change(key2, 18);
	ASSERT_EQ(0, comp.get_composition_metrics_at_position(78)->position);
	// Test at new location
	Key key3(g5, major_intervals);
	comp.add_key_change(key3, 13);
	ASSERT_EQ(key3.get_tonic(),
			comp.get_composition_metrics_at_position(14)->key.get_tonic());
}

TEST(compositionTest, addTempoChangeTest) {
	Composition comp;
	// Test with no initial tempo
	ASSERT_FALSE(comp.add_tempo_change(35, 5));
	comp.set_initial_tempo(65);
	// Test at position of a CompositionMetrics
	comp.add_tempo_change(35, 0);
	ASSERT_EQ(35, comp.get_composition_metrics_at_position(0)->tempo);
	// Test with same tempo as previous composition metrics
	comp.add_tempo_change(35, 444);
	ASSERT_EQ(0, comp.get_composition_metrics_at_position(480)->position);
	// Test at new location
	comp.add_tempo_change(121, 130);
	ASSERT_EQ(121, comp.get_composition_metrics_at_position(135)->tempo);
}

TEST(compositionTest, addTimeSignatureChangeTest) {
	Composition comp;
	TimeSignature timeSig;
	TimeSignature timeSig2(15, 2);
	// Test with no initial time signature
	ASSERT_FALSE(comp.add_time_signature_change(timeSig2, 5));
	comp.set_initial_time_signature(timeSig);
	// Test at position of a CompositionMetrics
	comp.add_time_signature_change(timeSig2, 0);
	ASSERT_EQ(timeSig2.num,
			comp.get_composition_metrics_at_position(0)->time_signature.num);
	// Test with same time signature as previous composition metrics
	comp.add_time_signature_change(timeSig2, 14);
	ASSERT_EQ(0, comp.get_composition_metrics_at_position(154)->position);
	// Test at new location
	TimeSignature timeSig3(6, 8);
	comp.add_time_signature_change(timeSig3, 7);
	ASSERT_EQ(timeSig3.num,
			comp.get_composition_metrics_at_position(9)->time_signature.num);
}

TEST(compositionTest, addNewCompositionMetricsTest) {
	Composition comp;
	TimeSignature timeSig(6, 4);
	Key key(af3, minor_intervals);
	CompositionMetrics mets;
	mets.key = key;
	mets.time_signature = timeSig;
	mets.tempo = 65;
	mets.position = 0;
	comp.set_initial_composition_metrics(&mets);
	// Test at position of a CompositionMetrics
	TimeSignature timeSig2(8, 8);
	Key key2(gf3, major_intervals);
	CompositionMetrics mets2;
	mets2.key = key2;
	mets2.time_signature = timeSig2;
	mets2.tempo = 99;
	mets2.position = 0;
	comp.add_new_composition_metrics(&mets2);
	ASSERT_EQ(timeSig2.num,
			comp.get_composition_metrics_at_position(0)->time_signature.num);
	// Test with same metrics as previous composition metrics
	CompositionMetrics mets3;
	mets3.key = key2;
	mets3.time_signature = timeSig2;
	mets3.tempo = 99;
	mets3.position = 48;
	comp.add_new_composition_metrics(&mets3);
	ASSERT_EQ(0, comp.get_composition_metrics_at_position(50)->position);
	// Test at new location
	CompositionMetrics mets4;
	mets4.key = key2;
	mets4.time_signature = timeSig2;
	mets4.position = 48;
	mets4.tempo = 120;
	comp.add_new_composition_metrics(&mets4);
	ASSERT_EQ(120, comp.get_composition_metrics_at_position(51)->tempo);
}

TEST(compositionTest, updateCompositionMetricsAtPositionTest) {
	Composition comp;
	Key key(a5, major_intervals);
	TimeSignature timeSig(5, 4);
	CompositionMetrics mets;
	mets.key = key;
	mets.time_signature = timeSig;
	mets.tempo = 80;
	mets.position = 0;
	comp.set_initial_composition_metrics(&mets);
	Key key2(a3, minor_intervals);
	TimeSignature timeSig2(6, 8);
	CompositionMetrics mets2;
	mets2.key = key2;
	mets2.time_signature = timeSig2;
	mets2.tempo = 85;
	mets2.position = 90;
	comp.add_new_composition_metrics(&mets2);
	Key key3(fs3, dorian_intervals);
	TimeSignature timeSig3(3, 4);
	comp.update_composition_metrics_at_position(90, key3, 86, timeSig3);
	ASSERT_EQ(fs3, comp.get_composition_metrics_at_position(90)->key.get_tonic());
	ASSERT_EQ(3, comp.get_composition_metrics_at_position(90)->time_signature.num);
	ASSERT_EQ(86, comp.get_composition_metrics_at_position(90)->tempo);
}

TEST(compositionTest, getPartTest) {
	Composition comp;
	Part p("drumline");
	comp.add_part(p);
	// Test no part with name
	ASSERT_EQ(NULL, comp.get_part("bass"));
	// Test part with name
	ASSERT_EQ("drumline", comp.get_part("drumline")->get_name());
}

TEST(compositionTest, getPartsTest) {
	Composition comp;
	Part p("drumline");
	Part p2("bass");
	Part p3("guitar");
	comp.add_part(p);
	comp.add_part(p2);
	comp.add_part(p3);
	std::vector<Part*> parts = comp.get_parts();
	ASSERT_EQ(3, parts.size());
	ASSERT_EQ("drumline", parts[0]->get_name());
	ASSERT_EQ("bass", parts[1]->get_name());
	ASSERT_EQ("guitar", parts[2]->get_name());
}

TEST(compositionTest, addPartTest) {
	Composition comp;
	Part p("drumline");
	// Test that part gets added
	comp.add_part(p);
	ASSERT_EQ("drumline", comp.get_part("drumline")->get_name());
	// Test that part with same name won't be added
	Part p2("drumline");
	ASSERT_FALSE(comp.add_part(p2));
}

TEST(compositionTest, registerPatternSegmentTest) {
	PatternSegment p("verse", 3084);
	Composition comp;
	comp.register_pattern_segment(&p);
	ASSERT_EQ("verse", comp.get_pattern_segment("verse")->get_name());
	PatternSegment p2("verse", 3084);
	ASSERT_FALSE(comp.register_pattern_segment(&p2));
}

TEST(compositionTest, editPatternSegmentTest) {
	PatternSegment p("verse", 3084);
	Composition comp;
	comp.register_pattern_segment(&p);
	PatternSegment p2("verse", 1024);
	comp.edit_pattern_segment(&p2);
	ASSERT_EQ(1024, comp.get_pattern_segment("verse")->get_duration());
	PatternSegment p3("vorse", 2048);
	ASSERT_FALSE(comp.edit_pattern_segment(&p3));
}

TEST(compositionTest, getPatternSegmentTest) {
	PatternSegment p("verse", 3084);
	Composition comp;
	comp.register_pattern_segment(&p);
	ASSERT_EQ("verse", comp.get_pattern_segment("verse")->get_name());
}

TEST(compositionTest, addToPatternTest) {
	Composition comp;
	// Test with no corresponding pattern segment
	ASSERT_FALSE(comp.add_to_pattern("verse"));
	// Test with corresponding pattern segment
	PatternSegment p("verse", 3084);
	comp.register_pattern_segment(&p);
	comp.add_to_pattern("verse");
	ASSERT_EQ("verse", comp.get_pattern()[0]);
}

TEST(compositionTest, getPatternTest) {
	Composition comp;
	PatternSegment p("verse", 3084);
	PatternSegment p2("chorus", 1024);
	comp.register_pattern_segment(&p);
	comp.register_pattern_segment(&p2);
	for (int i = 0; i < 3; i++) {
		comp.add_to_pattern("verse");
		comp.add_to_pattern("chorus");
	}
	std::vector<std::string> pattern = comp.get_pattern();
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
	comp.register_pattern_segment(&p);
	comp.register_pattern_segment(&p2);
	for (int i = 0; i < 3; i++) {
		comp.add_to_pattern("verse");
		comp.add_to_pattern("chorus");
	}
	comp.reset_pattern();
	ASSERT_EQ(0, comp.get_pattern().size());
}
