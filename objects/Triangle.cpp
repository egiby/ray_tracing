//
// Created by egiby on 15.05.17.
//

#include "Triangle.h"

NTriangle::Triangle::Triangle(const NGeometricObjects::Material *_material, const NGeometry::Point &_vertex,
                              const NGeometry::Vector &side_1, const NGeometry::Vector &side_2)
        : normal_vector(side_1 ^ side_2)
{
    assert(NGeometry::abs(normal_vector) != 0.);
    material = _material;

    vertex[0] = _vertex;
    vertex[1] = _vertex + side_1;
    vertex[2] = _vertex + side_2;
}

double NTriangle::Triangle::intersect(const NGeometry::Ray &ray) const {
    //~ cerr << "intersect\n";
    return intersectConvexPolygon(ray, this);
}

const NGeometry::Vector &NTriangle::Triangle::normal() const {
    return normal_vector;
}

size_t NTriangle::Triangle::size() const {
    return 3;
}

const NGeometry::Point &NTriangle::Triangle::operator[](int n) const {
    return vertex[n];
}
