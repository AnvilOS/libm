
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#include "cont_frac.hpp"

#include <string.h>
#include <stdlib.h>

bool ContFrac::load_coeffs(const std::vector<coeff_type> coeff)
{
    m_coeff = coeff;
    return true;
}

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

    m_coeff.clear();
    while (1)
    {
        xint_div(q, r, A, B);
        //printf("%ld %d\n", cf.size(), q->data[0]);
        m_coeff.push_back(q->data[0]);
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

bool ContFrac::apply_matrix(long int a, long int b, long int c, long int d)
{
    std::vector<coeff_type> output;
    
    int n = 0;
    long tmp;

    while (1)
    {
        // Can we output?
        coeff_type left = c == 0 ? s_inf : a / c;
        coeff_type right = d == 0 ? s_inf : b / d;
        
        if (left == right)
        {
            if (left == s_inf)
            {
                break;
            }
            //printf("Output %lu\n", left);
            output.push_back(left);
            unsigned long q = left;
            
            tmp = c;
            c = a - c * q;
            a = tmp;
            tmp = d;
            d = b - d * q;
            b = tmp;
            continue;
        }
        
        // Grab the next coeff
        coeff_type p = get_coeff(n++);
        
        if (p == s_inf)
        {
            // p is inifinity
            a = b;
            c = d;
        }
        else
        {
            tmp = b;
            b = a + b * p;
            a = tmp;
            tmp = d;
            d = c + d * p;
            c = tmp;
        }
    }
    
    m_coeff = output;
    return true;
}

bool ContFrac::invert()
{
    // Inversion is accomplished by inserting a zero to the front of the coeffs
    m_coeff.insert(m_coeff.begin(), 0);
    return true;
}
