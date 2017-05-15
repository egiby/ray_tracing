#ifndef _GEOMETRIC_OBJECT
#define _GEOMETRIC_OBJECT

#include "../geometry/Double.h"
#include "../geometry/Geometry.h"

#include <cstdint>
#include <cstdio>
#include <cmath>

#include <iostream>
#include <algorithm>

namespace NGeometricObjects
{
    using std::cerr;
    struct Color
    {
        ui32 red, green, blue;
    };
    
    Color operator * (const Color &c, const NDouble::Double &d);
    
    struct Material
    {
        NDouble::Double alpha;
        NDouble::Double reflect;
        NDouble::Double refract;
        
        Color color;
        
        bool has_texture;
        // TODO: add texture support
        
        Material (Color color, NDouble::Double _alpha = 0, NDouble::Double reflect = 0,
                  NDouble::Double refract = 0);
        
        Color calcColor(int x, int y) const;
    };
    
    class IGeometricObject
    {
    public:
        virtual NDouble::Double intersect(const NGeometry::Ray &r) const = 0;
        virtual const Material * getMaterial() const = 0;
        virtual NGeometry::Vector getNormal(const NGeometry::Point &p) const = 0;
        //~ virtual NGeometry::Point getCenter() const = 0;
        virtual ~IGeometricObject();
    };
};

#endif
