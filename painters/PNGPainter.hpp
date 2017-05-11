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
    using GeometricObjects::Color;
    
    using ImageSettings::ImageSettings;
    
    using Parsers::DefaultParser;
    using Parsers::IFileParser;

    using Calculations::Intersecter;

    using std::cerr;
    using std::vector;
    
    const std::string DEFAULT_OUTPUT_FILE = "rgb.png";
    const std::string DEFAULT_INPUT_FILE = "settings.in";
    
    png::rgb_pixel makePixel(const Color &c)
    {
        return png::rgb_pixel(c.red, c.green, c.blue);
    }
    
    class PNGPainter;
    
    void paintPart(ui32 first, ui32 last, png::image<png::rgb_pixel> &image, PNGPainter &painter);
    
    class PNGPainter: public IPainter
    {
        ui32 getNumThreads() const
        {
        #ifndef _DEBUG
            auto number_threads = std::thread::hardware_concurrency() + 1;
        #else
            ui32 number_threads = 1; // debug mode
        #endif
            return number_threads;
        }
    protected:
        ImageSettings * settings;
        Intersecter * intersecter;
        
        Point calcPixelCenter(ui32 x, ui32 y) const
        {
            return settings->screen.left_bottom_angle + settings->screen.x_basis * (x + 0.5) + 
                   settings->screen.y_basis * (y + 0.5);
        }
        
    public:
        explicit PNGPainter(ImageSettings * settings)
        : settings(settings), intersecter(new Intersecter(settings))
        {
        }
        
        explicit PNGPainter(std::string filename = DEFAULT_INPUT_FILE, IFileParser * parser = new DefaultParser())
        : settings(parser->parseFile(filename)), intersecter(new Intersecter(settings))
        {
            delete parser;
        }
        
        vector<vector<Color> > getImage() const
        {
            vector<vector<Color> > image(settings->screen.x_size, vector<Color>(settings->screen.y_size));
        
        #pragma omp parallel num_threads(getNumThreads())
            #pragma omp single
            for (ui32 x = 0; x < settings->screen.x_size; ++x)
                for (ui32 y = 0; y < settings->screen.y_size; ++y)
                {
                    #pragma omp task
                    {
                        Point pixel = calcPixelCenter(x, y);
                        Ray ray(settings->eye, pixel - settings->eye);
                        
                        image[x][y] = calcColor(intersecter->intersectAll(ray), settings, intersecter);
                    }
                }
            return image;
        }
        
        void paint(std::string result_file = DEFAULT_OUTPUT_FILE) const
        {
            png::image<png::rgb_pixel> image(settings->screen.x_size, settings->screen.y_size);
        
        #pragma omp parallel num_threads(getNumThreads())
            #pragma omp single
            for (ui32 x = 0; x < settings->screen.x_size; ++x)
                for (ui32 y = 0; y < settings->screen.y_size; ++y)
                {
                    #pragma omp task
                    {
                        Point pixel = calcPixelCenter(x, y);
                        Ray ray(settings->eye, pixel - settings->eye);

                        image[y][x] = makePixel(calcColor(intersecter->intersectAll(ray), settings, intersecter));
                    }
                }
            
            image.write(result_file);
        }
        
        friend void paintPart(ui32 first, ui32 last, png::image<png::rgb_pixel> &image, PNGPainter &painter);
        
        ~PNGPainter()
        {
            delete settings;
            delete intersecter;
        }
    };
};

#endif
