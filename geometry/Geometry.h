#ifndef _GEOMETRY
#define _GEOMETRY

#include "Double.h"

#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cassert>

#include <iostream>

using std::cerr;

typedef uint32_t ui32;

namespace NGeometry {
    struct Point {
        double x, y, z;

        Point operator-() const;
    };

    const Point INFINITY_POINT = {1e20, 1e20, 1e20};

    typedef Point Vector;

    Vector operator+(const Vector &v1, const Vector &v2);

    Vector operator-(const Vector &v1, const Vector &v2);

    Vector operator*(const Vector &v1, const double &c);

    Vector operator*(const double &c, const Vector &v1);

    double operator*(const Vector &v1, const Vector &v2);

    Vector operator/(const Vector &v1, const double &c);

    Vector operator^(const Vector &v1, const Vector &v2);

    double abs(const Vector &p);

    bool operator==(const Vector &v1, const Vector &v2);

    bool operator!=(const Vector &v1, const Vector &v2);

    std::ostream &operator<<(std::ostream &out, const Point &p);

    std::istream &operator>>(std::istream &in, Point &p);

    struct Ray {
        Point start;
        Vector direction;

        Ray(const Point &start, const Vector &direction);
    };

    typedef Ray Line;

    struct Plane {
        double a, b, c, d;

        Plane(const Vector &normal, const Point &p);

        Plane(const Point &p1, const Point &p2, const Point &p3);

        double operator()(const Point &p) const;

        Vector getNormal() const;

        Point intersect(const Line &l);
    };
};

#endif
