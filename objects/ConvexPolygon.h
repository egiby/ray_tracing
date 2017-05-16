#ifndef _CONVEX_POLYGON
#define _CONVEX_POLYGON

#include "PlaneGeometricObject.h"

namespace NConvexPolygon
{
    using NPlaneGeometricObject::PlaneGeometricObject;
    
    using NGeometry::Point;
    using NGeometry::Plane;
    
    class ConvexPolygon: public PlaneGeometricObject
    {
    public:
        virtual const Point& operator [] (int n) const = 0;
        virtual size_t size() const = 0;
    };
    
    bool isPointInConvexPolygon(const Point &p, const ConvexPolygon &polygon);
    
    double intersectConvexPolygon(const NGeometry::Ray &ray, const ConvexPolygon * polygon);
};

#endif
