//
// Created by egiby on 15.05.17.
//

#include "Intersecter.h"

NIntersecter::Intersecter::Intersecter(NImageSettings::ImageSettings *settings)
        : settings(settings) {
}

NIntersecter::Intersection NIntersecter::Intersecter::intersectAll(const NGeometry::Ray &ray) {
    double min_coefficient = NGeometry::INFINITY_POINT.x;
    NGeometricObjects::IGeometricObject *first_object = nullptr;

    for (auto object: settings->objects) {
        double coefficient = object->intersect(ray);

        if (NDouble::less(coefficient, 0.))
            continue;

        if (NDouble::less(coefficient, min_coefficient)) {
            first_object = object;
            min_coefficient = coefficient;
        }
    }
    if (first_object == nullptr)
        return {NGeometry::INFINITY_POINT, first_object};

    return {ray.start + min_coefficient * ray.direction, first_object};
}

NGeometricObjects::Color NIntersecter::calcColor(const Intersection &result,
                                                 const NImageSettings::ImageSettings *settings,
                                                 Intersecter *intersecter) {
    if (result.object == nullptr)
        return {0, 0, 0};

    double illuminance = 0.;

    for (const auto &source: settings->light_sources) {
        auto light_ray = NGeometry::Ray(source.point, result.point - source.point);
        auto intersection = intersecter->intersectAll(light_ray);

        if (intersection.object != result.object)
            continue;

        auto radius = -(result.point - source.point);
        auto normal = result.object->getNormal(result.point);

        illuminance += source.light_force * std::max(radius * normal, 0.) /
                       (std::pow(abs(radius), 3) * abs(normal));
    }

    return (result.object->getMaterial()->calcColor(0, 0)) * illuminance;
}