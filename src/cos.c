
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#include "libm_internal.h"

double cos(double x)
{
    double x_red[2];
    int n = _arg_reduce(x, x_red);
    switch (n)
    {
        // As per table 2 in Ng's Arg reduction
        case 0: return _cos_reduced(x_red); break;
        case 1: return -_sin_reduced(x_red); break;
        case 2: return -_cos_reduced(x_red); break;
        case 3: return _sin_reduced(x_red); break;
        default: break;
    }
    return 0.0;
}
