#ifndef MAIN_H
#define MAIN_H

__attribute__ ((aligned(16)))
#include <xmmintrin.h>
#include <smmintrin.h> //SSE4
#include <math.h> //powf
#include "smmath.inl"
#include "smport.inl"

#define _CRT_RAND_S

#include <vector>
#include <atomic>

typedef unsigned int uint;

#define DebugPrintf printf

#endif
