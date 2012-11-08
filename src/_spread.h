/*BGN::FILE_INFO*/
// This file is part of the spread library.
// Historically this algorithm has started life as a way to measure connectedness in CAPS
// (aka Conservation Assessment and Prioritization System), a software package conceived at
// the University of Massachusetts by Brad Compton, Kevin Mcgarigal and Eduard Ene, and 
// implemented in C++ by Eduard Ene.
// It has then been extracted and converted into a DLL for use from within APL by Eduard Ene
// Ethan Plunkett has adapted the library into an R package, and updated the formula for
// computing resistance loss.
// This package is made available in the hope that it will be useful. Enjoy!
/*END::FILE_INFO*/

#ifndef _PRIVATE_SPREAD_H_
#define _PRIVATE_SPREAD_H_

#ifndef NULL
#define NULL 0
#endif

const double	PI			   = 3.1415;
const int		FOUR_NEIGHBOR  = 4;
const int		EIGHT_NEIGHBOR = 8;

const int N_SHIFT = -1;
const int S_SHIFT =  1;
const int E_SHIFT =  1;
const int W_SHIFT = -1;
const int NOSHIFT =  0;


template<typename T> T sqr(T val){return val * val;};
template<typename T> T min(T val1, T val2){return ((val1 < val2) ? val1: val2);};
template<typename T> T max(T val1, T val2){return ((val1 > val2) ? val1: val2);};

#include <string>
#include <set>
#include <queue>
#endif