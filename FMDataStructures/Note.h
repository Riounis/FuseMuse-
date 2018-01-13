/* 
 * File:   Note.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 * Created on January 5, 2018, 5:05 PM
 */

#ifndef NOTE_H
#define NOTE_H

struct Note {
    Note(): pitch(0), duration(0), 
            staccato(0), tenuto(0), 
            accent(0), fermata(0), 
            tied(0), slurred(0) {}
    Note(int pitch, int duration, int staccato = 0, int tenuto = 0,
            int accent = 0, int fermata = 0, int tied = 0, int slurred = 0) :
            pitch(pitch), duration(duration), staccato(staccato), 
            tenuto(tenuto), accent(accent), fermata(fermata), tied(tied),
            slurred(slurred) {}
    bool dot() { 
        if (duration % 2 == 1) {
            return false;
        } else {
            duration *= 1.5;
        }
    }
    unsigned int pitch : 7;
    unsigned int duration : 9;
    unsigned int staccato : 1;
    unsigned int tenuto : 1;
    unsigned int accent : 1;
    unsigned int fermata : 1;
    unsigned int tied : 1;
    unsigned int slurred : 1;
};


#endif /* NOTE_H */

