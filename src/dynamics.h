/*
 * File: dynamics.h
 * Author: Sam Rappl
 *
 */
 
#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "constants.h"
#include "event.h"

struct Dynamics: public Event {
	Dynamics(): volume(3), cresc(0), decresc(0) {}
	Dynamics(int volume, int cresc = 0, int decresc = 0) : 
			volume(volume), cresc(cresc), decresc(decresc) {}
	unsigned int volume : 3;
	unsigned int cresc : 1;
	unsigned int decresc : 1;
};

#endif /* DYNAMICS_H */

