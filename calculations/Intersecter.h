#ifndef _INTERSECTER
#define _INTERSECTER

#include "../geometry/Double.h"
#include "../geometry/Geometry.h"

#include "../objects/GeometricObject.h"
#include "../ImageSettings.h"

namespace NIntersecter
{
    using NDouble::Double;

    struct Intersection
    {
        NGeometry::Point point;
        NGeometricObjects::IGeometricObject * object;
    };

    class Intersecter
    {
        NImageSettings::ImageSettings * settings;
    public:
        explicit Intersecter(NImageSettings::ImageSettings * settings);

        Intersection intersectAll(const NGeometry::Ray &ray);
    };

    NGeometricObjects::Color calcColor(const Intersection &result, const NImageSettings::ImageSettings * settings,
                                       Intersecter * intersecter);
}

#endif
