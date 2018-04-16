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
		{"triplet", note.triplet},
		{"dotted", note.dotted},
		{"double_dotted", note.double_dotted},
		{"staccato", note.staccato},
		{"tenuto", note.tenuto},
		{"accent", note.accent},
		{"fermata", note.fermata},
		{"tied", note.tied},
		{"slurred", note.slurred},
		{"type", "note"}
	};
}

void from_json(const nlohmann::json &j, Note &note) {
	note.pitch = j.at("pitch").get<int>();
	note.duration = j.at("duration").get<int>();
	note.triplet = j.at("triplet").get<int>();
	note.dotted = j.at("dotted").get<int>();
	note.double_dotted = j.at("double_dotted").get<int>();
	note.staccato = j.at("staccato").get<int>();
	note.tenuto = j.at("tenuto").get<int>();
	note.accent = j.at("accent").get<int>();
	note.fermata = j.at("fermata").get<int>();
	note.tied = j.at("tied").get<int>();
	note.slurred = j.at("slurred").get<int>();
}

// *************************CHORD**************************
void to_json(nlohmann::json &j, const Chord &chord) {
	j = nlohmann::json{
		{"pitches", chord.pitches},
		{"duration", chord.duration},
		{"triplet", chord.triplet},
		{"dotted", chord.dotted},
		{"double_dotted", chord.double_dotted},
		{"staccato", chord.staccato},
		{"tenuto", chord.tenuto},
		{"accent", chord.accent},
		{"fermata", chord.fermata},
		{"tied", chord.tied},
		{"slurred", chord.slurred},
		{"type", "chord"}
	};
}

void from_json(const nlohmann::json &j, Chord &chord) {
	chord.pitches = j.at("pitches").get<std::vector<int>>();
	chord.duration = j.at("duration").get<int>();
	chord.triplet = j.at("triplet").get<int>();
	chord.dotted = j.at("dotted").get<int>();
	chord.double_dotted = j.at("double_dotted").get<int>();
	chord.staccato = j.at("staccato").get<int>();
	chord.tenuto = j.at("tenuto").get<int>();
	chord.accent = j.at("accent").get<int>();
	chord.fermata = j.at("fermata").get<int>();
	chord.tied = j.at("tied").get<int>();
	chord.slurred = j.at("slurred").get<int>();
}

// ***********************DYNAMICS*************************
void to_json(nlohmann::json &j, const Dynamics &dynamics) {
	j = nlohmann::json{
		{"volume", dynamics.volume},
		{"cresc", dynamics.cresc},
		{"decresc", dynamics.decresc},
		{"type", "dynamics"}
	};
}

void from_json(const nlohmann::json &j, Dynamics &dynamics) {
	dynamics.volume = j.at("volume").get<int>();
	dynamics.cresc = j.at("cresc").get<int>();
	dynamics.decresc = j.at("decresc").get<int>();
}

// ************************PART****************************
void to_json(nlohmann::json &j, const Part &part) {
	j = nlohmann::json{
		{"name", part.getName()},
		{"events", nlohmann::json::array()},
		{"length", part.getLength()}
	};
	std::vector<Event*>::const_iterator it;
	for (it = part.const_begin(); it != part.const_end(); it++) {
		Event *e = *it;
		Note *n = nullptr;
		Chord *c = nullptr;
		Dynamics *d = nullptr;
    if (n = dynamic_cast<Note*>(e)) {
			j["events"].push_back(*n);
		}
		else if (c = dynamic_cast<Chord*>(e)) {
			j["events"].push_back(*c);
		}
		else if (d = dynamic_cast<Dynamics*>(e)) {
			j["events"].push_back(*d);
		}
	}	
}

void from_json(const nlohmann::json &j, Part &part) {
	part.setName(j.at("name").get<std::string>());
	for (int i = 0; i < j["events"].size(); i++) {
		if (j.at("events").at(i).at("type") == "note") {
			Note *n = new Note();
			*n = j.at("events").at(i);
			part.appendNote(n);
		}
		else if (j.at("events").at(i).at("type") == "chord") {
			Chord *c = new Chord();
			*c = j.at("events").at(i);
			part.appendChord(c);
		}
		else if (j.at("events").at(i).at("type") == "dynamics") {
			Dynamics *d = new Dynamics();
			*d = j.at("events").at(i);
			part.appendDynamic(d);
		}
	}
	
}

// ******************PATTERN SEGMENT***********************
void to_json(nlohmann::json &j, const PatternSegment &patternSegment) {
	j = nlohmann::json{
		{"name", patternSegment.getName()},
		{"duration", patternSegment.getDuration()},
		{"chordProgression", patternSegment.getChordProgression()}
	};
}

void from_json(const nlohmann::json &j, PatternSegment &patternSegment) {
	patternSegment.setName(j.at("name").get<std::string>());
	patternSegment.setDuration(j.at("duration").get<int>());
	Part *p = new Part();
	*p = j.at("chordProgression").get<Part>();
	patternSegment.setChordProgression(p);
}

// **************************KEY***************************
void to_json(nlohmann::json &j, const Key &key) {
	j = nlohmann::json{
		{"tonic", key.getTonic()},
		{"intervals", key.getIntervals()}
	};
}

void from_json(const nlohmann::json &j, Key &key) {
	key.setTonic(j.at("tonic").get<int>());
	key.setIntervals(j.at("intervals").get<std::vector<char>>());
}

// ********************TIME SIGNATURE**********************
void to_json(nlohmann::json &j, const TimeSignature &timeSig) {
	j = nlohmann::json{
		{"num", timeSig.num},
		{"denom", timeSig.denom}
	};
}

