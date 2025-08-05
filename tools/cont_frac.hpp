
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#ifndef cont_frac_hpp
#define cont_frac_hpp

#include "xint.h"
#include "xint_io.h"

#include <vector>

class ContFrac
{
public:
    typedef __uint128_t coeff_type;
    static const coeff_type s_inf = (coeff_type)-1;
    
    bool load_str(const char *str);
    bool load_coeffs(const std::vector<coeff_type> coeffs);
    coeff_type get_coeff(size_t ndx) { return ndx < m_coeff.size() ? m_coeff[ndx] : s_inf; }
    bool apply_matrix(long int a, long int b, long int c, long int d);
    bool invert();
    size_t size() { return m_coeff.size(); }
        
private:
    std::vector<coeff_type> m_coeff;
};

#include <stdio.h>

#endif /* cont_frac_hpp */
