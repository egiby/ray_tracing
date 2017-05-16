#ifndef _PAINTER
#define _PAINTER

#include "../ray_tracing.h"

#include "IPainter.hpp"

#include <png++/png.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <future>

#include <cstdlib>
#include <cmath>

namespace NPainter
{
    using Geometry::Point;
    using Geometry::Vector;
    using Geometry::Ray;
    
    using GeometricObjects::IGeometricObject;
    
    using ImageSettings::ImageSettings;
    
    using Parsers::DefaultParser;
    using Parsers::IFileParser;

    using Calculations::Intersecter;

    using std::cerr;
    using std::vector;
    
    const std::string DEFAULT_OUTPUT_FILE = "rgb.png";
    const std::string DEFAULT_INPUT_FILE = "settings.in";
    
    png::rgb_pixel makePixel(const Color &c);
    
    class PNGPainter;

    class PNGPainter: public IPainter
    {
        ui32 getNumThreads() const;
    protected:
        ImageSettings * settings;
        Intersecter * intersecter;
        
        Point calcPixelCenter(ui32 x, ui32 y) const;
        
    public:
        explicit PNGPainter(ImageSettings * settings);
        
        explicit PNGPainter(std::string filename = DEFAULT_INPUT_FILE, IFileParser * parser = new DefaultParser());
        
        vector<vector<Color> > getImage() const;
        
        void paint(std::string result_file = DEFAULT_OUTPUT_FILE) const;

        ~PNGPainter();
    };
};

#endif
