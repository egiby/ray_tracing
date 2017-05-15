#ifndef _SPHERE
#define _SPHERE

#include "GeometricObject.h"
#include "../ImageSettings.h"


namespace NSphere
{
    using NGeometricObjects::Material;


    class Sphere: public NGeometricObjects::IGeometricObject
    {
        NGeometry::Point center;
        double radius;
        const NGeometricObjects::Material * material;
    public:

        Sphere(const NGeometry::Point &center, const double &radius, const Material * material);

        double intersect(const NGeometry::Ray &r) const;

        const Material * getMaterial() const;

        NGeometry::Vector getNormal(const NGeometry::Point &p) const;
    };
}

#endif
