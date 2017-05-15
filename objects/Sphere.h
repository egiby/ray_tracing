#ifndef _SPHERE
#define _SPHERE

#include "GeometricObject.h"
#include "../ImageSettings.h"


namespace NSphere
{
    using NDouble::Double;
    using NGeometricObjects::Material;


    class Sphere: public NGeometricObjects::IGeometricObject
    {
        NGeometry::Point center;
        NDouble::Double radius;
        const NGeometricObjects::Material * material;
    public:

        Sphere(const NGeometry::Point &center, const NDouble::Double &radius, const Material * material);

        NDouble::Double intersect(const NGeometry::Ray &r) const;

        const Material * getMaterial() const;

        NGeometry::Vector getNormal(const NGeometry::Point &p) const;
    };
}

#endif