void from_json(const nlohmann::json &j, TimeSignature &timeSig) {
	timeSig.num = j.at("num").get<char>();
	timeSig.denom = j.at("denom").get<char>();
}

// *****************COMPOSITION METRICS********************
void to_json(nlohmann::json &j, const CompositionMetrics &compositionMetrics) {
	j = nlohmann::json{
		{"key", compositionMetrics.key},
		{"timeSignature", compositionMetrics.timeSignature},
		{"tempo", compositionMetrics.tempo},
		{"position", compositionMetrics.position}
	};
}

void from_json(const nlohmann::json &j, CompositionMetrics &compositionMetrics) {
	compositionMetrics.key = j.at("key").get<Key>();
	compositionMetrics.timeSignature = j.at("timeSignature").get<TimeSignature>();
	compositionMetrics.tempo = j.at("tempo").get<int>();
	compositionMetrics.position = j.at("position").get<int>();
}

// ********************PACKET PART*************************
void to_json(nlohmann::json &j, const PacketPart &packetPart) {
	j = nlohmann::json{
		{"children"},
		{"part", packetPart.getPart()},
		{"packetPath", packetPart.getPacketPath()},
		{"mode", packetPart.getMode()},
		{"executed", packetPart.hasBeenExecuted()}
	};
	std::vector<PacketPart*> children = packetPart.getChildren();
	for (int i = 0; i < children.size(); i++) {
		j["children"].push_back(*children[i]);
	}
}

void from_json(const nlohmann::json &j, PacketPart &packetPart) {
	packetPart.setPart(j.at("part").get<Part>());
	packetPart.setPacketPath(j.at("packetPath").get<std::string>());
	packetPart.setMode(j.at("mode").get<std::string>());
	packetPart.setExecuted(j.at("executed").get<bool>());
	for (int i = 0; i < j.at("children").size(); i++) {
		PacketPart *p = new PacketPart();
		*p = j.at("children").at(i).get<PacketPart>();
		packetPart.appendChild(p);
	}
}

// ********************COMPOSITION*************************
void to_json(nlohmann::json &j, const Composition &comp) {
  j["metrics"] = std::vector<CompositionMetrics>();
	j["parts"] = std::vector<Part>();
	j["patternSegments"] = std::vector<PatternSegment>();
	j["pattern"] = comp.getPattern();
  if(comp.getPacketTreeRoot())
    j["packetTreeRoot"] = *comp.getPacketTreeRoot();
	
	std::vector<CompositionMetrics*> metrics = comp.getAllCompositionMetrics();
	for (int i = 0; i < metrics.size(); i++) {
		j["metrics"].push_back(*metrics[i]);
	}
	std::vector<Part*> parts = comp.getParts();
	for (int i = 0; i < parts.size(); i++) {
		j["parts"].push_back(*parts[i]);
	}
	std::vector<PatternSegment*> segments = comp.getPatternSegments();
	for (int i = 0; i < segments.size(); i++) {
		j["patternSegments"].push_back(*segments[i]);
	}
}

void from_json(const nlohmann::json &j, Composition &comp) {
	for (int i = 0; i < j.at("metrics").size(); i++) {
		CompositionMetrics *mets = new CompositionMetrics();
		*mets = j.at("metrics").at(i).get<CompositionMetrics>();
		comp.addNewCompositionMetrics(mets);
	}
	for (int i = 0; i < j.at("parts").size(); i++) {
		Part *p = new Part();
		*p = j.at("part").at(i).get<Part>();
		comp.addPart(*p);
	}
	for (int i = 0; i < j.at("patternSegments").size(); i++) {
		PatternSegment *seg = new PatternSegment();
		*seg = j.at("patternSegments").at(i).get<PatternSegment>();
		comp.registerPatternSegment(seg);
	}
	for (int i = 0; i < j.at("pattern").size(); i++) {
		comp.addToPattern(j.at("pattern").at(i).get<std::string>());
	}
	PacketPart *pt = new PacketPart();
	*pt = j.at("packetTreeRoot").get<PacketPart>();
	comp.setPacketTreeRoot(pt);
}

// **********************SHELL**************************
typedef std::string (*callback)(std::string zipPath, std::string mode, std::string input);

void run(callback execute, PacketPart *node, nlohmann::json *compositionJSON,
                std::string cmPath) {
        if (node->executed == false) {
                *compositionJSON = execute(node->packetPath, node->mode, *compositionJSON);
                *compositionJSON = execute(cmPath, "control", *compositionJSON);
                node->executed = true;
        }
        if (!node->isLeaf()) {
                std::vector<PacketPart*> children = node->getChildren();
                for (int i = 0; i < children.size(); i++) {
                        run(execute, children[i], compositionJSON, cmPath);
                }
        }
}

std::string executeShell(callback execute, PacketPart *rootNode,
                std::string dmPath, std::string cmPath) {
	// Call the Driver Module and store the JSON it passes back as a composition
        std::string dmout;
        dmout = execute(dmPath, "driver", "");
        // Populate the composition with the Packet Hierarchy
        Composition comp;
		from_json(dmout, comp);
        comp.setPacketTreeRoot(rootNode);
        nlohmann::json packetin; 
		to_json(packetin, comp);
        // Execute Packets in a Leftmost Depth-First-Search order, passing them the
        // most recent composition JSON
        run(execute, rootNode, &packetin, cmPath);
        return execute(cmPath, "finalcontrol", packetin);
}

#endif /* UTILITIES_H */
