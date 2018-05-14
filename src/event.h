/*
 * File:    event.h
 * Author:  Sam Rappl
 *
 */

#ifndef EVENT_H
#define EVENT_H

/**
 * An Event or music event is the parent object of Notes, Chords, and Dynamics.
 */
struct Event {
    virtual ~Event(){};
};

#endif /* EVENT_H */
