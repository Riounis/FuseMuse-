#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <nlohmann/json.hpp>
#include "libfm/composition.h"
#include "libfm/utilities.h"

int main() {
	Composition comp;
	
	// Some notes:
	// Most songs don't switch scales even if they switch keys
	// Most songs don't switch tempos
	// Most songs don't switch time signatures, and if they do,
	// 		it's usually as part of a phrase rather than part of a
	// 		composition segment change.
	// When songs switch keys, they usually go up a half step, a
	// 		whole step, or to the third or fifth of their previous key
	// Usually, either the intro will be a different key and chord
	// 		progression from the rest of the song, and the rest of the
	// 		song won't change, or the intro will be the same as the verse
	// 		and the chorus or bridge may change
	
	// Generate benchmark metrics
	CompositionMetrics mets;
	int ton = rand() % 12;
	ton += 36;
	int scale = rand() % 100;
	if (scale < 50) {
		mets.key = new Key(ton, major_intervals);
	}
	else if (scale < 90) {
		mets.key = new Key(ton, minor_intervals);
	}
	else {
		mets.key = new Key(ton, dorian_intervals);
	}
	int time = rand() % 100;
	if (time < 75) {
		mets.timeSignature = new TimeSignature(4, 4);
	}
	else if (time < 95) {
		mets.timeSignature = new TimeSignature(3, 4);
	}
	else {
		mets.timeSignature = new TimeSignature(6, 8);
	}
	int temp = 60;
	temp += rand() % 180;
	mets.tempo = temp;
	mets.position = 0;
	comp.setInitalCompositionMetrics(&mets);
	
	// Generate generic chord progression
	std::vector<int> chords;
	int prev = 1;
	int curr = rand() % 4 + 3;
	chords.push_back(prev);
	chords.push_back(curr);
	for (int i = 0; i < 2; i++) {
		switch(curr) {
			case 1:
				prev = curr;
				curr = rand() % 4 + 3;
				break;
			case 2:
				prev = curr;
				curr = rand() % 2 + 5;
				break;
			case 3:
				if (prev == 6) {
					prev = curr;
					curr = rand() % 3 + 4;
				}
				else {
					prev = curr;
					if (rand % 5 == 0) {
						curr = 6;
					}
					else {
						curr = 2;
					}
				}
				break;
			case 4:
				if (prev == 1) {
					prev = curr;
					curr = (rand() % 2 + 1) + (rand() % 2 * 4);
				}
				else {
					prev = curr;
					if (rand % 5 == 0) {
						curr = 1;
					}
					else {
						curr = 5;
					}
				}
				break;
			case 5:
				prev = curr;
				curr = 1 + (rand() % 2 * (3 + rand() % 2 * 2);
				break;
			case 6:
				prev = curr;
				curr = rand() % 5 + 1;
				break;
		}
		chords.push_back(curr);
	}
	
	
	// Generate Intro: can be 4 or 8 measures
	/*CompositionMetrics introMets;
	Key introKey;
	TimeSignature introTimeSig;
	int introTempo;*/
	int introLength = (rand() % 2 + 1) * 4;
	PatternSegment intro("intro", introLength * mets.timeSignature.durationOfMeasure());
	Part introPart;
	for (int i = 0; i < introLength / 4; i++) {
		Chord c(mets.key.getSimpleChord(chords[0]), whole_note);
		Chord c1(mets.key.getSimpleChord(chords[1]), whole_note);
		Chord c2(mets.key.getSimpleChord(chords[2]), whole_note);
		Chord c3(mets.key.getSimpleChord(chords[3]), whole_note);
		introPart.appendChord(&c);
		introPart.appendChord(&c1);
		introPart.appendChord(&c2);
		introPart.appendChord(&c3);
	}
	intro.setChordProgression(&introPart);
	
	// Generate Verse: can be 8, 12, 16, or 20 measures
	/*CompositionMetrics verseMets;
	Key verseKey;
	TimeSignature verseTimeSig;
	int verseTempo;*/
	int verseLength = (rand() % 4 + 2) * 4;
	PatternSegment verse("verse", verseLength * mets.timeSignature.durationOfMeasure());
	Part versePart;
	for (int i = 0; i < verseLength / 4; i++) {
		Chord c(mets.key.getSimpleChord(chords[0]), whole_note);
		Chord c1(mets.key.getSimpleChord(chords[1]), whole_note);
		Chord c2(mets.key.getSimpleChord(chords[2]), whole_note);
		Chord c3(mets.key.getSimpleChord(chords[3]), whole_note);
		versePart.appendChord(&c);
		versePart.appendChord(&c1);
		versePart.appendChord(&c2);
		versePart.appendChord(&c3);
	}
	verse.setChordProgression(&versePart);
	
	// Generate Pre-Chorus: can be 4 measures
	/*CompositionMetrics prechorusMets;
	Key prechorusKey;
	TimeSignature prechorusTimeSig;
	int prechorusTempo;*/
	int prechorusLength = 4;
	PatternSegment prechorus("prechorus", prechorusLength * mets.timeSignature.durationOfMeasure());
	Part prechorusPart;
	for (int i = 0; i < prechorusLength / 4; i++) {
		Chord c(mets.key.getSimpleChord(chords[0]), whole_note);
		Chord c1(mets.key.getSimpleChord(chords[1]), whole_note);
		Chord c2(mets.key.getSimpleChord(chords[2]), whole_note);
		Chord c3(mets.key.getSimpleChord(chords[3]), whole_note);
		prechorusPart.appendChord(&c);
		prechorusPart.appendChord(&c1);
		prechorusPart.appendChord(&c2);
		prechorusPart.appendChord(&c3);
	}
	prechorus.setChordProgression(&prechorusPart);
	
	// Generate Chorus: can be 4, 8, or 16 measures
	/*CompositionMetrics chorusMets;
	Key chorusKey;
	TimeSignature chorusTimeSig;
	int chorusTempo;*/
	int chorusLength = pow(2, rand() % 3 + 2);
	PatternSegment chorus("chorus", chorusLength * mets.timeSignature.durationOfMeasure());
	Part chorusPart;
	for (int i = 0; i < chorusLength / 4; i++) {
		Chord c(mets.key.getSimpleChord(chords[0]), whole_note);
		Chord c1(mets.key.getSimpleChord(chords[1]), whole_note);
		Chord c2(mets.key.getSimpleChord(chords[2]), whole_note);
		Chord c3(mets.key.getSimpleChord(chords[3]), whole_note);
		chorusPart.appendChord(&c);
		chorusPart.appendChord(&c1);
		chorusPart.appendChord(&c2);
		chorusPart.appendChord(&c3);
	}
	chorus.setChordProgression(&chorusPart);
	
	// Generate Bridge: can be 8 or 16 measures
	/*CompositionMetrics bridgeMets;
	Key bridgeKey;
	TimeSignature bridgeTimeSig;
	int bridgeTempo;*/
	int bridgeLength = (rand() % 2 + 1) * 8;
	PatternSegment bridge("bridge", bridgeLength * mets.timeSignature.durationOfMeasure());
	Part bridgePart;
	for (int i = 0; i < bridgeLength / 4; i++) {
		Chord c(mets.key.getSimpleChord(chords[0]), whole_note);
		Chord c1(mets.key.getSimpleChord(chords[1]), whole_note);
		Chord c2(mets.key.getSimpleChord(chords[2]), whole_note);
		Chord c3(mets.key.getSimpleChord(chords[3]), whole_note);
		bridgePart.appendChord(&c);
		bridgePart.appendChord(&c1);
		bridgePart.appendChord(&c2);
		bridgePart.appendChord(&c3);
	}
	bridge.setChordProgression(&bridgePart);
	
	// Register pattern segments
	comp.registerPatternSegment(&intro);
	comp.registerPatternSegment(&verse);
	comp.registerPatternSegment(&prechorus);
	comp.registerPatternSegment(&chorus);
	comp.registerPatternSegment(&bridge);
	
	// generate pattern
	if (rand() % 2 == 0) {
		comp.addToPattern("intro");
	}
	int pchorus = rand() % 2;
	int pat = rand() % 5;
	if (pat == 0) {
		comp.addToPattern("verse");
		if (pchorus == 0) {
			comp.addToPattern("prechorus");
		}
		comp.addToPattern("chorus");
		comp.addToPattern("verse");
		if (pchorus == 0) {
			comp.addToPattern("prechorus");
		}
		comp.addToPattern("chorus");
		comp.addToPattern("bridge");
		comp.addToPattern("chorus");
	}
	else if (pat == 1) {
		comp.addToPattern("verse");
		comp.addToPattern("verse");
		comp.addToPattern("bridge");
		comp.addToPattern("verse");
	}
	else if (pat == 2) {
		comp.addToPattern("verse");
		if (pchorus == 0) { 
			comp.addToPattern("prechorus");
		}
		comp.addToPattern("chorus");
		comp.addToPattern("verse");
		if (pchorus == 0) { 
			comp.addToPattern("prechorus");
		}
		comp.addToPattern("chorus");
		comp.addToPattern("verse");
		comp.addToPattern("chorus");
	}
	else if (pat == 3) {
		comp.addToPattern("verse");
		comp.addToPattern("verse");
		if (pchorus == 0) { 
			comp.addToPattern("prechorus");
		}
		comp.addToPattern("chorus");
		comp.addToPattern("verse");
		if (pchorus == 0) { 
			comp.addToPattern("prechorus");
		}
		comp.addToPattern("chorus");
	}
	else {
		comp.addToPattern("verse");
		comp.addToPattern("verse");
		if (pchorus == 0) { 
			comp.addToPattern("prechorus");
		}
		comp.addToPattern("chorus");
		comp.addToPattern("bridge");
		comp.addToPattern("chorus");
	}
	
	nlohmann::json j;
	to_json(j, comp);
	std::cout << j.dump() << std::endl;
}
