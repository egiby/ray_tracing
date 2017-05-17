//
// Created by egiby on 15.05.17.
//

#include "../ApiImplementation.h"
#include "Sphere.h"

NSphere::Sphere::Sphere(const NGeometry::Point &center, const double &radius,
                        const NGeometricObjects::Material *material)
        : center(center), radius(radius), material(material)
{
}

double NSphere::Sphere::intersect(const NGeometry::Ray &r) const {
    double coefficient = (r.direction * (center - r.start)) / (r.direction * r.direction);
    NGeometry::Point closest = r.start + r.direction * coefficient;

    if ((closest - center) * (closest - center) > radius * radius)
        return -1;

    if ((closest - center) * (closest - center) == radius * radius)
    {
        return coefficient;
    }

    double d_coef = sqrt(radius * radius - (closest - center) * (closest - center)) / abs(r.direction);

    if (coefficient - d_coef >= 0.)
        return coefficient - d_coef;

    if (coefficient + d_coef < 0.)
        return -1;

    return coefficient + d_coef;
}

const NGeometricObjects::Material *NSphere::Sphere::getMaterial() const {
    return material;
}

NGeometry::Vector NSphere::Sphere::getNormal(const NGeometry::Point &p) const {
    return p - center;
}
