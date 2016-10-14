#ifndef _PLANE_GEOMETRIC_OBJECT
#define _PLANE_GEOMETRIC_OBJECT

#include "GeometricObject.hpp"

#include <cassert>

namespace NPlaneGeometricObject
{
    class PlaneGeometricObject: public NGeometricObjects::IGeometricObject
    {
    protected:
        const NGeometricObjects::Material * material;
    public:
        virtual const NGeometry::Vector& normal() const = 0;
        
        NGeometry::Vector getNormal(const NGeometry::Point &p) const
        {
            assert(p != NGeometry::INFINITY_POINT);
            return normal();
        }
        
        const NGeometricObjects::Material * getMaterial() const
        {
            return material;
        }
    };
};

#endif
