//
// Created by egiby on 15.05.17.
//

#include "ImageSettings.h"

NImageSettings::Screen::Screen(const NGeometry::Point &left_bottom_angle, const NGeometry::Point &left_upper,
                               const NGeometry::Point &right_bottom, ui32 x_size, ui32 y_size)
        : x_size(x_size), y_size(y_size), left_bottom_angle(left_bottom_angle),
          x_basis((right_bottom - left_bottom_angle) / x_size), y_basis((left_upper - left_bottom_angle) / y_size)
{
}

NImageSettings::ImageSettings::~ImageSettings() {
    for (auto object: objects)
        delete object;
    for (auto material: materials)
        delete material;
}
