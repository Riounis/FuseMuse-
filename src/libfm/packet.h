/*
 * File: packet.h
 * Author: Sam Rappl
 *
 */
 
#ifndef PACKET_H
#define PACKET_H

#include <vector>
#include "composition.h"
#include "part.h"

class Packet {
public:
	std::vector<Part*> executeMelody(Composition c) {};
	std::vector<Part*> executeHarmony(Composition c) {};
	std::vector<Part*> executeSupport(Composition c) {};
}

#endif /* PACKET_H */
