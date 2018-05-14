/*
 * File:   part.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef PART_H
#define PART_H

#include <vector>
#include <string>
#include <iostream>
#include "constants.h"
#include "note.h"
#include "chord.h"
#include "dynamics.h"

/**
 * A Part is an object that represents a single line of music played by a single
 * instrument.
 */
class Part {
public:

    /**
     * Constructs a Part object with no name and no music.
     */
    Part(): name(), events(0), length(0) {}

    /**
     * Constructs a Part object with a name and no music.
     *
     * @param name The name of the Part.
     */
    Part(std::string name): name(name), events(0), length(0) {}

    /**
     * Sets the name of the Part to the given name.
     *
     * @param n The new name of the Part.
     */
    void set_name(std::string n) { name = n; }

    /**
     * Returns the name of the Part.
     *
     * @return The name of the Part.
     */
    std::string get_name() const { return name; }

    /**
     * Returns an iterator indexed to the beginning of the list of music notes,
     * chords, and dynamics in this Part. The ++ operator advances this iterator,
     * the -- operator moves this iterator back, and the * operator when used to
     * dereference the iterator gives the contents of the list at the location of
     * the iterator.
     *
     * @return An iterator indexed to the beginning of the list of music notes,
     *         chords, and dynamics in this Part.
     */
    std::vector<Event*>::const_iterator const_begin() const { return events.begin(); }
    std::vector<Event*>::iterator begin() { return events.begin(); }

    /**
     * Returns an iterator indexed to the end of the list of music notes, chords,
     * and dynamics in this Part. The ++ operator advances this iterator,
     * the -- operator moves this iterator back, and the * operator when used to
     * dereference the iterator gives the contents of the list at the location of
     * the iterator.
     *
     * @return An iterator indexed to the end of the list of music notes, chords,
     *         and dynamics in this Part.
     */
    std::vector<Event*>::const_iterator const_end() const { return events.end(); }
    std::vector<Event*>::iterator end() { return events.end(); }

    /**
     * Erases the music note, chord, or dynamic event at the location of the
     * iterator passed in and returns an iterator pointing to the location following
     * the removed music event. If the removed event was the end of the list, it
     * returns the end iterator.
     *
     * @param it An iterator pointing to the music event to be removed from the Part.
     * @return An iterator indexed to the music event after the one which was removed,
     *         or an iterator indexed to the end of the list if the removed event was the
     *         last event.
     */
    std::vector<Event*>::iterator erase(std::vector<Event*>::const_iterator it) {
        Event *e = *it;
        Note *n = nullptr;
        Chord *c = nullptr;
        if (n = dynamic_cast<Note*>(e)) {
            length -= n->duration;
        }
        else if (c = dynamic_cast<Chord*>(e)) {
            length -= c->duration;
        }
        return events.erase(it);
    }

    /**
     * Inserts a Note event at the position in the Part before the given iterator.
     *
     * @param it An iterator pointing to the music event after the Note that is
     *         to be inserted.
     * @param n A pointer to the Note to be inserted at the position before the iterator.
     */
    void insert_note(std::vector<Event*>::const_iterator it, Note *n) {
        events.insert(it, n);
        length += n->duration;
    }

    /**
     * Inserts a Chord event at the position in the Part before the given iterator.
     *
     * @param it An iterator pointing to the music event after the Chord that is
     *         to be inserted.
     * @param n A pointer to the Chord to be inserted at the position before the iterator.
     */
    void insert_chord(std::vector<Event*>::const_iterator it, Chord *c) {
        events.insert(it, c);
        length += c->duration;
    }

    /**
     * Inserts a Dynamic event at the position in the Part before the given iterator.
     *
     * @param it An iterator pointing to the music event after the Dynamic that is
     *         to be inserted.
     * @param n A pointer to the Note to be inserted at the position before the iterator.
     */
    void insert_dynamic(std::vector<Event*>::const_iterator it, Dynamic *d) {
        events.insert(it, d);
    }

    /**
     * Appends a music event (a Note, Chord, or Dynamic object) to the end of the Part.
     *
     * @param e A pointer to the Note, Chord, or Dynamic to be appended to the Part.
     */
    void append(Event *e) {
        Note *n = nullptr;
        Chord *c = nullptr;
        Dynamic *d = nullptr;
        if (n = dynamic_cast<Note*>(e)) {
            append_note(n);
        }
        else if (c = dynamic_cast<Chord*>(e)) {
            append_chord(c);
        }
        else if (d = dynamic_cast<Dynamic*>(e)) {
            append_dynamic(d);
        }
    }

