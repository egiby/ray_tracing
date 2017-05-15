#ifndef _TRIANGLE
#define _TRIANGLE

#include "ConvexPolygon.h"

namespace NTriangle
{
    using NGeometry::Point;
    using NGeometry::Vector;
    using NGeometricObjects::Material;
    
    class Triangle: public NConvexPolygon::ConvexPolygon
    {
        Vector normal_vector;
        Point vertex[3];
    public:
        Triangle(const Material * _material, const Point &_vertex, const Vector &side_1, const Vector &side_2);

        double intersect(const NGeometry::Ray &ray) const;
        
        virtual const NGeometry::Vector& normal() const;
        
        virtual size_t size() const;
        
        virtual const Point& operator [] (int n) const;
    };
};

#endif
