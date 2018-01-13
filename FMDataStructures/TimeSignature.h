/* 
 * File:   TimeSignature.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 * Created on January 6, 2018, 8:57 PM
 */

#ifndef TIMESIGNATURE_H
#define TIMESIGNATURE_H

struct TimeSignature {
    TimeSignature() : num(4), denom(4) {}
    TimeSignature(int num = 4, int denom = 4) : num(num), denom(denom) {}
    char num;
    char denom;
};

#endif /* TIMESIGNATURE_H */

