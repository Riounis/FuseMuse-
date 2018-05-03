/*
 * File:    composition_metrics.h
 * Author:  Sam Rappl and Jacob Inkrote
 *
 */

#ifndef COMPOSITIONMETRICS_H
#define COMPOSITIONMETRICS_H

#include <string>
#include <vector>
#include "constants.h"

/**
 * A TimeSignature represents the number of beats per measure and which note
 * gets the beat.
 */
struct TimeSignature {

    /**
     * Constructs a TimeSignature with the given number of beats per measure
     * and which note gets the beat. By default, they are 4 beats per measure,
     * and the quarter note gets the beat. Throws an error if the note that gets
     * a beat is not a power of 2 (ex. a 1/3 note).
     *
     * @param num The number of beats per measure.
     * @param denom Which note gets the beat (4 for quarter note, 8 for eighth
     *         note, etc...)
     */
    TimeSignature(int num = 4, int denom = 4) : num(num), denom(denom) {
        if ((denom & (denom - 1)) != 0) {
            throw std::string("Time Signature Denominator must be a power of 2.");
        }
    }

    /**
     * Returns the duration of one measure in FuseMuse position units
     *
     * @return The duration of one measure in FuseMuse position units
     */
    int duration_of_measure() {
        return (whole_note * num) / denom;
    }

    int num;
    int denom;
};

/**
 * A Key represents a scale, or group of pitches, which makes up the pitches used
 * in a song. This Key object contains the key quality (whether it's major or minor),
 * the key signature (number of sharps or flats in conventional western music), but it
 * can also contain arbitrarily constructed scales.
 */
class Key {
public:

    /**
     * Constructs a Key which defaults to C major.
     *
     * @param tonic The tonic note of the scale.
     * @param intervals A vector filled with numbers of half steps between steps in
     *         the scale.
     */
    Key(int tonic = c3, std::vector<int> intervals = major_intervals) :
            tonic(tonic), intervals(intervals) {
        if (tonic >= 102) {
            tonic = tonic % 12 + 36;
        }
        if (!valid_intervals(intervals)) {
            throw std::string("Intervals do not add up to an octave.");
        }
        calculate_scale();
    }

    /**
     * Returns a list of notes in the scale in this Key.
     *
     * @return A vector containing the pitches in this scale.
     */
    std::vector<int> get_scale() const { return scale; }

    /**
     * Returns a list of intervals in between notes in the scale in this Key.
     *
     * @return A vector containing the intervals in this scale.
     */
    std::vector<int> get_intervals() const { return intervals; }

    /**
     * Sets the intervals of this key if they equal 12 half steps, and recalculates
     * the scale of this key based on the new intervals.
     *
     * @param newIntervals The new intervals to be set.
     * @return Whether the new intervals were set.
     */
    bool set_intervals(std::vector<int> new_intervals) {
        if (valid_intervals(new_intervals)) {
            intervals = new_intervals;
            calculate_scale();
        }
        else {
            return false;
        }
    }

    /**
     * Returns the number of sharps or flats in this key signature.
     *
     * @return The number of sharps or flats in this key signature (- for flats,
     *         + for sharps)
     */
    int get_key_signature() const {
        if (intervals != major_intervals && intervals != minor_intervals) {
            return 0;
        }
        else if (intervals == major_intervals) {
            int current_value = 0;
            for (int i = 0; i < 12; i++) {
                if (tonic % 12 == i) {
                    return current_value;
                }
                if (current_value >= 0) {
                    current_value -= 5;
                }
                else {
                    current_value += 7;
                }
            }
        }
        else {
            int current_value = -3;
            for (int i = 0; i < 12; i++) {
                if (tonic % 12 == i) {
                    return current_value;
                }
                if (current_value >= 0) {
                    current_value -= 5;
                }
                else {
                    current_value += 7;
                }
            }
        }
    }

    /**
     * Returns whether the key is major or minor.
     *
     * @return 0 for major, 1 for minor, -1 if the scale is not large enough to determine,
     *      and 2 if the scale is neither major nor minor.
     */
    int get_key_quality() const {
        if (scale.size() < 3) {
            return -1;
        }
        else if (tonic + 4 == scale[2]) {
            return 0;
        }
        else if (tonic + 3 == scale[2]) {
            return 1;
        }
        else {
            return 2;
        }
    }

    /**
     * Returns whether the given pitch is in the scale.
     *
     * @param pitch The pitch to compare to the pitches in the scale.
     * @return Whether the pitch is in the scale.
     */
    bool is_in_scale(int pitch) const {
        int pmod = pitch % 12;
        for (int i = 0; i < scale.size(); i++) {
            if (pmod == scale[i] % 12) {
                return true;
            }
        }
        return false;
    }