    /**
     * Appends a Note to the end of the Part.
     *
     * @param n A pointer to the Note to be appended to the Part.
     */
    void append_note(Note *n) { events.push_back(n); length += n->duration; }

    /**
     * Appends a Chord to the end of the Part.
     *
     * @param c A pointer to the Chord to be appended to the Part.
     */
    void append_chord(Chord *c) { events.push_back(c); length += c->duration; }

    /**
     * Appends a Dynamic object to the end of the Part.
     *
     * @param d A pointer to the Dynamic to be appended to the Part.
     */
    void append_dynamic(Dynamic *d) { events.push_back(d); }

    /**
     * Returns the length of the Part in FuseMuse duration units.
     * (see libfm/constants.h for help understanding FuseMuse duration units)
     *
     * @return The length of the Part in FuseMuse duration units.
     */
    int get_length() const { return length; }

    /**
     * Returns the number of music events in the Part.
     *
     * @return The number of music events in the Part.
     */
    int get_num_events() const { return events.size(); }

    /**
     * Returns the Dynamic that is applied to the music event pointed to
     * by the iterator passed in.
     *
     * @param it An iterator pointing to the music event to have its Dynamics
     *         retrieved.
     * @return The Dynamics that are used at the position of the music event
     *         pointed to by the iterator.
     */
    Dynamic get_current_dynamics(std::vector<Event*>::const_iterator it) {
        if (events.size() == 0) {
            Dynamic dynamics;
            return dynamics;
        }
        std::vector<Event*>::iterator start = begin();
        while (true) {
            Event *e = *it;
            Dynamic *d = nullptr;
            if (d = dynamic_cast<Dynamic*>(e)) {
                return *d;
            }
            if (it == start) {
                Dynamic dynamics;
                return dynamics;
            }
            it--;
        }
    }

    /**
     * Returns the Dynamic that is applied to the music event at the
     * given position.
     *
     * @param pos The position at which to retrieve Dynamics.
     * @return The Dynamics used at the given position.
     */
    Dynamic get_dynamics_at_position(int pos) {
        return get_current_dynamics(get_iterator_at_position(pos));
    }

    /**
     * Returns the pitches that are played by the music event pointed to
     * by the iterator passed in or at the position of that iterator if the
     * music event pointed to by the iterator is a Dynamics object.
     *
     * @param it An iterator pointing to the music event at the position to
     *         check for pitches being played.
     * @return The pitches that are played at the position of the music event
     *         pointed to by the iterator.
     */
    std::vector<int> get_current_pitches(std::vector<Event*>::iterator it) {
        if (events.size() == 0) {
            std::vector<int> drop;
            return drop;
        }
        bool up = false;
        while (true) {
            Event *e = *it;
            Dynamic *d = nullptr;
            if (d = dynamic_cast<Dynamic*>(e)) {
                if (it == begin() && !list_contains_pitches()) {
                    std::vector<int> drop;
                    return drop;
                }
                else if (it == begin()) {
                    up = true;
                }
                if (up) {
                    it++;
                }
                else {
                    it--;
                }
            }
            else {
                Note *n = nullptr;
                Chord *c = nullptr;
                if (n = dynamic_cast<Note*>(e)) {
                    std::vector<int> ret;
                    ret.push_back(n->pitch);
                    return ret;
                }
                else if (c = dynamic_cast<Chord*>(e)) {
                    return c->pitches;
                }
            }
        }
    }

    /**
     * Returns the pitches that are played at the given position.
     *
     * @param pos The position at which to retrieve pitches.
     * @return The pitches played at the given position.
     */
    std::vector<int> get_pitches_at_position(int pos) {
        return get_current_pitches(get_iterator_at_position(pos));
    }

    /**
     * Returns the FuseMuse position at the beginning of the music event pointed to
     * by the iterator passed in. (see libfm/utilities.h for help understanding
     * FuseMuse duration units)
     *
     * @param it An iterator pointing to the music event of which to get the
     *         starting position.
     * @return The FuseMuse position at which the music event pointed to by the
     *         iterator begins.
     */
    int get_position_of(std::vector<Event*>::iterator it) {
        int pos = 0;
        while (it != begin()) {
            it--;
            Event *e = *it;
            Note *n = nullptr;
            Chord *c = nullptr;
            if (n = dynamic_cast<Note*>(e)) {
                pos += n->duration;
            }
            else if (c = dynamic_cast<Chord*>(e)) {
                pos += c->duration;
            }
        }
        return pos;
    }

