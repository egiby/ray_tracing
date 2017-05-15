//
// Created by egiby on 15.05.17.
//

#include "GeometricObject.h"

NGeometricObjects::Color NGeometricObjects::operator*(const NGeometricObjects::Color &c,
                                                      const NDouble::Double &d) {
    int r = std::min(std::max((int) std::lround(c.red * d), 0), 255),
            g = std::min(std::max((int) std::lround(c.green * d), 0), 255),
            b = std::min(std::max((int) std::lround(c.blue * d), 0), 255);

    return {(ui32) r, (ui32) g, (ui32) b};
}

NGeometricObjects::Material::Material(NGeometricObjects::Color color, NDouble::Double _alpha, NDouble::Double reflect,
                                      NDouble::Double refract)
        : alpha(_alpha), reflect(reflect), refract(refract), color(color), has_texture(0)
{
}

NGeometricObjects::Color NGeometricObjects::Material::calcColor(int x, int y) const {
    if (!has_texture)
        return color;

    assert(!has_texture);
    return {0, 0, 0};
}

NGeometricObjects::IGeometricObject::~IGeometricObject() {
}
