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
	bool isRoot() const {
		if (parent == NULL) {
			return true;
		}
		return false;
	}
	bool isLeaf() const {
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
	Part getPart() const { return part; }
	bool setMode(std::string m) {
		if (m == "melody" || m == "harmony" || m == "support") {
			mode = m;
			return true;
		}
		return false;
	}
	std::string getMode() const { return mode; }
	void setPacketPath(std::string path) { packetPath = path; }
	std::string getPacketPath() const { return packetPath; }
	bool hasBeenExecuted() const { return executed; }
	void clearExecution() { executed = false; }
	void setExecuted(bool exe) { executed = exe; }
	void execute() { executed = true; }
	std::vector<PacketPart*> getChildren() const { return children; }
	
	PacketPart *parent;
	std::vector<PacketPart*> children;
	Part part;
	std::string packetPath;
	std::string mode;
	bool executed;
};

#endif /* PACKETPART_H */
