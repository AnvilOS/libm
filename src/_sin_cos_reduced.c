
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#include <stdint.h>
#include <stdio.h>

#include "libm_internal.h"

int _arg_reduce(double x, double red[2])
{
    red[0] = x;
    red[1] = 0.0;
    
    return 0;
}

double _sin_reduced(double red[2])
{
    // From ./lolremez --degree 13 --range "-pi/4:pi/4" "sin(x)"
    // The even terms were all < 10^-100 so were discarded
    double x = red[0] * red[0];
    double u = 1.588306354239276e-10;
    u = u * x + -2.5050482945653454e-08;
    u = u * x + 2.7557311571799106e-06;
    u = u * x + -0.00019841269821970861;
    u = u * x + 0.0083333333333083445;
    u = u * x + -0.16666666666666524;
    u = u * x + 1;
    return u * red[0];
}

double _cos_reduced(double red[2])
{
    // From ./lolremez --degree 14 --range "-pi/4:pi/4" "cos(x)"
    // The odd terms were all < 10^-100 so were discarded
    double x = red[0] * red[0];
    double u = -1.1353387007201706e-11;
    u = u * x + 2.0875582539758573e-09;
    u = u * x + -2.7557313099139494e-07;
    u = u * x + 2.4801587283886827e-05;
    u = u * x + -0.0013888888888861108;
    u = u * x + 0.041666666666666449;
    u = u * x + -0.5;
    return u * x + 1;
}
