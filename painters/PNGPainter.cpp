//
// Created by egiby on 15.05.17.
//

#include "PNGPainter.h"

png::rgb_pixel NPainter::makePixel(const Color &c) {
    return png::rgb_pixel(c.red, c.green, c.blue);
}

ui32 NPainter::PNGPainter::getNumThreads() const {
#ifndef _DEBUG
    auto number_threads = std::thread::hardware_concurrency() + 1;
#else
    ui32 number_threads = 1; // debug mode
#endif
    return number_threads;
}

NGeometry::Point NPainter::PNGPainter::calcPixelCenter(ui32 x, ui32 y) const {
    return settings->screen.left_bottom_angle + settings->screen.x_basis * (x + 0.5) +
           settings->screen.y_basis * (y + 0.5);
}

NPainter::PNGPainter::PNGPainter(NImageSettings::ImageSettings *settings)
        : settings(settings), intersecter(new Intersecter(settings)) {
}

NPainter::PNGPainter::PNGPainter(std::string filename, NIFileParser::IFileParser *parser)
        : settings(parser->parseFile(filename)), intersecter(new Intersecter(settings)) {
    delete parser;
}

std::vector<std::vector<Color>> NPainter::PNGPainter::getImage() const {
    vector<vector<Color> > image(settings->screen.x_size, vector<Color>(settings->screen.y_size));

#pragma omp parallel num_threads(getNumThreads())
#pragma omp single
    for (ui32 x = 0; x < settings->screen.x_size; ++x)
        for (ui32 y = 0; y < settings->screen.y_size; ++y) {
#pragma omp task
            {
                Point pixel = calcPixelCenter(x, y);
                Ray ray(settings->eye, pixel - settings->eye);

                image[x][y] = calcColor(intersecter->intersectAll(ray), settings, intersecter);
            }
        }
    return image;
}

void NPainter::PNGPainter::paint(std::string result_file) const {
    png::image<png::rgb_pixel> image(settings->screen.x_size, settings->screen.y_size);

#pragma omp parallel num_threads(getNumThreads())
#pragma omp single
    for (ui32 x = 0; x < settings->screen.x_size; ++x)
        for (ui32 y = 0; y < settings->screen.y_size; ++y) {
#pragma omp task
            {
                Point pixel = calcPixelCenter(x, y);
                Ray ray(settings->eye, pixel - settings->eye);

                image[y][x] = makePixel(calcColor(intersecter->intersectAll(ray), settings, intersecter));
            }
        }

    image.write(result_file);
}

NPainter::PNGPainter::~PNGPainter() {
    delete settings;
    delete intersecter;
}
