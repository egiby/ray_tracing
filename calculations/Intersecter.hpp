#ifndef _INTERSECTER
#define _INTERSECTER

#include "../geometry/Double.hpp"
#include "../geometry/Geometry.hpp"

#include "../objects/GeometricObject.hpp"
#include "../ImageSettings.hpp"

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
        explicit Intersecter(NImageSettings::ImageSettings * settings)
                : settings(settings)
        {
        }

        Intersection intersectAll(const NGeometry::Ray &ray)
        {
            NDouble::Double min_coefficient = NGeometry::INFINITY_POINT.x;
            NGeometricObjects::IGeometricObject * first_object = nullptr;

            for (auto object: settings->objects)
            {
                NDouble::Double coefficient = object->intersect(ray);

                if (coefficient < NDouble::Double(0.))
                    continue;

                if (coefficient < min_coefficient)
                {
                    first_object = object;
                    min_coefficient = coefficient;
                }
            }
            if (first_object == nullptr)
                return {NGeometry::INFINITY_POINT, first_object};

            return {ray.start + min_coefficient * ray.direction, first_object};
        }
    };

    NGeometricObjects::Color calcColor(const Intersection &result, const NImageSettings::ImageSettings * settings,
                                       Intersecter * intersecter)
    {
        if (result.object == nullptr)
            return {0, 0, 0};

        NDouble::Double illuminance = 0.;

        for (const auto &source: settings->light_sources)
        {
            auto light_ray = NGeometry::Ray(source.point, result.point - source.point);
            auto intersection = intersecter->intersectAll(light_ray);

            if (intersection.object != result.object)
                continue;

            auto radius = -(result.point - source.point);
            auto normal = result.object->getNormal(result.point);

            illuminance += source.light_force * std::max(radius * normal, Double(0.)) /
                           (std::pow(abs(radius), 3) * abs(normal));
        }

        return (result.object->getMaterial()->calcColor(0, 0)) * illuminance;
    }
}

#endif
