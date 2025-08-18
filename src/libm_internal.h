
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#ifndef libm_internal_h
#define libm_internal_h

#include <math.h>
#include <stdint.h>

union double_bits
{
    double dbl;
    uint64_t uint;
    uint32_t uint32[2];
};

int _arg_reduce(double x, double red[2]);
double _sin_reduced(double red[2]);
double _cos_reduced(double red[2]);

#if defined TESTING
#define sin _Anvil_sin
#define cos _Anvil_cos
#define sqrt _Anvil_sqrt
#endif

#endif /* libm_internal_h */
