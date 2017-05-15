#ifndef _RT_PARSER
#define _RT_PARSER

#include "IFileParser.hpp"

#include "../objects/Triangle.h"
#include "../objects/Parallelogram.h"
#include "../objects/Sphere.h"

#include <iostream>
#include <fstream>
#include <map>

namespace NRTParser
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
    
    using std::string;
    
    class RTParser: public IFileParser
    {
        Screen parseVievport(std::ifstream &in, Point &eye);
        
        void parseEntry(std::ifstream &in, std::map<string, Material*> &materials);
        
        std::map<string, Material*> parseMaterials(std::ifstream &in);

        double parseReference(std::ifstream &in);
        
        LightSource parsePoint(std::ifstream &in);
        
        std::vector<LightSource> parseLightSources(std::ifstream &in);
        
        IGeometricObject * parseSphere(std::ifstream &in, std::map<string, Material*> materials);
        
        IGeometricObject * parseTriangle(std::ifstream &in, std::map<string, Material*> materials);
        
        std::vector<IGeometricObject*> parseGeometry(std::ifstream &in, const std::map<string, Material*> materials);
        
    public:
        ImageSettings * parseFile(std::string filename);
    };
};

#endif
