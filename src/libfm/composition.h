/*
 * File:   composition.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <vector>
#include <string>
#include "composition_metrics.h"
#include "part.h"
#include "packetpart.h"

/**
 * A PatternSegment is an object that represents a piece of a song (such as a chorus or
 * a verse).
 */
class PatternSegment {
public:

    /**
     * Constructs a PatternSegment object with no name and no chord progression
     */
    PatternSegment(): name(), duration(), chord_progression(){}

    /**
     * Constructs a PatternSegment with a name and a duration
     *
     * @param name The name of the PatternSegment.
     * @param duration The length of the PatternSegment in FuseMuse duration units.
     */
    PatternSegment(std::string name, int duration) : name(name), duration(duration),
            chord_progression(){}

    /**
     * Returns the chord progression of this PatternSegment.
     *
     * @return The chord progression of this PatternSegment.
     */
    Part get_chord_progression() const { return chord_progression; }

    /**
     * Sets the chord progression of this PatternSegment.
     *
     * @param p A pointer to the chord progression to be set for this PatternSegment.
     */
    void set_chord_progression(Part *p) { chord_progression = *p; }

    /**
     * Returns the name of this PatternSegment.
     *
     * @return The name of this PatternSegment.
     */
    std::string get_name() const { return name; }

    /**
     * Sets the name of this PatternSegment.
     *
     * @param n The new name for this PatternSegment.
     */
    void set_name(std::string n) { name = n; }

    /**
     * Returns the duration of this PatternSegment.
     *
     * @return The duration of this PatternSegment.
     */
    int get_duration() const { return duration; }

    /**
     * Sets the duration of this PatternSegment.
     *
     * @param d The new duration of this PatternSegment.
     */
    void set_duration(int d) { duration = d; }
private:
    std::string name;
    int duration;
    Part chord_progression;
};

class Composition {
public:
    Composition(): metrics(), parts(), pattern(), pattern_segments(), chord_progression(),
        root(NULL){};

    /**
     * Returns the composition metrics being used at the given position in the composition.
     *
     * @param pos The position in the composition from which to retrieve composition metrics.
     * @return The composition metrics used at the position.
     */
    CompositionMetrics* get_composition_metrics_at_position(int pos) const {
        for (int i = metrics.size() - 1; i >= 0; i--) {
            if (pos >= metrics[i]->position) {
                return metrics[i];
            }
        }
        return NULL;
    }

    /**
     * Sets the composition metrics at position 0 to the given composition metrics.
     *
     * @param The composition metrics to use at the start of the composition.
     */
    void set_initial_composition_metrics(CompositionMetrics *mets) {
        if (mets->position != 0) {
            mets->position = 0;
        }
        if (metrics.size() == 0) {
            metrics.push_back(mets);
        }
        else {
            metrics[0] = mets;
        }
    }

    /**
     * Sets the key at position 0 of this composition to the given key.
     *
     * @param initKey The initial key of the composition.
     */
    void set_initial_key(Key init_key) {
        if (metrics.size() == 0) {
            CompositionMetrics *m = new CompositionMetrics();
            m->key = init_key;
            m->position = 0;
            metrics.push_back(m);
        }
        else {
            metrics[0]->key = init_key;
        }
    }

    /**
     * Sets the tempo at position 0 of this composition to the given tempo.
     *
     * @param initTempo The initial tempo of the composition.
     */
    void set_initial_tempo(int init_tempo) {
        if (metrics.size() == 0) {
            CompositionMetrics *m = new CompositionMetrics();
            m->tempo = init_tempo;
            m->position = 0;
            metrics.push_back(m);
        }
        else {
            metrics[0]->tempo = init_tempo;
        }
    }

    /**
     * Sets the time signature at position 0 of this composition to the given
     * time signature.
     *
     * @param initTimeSig The initial time signature of the composition.
     */
    void set_initial_time_signature(TimeSignature init_time_sig) {
        if (metrics.size() == 0) {
            CompositionMetrics *m = new CompositionMetrics();
            m->time_signature = init_time_sig;
            m->position = 0;
            metrics.push_back(m);
        }
        else {
            metrics[0]->time_signature = init_time_sig;
        }
    }

    /**
     * Adds a key change to the given key at the given position in the composition.
     *
     * @param newKey The key that should be changed to at the given position.
     * @param pos The position the key change should occur.
     * @return Whether the key was changed.
     */
    bool add_key_change(Key new_key, int pos) {
        if (metrics.size() == 0) {
            return false;
        }
        int index = composition_metrics_at_position(pos);
        if (index > -1) {
            metrics[index]->key = new_key;
            return true;
        }
        else {
            CompositionMetrics *mets = get_composition_metrics_at_position(pos);
            if (mets->key.equals(new_key)) {
                return false;
            }
            else {
                CompositionMetrics *key_change = new CompositionMetrics();
                key_change->position = pos;
                key_change->key = new_key;
                key_change->tempo = mets->tempo;
                key_change->time_signature = mets->time_signature;
                for (std::vector<CompositionMetrics*>::iterator it = metrics.begin();
                        it != metrics.end(); ++it) {
                    if ((*it)->position > pos) {
                        metrics.insert(it, key_change);
                        return true;
                    }
                }
                metrics.push_back(key_change);
                return true;
            }
        }
    }

