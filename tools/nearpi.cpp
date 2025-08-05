
//
// Copyright (c) 2025 Gerard Green
// All rights reserved
//
// Please see the file 'LICENSE' for further information
//

#include "nearpi.hpp"
#include "cont_frac.hpp"
#include "pi_25000.hpp"

void nearpi(int d)
{
    ContFrac cf;
    cf.load_str(pi_25000);

    for (int i=0; i<d-3; ++i)
    {
        cf.apply_matrix(0, 2, 1, 0);
    }
    cf.invert();
}
