
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#include "cont_frac.hpp"

#include <string.h>
#include <stdlib.h>

bool ContFrac::load_str(const char *str)
{
    xint_t A;
    xint_t B;
    xint_t q;
    xint_t r;

    // Check that there is a decimal point
    const char *p_dec = strchr(str, '.');
    if (p_dec == NULL)
    {
        return false;
    }

    xint_init(A);
    xint_init(B);
    xint_init(q);
    xint_init(r);
    
    char *end;
    long val = strtol(str, &end, 10);
    
    xint_assign_ulong(A, val);
    xint_from_dec_string(A, end + 1);

    xint_assign_ulong(B, 10);
    while (1)
    {
        if (xint_cmp(A, B) < 0)
        {
            uint32_t r;
            xint_div_1(B, &r, B, 10);
            break;
        }
        xint_mul_ulong(B, B, 10);
    }

    coeff.clear();
    while (1)
    {
        xint_div(q, r, A, B);
        //printf("%ld %d\n", cf.size(), q->data[0]);
        coeff.push_back(q->data[0]);
        if (xint_is_zero(r))
        {
            break;
        }
        xint_copy(A, B);
        xint_copy(B, r);
    }

    xint_delete(A);
    xint_delete(B);
    xint_delete(q);
    xint_delete(r);
    
    return true;
}
