#ifndef _PAINTER
#define _PAINTER

#include "../geometry/Double.hpp"
#include "../geometry/Geometry.hpp"

#include "../objects/GeometricObject.hpp"
#include "../objects/Triangle.hpp"
#include "../objects/Parallelogram.hpp"

#include "../parsers/DefaultParser.hpp"

#include "../calculations/Intersecter.hpp"

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
    using NGeometry::Point;
    using NGeometry::Vector;
    using NGeometry::Ray;
    
    using NDouble::Double;
    
    using NGeometricObjects::IGeometricObject;
    using NGeometricObjects::Color;
    
    using NImageSettings::ImageSettings;
    
    using NDefaultParser::DefaultParser;
    
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
    
    Color calcColor(const Intersection &result, const ImageSettings * settings)
    {
        if (result.object == nullptr)
            return {0, 0, 0};
        
        Double illuminance = 0.;
        
        for (const auto &source: settings->light_sources)
        {
            Ray light_ray = Ray(source.point, result.point - source.point);
            auto intersection = intersectAll(light_ray, settings);
            
            if (intersection.object != result.object)
                continue;
            
            Vector radius = -(result.point - source.point);
            Vector normal = result.object->getNormal(result.point);
            
            illuminance += source.light_force * std::max(radius * normal, Double(0.)) / 
                           (std::pow(abs(radius), 3) * abs(normal));
        }
        
        return (result.object->getMaterial()->calcColor(0, 0)) * illuminance;
    }
    
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
        
        Point calcPixelCenter(ui32 x, ui32 y) const
        {
            return settings->screen.left_bottom_angle + settings->screen.x_basis * (x + 0.5) + 
                   settings->screen.y_basis * (y + 0.5);
        }
        
    public:
        explicit PNGPainter(ImageSettings * settings)
        : settings(settings)
        {
        }
        
        explicit PNGPainter(std::string filename = DEFAULT_INPUT_FILE, IFileParser * parser = new DefaultParser())
        : settings(parser->parseFile(filename))
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
                        
                        image[x][y] = calcColor(intersectAll(ray, settings), settings);
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
                        
                        image[y][x] = makePixel(calcColor(intersectAll(ray, settings), settings));
                    }
                }
            
            image.write(result_file);
        }
        
        friend void paintPart(ui32 first, ui32 last, png::image<png::rgb_pixel> &image, PNGPainter &painter);
        
        ~PNGPainter()
        {
            delete settings;
        }
    };
};

#endif
