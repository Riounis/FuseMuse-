/* 
 * File:   utilities.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <exception>
#include <string>
#include "composition.h"

// deprecated
/**int dot(int duration) {
    if (duration % 2 == 1) {
        throw std::exception("This note has an odd duration and cannot be" +
                "dotted.");
    } else {
        return duration * 1.5;
    }
}*/

string fmCompToJSON(composition comp) {
	
}

m21 fmCompToM21(composition comp) {
	
}

composition m21ToFmComp(m21 m) {
	
}

#endif /* UTILITIES_H */
