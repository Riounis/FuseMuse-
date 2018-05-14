/* 
 * File:   utilitestest.cpp
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include "utilities.h"
#include "gtest/gtest.h"

TEST(utilitiesTest, jsonTest) {
	// This is here to ensure nlohmann's json library is included properly
	nlohmann::json j;
	j["hi"] = "good morning";
	ASSERT_EQ("good morning", j["hi"]);
}

TEST(utilitiesTest, noteJSONTest) {
    Note n(g4, dotted_half_note);
    Note n2;
    nlohmann::json j;
    to_json(j, n);
    from_json(j, n2);
    ASSERT_TRUE(n.equals(&n2));
}

TEST(utilitiesTest, chordJSONTest) {
    Chord c(e_major_chord, eighth_note);
    Chord c2;
    nlohmann::json j;
    to_json(j, c);
    from_json(j, c2);
    ASSERT_TRUE(c.equals(&c2));
}

TEST(utilitiesTest, dynamicJSONTest) {
    Dynamic d(ff);
    Dynamic d2;
    nlohmann::json j;
    to_json(j, d);
    from_json(j, d2);
    ASSERT_TRUE(d.equals(&d2));
}

TEST(utilitiesTest, partJSONTest) {
    Part p;
    Part p2;
    Dynamic d(mp);
    Note n(e3, quarter_note);
    Note n2(d3, quarter_note);
    Chord c(c_major_chord, dotted_quarter_note);
    p.append_dynamic(&d);
    p.append_note(&n);
    p.append_note(&n2);
    p.append_chord(&c);
    nlohmann::json j;
    to_json(j, p);
    from_json(j, p2);
    ASSERT_TRUE(p.equals(&p2));
}

TEST(utilitiesTest, patternSegmentJSONTest) {
    PatternSegment ps("testps", quarter_note + quarter_note + dotted_quarter_note);
    PatternSegment ps2;
    Part p;
    Dynamic d(mp);
    Note n(e3, quarter_note);
    Note n2(d3, quarter_note);
    Chord c(c_major_chord, dotted_quarter_note);
    p.append_dynamic(&d);
    p.append_note(&n);
    p.append_note(&n2);
    p.append_chord(&c);
    ps.set_chord_progression(&p);
    nlohmann::json j;
    to_json(j, ps);
    from_json(j, ps2);
    ASSERT_TRUE(ps.equals(&ps2));
}

TEST(utilitiesTest, keyJSONTest) {
    Key k(d4, major_intervals);
    Key k2;
    nlohmann::json j;
    to_json(j, k);
    from_json(j, k2);
    ASSERT_TRUE(k.equals(&k2));
}

TEST(utilitiesTest, timeSignatureJSONTest) {
    TimeSignature t(6, 8);
    TimeSignature t2;
    nlohmann::json j;
    to_json(j, t);
    from_json(j, t2);
    ASSERT_TRUE(t.equals(&t2));
}

TEST(utilitiesTest, compositionMetricsJSONTest) {
    Key k(f3, lydian_intervals);
    TimeSignature t(6, 8);
    CompositionMetrics c;
    c.key = k;
    c.time_signature = t;
    c.tempo = 77;
    c.position = 40;
    CompositionMetrics c2;
    nlohmann::json j;
    to_json(j, c);
    from_json(j, c2);
    ASSERT_TRUE(c.equals(&c2));
}

TEST(utilitiesTest, packetPartJSONTest) {
    
}

TEST(utilitiesTest, compositionJSONTest) {
    
}