    /**
     * Returns the FuseMuse position after the music event pointed to by
     * the iterator passed in. (see libfm/utilities.h for help understanding
     * FuseMuse duration units)
     *
     * @param it An iterator pointing to the music event of which to get the
     *         ending position.
     * @return The FuseMuse position at which the music event pointed to by the
     *         iterator ends.
     */
    int get_position_after(std::vector<Event*>::iterator it) {
        int pos = 0;
        Event *e = *it;
        Note *n = nullptr;
        Chord *c = nullptr;
        if (n = dynamic_cast<Note*>(e)) {
            pos += n->duration;
        }
        else if (c = dynamic_cast<Chord*>(e)) {
            pos += c->duration;
        }
        while (it != begin()) {
            it--;
            Event *e = *it;
            Note *n = nullptr;
            Chord *c = nullptr;
            if (n = dynamic_cast<Note*>(e)) {
                pos += n->duration;
            }
            else if (c = dynamic_cast<Chord*>(e)) {
                pos += c->duration;
            }
        }
        return pos;
    }
    
    /**
     * Return true if this part is the same as the part passed in.
     *
     * @param part The part to compare this to.
     * @return true if the parts are the same.
     */
    bool equals(Part *part) {
        if (name != part->get_name()) {
            return false;
        }
        if (length != part->get_length()) {
            return false;
        }
        if (events.size() != part->get_num_events()) {
            return false;
        }
        else {
            auto itthis = begin();
            auto itthat = part->begin();
            for (int i = 0; i < events.size(); i++) {
                Event *ethis = *itthis;
                Note *nthis = nullptr;
                Chord *cthis = nullptr;
                Dynamic *dthis = nullptr;
                if (nthis = dynamic_cast<Note*>(ethis)) {
                    Event *ethat = *itthat;
                    Note *nthat = nullptr;
                    if (nthat = dynamic_cast<Note*>(ethat)) {
                        if (!nthis->equals(nthat)) {
                            return false;
                        }
                    }
                    else {
                        return false;
                    }
                }
                else if (cthis = dynamic_cast<Chord*>(ethis)) {
                    Event *ethat = *itthat;
                    Chord *cthat = nullptr;
                    if (cthat = dynamic_cast<Chord*>(ethat)) {
                        if (!cthis->equals(cthat)) {
                            return false;
                        }
                    }
                    else {
                        return false;
                    }
                }
                else if (dthis = dynamic_cast<Dynamic*>(ethis)) {
                    Event *ethat = *itthat;
                    Dynamic *dthat = nullptr;
                    if (dthat = dynamic_cast<Dynamic*>(ethat)) {
                        if (!dthis->equals(dthat)) {
                            return false;
                        }
                    }
                    else {
                        return false;
                    }
                }
                itthis++;
                itthat++;
            }
        }
        return true;
    }
    
private:

    /** The name of the Part. */
    std::string name;

    /**
     * The FuseMuse duration of the entire Part. (see libfm/utilities.h for help
     * understanding FuseMuse duration units)
     */
    int length;

    /**
     * An ordered list of the music events (Notes, Chords, and Dynamics) in the Part.
     */
    std::vector<Event*> events;

    /**
     * A private helper method to get an iterator for a music event at a specific
     * FuseMuse position. see libfm/utilities.h for help understanding FuseMuse
     * duration units)
     *
     * @param pos The position at which the music event the iterator will point to
     *         resides.
     * @return An iterator to the music event at the given position.
     */
    std::vector<Event*>::iterator get_iterator_at_position(int pos) {
        if (pos <= 0) {
            return begin();
        }
        else if (pos >= length) {
            std::vector<Event*>::iterator it = begin();
            while (it != end()) { it++; }
            it --;
            return it;
        }
        else {
            std::vector<Event*>::iterator it = begin();
            int temp_pos = 0;
            while (temp_pos < pos) {
                Event *e = *it;
                Note *n = nullptr;
                Chord *c = nullptr;
                if (n = dynamic_cast<Note*>(e)) {
                    temp_pos += n->duration;
                }
                else if (c = dynamic_cast<Chord*>(e)) {
                    temp_pos += c->duration;
                }
                if (temp_pos >= pos) {
                    return it;
                }
                it++;
            }
        }
    }

    /**
     * A private helper method to see if there are any pitches (Notes or Chords) in
     * the Part.
     *
     * @return Whether the Part contains any pitches.
     */
    bool list_contains_pitches() {
        if (length > 0) {
            return true;
        }
        return false;
    }
};

#endif /* PART_H */
