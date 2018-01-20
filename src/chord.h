/* 
 * File:   chord.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef CHORD_H
#define CHORD_H

#include <vector>

struct Chord {
    Chord(): pitches(0), duration(0), 
            staccato(0), tenuto(0), 
            accent(0), fermata(0), 
            tied(0), slurred(0) {}
    Chord(std::vector<char> pitches, int duration, int staccato = 0, 
            int tenuto = 0, int accent = 0, int fermata = 0, int tied = 0,
            int slurred = 0) : pitches(pitches), duration(duration),
            staccato(staccato), tenuto(tenuto), accent(accent),
            fermata(fermata), tied(tied), slurred(slurred) {}
    std::vector<char> pitches;
    bool dot() { 
        if (duration % 2 == 1) {
            return false;
        } else {
            duration *= 1.5;
        }
    }
    unsigned int duration : 9;
    unsigned int staccato : 1;
    unsigned int tenuto : 1;
    unsigned int accent : 1;
    unsigned int fermata : 1;
    unsigned int tied : 1;
    unsigned int slurred : 1;
};

#endif /* CHORD_H */

