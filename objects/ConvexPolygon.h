#ifndef _CONVEX_POLYGON
#define _CONVEX_POLYGON

#include "../ApiHeader.h"

#include "PlaneGeometricObject.h"

namespace NConvexPolygon
{
    using NPlaneGeometricObject::PlaneGeometricObject;
    
    using NGeometry::Point;
    using NGeometry::Plane;
    
    class RAYTRACINGAPI ConvexPolygon: public PlaneGeometricObject
    {
    public:
        virtual const Point& operator [] (int n) const = 0;
        virtual size_t size() const = 0;
    };
    
    bool RAYTRACINGAPI isPointInConvexPolygon(const Point &p, const ConvexPolygon &polygon);
    
    double RAYTRACINGAPI intersectConvexPolygon(const NGeometry::Ray &ray, const ConvexPolygon * polygon);
};

#endif
