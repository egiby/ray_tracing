//
// Created by egiby on 15.05.17.
//

#include "Double.h"

NDouble::Double::Double(const double &value)
        : value(value) {
}

NDouble::Double::Double()
        : value(0.) {
}

NDouble::Double NDouble::Double::operator-() const {
    return Double(-value);
}

NDouble::Double &NDouble::Double::operator+=(const NDouble::Double &d) {
    value += d.value;
    return *this;
}

NDouble::Double &NDouble::Double::operator-=(const NDouble::Double &d) {
    value -= d.value;
    return *this;
}

NDouble::Double::operator double() const {
    return value;
}

const double NDouble::Double::EPS = 1e-9;