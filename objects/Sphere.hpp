#ifndef _SPHERE
#define _SPHERE

#include "GeometricObject.hpp"
#include "../ImageSettings.hpp"

using NDouble::Double;
using NGeometricObjects::Material;


class Sphere: public NGeometricObjects::IGeometricObject
{
    NGeometry::Point center;
    NDouble::Double radius;
    const NGeometricObjects::Material * material;
public:
    
    Sphere(const NGeometry::Point &center, const NDouble::Double &radius, const Material * material)
    : center(center), radius(radius), material(material)
    {
    }
    
    NDouble::Double intersect(const NGeometry::Ray &r) const
    {
        NDouble::Double coefficient = (r.direction * (center - r.start)) / (r.direction * r.direction);
        NGeometry::Point closest = r.start + r.direction * coefficient;
        
        if ((closest - center) * (closest - center) > radius * radius)
            return -1;
        
        if ((closest - center) * (closest - center) == radius * radius)
        {
            return coefficient;
        }
        
        NDouble::Double d_coef = sqrt(radius * radius - (closest - center) * (closest - center)) / abs(r.direction);
        
        if (coefficient - d_coef >= 0.)
            return coefficient - d_coef;
        
        if (coefficient + d_coef < 0.)
            return -1;
        
        return coefficient + d_coef;
    }
    
    const Material * getMaterial() const
    {
        return material;
    }
    
    NGeometry::Vector getNormal(const NGeometry::Point &p) const
    {
        return p - center;
    }
};

#endif
