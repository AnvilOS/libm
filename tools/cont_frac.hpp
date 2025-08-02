
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
    bool load_str(const char *str);
    unsigned long get_coeff(int ndx) { return ndx < coeff.size() ? coeff[ndx] : (unsigned long)-1; }
    
    
private:
    std::vector<unsigned long> coeff;
};

#include <stdio.h>

#endif /* cont_frac_hpp */
