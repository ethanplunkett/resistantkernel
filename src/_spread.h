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
