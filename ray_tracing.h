#ifndef RAY_TRACING_RAY_TRACING_H
#define RAY_TRACING_RAY_TRACING_H

#include "calculations/Intersecter.hpp"

namespace Calculations
{
    using namespace NIntersecter;
}

#include "geometry/Double.hpp"
#include "geometry/Geometry.hpp"

using NDouble::Double;

namespace Geometry
{
    using namespace NGeometry;
}

#include "objects/GeometricObject.hpp"
#include "objects/Parallelogram.hpp"
#include "objects/Sphere.hpp"
#include "objects/Triangle.hpp"

namespace GeometricObjects
{
    using namespace NGeometricObjects;
    using namespace NParallelogram;
    using namespace NSphere;
    using namespace NTriangle;
}

#include "parsers/DefaultParser.hpp"
#include "parsers/IFileParser.hpp"
#include "parsers/RTParser.hpp"
#include "parsers/STLParser.hpp"

namespace Parsers
{
    using namespace NDefaultParser;
    using namespace NIFileParser;
    using namespace NRTParser;
    using namespace NSTLParser;
}

#include "ImageSettings.hpp"

namespace ImageSettings
{
    using namespace NImageSettings;
}

#endif //RAY_TRACING_RAY_TRACING_H
