/*
 * File:	simpledriver.cpp
 * Author:	Sam Rappl
 *
 */

#include "simpledriver.hpp"

nlohmann::json execute() {
	Composition comp;
	CompositionMetrics mets;
	Key key(c3, major_intervals);
	TimeSignature timeSig(4, 4);
	mets.key = key;
	mets.timeSignature = timeSig;
	mets.tempo = 80;
	mets.position = 0;
	comp.setInitialCompositionMetrics(&mets);
	PatternSegment seg("song", timeSig.durationOfMeasure()*4);
	Part chordProg;
	Chord one(c_major_chord);
	Chord two(g_major_chord);
	Chord three(a_minor_chord);
	Chord four(f_major_chord);
	chordProg.appendChord(&one);
	chordProg.appendChord(&two);
	chordProg.appendChord(&three);
	chordProg.appendChord(&four);
	seg.setChordProgression(&chordProg);
	comp.registerPatternSegment(&seg);
	comp.addToPattern("song");
	nlohmann::json *j = new nlohmann::json();
	to_json(*j, comp);
	return *j;	
}
 