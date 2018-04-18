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
	
	
	// Generate Intro: can be 4 or 8 measures
	/*CompositionMetrics introMets;
	Key introKey;
	TimeSignature introTimeSig;
	int introTempo;*/
	int introLength = (rand() % 2 + 1) * 4;
	
	// Generate Verse: can be 8, 12, 16, or 20 measures
	/*CompositionMetrics verseMets;
	Key verseKey;
	TimeSignature verseTimeSig;
	int verseTempo;*/
	int verseLength = (rand() % 4 + 2) * 4;
	
	// Generate Pre-Chorus: can be 4 measures
	/*CompositionMetrics prechorusMets;
	Key prechorusKey;
	TimeSignature prechorusTimeSig;
	int prechorusTempo;*/
	int prechorusLength = 4;
	
	// Generate Chorus: can be 4, 8, or 16 measures
	/*CompositionMetrics chorusMets;
	Key chorusKey;
	TimeSignature chorusTimeSig;
	int chorusTempo;*/
	int chorusLength = pow(2, rand() % 3 + 2);
	
	// Generate Bridge: can be 8 or 16 measures
	/*CompositionMetrics bridgeMets;
	Key bridgeKey;
	TimeSignature bridgeTimeSig;
	int bridgeTempo;*/
	int bridgeLength = (rand() % 2 + 1) * 8;
	
	nlohmann::json j;
	to_json(j, comp);
	std::cout << j.dump() << std::endl;
}
