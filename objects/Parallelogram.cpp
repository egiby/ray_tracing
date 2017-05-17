//
// Created by egiby on 15.05.17.
//

#include "../ApiImplementation.h"
#include "Parallelogram.h"

NParallelogram::Parallelogram::Parallelogram(const NGeometricObjects::Material *_material,
                                             const NGeometry::Point &_vertex, const NGeometry::Vector &side_1,
                                             const NGeometry::Vector &side_2)
        : normal_vector(side_1 ^ side_2)
{
    material = _material;
    vertex[0] = _vertex;
    vertex[1] = _vertex + side_1;
    vertex[2] = _vertex + side_1 + side_2;
    vertex[3] = _vertex + side_2;
}

double NParallelogram::Parallelogram::intersect(const NGeometry::Ray &ray) const {
    return NConvexPolygon::intersectConvexPolygon(ray, this);
}

const NGeometry::Vector &NParallelogram::Parallelogram::normal() const {
    return normal_vector;
}

size_t NParallelogram::Parallelogram::size() const {
    return 4;
}

const NGeometry::Point &NParallelogram::Parallelogram::operator[](int n) const {
    return vertex[n];
}
