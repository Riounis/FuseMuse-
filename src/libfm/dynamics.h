/*
 * File: 	dynamics.h
 * Author: 	Sam Rappl
 *
 */

#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "constants.h"
#include "event.h"

/**
 * A Dynamics object holds the volume at which Notes and Chords after the Dynamics
 * should be played, and it holds data about whether the Notes should be getting louder,
 * softer, or staying constant in volume (crescendo, decrescendo, or dynamically static).
 */
struct Dynamic: public Event {
    
    /**
     * Constructs a Dynamic object with volume mezzo piano.
     */
    Dynamic(): volume(mp), cresc(0), decresc(0), duration(0) {}
    
    /**
     * Constructs a Dynamic object with specified volume. Volume parameter is mandatory,
     * crescendo and decrescendo are optional.
     *
     * @param volume The musical volume level (ex. pp, mf, ff).
     * @param cresc Whether the notes folloing this Dynamics object are in a crescendo.
     * @param decresc Whether the notes following this Dynamics object are in a decrescendo.
     */
    Dynamic(int volume, int cresc = 0, int decresc = 0) :
            volume(volume), cresc(cresc), decresc(decresc), duration(0) {}

    int volume;
    bool cresc;
    bool decresc;
    // Do not use this; only here for Event inheritance
    int duration;
};

#endif /* DYNAMICS_H */
