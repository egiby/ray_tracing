//
// Created by egiby on 15.05.17.
//

#include "../ApiImplementation.h"
#include "RTParser.h"

using NGeometricObjects::IGeometricObject;

NImageSettings::Screen NRTParser::RTParser::parseVievport(std::ifstream &in, NGeometry::Point &eye) {
    string word;
    Point left_bottom, left_upper, right_upper;
    ui32 x_size = 500, y_size = 500;

    while (1) {
        in >> word;

        if (word[0] == '#') {
            std::getline(in, word);
            continue;
        }

        if (word == "endviewport")
            break;

        if (word == "origin") {
            in >> eye;
        }

        if (word == "topleft") {
            in >> left_upper;
        }

        if (word == "bottomleft") {
            in >> left_bottom;
        }

        if (word == "topright") {
            in >> right_upper;
        }

        if (word == "size") {
            in >> x_size >> y_size;
        }
    }

    Point right_bottom = right_upper - (left_upper - left_bottom);
    cerr << "screen\n";
    cerr << left_bottom << '\n' << left_upper << '\n' << right_bottom << '\n';

    return Screen(left_bottom, left_upper, right_bottom, x_size, y_size);
}

void
NRTParser::RTParser::parseEntry(std::ifstream &in, std::map<std::string, NGeometricObjects::Material *> &materials) {
    string word;

    string name;
    double alpha(0), reflect(0), refract(0);
    Color color;
    string filename = "";

    while (1) {
        in >> word;

        if (word[0] == '#') {
            std::getline(in, word);
            continue;
        }

        if (word == "name") {
            in >> name;
        }

        if (word == "color") {
            in >> color.red >> color.green >> color.blue;
        }

        if (word == "alpha") {
            in >> alpha;
        }

        if (word == "reflect") {
            in >> reflect;
        }

        if (word == "refract") {
            in >> refract;
        }

        if (word == "endentry")
            break;
    }

    if (filename == "")
        materials[name] = new Material(color, alpha, reflect, refract);
    else {
        // TODO: add material support
        assert(0);
    }
}

std::map<std::string, NGeometricObjects::Material *> NRTParser::RTParser::parseMaterials(std::ifstream &in) {
    string word;

    std::map<string, Material *> materials;
    while (1) {
        in >> word;

        if (word[0] == '#') {
            std::getline(in, word);
            continue;
        }

        if (word == "endmaterials")
            break;

        if (word == "entry")
            parseEntry(in, materials);
    }

    return materials;
}

double NRTParser::RTParser::parseReference(std::ifstream &in) {
    string word;

    double distance = 1;
    double power = 1;
    while (1) {
        in >> word;

        if (word[0] == '#') {
            std::getline(in, word);
            continue;
        }

        if (word == "power") {
            in >> power;
        }

        if (word == "distance")
            in >> distance;

        if (word == "endreference")
            break;
    }

    return distance * distance / power;
}

NImageSettings::LightSource NRTParser::RTParser::parsePoint(std::ifstream &in) {
    LightSource source;

    string word;
    while (1) {
        in >> word;
        if (word[0] == '#') {
            std::getline(in, word);
            continue;
        }

        if (word == "endpoint") {
            break;
        }

        if (word == "coords") {
            in >> source.point;
        }

        if (word == "power") {
            in >> source.light_force;
        }
    }

    return source;
}

std::vector<NImageSettings::LightSource> NRTParser::RTParser::parseLightSources(std::ifstream &in) {
    double coeff = 1;
    std::vector<LightSource> sources;

    string word;
    while (1) {
        in >> word;

        if (word[0] == '#') {
            std::getline(in, word);
            continue;
        }

        if (word == "endlights")
            break;

        if (word == "reference") {
            coeff = parseReference(in);
        }

        if (word == "point") {
            auto source = parsePoint(in);
            source.light_force = source.light_force * coeff;
            sources.push_back(source);
        }
    }

    cerr << "light source:\n";
    cerr << sources[0].point << '\n';

    return sources;
}

NGeometricObjects::IGeometricObject *
NRTParser::RTParser::parseSphere(std::ifstream &in, std::map<std::string, NGeometricObjects::Material *> materials) {
    Point center;
    double radius(0);
    Material *material(0);

    string word;
    while (1) {
        in >> word;

        if (word[0] == '#') {
            std::getline(in, word);
            continue;
        }

        if (word == "endsphere")
            break;

        if (word == "coords") {
            in >> center;
        }

        if (word == "radius") {
            in >> radius;
        }

        if (word == "material") {
            in >> word;
            material = materials[word];
        }
    }

    cerr << "sphere:\n";
    cerr << center << '\n';
    cerr << radius << '\n';

    return new NSphere::Sphere{center, radius, material};
}

NGeometricObjects::IGeometricObject *
NRTParser::RTParser::parseTriangle(std::ifstream &in, std::map<std::string, NGeometricObjects::Material *> materials) {
    Material *material = 0;
    std::vector<Point> v;

    string word;
    while (1) {
        in >> word;

        if (word[0] == '#') {
            std::getline(in, word);
            continue;
        }

        if (word == "endtriangle")
            break;

        if (word == "vertex") {
            Point vertex;
            in >> vertex;
            v.push_back(vertex);
        }

        if (word == "material") {
            in >> word;
            material = materials[word];
        }
    }

    return new NTriangle::Triangle{material, v[0], v[1] - v[0], v[2] - v[0]};
}

std::vector<IGeometricObject *> NRTParser::RTParser::parseGeometry(std::ifstream &in,
                                                                   const std::map<std::string, NGeometricObjects::Material *> materials) {
    std::vector<IGeometricObject *> objects;
    string word;
    while (1) {
        cerr << "geometry " << word << '\n';
        in >> word;

        if (word[0] == '#') {
            std::getline(in, word);
            continue;
        }

        if (word == "endgeometry") {
            break;
        }

        if (word == "sphere") {
            objects.push_back(parseSphere(in, materials));
        }

        if (word == "triangle") {
            objects.push_back(parseTriangle(in, materials));
        }

        if (word == "quadrangle") {
            cerr << "I can't parse it\n";
            while (1) {
                in >> word;
                if (word == "endquadrangle")
                    break;
            }
        }
    }

    return objects;
}

NImageSettings::ImageSettings* NRTParser::RTParser::parse( std::ifstream& in ) {
	Point eye = NImageSettings::DEFAULT_EYE;
	Screen screen = NImageSettings::DEFAULT_SCREEN;
	std::vector<IGeometricObject *> objects;
	std::vector<LightSource> sources;
	std::vector<Material *> materials;
	std::map<string, Material *> id_to_material;

	std::string word;
	while( in >> word ) {
		cerr << word << '\n';
		if( word[0] == '#' ) {
			std::getline( in, word );
			continue;
		}

		if( word == "viewport" ) {
			screen = parseVievport( in, eye );
		}

		if( word == "materials" ) {
			id_to_material = parseMaterials( in );
			for( auto p : id_to_material )
				materials.push_back( p.second );
		}

		if( word == "lights" ) {
			sources = parseLightSources( in );
		}

		if( word == "geometry" ) {
			objects = parseGeometry( in, id_to_material );
		}
	}

	//~ cerr << eye << '\n' << objects.size() << ' ' << sources.size() << ' ' << materials.size() << '\n';

	return new ImageSettings{ eye, screen, objects, sources, materials };
}

NImageSettings::ImageSettings *NRTParser::RTParser::parseFile(std::string filename) {
	std::ifstream in( filename );
	return parse( in );
}
