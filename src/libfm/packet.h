/*
 * File: packet.h
 * Author: Sam Rappl
 *
 */
 
#ifndef PACKET_H
#define PACKET_H

#include "composition.h"
#include "part.h"

class Packet {
public:
	Part executeMelody(Composition c) {};
	Part executeHarmony(Composition c) {};
	Part executeSupport(Composition c) {};
}

#endif /* PACKET_H */