    /**
     * Adds a tempo change at the given position in the composition.
     *
     * @param newTempo The tempo that should be changed to at the given position.
     * @param pos The position the tempo change should occur.
     * @return Whether the tempo was changed.
     */
    bool add_tempo_change(int new_tempo, int pos) {
        if (metrics.size() == 0) {
            return false;
        }
        int index = composition_metrics_at_position(pos);
        if (index > -1) {
            metrics[index]->tempo = new_tempo;
        }
        else {
            CompositionMetrics *mets = get_composition_metrics_at_position(pos);
            if (mets->tempo == new_tempo) {
                return false;
            }
            else {
                CompositionMetrics *tempo_change = new CompositionMetrics();
                tempo_change->position = pos;
                tempo_change->tempo = new_tempo;
                tempo_change->key = mets->key;
                tempo_change->time_signature = mets->time_signature;
                for (std::vector<CompositionMetrics*>::iterator it = metrics.begin();
                        it != metrics.end(); ++it) {
                    if ((*it)->position > pos) {
                        metrics.insert(it, tempo_change);
                        return true;
                    }
                }
                metrics.push_back(tempo_change);
                return true;
            }
        }
    }

    /**
     * Adds a time signature change at the given position in the composition.
     *
     * @param newTimeSig The time signature that should be changed to at the given position.
     * @param pos The position the time signature change should occur.
     * @return Whether the time signature was changed.
     */
    bool add_time_signature_change(TimeSignature new_time_sig, int pos) {
        if (metrics.size() == 0) {
            return false;
        }
        int index = composition_metrics_at_position(pos);
        if (index > -1) {
            metrics[index]->time_signature = new_time_sig;
        }
        else {
            CompositionMetrics *mets = get_composition_metrics_at_position(pos);
            if (mets->time_signature.num == new_time_sig.num &&
                    mets->time_signature.denom == new_time_sig.denom) {
                return false;
            }
            else {
                CompositionMetrics *time_sig_change = new CompositionMetrics();
                time_sig_change->position = pos;
                time_sig_change->key = mets->key;
                time_sig_change->tempo = mets->tempo;
                time_sig_change->time_signature = new_time_sig;
                for (std::vector<CompositionMetrics*>::iterator it = metrics.begin();
                        it != metrics.end(); ++it) {
                    if ((*it)->position > pos) {
                        metrics.insert(it, time_sig_change);
                        return true;
                    }
                }
                metrics.push_back(time_sig_change);
                return true;
            }
        }
    }

    /**
     * Adds a new set of composition metrics to the composition at the given position.
     * If the composition has no composition metrics, the new set of composition metrics
     * will instead be inserted at position 0.
     *
     * @param mets A pointer to the composition metrics to be added.
     * @return whether the composition metrics were added.
     */
    bool add_new_composition_metrics(CompositionMetrics *mets) {
        if (metrics.size() == 0) {
            mets->position = 0;
            metrics.push_back(mets);
            return true;
        }
        else {
            std::vector<CompositionMetrics*>::iterator it = metrics.begin();
            while (it != metrics.end()) {
                if ((*it)->position == mets->position) {
                    (*it)->key = mets->key;
                    (*it)->time_signature = mets->time_signature;
                    (*it)->tempo = mets->tempo;
                    return true;
                }
                else if ((*it)->position > mets->position) {
                    it--;
                    if ((*it)->key.equals(mets->key) &&
                            (*it)->time_signature.num == mets->time_signature.num &&
                            (*it)->time_signature.denom == mets->time_signature.denom &&
                            (*it)->tempo == mets->tempo) {
                        return false;
                    }
                    it++;
                    metrics.insert(it, mets);
                    return true;
                }
                it++;
            }
            it--;
            if ((*it)->key.equals(mets->key) &&
                    (*it)->time_signature.num == mets->time_signature.num &&
                    (*it)->time_signature.denom == mets->time_signature.denom &&
                    (*it)->tempo == mets->tempo) {
                return false;
            }
            metrics.push_back(mets);
            return true;
        }
    }

    /**
     * Updates the composition metrics at the given position to have the new key,
     * tempo, and time signature.
     *
     * @param pos The position at which to update composition metrics.
     * @param new_key The new key of the composition metrics at that position.
     * @param new_tempo The new tempo of the composition metrics at that position.
     * @param new_time_sig The new time signature of the composition metrics at that position.
     */
    bool update_composition_metrics_at_position(int pos, Key new_key, int new_tempo,
            TimeSignature new_time_sig) {
        CompositionMetrics *mets = get_composition_metrics_at_position(pos);
        if (mets != NULL) {
            mets->key = new_key;
            mets->tempo = new_tempo;
            mets->time_signature = new_time_sig;
            return true;
        }
        else {
            return false;
        }
    }

