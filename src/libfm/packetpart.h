/* 
 * File:   packetpart.h
 * Author: Sam Rappl
 *
 */
 
#ifndef PACKETPART_H
#define PACKETPART_H

#include <vector>
#include <string>
#include "part.h"

class PacketPart {
public:
	PacketPart() : parent(NULL), children(), part(), packetPath(), mode(), executed(false){}
	bool isRoot() {
		if (parent == NULL) {
			return true;
		}
		return false;
	}
	bool isLeaf() {
		if (children.size() > 0) {
			return false;
		}
		return true;
	}
	void setParent(PacketPart *p) {
		parent = p;
	}
	void appendChild(PacketPart *child) {
		child->setParent(this);
		children.push_back(child);
	}
	void popBackChild() {
		children.pop_back();
	}
	void removeChild(int pos) {   
		if(children.size() > 0) {
			children.erase(children.begin()+ pos);
		}
		else {
			children.pop_back();
		}
	}
	void setPart(Part p) {
		part = p;
	}
	bool setMode(std::string m) {
		if (m == "melody" || m == "harmony" || m == "support") {
			mode = m;
			return true;
		}
		return false;
	}
	std::vector<PacketPart*> getChildren() { return children; }
  
	PacketPart *parent;
	std::vector<PacketPart*> children;
	Part part;
	std::string packetPath;
	std::string mode;
	bool executed;
};

#endif /* PACKETPART_H */
