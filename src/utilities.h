/*
 * File:   utilities.h
 * Author: Sam Rappl
 *
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <exception>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "composition.h"

// *************************NOTE***************************
void to_json(nlohmann::json &j, const Note &note) {
    j = nlohmann::json{
        {"pitch", note.pitch},
        {"duration", note.duration},
        {"type", "note"}
    };
    if (note.triplet == 1) { j["triplet"] = 1; }
    if (note.dotted == 1) { j["dotted"] = 1; }
    if (note.double_dotted == 1) { j["double_dotted"] = 1; }
    if (note.staccato == 1) { j["staccato"] = 1; }
    if (note.tenuto == 1) { j["tenuto"] = 1; }
    if (note.accent == 1) { j["accent"] = 1; }
    if (note.fermata == 1) { j["fermata"] = 1; }
    if (note.tied == 1) { j["tied"] = 1; }
    if (note.slurred == 1) { j["slurred"] = 1; }
}

void from_json(const nlohmann::json &j, Note &note) {
    note.pitch = j.at("pitch").get<int>();
    note.duration = j.at("duration").get<int>();
    if (j.find("triplet") != j.end()) { note.triplet = 1; }
    if (j.find("dotted") != j.end()) { note.dotted = 1; }
    if (j.find("double_dotted") != j.end()) { note.double_dotted = 1; }
    if (j.find("staccato") != j.end()) { note.staccato = 1; }
    if (j.find("tenuto") != j.end()) { note.tenuto = 1; }
    if (j.find("accent") != j.end()) { note.accent = 1; }
    if (j.find("fermata") != j.end()) { note.fermata = 1; }
    if (j.find("tied") != j.end()) { note.tied = 1; }
    if (j.find("slurred") != j.end()) { note.slurred = 1; }
}

// *************************CHORD**************************
void to_json(nlohmann::json &j, const Chord &chord) {
    j = nlohmann::json{
        {"pitches", chord.pitches},
        {"duration", chord.duration},
        {"type", "chord"}
    };
    if (chord.triplet == 1) { j["triplet"] = 1; }
    if (chord.dotted == 1) { j["dotted"] = 1; }
    if (chord.double_dotted == 1) { j["double_dotted"] = 1; }
    if (chord.staccato == 1) { j["staccato"] = 1; }
    if (chord.tenuto == 1) { j["tenuto"] = 1; }
    if (chord.accent == 1) { j["accent"] = 1; }
    if (chord.fermata == 1) { j["fermata"] = 1; }
    if (chord.tied == 1) { j["tied"] = 1; }
    if (chord.slurred == 1) { j["slurred"] = 1; }
}

void from_json(const nlohmann::json &j, Chord &chord) {
    chord.pitches = j.at("pitches").get<std::vector<int>>();
    chord.duration = j.at("duration").get<int>();
    if (j.find("triplet") != j.end()) { chord.triplet = 1; }
    if (j.find("dotted") != j.end()) { chord.dotted = 1; }
    if (j.find("double_dotted") != j.end()) { chord.double_dotted = 1; }
    if (j.find("staccato") != j.end()) { chord.staccato = 1; }
    if (j.find("tenuto") != j.end()) { chord.tenuto = 1; }
    if (j.find("accent") != j.end()) { chord.accent = 1; }
    if (j.find("fermata") != j.end()) { chord.fermata = 1; }
    if (j.find("tied") != j.end()) { chord.tied = 1; }
    if (j.find("slurred") != j.end()) { chord.slurred = 1; }
}

// ***********************DYNAMIC*************************
void to_json(nlohmann::json &j, const Dynamic &dynamic) {
    j = nlohmann::json{
        {"volume", dynamic.volume},
        {"type", "dynamic"}
    };
    if (dynamic.cresc == 1) { j["cresc"] = 1; }
    if (dynamic.decresc == 1) { j["decresc"] = 1; }
}

void from_json(const nlohmann::json &j, Dynamic &dynamic) {
    dynamic.volume = j.at("volume").get<int>();
    if (j.find("cresc") != j.end()) { dynamic.cresc = 1; }
    if (j.find("decresc") != j.end()) { dynamic.decresc = 1; }
}

// ************************PART****************************
void to_json(nlohmann::json &j, const Part &part) {
    j = nlohmann::json{
        {"name", part.get_name()},
        {"events", nlohmann::json::array()},
        {"length", part.get_length()}
    };
    std::vector<Event*>::const_iterator it;
    for (it = part.const_begin(); it != part.const_end(); it++) {
        Event *e = *it;
        Note *n = nullptr;
        Chord *c = nullptr;
        Dynamic *d = nullptr;
        if (n = dynamic_cast<Note*>(e)) {
            j["events"].push_back(*n);
        }
        else if (c = dynamic_cast<Chord*>(e)) {
            j["events"].push_back(*c);
        }
        else if (d = dynamic_cast<Dynamic*>(e)) {
            j["events"].push_back(*d);
        }
    }
}

void from_json(const nlohmann::json &j, Part &part) {
    part.set_name(j.at("name").get<std::string>());
    for (int i = 0; i < j["events"].size(); i++) {
        if (j.at("events").at(i).at("type") == "note") {
            Note *n = new Note();
            *n = j.at("events").at(i);
            part.append_note(n);
        }
        else if (j.at("events").at(i).at("type") == "chord") {
            Chord *c = new Chord();
            *c = j.at("events").at(i);
            part.append_chord(c);
        }
        else if (j.at("events").at(i).at("type") == "dynamic") {
            Dynamic *d = new Dynamic();
            *d = j.at("events").at(i);
            part.append_dynamic(d);
        }
    }
}

// ******************PATTERN SEGMENT***********************
void to_json(nlohmann::json &j, const PatternSegment &pattern_segment) {
    j = nlohmann::json{
        {"name", pattern_segment.get_name()},
        {"duration", pattern_segment.get_duration()},
        {"chord_progression", pattern_segment.get_chord_progression()}
    };
}

void from_json(const nlohmann::json &j, PatternSegment &pattern_segment) {
    pattern_segment.set_name(j.at("name").get<std::string>());
    pattern_segment.set_duration(j.at("duration").get<int>());
    Part *p = new Part();
    *p = j.at("chord_progression").get<Part>();
    pattern_segment.set_chord_progression(p);
}

// **************************KEY***************************
void to_json(nlohmann::json &j, const Key &key) {
    j = nlohmann::json{
        {"tonic", key.get_tonic()},
        {"intervals", key.get_intervals()}
    };
}

void from_json(const nlohmann::json &j, Key &key) {
    key.set_tonic(j.at("tonic").get<int>());
    key.set_intervals(j.at("intervals").get<std::vector<int>>());
}

// ********************TIME SIGNATURE**********************
void to_json(nlohmann::json &j, const TimeSignature &time_signature) {
    j = nlohmann::json{
        {"num", time_signature.num},
        {"denom", time_signature.denom}
    };
}

void from_json(const nlohmann::json &j, TimeSignature &time_signature) {
    time_signature.num = j.at("num").get<char>();
    time_signature.denom = j.at("denom").get<char>();
}

// *****************COMPOSITION METRICS********************
void to_json(nlohmann::json &j, const CompositionMetrics &composition_metrics) {
    j = nlohmann::json{
        {"key", composition_metrics.key},
        {"time_signature", composition_metrics.time_signature},
        {"tempo", composition_metrics.tempo},
        {"position", composition_metrics.position}
    };
}

void from_json(const nlohmann::json &j, CompositionMetrics &composition_metrics) {
    composition_metrics.key = j.at("key").get<Key>();
    composition_metrics.time_signature = j.at("time_signature").get<TimeSignature>();
    composition_metrics.tempo = j.at("tempo").get<int>();
    composition_metrics.position = j.at("position").get<int>();
}

// ********************PACKET PART*************************
void to_json(nlohmann::json &j, const PacketPart &packet_part) {
    j = nlohmann::json{
        {"children", std::vector<PacketPart>()},
        {"part", packet_part.get_part()},
        {"packet_path", packet_part.get_packet_path()},
        {"mode", packet_part.get_mode()},
        {"executed", packet_part.has_been_executed()},
        {"is_active", packet_part.is_active()}
    };
    std::vector<PacketPart*> children = packet_part.get_children();
    for (int i = 0; i < children.size(); i++) {
        j["children"].push_back(*children[i]);
    }
}

void from_json(const nlohmann::json &j, PacketPart &packet_part) {
    packet_part.set_part(j.at("part").get<Part>());
    packet_part.set_packet_path(j.at("packet_path").get<std::string>());
    packet_part.set_mode(j.at("mode").get<std::string>());
    packet_part.set_executed(j.at("executed").get<bool>());
    packet_part.set_inactive();
    for (int i = 0; i < j.at("children").size(); i++) {
        PacketPart *p = new PacketPart();
        *p = j.at("children").at(i).get<PacketPart>();
        packet_part.append_child(p);
    }
}

// ********************COMPOSITION*************************
void to_json(nlohmann::json &j, const Composition &comp) {
    j["metrics"] = std::vector<CompositionMetrics>();
    j["parts"] = std::vector<Part>();
    j["pattern_segments"] = std::vector<PatternSegment>();
    j["pattern"] = comp.get_pattern();

    if(comp.get_packet_tree_root()){
        j["packet_tree_root"] = *comp.get_packet_tree_root();
    }
    std::vector<CompositionMetrics*> metrics = comp.get_all_composition_metrics();
    for (int i = 0; i < metrics.size(); i++) {
            j["metrics"].push_back(*metrics[i]);
    }
    std::vector<Part*> parts = comp.get_parts();
    for (int i = 0; i < parts.size(); i++) {
            auto x = *parts[i];
            j["parts"].push_back(x);
    }
    std::vector<PatternSegment*> segments = comp.get_pattern_segments();
    for (int i = 0; i < segments.size(); i++) {
            j["pattern_segments"].push_back(*segments[i]);
    }
}

void from_json(const nlohmann::json &j, Composition &comp) {
    for (int i = 0; i < j["metrics"].size(); i++) {
        CompositionMetrics *mets = new CompositionMetrics();
        *mets = j.at("metrics").at(i).get<CompositionMetrics>();
        comp.add_new_composition_metrics(mets);
    }
    for (int i = 0; i < j["parts"].size(); i++) {
        Part *p = new Part();
        *p = j.at("part").at(i).get<Part>();
        comp.add_part(*p);
    }
    for (int i = 0; i < j["pattern_segments"].size(); i++) {
        PatternSegment *seg = new PatternSegment();
        *seg = j.at("pattern_segments").at(i).get<PatternSegment>();
        comp.register_pattern_segment(seg);
    }
    for (int i = 0; i < j["pattern"].size(); i++) {
        comp.add_to_pattern(j.at("pattern").at(i).get<std::string>());
    }
    PacketPart *pt = new PacketPart();
    try {
        *pt = j.at("packet_tree_root").get<PacketPart>();
    } catch(const std::exception& ex) {
        pt = NULL;
    }
    comp.set_packet_tree_root(pt);
}

// **********************SHELL**************************
typedef std::string (*callback)(std::string zip_path, std::string mode, std::string input);

void run(callback execute, PacketPart *node, nlohmann::json *composition_json,
                std::string cm_path, Composition &comp) {
    if(node) {
        if (node->has_been_executed() == false) {
            nlohmann::json packet_out;
            node->set_active();
            to_json(*composition_json, comp);
            packet_out = nlohmann::json::parse(execute(node->get_packet_path(), node->get_mode(), composition_json->dump()));
            node->set_inactive();
            Part* new_part = new Part();
            from_json(packet_out, *new_part);
            comp.add_part(*new_part);
            node->set_part(*new_part);
            to_json(*composition_json, comp);
            *composition_json = nlohmann::json::parse(execute(cm_path, "control", composition_json->dump()));
            node->execute();
        }
        if (!node->is_leaf()) {
            std::vector<PacketPart*> children = node->get_children();
            for (int i = 0; i < children.size(); i++) {
                run(execute, children[i], composition_json, cm_path, comp);
            }
        }
    }
}

std::string executeShell(callback execute, PacketPart *root_node,
               std::string dm_path, std::string cm_path) {
       // Call the Driver Module and store the JSON it passes back as a composition
       nlohmann::json dm_output = nlohmann::json::parse(execute(dm_path, "driver", ""));
       // Populate the composition with the Packet Hierarchy
       Composition comp;
       from_json(dm_output, comp);
       comp.set_packet_tree_root(root_node);
       // Execute Packets in a Leftmost Depth-First-Search order, passing them the
       // most recent composition JSON
       run(execute, root_node, &dm_output, cm_path, comp);
       std::string final_json = execute(cm_path, "finalcontrol", dm_output.dump());
       execute("", "play", final_json);
       return final_json;
}

#endif /* UTILITIES_H */
