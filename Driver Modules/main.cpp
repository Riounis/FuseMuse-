#include <stdio.h>
#include <nlohmann/json.hpp>
#include "libfm/composition.h"
#include "libfm/utilities.h"

int main() {
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
	Chord one(c_major_chord, whole_note);
	Chord two(g_major_chord, whole_note);
	Chord three(a_minor_chord, whole_note);
	Chord four(f_major_chord, whole_note);
	chordProg.appendChord(&one);
	chordProg.appendChord(&two);
	chordProg.appendChord(&three);
	chordProg.appendChord(&four);
	seg.setChordProgression(&chordProg);
	comp.registerPatternSegment(&seg);
	comp.addToPattern("song");
	nlohmann::json j;
	to_json(j, comp);
	std::cout << j.dump() << std::endl;
}
