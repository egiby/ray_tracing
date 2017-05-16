//
// Created by egiby on 15.05.17.
//

#include "ConvexPolygon.h"

bool NConvexPolygon::isPointInConvexPolygon(const NGeometry::Point &p, const NConvexPolygon::ConvexPolygon &polygon) {
    double s(0.), s_abs(0.);

    for (ui32 i = 0; i < polygon.size(); ++i)
    {
        ui32 next = (i + 1);
        if (next >= polygon.size())
            next -= polygon.size();

        NGeometry::Vector normal = (polygon[i] - p) ^ (polygon[next] - p);

        double d = abs(normal);
        s_abs += d;

        if (NDouble::greater(normal * polygon.normal(), 0.))
            s += d;
        else
            s -= d;
    }

    return s_abs == s;
}

double NConvexPolygon::intersectConvexPolygon(const NGeometry::Ray &ray, const NConvexPolygon::ConvexPolygon *polygon) {
    Plane plane(polygon->normal(), (*polygon)[0]);

    Point intersection = plane.intersect(ray);

    if (intersection == NGeometry::INFINITY_POINT || NDouble::less((intersection - ray.start) * ray.direction, 0.))
        return -1.;

    if (!isPointInConvexPolygon(intersection, *polygon))
        return -1.;

    return abs(intersection - ray.start) / abs(ray.direction);
}