    /**
     * Returns whether the pitch given is the tonic, 2nd, 3rd, etc... in the
     * scale.
     *
     * @param pitch The pitch to find the position of in the scale.
     * @return The position of the pitch in the scale. (1 if tonic, 2nd, 3rd, etc.)
     */
    int position_in_scale(int pitch) const {
        int pmod = pitch % 12;
        for (int i = 0; i < scale.size(); i++) {
            if (pmod == scale[i] % 12) {
                return i + 1;
            }
        }
        return -1;
    }

    /**
     * Returns the next pitch up in the scale above the given pitch.
     *
     * @param pitch The pitch to get the pitch above on the scale.
     * @return The next pitch up in the scale.
     */
    int next_pitch_in_scale(int pitch) const {
        int num_octaves = pitch / 12;
        int pmod = pitch % 12;
        int index_of_next = -1;
        for (int i = 0; i < scale.size(); i++) {
            if (pmod == scale[i] % 12) {
                index_of_next = i+1;
            }
        }
        if (index_of_next == -1) {
            for (int i = 0; i < scale.size() - 1; i++) {
                if (pmod > scale[i] % 12 && pmod < scale[i+1] % 12) {
                    index_of_next = i + 1;
                }
            }
        }
        return scale[index_of_next] % 12 + num_octaves * 12;
    }

    /**
     * Returns the nth pitch in the scale.
     *
     * @param n The index of the pitch in the scale (1 is tonic, 2 is 2nd etc)
     * @return The pitch in the scale at the given index, or -1 if there is no
     *         pitch at the given index.
     */
    int get_nth_pitch(int n) const {
        if (n < scale.size() && n >= 0) {
            return scale[n-1];
        }
        else {
            return -1;
        }
    }

    /**
     * Returns the tonic pitch of the scale.
     *
     * @return The tonic pitch of the scale.
     */
    int get_tonic() const { return tonic; }

    /**
     * Sets the tonic of the scale and recalculates the scale.
     *
     * @param new_tonic The new tonic pitch of the scale.
     * @return True if the tonic pitch is between 0 and 101.
     */
    bool set_tonic(int new_tonic) {
        if (new_tonic >= 0 && new_tonic < 102) {
            tonic = new_tonic;
            calculate_scale();
            return true;
        }
    }

    /**
     * Returns a chord using the note given as the root, then adding
     * the note two above it in the scale, and finally the note two above
     * the second note in the chord. (In a major or minor scale, this will
     * be a triad)
     *
     * @param start_position The starting position in the scale (i.e. the 4th)
     * @return A list of integers comprised of the pitches of the chord
     */
    std::vector<int> get_chord(int start_position) {
        std::vector<int> pitches;
        int start_index = start_position % scale.size();
        pitches.push_back(scale[start_index]);
        int mid_index = (start_index + 2) % scale.size();
        if (mid_index < start_index) {
            pitches.push_back(scale[mid_index] + 12);
        }
        else {
            pitches.push_back(scale[mid_index]);
        }
        int top_index = (mid_index + 2) % scale.size();
        if (top_index < mid_index) {
            pitches.push_back(scale[top_index] + 12);
        }
        else {
            pitches.push_back(scale[top_index]);
        }
        return pitches;
    }

    /**
     * Returns whether the key is the same as the key passed in.
     *
     * @param key The key to be tested against this key
     * @return Whether the key is the same as the given key
     */
    bool equals(Key key) const {
        if (key.get_tonic() != tonic) {
            return false;
        }
        else {
            std::vector<int> other_intervals = key.get_intervals();
            for (int i = 0; i < intervals.size(); i++) {
                if (other_intervals[i] != intervals[i]) {
                    return false;
                }
            }
            return true;
        }
    }
private:
    /**
     * Helper method to recalculate the scale. 
     */
    void calculate_scale() {
        scale = new std::vector<int>();
        scale.push_back(tonic);
        int pitch = tonic;
        for (std::vector<int>::size_type i = 0; i < intervals.size(); i++) {
            pitch += intervals[i];
            scale.push_back(pitch);
        }
    }

    /**
     * Helper method to determine whether a set of intervals is valid.
     */
    bool valid_intervals(std::vector<int> test_intervals) {
        int sum = 0;
        for (int i = 0; i < test_intervals.size(); i++) {
            sum += test_intervals[i];
        }
        if (sum != 12) {
            return false;
        }
        return true;
    }

    int tonic;
    std::vector<int> intervals;
    std::vector<int> scale;
};

/**
 * A CompositionMetric is a simple structure to hold key, time signature, and tempo
 * data, as well as a FuseMuse position signifying the CompositionMetrics' position
 * in its respective Composition.
 */
struct CompositionMetrics {
    CompositionMetrics() : key(), time_signature(), tempo(80), position(0) {}
    Key key;
    TimeSignature time_signature;
    unsigned int tempo;
    int position;
};

#endif /* COMPOSITIONMETRICS_H */
