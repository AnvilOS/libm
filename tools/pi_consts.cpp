
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#include "pi_consts.hpp"
#include "pi_25000.hpp"
#include "xint.h"
#include "xint_io.h"

#include <string.h>

void pi_consts()
{
    // Check that there is a decimal point
    const char *p_dec = strchr(pi_25000, '.');
    if (p_dec == NULL)
    {
        return;
    }
    char *end;
    long val = strtol(pi_25000, &end, 10);
    
    xint_t PI;
    xint_init(PI);
    xint_assign_ulong(PI, val);
    xint_from_dec_string(PI, end + 1);

    xint_t TWO;
    xint_init(TWO);
    xint_assign_ulong(TWO, 2);
    while (1)
    {
        if (xint_cmp(PI, TWO) < 0)
        {
            uint32_t r;
            xint_div_1(TWO, &r, TWO, 10);
            break;
        }
        xint_mul_ulong(TWO, TWO, 10);
    }

    xint_lshift(TWO, TWO, 1152);

    xint_t q;
    xint_t r;
    xint_init(q);
    xint_init(r);

    xint_div(q, r, TWO, PI);
    xint_print_raw("2/PI", q);
    
    for (int i=0; i<1152; ++i)
    {
        xint_mul_ulong(q, q, 10);
    }
    xint_rshift(q, q, 1152);
    xint_print("2/PI", q);

    xint_delete(PI);
    xint_delete(TWO);
    xint_delete(q);
    xint_delete(r);
}
