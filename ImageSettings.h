#ifndef _IMAGE_SETTINGS
#define _IMAGE_SETTINGS

#include "geometry/Double.h"
#include "geometry/Geometry.h"
#include "objects/GeometricObject.h"

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
               ui32 x_size = 500, ui32 y_size = 500);
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
        
        ~ImageSettings();
    };
    
    const Point DEFAULT_EYE = {-100000, 0, 0};
    //~ const Point DEFAULT_EYE = {0, -100000, 0};
    const Screen DEFAULT_SCREEN = Screen(Point{-1, -30, -30}, Point{-1, -30, 30}, Point{-1, 30, -30});
    //~ const Screen DEFAULT_SCREEN = Screen(Point{-30, -20, -30}, Point{-30, -20, 30}, Point{30, -20, -30});
};
#endif
