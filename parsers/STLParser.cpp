//
// Created by egiby on 15.05.17.
//

#include "STLParser.h"
#include "../objects/Triangle.h"

NGeometry::Point NSTLParser::STLParser::readVertex(std::ifstream &in) {
    std::string word;
    in >> word;
    //~ cerr << word << '\n';
    assert(word == "vertex");

    Point p;
    in >> p;
    return p;
}

NSTLParser::STLParser::STLParser(NGeometry::Point eye, NImageSettings::Screen screen,
                                 std::vector<NImageSettings::LightSource> sources)
        : sources(sources), eye(eye), screen(screen)
{
    //~ cerr << "parser created\n";
}

NImageSettings::ImageSettings *NSTLParser::STLParser::parseFile(std::string filename) {
    std::vector<IGeometricObject*> objects;
    std::vector<Material*> materials;
    srand(501);

    std::ifstream in(filename);

    materials.push_back(new Material({0, 0, 128}));

    std::string word;
    while (in >> word)
    {
        if (word == "normal")
        {
            Vector normal;
            in >> normal;

            in >> word >> word;
            Point v1, v2, v3;

            v1 = readVertex(in);
            v2 = readVertex(in);
            v3 = readVertex(in);

            //~ cerr << v1 << '\n' << v2 << '\n' << v3 << '\n';
            //~ cerr << '\n';

            if (((v2 - v1) ^ (v3 - v1)) * normal < 0)
                std::swap(v2, v3);


            objects.push_back(new NTriangle::Triangle(materials.back(), v1, v2 - v1, v3 - v1));
        }
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

        sources.push_back({300, left_bottom_angle - normal * ((screen.x_size + screen.y_size) / 2.0)});
        sources.push_back({300, left_upper - normal * ((screen.x_size + screen.y_size) / 2.0)});
        sources.push_back({300, right_bottom - normal * ((screen.x_size + screen.y_size) / 2.0)});
        sources.push_back({300, right_upper - normal * ((screen.x_size + screen.y_size) / 2.0)});
        //~ cerr << source.light_force << '\n' << source.point << '\n';
        //~ cerr << eye << '\n';
    }

    return new ImageSettings{eye, screen, objects, sources, materials};
}
