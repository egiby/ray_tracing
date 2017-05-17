#ifndef _PARALLELOGRAM
#define _PARALLELOGRAM

#include "ConvexPolygon.h"

#include "../ApiHeader.h"

namespace NParallelogram
{
    using NGeometry::Point;
    using NGeometry::Vector;
    using NGeometricObjects::Material;
    
    class RAYTRACINGAPI Parallelogram: public NConvexPolygon::ConvexPolygon
    {
        Vector normal_vector;
        Point vertex[4];
    public:
        Parallelogram(const Material * _material, const Point &_vertex, const Vector &side_1, const Vector &side_2);

        double intersect(const NGeometry::Ray &ray) const;
        
        virtual const NGeometry::Vector& normal() const;
        
        size_t size() const;
        
        const Point& operator [] (int n) const;
    };
};

#endif  
