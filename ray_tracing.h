#ifndef RAY_TRACING_RAY_TRACING_H
#define RAY_TRACING_RAY_TRACING_H

#include "calculations/Intersecter.h"

namespace Calculations
{
    using NIntersecter::Intersecter;
    using NIntersecter::Intersection;
    using NIntersecter::calcColor;
}

#include "geometry/Double.h"
#include "geometry/Geometry.h"

using NDouble::Double;

namespace Geometry
{
    using NGeometry::Point;
    using NGeometry::Vector;
    using NGeometry::INFINITY_POINT;
    using NGeometry::Ray;
    using NGeometry::Line;
    using NGeometry::Plane;
}

#include "objects/GeometricObject.h"
#include "objects/Parallelogram.h"
#include "objects/Sphere.h"
#include "objects/Triangle.h"

using NGeometricObjects::Color;
using NGeometricObjects::Material;

namespace GeometricObjects
{
    using NGeometricObjects::IGeometricObject;
    using NParallelogram::Parallelogram;
    using NSphere::Sphere;
    using NTriangle::Triangle;
}

#include "parsers/DefaultParser.h"
#include "parsers/IFileParser.hpp"
#include "parsers/RTParser.h"
#include "parsers/STLParser.h"

namespace Parsers
{
    using NDefaultParser::DefaultParser;
    using NIFileParser::IFileParser;
    using NRTParser::RTParser;
    using NSTLParser::STLParser;
}

#include "ImageSettings.h"

namespace ImageSettings
{
    using NImageSettings::ImageSettings;
    using NImageSettings::Screen;
    using NImageSettings::LightSource;
    using NImageSettings::DEFAULT_EYE;
    using NImageSettings::DEFAULT_SCREEN;
}

#endif //RAY_TRACING_RAY_TRACING_H
