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
    // Testing booleans
    Note n3(f4, half_note, false, false, false, false, true, false, false, false, false);
    Note n4;
    nlohmann::json k;
    to_json(k, n3);
    from_json(k, n4);
    ASSERT_TRUE(n3.equals(&n4));
}

TEST(utilitesTest, noteJSONTestFail) {
    Note n(g4, dotted_half_note, false, false, false, false, true, false, false, false, false);
    Note n2;
    Note n3(f4, dotted_half_note, false, false, false, false, true, false, false, false, false);
    Note n4(g4, half_note, false, false, false, false, true, false, false, false, false);
    Note n5(g4, dotted_half_note, false, false, false, false, false, false, false, false, false);
    nlohmann::json j;
    to_json(j, n);
    from_json(j, n2);
    ASSERT_TRUE(n.equals(&n2));
    ASSERT_FALSE(n.equals(&n3));
    ASSERT_FALSE(n.equals(&n4));
    ASSERT_FALSE(n.equals(&n5));
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
    PacketPart root;
    PacketPart root2;
    root.set_packet_path("/");
    root.set_mode("melody");
    PacketPart left_child;
    left_child.set_packet_path("/left");
    left_child.set_mode("harmony");
    PacketPart right_child;
    right_child.set_packet_path("/right");
    right_child.set_mode("harmony");
    PacketPart right_grandchild;
    right_grandchild.set_packet_path("/right/center");
    right_grandchild.set_mode("support");
    root.append_child(&left_child);
    root.append_child(&right_child);
    right_child.append_child(&right_grandchild);
    nlohmann::json j;
    printf("before conversion\n");
    to_json(j, root);
    printf("after conversion\n");
    from_json(j, root2);
    printf("after conversion back\n");
    ASSERT_TRUE(root.equals(&root2));
    printf("after assertion\n");
}

TEST(utilitiesTest, compositionJSONTest) {
    Composition comp;
    Composition comp2;
    // PatternSegment
    PatternSegment ps("testps", quarter_note + quarter_note + dotted_quarter_note);
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
    PatternSegment ps2("testps2", quarter_note + half_note + dotted_quarter_note);
    Part p2;
    Dynamic d2(mp);
    Note n3(e3, quarter_note);
    Note n4(a3, half_note);
    Chord c2(c_major_chord, dotted_quarter_note);
    p2.append_dynamic(&d2);
    p2.append_note(&n3);
    p2.append_note(&n4);
    p2.append_chord(&c2);
    ps2.set_chord_progression(&p2);
    PatternSegment ps3("testps3", quarter_note + eighth_note + dotted_quarter_note);
    Part p3;
    Dynamic d_3(mp);
    Note n5(b3, quarter_note);
    Note n6(d3, eighth_note);
    Chord c3(c_major_chord, dotted_quarter_note);
    p3.append_dynamic(&d_3);
    p3.append_note(&n5);
    p3.append_note(&n6);
    p3.append_chord(&c3);
    ps3.set_chord_progression(&p3);
    // PacketPart
    PacketPart root;
    root.set_packet_path("/");
    root.set_mode("melody");
    PacketPart left_child;
    left_child.set_packet_path("/left");
    left_child.set_mode("harmony");
    PacketPart right_child;
    right_child.set_packet_path("/right");
    right_child.set_mode("harmony");
    PacketPart right_grandchild;
    right_grandchild.set_packet_path("/right/center");
    right_grandchild.set_mode("support");
    root.append_child(&left_child);
    root.append_child(&right_child);
    right_child.append_child(&right_grandchild);
    // CompositionMetrics
    Key k0(f3, lydian_intervals);
    TimeSignature t0(6, 8);
    CompositionMetrics c0;
    c0.key = k0;
    c0.time_signature = t0;
    c0.tempo = 77;
    c0.position = 0;
    Key k(e3, minor_intervals);
    TimeSignature t(5, 4);
    CompositionMetrics c1;
    c1.key = k;
    c1.time_signature = t;
    c1.tempo = 79;
    c1.position = 40;
    comp.add_new_composition_metrics(&c0);
    comp.add_new_composition_metrics(&c1);
    comp.set_packet_tree_root(&root);
    comp.register_pattern_segment(&ps);
    comp.register_pattern_segment(&ps2);
    comp.register_pattern_segment(&ps3);
    comp.add_to_pattern("testps3");
    comp.add_to_pattern("testps2");
    comp.add_to_pattern("testps3");
    comp.add_to_pattern("testps");
    nlohmann::json j;
    to_json(j, comp);
    from_json(j, comp2);
    ASSERT_TRUE(comp.equals(&comp2));
}