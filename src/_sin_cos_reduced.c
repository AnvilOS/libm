
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#include <stdint.h>
#include <stdio.h>

#include "libm_internal.h"

// We need 1144 bits (from Ng). We have 1152
uint32_t two_on_pi[] =
{
    0xa2f9836e, 0x4e441529, 0xfc2757d1, 0xf534ddc0, 0xdb629599, 0x3c439041,
    0xfe5163ab, 0xdebbc561, 0xb7246e3a, 0x424dd2e0, 0x06492eea, 0x09d1921c,
    0xfe1deb1c, 0xb129a73e, 0xe88235f5, 0x2ebb4484, 0xe99c7026, 0xb45f7e41,
    0x3991d639, 0x835339f4, 0x9c845f8b, 0xbdf9283b, 0x1ff897ff, 0xde05980f,
    0xef2f118b, 0x5a0a6d1f, 0x6d367ecf, 0x27cb09b7, 0x4f463f66, 0x9e5fea2d,
    0x7527bac7, 0xebe5f17b, 0x3d0739f7, 0x8a5292ea, 0x6bfb5fb1, 0x1f8d5d08
};

#define split_double(__dd, __sign, __f, __e)    \
{                                               \
    union double_bits value;                    \
    value.dbl = __dd;                           \
    __sign = value.uint >> 63;                  \
    __e = ((value.uint >> 52) & 0x7ff) - 1023;  \
    __f = value.uint & 0xfffffffffffff;         \
    if (__e == -1023)                           \
    {                                           \
        ++__e;                                  \
    }                                           \
    else                                        \
    {                                           \
        __f |= 0x10000000000000;                \
    }                                           \
}

int _arg_reduce(double x, double red[2])
{
    uint64_t N;
    int M;
    int sign;
    split_double(x, sign, N, M);
    M -= 52;
    while ((N & 1) == 0)
    {
        N >>= 1;
        ++M;
    }
    // Now we have x = N * 2 ^ M
    printf("N=%llu M=%d\n", N, M); // N=2384185791015625   M=22
    
    

    
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
