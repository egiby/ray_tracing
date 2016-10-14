#ifndef _IMAGE_SETTINGS
#define _IMAGE_SETTINGS

#include "geometry/Double.hpp"
#include "geometry/Geometry.hpp"
#include "objects/GeometricObject.hpp"

#include <vector>

namespace NImageSettings
{
    using NGeometry::Point;
    using NGeometry::Vector;
    
    struct Screen
    {
        ui32 x_size, y_size;
        Point left_bottom_angle;
        Vector x_basis;
        Vector y_basis;
        
        Screen(const Point &left_bottom_angle, const Point &left_upper, const Point &right_bottom, 
               ui32 x_size = 500, ui32 y_size = 500)
        : x_size(x_size), y_size(y_size), left_bottom_angle(left_bottom_angle), 
        x_basis((right_bottom - left_bottom_angle) / x_size), y_basis((left_upper - left_bottom_angle) / y_size)
        {
        }
    };
    
    struct LightSource
    {
        NDouble::Double light_force;
        Point point;
    };
    
    struct ImageSettings
    {
        Point eye;
        Screen screen;
        std::vector<NGeometricObjects::IGeometricObject*> objects;
        std::vector<LightSource> light_sources;
        std::vector<NGeometricObjects::Material*> materials;
        
        ~ImageSettings()
        {
            for (auto object: objects)
                delete object;
            for (auto material: materials)
                delete material;
        }
    };
    
    const Point DEFAULT_EYE = {-100000, 0, 0};
    //~ const Point DEFAULT_EYE = {0, -100000, 0};
    const Screen DEFAULT_SCREEN = Screen(Point{-1, -30, -30}, Point{-1, -30, 30}, Point{-1, 30, -30});
    //~ const Screen DEFAULT_SCREEN = Screen(Point{-30, -20, -30}, Point{-30, -20, 30}, Point{30, -20, -30});
};
#endif
