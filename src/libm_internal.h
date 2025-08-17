
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#ifndef libm_internal_h
#define libm_internal_h

#include <math.h>

#if defined TESTING
#define sin _Anvil_sin
#define cos _Anvil_cos
#define sqrt _Anvil_sqrt

#endif

int _arg_reduce(double x, double red[2]);
double _sin_reduced(double red[2]);
double _cos_reduced(double red[2]);

#endif /* libm_internal_h */
