#ifndef _DEFAULT_PARSER
#define _DEFAULT_PARSER

#include "IFileParser.hpp"

#include "../objects/Triangle.h"
#include "../objects/Parallelogram.h"
#include "../objects/Sphere.h"

#include <iostream>
#include <fstream>

#include "../ApiHeader.h"

/*
 * language:
 * <point> = <double> <double> <double>
 * <color> = <uint8_t> <uint8_t> <uint8_t>
 * <size> = <size_t> <size_t>
 * 
 * <eye> = "eye" <point>
 * 
 * <screen> = "screen" [
 * (left bottom angle)<point>
 * (left upper angle)<point>
 * (right bottom angle)<point>
 * (size)<size>]
 * 
 * <triangle> = "triangle" [
 * (vertex)<point>
 * (side_1)<vector>
 * (side_2)<vector>
 * (rgb)<color>]
 * 
 * <parallelogram> = "parallelogram" [
 * (vertex)<point>
 * (side_1)<vector>
 * (side_2)<vector>
 * (rgb)<color>]
 * 
 * <light source> = "light_source" [
 * (point)<point>
 * (light force)<double>]
 * 
 * <sphere> = "sphere" [
 * (center)<point>
 * (radius)<double>
 * (color)<color>]
 */

namespace NDefaultParser
{
    using NImageSettings::ImageSettings;
    using NImageSettings::Screen;
    using NImageSettings::LightSource;
    
    using NGeometry::Point;
    using NGeometry::Vector;
    
    using NGeometricObjects::IGeometricObject;
    using NGeometricObjects::Color;
    using NGeometricObjects::Material;
    using NIFileParser::IFileParser;
    
    class RAYTRACINGAPI DefaultParser: public IFileParser
    {
    public:
        ImageSettings * parseFile(std::string filename);
    };
};

#endif
