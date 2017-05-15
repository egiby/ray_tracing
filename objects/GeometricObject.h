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
    
    Color operator * (const Color &c, const double &d);
    
    struct Material
    {
        double alpha;
        double reflect;
        double refract;
        
        Color color;
        
        bool has_texture;
        // TODO: add texture support
        
        Material (Color color, double _alpha = 0, double reflect = 0,
                  double refract = 0);
        
        Color calcColor(int x, int y) const;
    };
    
    class IGeometricObject
    {
    public:
        virtual double intersect(const NGeometry::Ray &r) const = 0;
        virtual const Material * getMaterial() const = 0;
        virtual NGeometry::Vector getNormal(const NGeometry::Point &p) const = 0;
        //~ virtual NGeometry::Point getCenter() const = 0;
        virtual ~IGeometricObject();
    };
};

#endif
