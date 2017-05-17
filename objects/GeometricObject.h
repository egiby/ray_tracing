#ifndef _GEOMETRIC_OBJECT
#define _GEOMETRIC_OBJECT

#include "../geometry/Double.h"
#include "../geometry/Geometry.h"

#include <cstdint>
#include <cstdio>
#include <cmath>

#include <iostream>
#include <algorithm>

#include "../ApiHeader.h"

namespace NGeometricObjects
{
    using std::cerr;
    struct RAYTRACINGAPI Color
    {
        ui32 red, green, blue;
    };
    
	RAYTRACINGAPI Color operator * (const Color &c, const double &d);
    
    struct RAYTRACINGAPI Material
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
    
    class RAYTRACINGAPI IGeometricObject
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
