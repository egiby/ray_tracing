//
// Created by egiby on 15.05.17.
//

#include "Geometry.h"

NGeometry::Point NGeometry::Point::operator-() const {
    return {-x, -y, -z};
}

NGeometry::Vector NGeometry::operator+(const NGeometry::Vector &v1, const NGeometry::Vector &v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

NGeometry::Vector NGeometry::operator-(const NGeometry::Vector &v1, const NGeometry::Vector &v2) {
    return v1 + (-v2);
}

NGeometry::Vector NGeometry::operator*(const NGeometry::Vector &v1, const NDouble::Double &c) {
    return {v1.x * c, v1.y * c, v1.z * c};
}

NGeometry::Vector NGeometry::operator*(const NDouble::Double &c, const NGeometry::Vector &v1) {
    return v1 * c;
}

NDouble::Double NGeometry::operator*(const NGeometry::Vector &v1, const NGeometry::Vector &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

NGeometry::Vector NGeometry::operator/(const NGeometry::Vector &v1, const NDouble::Double &c) {
    return v1 * (Double(1) / c);
}

NGeometry::Vector NGeometry::operator^(const NGeometry::Vector &v1, const NGeometry::Vector &v2) {
    return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

NDouble::Double NGeometry::abs(const NGeometry::Vector &p) {
    return sqrt(p * p);
}

bool NGeometry::operator==(const NGeometry::Vector &v1, const NGeometry::Vector &v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

bool NGeometry::operator!=(const NGeometry::Vector &v1, const NGeometry::Vector &v2) {
    return !(v1 == v2);
}

std::ostream &NGeometry::operator<<(std::ostream &out, const NGeometry::Point &p) {
    return out << p.x << ' ' << p.y << ' ' << p.z;
}

std::istream &NGeometry::operator>>(std::istream &in, NGeometry::Point &p) {
    in >> p.x >> p.y >> p.z;
    return in;
}

NGeometry::Ray::Ray(const NGeometry::Point &start, const NGeometry::Vector &direction)
        : start(start), direction(direction) {
}

NGeometry::Plane::Plane(const NGeometry::Vector &normal, const NGeometry::Point &p)
        : a(normal.x), b(normal.y), c(normal.z), d(-(a * p.x + b * p.y + c * p.z)) {
}

NGeometry::Plane::Plane(const NGeometry::Point &p1, const NGeometry::Point &p2, const NGeometry::Point &p3) {
    Vector normal = (p2 - p1) ^(p3 - p1);
    Plane(normal, p3);
}

NDouble::Double NGeometry::Plane::operator()(const NGeometry::Point &p) const {
    return a * p.x + b * p.y + c * p.z + d;
}

NGeometry::Vector NGeometry::Plane::getNormal() const {
    return Vector{a, b, c};
}

NGeometry::Point NGeometry::Plane::intersect(const NGeometry::Line &l) {
    Vector normal = (*this)(l.start) * getNormal() / (getNormal() * getNormal());

    if (normal * l.direction == Double(0.))
        return INFINITY_POINT;

    return l.start - l.direction * (normal * normal) / (normal * l.direction); // it must work
}
