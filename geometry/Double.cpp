#include "Double.h"

////
//// Created by egiby on 15.05.17.
////

bool NDouble::isEqual(const double a, const double b) {
    return fabs(a - b) < NDouble::EPS;
}

bool NDouble::less(const double a, const double b) {
    return a < b - NDouble::EPS;
}

bool NDouble::greater(const double a, const double b) {
    return a > b + NDouble::EPS;
}
