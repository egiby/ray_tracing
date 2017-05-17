#ifndef _INTERSECTER
#define _INTERSECTER

#include "../geometry/Double.h"
#include "../geometry/Geometry.h"

#include "../objects/GeometricObject.h"
#include "../ImageSettings.h"

#include "../ApiHeader.h"

namespace NIntersecter
{
    struct RAYTRACINGAPI Intersection
    {
        NGeometry::Point point;
        NGeometricObjects::IGeometricObject * object;
    };

    class RAYTRACINGAPI Intersecter
    {
        NImageSettings::ImageSettings * settings;
    public:
        explicit Intersecter(NImageSettings::ImageSettings * settings);

        Intersection intersectAll(const NGeometry::Ray &ray);
    };

	RAYTRACINGAPI NGeometricObjects::Color calcColor(const Intersection &result, const NImageSettings::ImageSettings * settings,
                                       Intersecter * intersecter);
}

#endif
