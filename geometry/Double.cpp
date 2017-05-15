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

NDouble::Double NDouble::operator+(const NDouble::Double &a, const NDouble::Double &b) {
    return Double(double(a) + double(b));
}

NDouble::Double NDouble::operator-(const NDouble::Double &a, const NDouble::Double &b) {
    return Double(double(a) - double(b));
}

bool NDouble::operator==(const NDouble::Double &a, const NDouble::Double &b) {
    return fabs(a - b) < Double::EPS;
}

bool NDouble::operator<(const NDouble::Double &a, const NDouble::Double &b) {
    return double(a) < double(b) - Double::EPS;
}

bool NDouble::operator>(const NDouble::Double &a, const NDouble::Double &b) {
    return double(a) > double(b) + Double::EPS;
}

bool NDouble::operator>(const NDouble::Double &a, const double &b) {
    return double(a) > double(b) + Double::EPS;
}

bool NDouble::operator>(const double &a, const NDouble::Double &b) {
    return double(a) > double(b) + Double::EPS;
}

std::istream &::NDouble::operator>>(std::istream &in, NDouble::Double &d) {
    double _d;
    in >> _d;
    d = Double(_d);

    return in;
}

std::ostream &::NDouble::operator<<(std::ostream &out, const NDouble::Double &d) {
    out << double(d);
    return out;
}
