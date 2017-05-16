//
// Created by egiby on 15.05.17.
//

#include "DefaultParser.h"

NImageSettings::ImageSettings *NDefaultParser::DefaultParser::parseFile(std::string filename) {
    Point eye = NImageSettings::DEFAULT_EYE;
    Screen screen = NImageSettings::DEFAULT_SCREEN;
    std::vector<IGeometricObject*> objects;
    std::vector<LightSource> sources;
    std::vector<Material*> materials;

    std::ifstream in(filename);

    std::string word;
    while (in >> word)
    {
        if (word == "screen")
        {
            Point left_bottom, left_upper, right_bottom;
            ui32 x_size, y_size;
            in >> left_bottom >> left_upper >> right_bottom;
            in >> x_size >> y_size;

            screen = Screen(left_bottom, left_upper, right_bottom, x_size, y_size);
        }

        if (word == "eye")
        {
            in >> eye;
        }

        if (word == "triangle")
        {
            Point vertex;
            Vector side_1, side_2;
            in >> vertex >> side_1 >> side_2;

            Color c;
            in >> c.red >> c.green >> c.blue;

            materials.push_back(new Material(c));

            objects.push_back(new NTriangle::Triangle(materials.back(), vertex, side_1, side_2));
        }

        if (word == "parallelogram")
        {
            Point vertex;
            Vector side_1, side_2;
            in >> vertex >> side_1 >> side_2;

            Color c;
            in >> c.red >> c.green >> c.blue;

            materials.push_back(new Material(c));
            objects.push_back(new NParallelogram::Parallelogram(materials.back(), vertex, side_1, side_2));
        }

        if (word == "light_source")
        {
            Point point;
            double force;
            in >> point >> force;

            sources.push_back(LightSource{force, point});
        }

        if (word == "sphere")
        {
            Point center;
            double radius;
            Color c;
            in >> center >> radius >> c.red >> c.green >> c.blue;

            materials.push_back(new Material(c));
            objects.push_back(new NSphere::Sphere{center, radius, materials.back()});
        }
        // to be continued...
    }

    if (sources.empty())
    {
        Vector normal = screen.x_basis ^ screen.y_basis;

        Point left_bottom_angle = screen.left_bottom_angle;
        Point left_upper = left_bottom_angle + screen.x_basis * screen.x_size;
        Point right_bottom = left_bottom_angle + screen.y_basis * screen.y_size;
        Point right_upper = left_bottom_angle + screen.y_basis * screen.y_size + screen.x_basis * screen.x_size;

        //~ LightSource source = {1000, left_bottom_angle - normal * ((screen.x_size + screen.y_size) / 2.0)};
        //~ sources.push_back(source);

        sources.push_back({1000, left_bottom_angle - normal * ((screen.x_size + screen.y_size) / 0.01)});
        sources.push_back({1000, left_upper - normal * ((screen.x_size + screen.y_size) / 0.01)});
        sources.push_back({1000, right_bottom - normal * ((screen.x_size + screen.y_size) / 0.01)});
        sources.push_back({1000, right_upper - normal * ((screen.x_size + screen.y_size) / 0.01)});
        //~ cerr << source.light_force << '\n' << source.point << '\n';
        //~ cerr << eye << '\n';
    }

    return new ImageSettings{eye, screen, objects, sources, materials};
}
