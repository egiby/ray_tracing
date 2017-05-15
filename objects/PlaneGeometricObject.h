#ifndef _PLANE_GEOMETRIC_OBJECT
#define _PLANE_GEOMETRIC_OBJECT

#include "GeometricObject.h"

#include <cassert>

namespace NPlaneGeometricObject
{
    class PlaneGeometricObject: public NGeometricObjects::IGeometricObject
    {
    protected:
        const NGeometricObjects::Material * material;
    public:
        virtual const NGeometry::Vector& normal() const = 0;
        
        NGeometry::Vector getNormal(const NGeometry::Point &p) const;
        
        const NGeometricObjects::Material * getMaterial() const;
    };
};

#endif
