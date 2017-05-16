#ifndef _DOUBLE
#define _DOUBLE

#include <cmath>
#include <iostream>

namespace NDouble
{
    bool isEqual(const double, const double);
    bool less(const double, const double);
    bool greater(const double, const double);

    const double EPS = 1e-9;
};

#endif
