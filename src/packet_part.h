/* 
 * File:    packetpart.h
 * Author:  Sam Rappl
 *
 */

#ifndef PACKETPART_H
#define PACKETPART_H

#include <vector>
#include <string>
#include "part.h"

/**
 * A PacketPart is a wrapper for a Packet that contains the path of the Packet,
 * the part it generated, and whether it has executed yet or is currently being
 * executed. It is also a tree node.
 */
class PacketPart {
public:

    /**
     * Constructs an empty PacketPart.
     */
    PacketPart() : parent(NULL), children(), part(), packet_path(), mode(),
            executed(false), active(false){}
    
    /**
     * Returns true if this PacketPart is the root of the Packet tree.
     *
     * @return true if this PacketPart is the root of the Packet tree.
     */
    bool is_root() const {
        if (parent == NULL) {
            return true;
        }
        return false;
    }
    
    /**
     * Returns true if this PacketPart is a leaf of the tree.
     *
     * @return true if this PacketPart has no children.
     */
    bool is_leaf() const {
        if (children.size() > 0) {
            return false;
        }
        return true;
    }
    
    /**
     * Sets the parent of this PacketPart.
     *
     * @param p The parent of this PacketPart.
     */
    void set_parent(PacketPart *p) {
        parent = p;
    }
    
    /**
     * Appends a child to this PacketPart's list of children.
     *
     * @param child The child to be appended.
     */
    void append_child(PacketPart *child) {
        child->set_parent(this);
        children.push_back(child);
    }
    
    /**
     * Pops the last child off this Packet's list of children.
     */
    void pop_back_child() {
        children.pop_back();
    }
    
    /**
     * Removes this PacketPart's child at the specified position.
     *
     * @param pos The position of the child to be removed.
     */
    void remove_child(int pos) {
        if(children.size() > 0) {
            children.erase(children.begin()+ pos);
        }
        else {
            children.pop_back();
        }
    }
    
    /**
     * Sets the Part produced by this PacketPart.
     *
     * @param p The Part produced by this PacketPart.
     */
    void set_part(Part p) {
        part = p;
    }
    
    /**
     * Returns the Part produced by this PacketPart.
     *
     * @return the Part produced by this PacketPart.
     */
    Part get_part() const { return part; }
    
    /**
     * Sets the mode of this PacketPart.
     *
     * @param m The mode of this PacketPart.
     * @return Whether the new mode was valid.
     */
    bool set_mode(std::string m) {
        if (m == "melody" || m == "harmony" || m == "support") {
            mode = m;
            return true;
        }
        return false;
    }
    
    /**
     * Returns the mode of this PacketPart.
     *
     * @return The mode of this PacketPart.
     */
    std::string get_mode() const { return mode; }
    
    /**
     * Sets the file path of this PacketPart.
     *
     * @param path The file path of this PacketPart.
     */
    void set_packet_path(std::string path) { packet_path = path; }
    
    /**
     * Returns the file path of this PacketPart.
     *
     * @return the file path of this PacketPart.
     */
    std::string get_packet_path() const { return packet_path; }
    
    /**
     * Returns true if this PacketPart has been executed.
     *
     * @return true if this PacketPart has been executed.
     */
    bool has_been_executed() const { return executed; }
    
    /**
     * Resets the execution status of this PacketPart.
     */
    void clear_execution() { executed = false; }
    
    /**
     * Sets the execution status of this PacketPart.
     *
     * @param exe The new execution status of this PacketPart.
     */
    void set_executed(bool exe) { executed = exe; }
    
    /**
     * Executes this PacketPart. Does not execute the Packet wrapped by
     * this PacketPart. That is done separately.
     */
    void execute() { executed = true; }
    
    /**
     * Returns the children of this PacketPart.
     *
     * @return the children of this PacketPart.
     */
    std::vector<PacketPart*> get_children() const { return children; }
    
    /**
     * Sets this PacketPart as the active PacketPart.
     */
    void set_active() { active = true; }
    
    /**
     * Sets this PacketPart as inactive.
     */
    void set_inactive() { active = false; }
    
    /**
     * Returns true if this PacketPart is active.
     *
     * @return true if this PacketPart is active.
     */
    bool is_active() const { return active; }
    
    /**
     * Returns the parent of this packet part.
     *
     * @return this packet part's parent.
     */
    PacketPart* get_parent() { return parent; }
    
    /**
     * Returns true if the packet part given is the same as this packet part.
     * This method takes a lot of time to run. It is used for testing. Please
     * do not use it in applications.
     *
     * @param packet_part The packet part to compare to this.
     * @return true if the parts are the same.
     */
    bool equals(PacketPart *packet_part) {
        if (!parent->equals(packet_part->get_parent())) {
            return false;
        }
        if (children.size() != packet_part->get_children().size()) {
            return false;
        }
        else {
            std::vector<PacketPart*> comp_children = packet_part->get_children();
            for (int i = 0; i < children.size(); i++) {
                if (!children[i]->equals(comp_children[i])) {
                    return false;
                }
            }
        }
        Part temp_part = packet_part->get_part();
        if (!part.equals(&temp_part)) {
            return false;
        }
        if (packet_path != packet_part->get_packet_path()) {
            return false;
        }
        if (mode != packet_part->get_mode()) {
            return false;
        }
        return true;
    }
    
private:
    PacketPart *parent;
    std::vector<PacketPart*> children;
    Part part;
    std::string packet_path;
    std::string mode;
    bool executed;
    bool active;
};

#endif /* PACKETPART_H */
