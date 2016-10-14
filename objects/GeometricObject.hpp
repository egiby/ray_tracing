#ifndef _GEOMETRIC_OBJECT
#define _GEOMETRIC_OBJECT

#include "../geometry/Double.hpp"
#include "../geometry/Geometry.hpp"

#include <cstdint>
#include <cstdio>
#include <cmath>

#include <iostream>
#include <algorithm>

#include <png++/png.hpp>

using std::cerr;

namespace NGeometricObjects
{
    struct Color
    {
        ui32 red, green, blue;
    };
    
    Color operator * (const Color &c, const NDouble::Double &d)
    {
        int r = std::min(std::max((int)std::lround(c.red * d), 0), 255),
            g = std::min(std::max((int)std::lround(c.green * d), 0), 255),
            b = std::min(std::max((int)std::lround(c.blue * d), 0), 255);
        
        return {(ui32)r, (ui32)g, (ui32)b};
    }
    
    struct Material
    {
        NDouble::Double alpha;
        NDouble::Double reflect;
        NDouble::Double refract;
        
        Color color;
        
        bool has_texture;
        png::image<png::rgb_pixel> image;
        
        Material (Color color, NDouble::Double _alpha = 0, NDouble::Double reflect = 0,
                  NDouble::Double refract = 0)
        : alpha(_alpha), reflect(reflect), refract(refract), color(color), has_texture(0)
        {
        }
        
        Material (png::image<png::rgb_pixel> image, NDouble::Double alpha = 0, NDouble::Double reflect = 0,
                  NDouble::Double refract = 0)
        : alpha(alpha), reflect(reflect), refract(refract), color({0, 0, 0}), has_texture(1), image(image)
        {
        }
        
        Color calcColor(int x, int y) const
        {
            if (!has_texture)
                return color;
            
            auto pixel = image.get_pixel(x % image.get_width(), y % image.get_height());
            return {pixel.red, pixel.green, pixel.blue};
        }
    };
    
    class IGeometricObject
    {
    public:
        virtual NDouble::Double intersect(const NGeometry::Ray &r) const = 0;
        virtual const Material * getMaterial() const = 0;
        virtual NGeometry::Vector getNormal(const NGeometry::Point &p) const = 0;
        //~ virtual NGeometry::Point getCenter() const = 0;
        virtual ~IGeometricObject()
        {
        }
    };
};

#endif
