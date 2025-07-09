
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#include <math.h>

double _Anvil_sqrt(double x)
{
    // XXX: Need to handle nan, inf, neg and zero
    
    // XXX: Only accurate to +/- the lowest bit

    // From Cody and Waite
    double yi = 0.41731 + 0.59016 * x;
    for (int i=0; i<3; ++i)
    {
        yi = 0.5 * (yi + x / yi);
    }
    return yi;
}
