//
// Created by egiby on 15.05.17.
//

#include "PlaneGeometricObject.h"

NGeometry::Vector NPlaneGeometricObject::PlaneGeometricObject::getNormal(const NGeometry::Point &p) const {
    assert(p != NGeometry::INFINITY_POINT);
    return normal();
}

const NGeometricObjects::Material *NPlaneGeometricObject::PlaneGeometricObject::getMaterial() const {
    return material;
}
