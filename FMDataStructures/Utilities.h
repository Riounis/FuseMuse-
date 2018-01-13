/* 
 * File:   Utilities.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 * Created on January 6, 2018, 10:09 PM
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <exception>
#include <string>

int dot(int duration) {
    if (duration % 2 == 1) {
        throw std::exception("This note has an odd duration and cannot be" +
                "dotted.");
    } else {
        return duration * 1.5;
    }
}

#endif /* UTILITIES_H */