    /**
     * Returns all of the composition metrics in this composition.
     *
     * @return a list of composition metrics in this composition.
     */
    std::vector<CompositionMetrics*> get_all_composition_metrics() const {
        return metrics;
    }

    /**
     * Returns the Part with the given name, or null if there is no such Part.
     *
     * @param name The name of the Part to be retrieved.
     * @return The part with the given name.
     */
    Part* get_part(std::string name) const {
        for (int i = 0; i < parts.size(); i++) {
            if (parts[i]->get_name() == name) {
                return parts[i];
            }
        }
        return NULL;
    }

    /**
     * Returns all Parts in this composition.
     *
     * @return all Parts in this composition.
     */
    std::vector<Part*> get_parts() const {
        return parts;
    }

    /**
     * Adds the given Part to the list of Parts if there is not already a Part with
     * the same name.
     *
     * @param p The Part to be added to the list of Parts.
     * @return Whether the Part was added.
     */
    bool add_part(Part& p) {
        for (int i = 0; i < parts.size(); i++) {
            if (parts[i]->get_name() == p.get_name()) {
                return false;
            }
        }
        parts.push_back(&p);
        return true;
    }

    /**
     * Registers the given PatternSegment with this composition so it can be added
     * to the pattern.
     *
     * @param p The PatternSegment to register.
     * @return Whether the PatternSegment was registered.
     */
    bool register_pattern_segment(PatternSegment *p) {
        for (int i = 0; i < pattern_segments.size(); i++) {
            if (pattern_segments[i]->get_name() == p->get_name()) {
                return false;
            }
        }
        pattern_segments.push_back(p);
        return true;
    }

    /**
     * Changes the PatternSegment with the name of the PatternSegment passed in
     * to the PatternSegment passed in.
     *
     * @param p The new PatternSegment.
     * @return Whether the PatternSegment with the same name as the one passed in
     *      was updated to be the PatternSegment passed in.
     */
    bool edit_pattern_segment(PatternSegment *p) {
        for (int i = 0; i < pattern_segments.size(); i++) {
            if (pattern_segments[i]->get_name() == p->get_name()) {
                pattern_segments[i] = p;
                return true;
            }
        }
        return false;
    }

    /**
     * Returns the PatternSegment with the given name.
     *
     * @param name The name of the PatternSegment to return.
     * @return The PatternSegment with the given name.
     */
    PatternSegment* get_pattern_segment(std::string name) const {
        for (int i = 0; i < pattern_segments.size(); i++) {
            if (pattern_segments[i]->get_name() == name) {
                return pattern_segments[i];
            }
        }
        return NULL;
    }

    /**
     * Adds the given name to the pattern if there is a PatternSegment registered with
     * the same name.
     *
     * @param name The name of the PatternSegment to add to the Pattern.
     * @return Whether there is a PatternSegment with the given name.
     */
    bool add_to_pattern(std::string name) {
        if (get_pattern_segment(name) != NULL) {
            pattern.push_back(name);
            return true;
        }
        return false;
    }

    /**
     * Returns the pattern of this composition.
     *
     * @return the pattern of this composition.
     */
    std::vector<std::string> get_pattern() const { return pattern; }

    
    /**
     * Returns all of the PatternSegments in this composition.
     *
     * @return all of the PatternSegments in this composition.
     */
    std::vector<PatternSegment*> get_pattern_segments() const { return pattern_segments; }

    /**
     * Resets the pattern of this composition.
     */
    void reset_pattern() {
        pattern.clear();
    }

    /**
     * Returns the chord progression of this composition.
     *
     * @return the chord progression of this composition.
     */
    Part get_chord_progression() const { return chord_progression; }

    /**
     * Returns the root of the Packet tree.
     *
     * @return the root of the Packet tree.
     */
    PacketPart* get_packet_tree_root() const { return root; }

    /**
     * Sets the root of the Packet tree.
     *
     * @param r The root of the Packet tree.
     */
    void set_packet_tree_root(PacketPart *r) { root = r; }

private:
    /**
     * Returns the index of the composition metrics at a given position.
     *
     * @param pos The position at which to retrieve composition metrics.
     * @return The index of the composition metrics in the list.
     */
    int composition_metrics_at_position(int pos) {
        for (int i = 0; i < metrics.size(); i++) {
            if (metrics[i]->position == pos) {
                return i;
            }
        }
        return -1;
    }
    std::vector<CompositionMetrics*> metrics;
    std::vector<Part*> parts;
    std::vector<PatternSegment*> pattern_segments;
    std::vector<std::string> pattern;
    Part chord_progression;
    PacketPart *root;
};


#endif /* COMPOSITION_H */

