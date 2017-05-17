#ifndef _DOUBLE
#define _DOUBLE

#include <cmath>
#include <iostream>

#include "../ApiHeader.h"

namespace NDouble
{
    bool RAYTRACINGAPI isEqual(const double, const double);
    bool RAYTRACINGAPI less(const double, const double);
    bool RAYTRACINGAPI greater(const double, const double);

    const double EPS = 1e-9;
};

#endif
