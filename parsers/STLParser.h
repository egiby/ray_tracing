#ifndef _STL_PARSER
#define _STL_PARSER

#include "IFileParser.hpp"

#include <iostream>
#include <fstream>

#include <cassert>

namespace NSTLParser
{
    using NImageSettings::ImageSettings;
    using NImageSettings::Screen;
    
    using NGeometry::Point;
    using NGeometry::Vector;
    
    using NGeometricObjects::IGeometricObject;
    using NGeometricObjects::Color;
    using NGeometricObjects::Material;
    using NImageSettings::LightSource;
    using NIFileParser::IFileParser;
    
    class STLParser: public IFileParser
    {
        Point readVertex(std::ifstream &in);
        
        std::vector<LightSource> sources;
        Point eye;
        Screen screen;
        
    public:
        STLParser (Point eye = NImageSettings::DEFAULT_EYE,
                   Screen screen = NImageSettings::DEFAULT_SCREEN,
                   std::vector<LightSource> sources = std::vector<LightSource>());
        
        ImageSettings * parseFile(std::string filename);
    };
};

#endif
