#ifndef _I_FILE_PARSER
#define _I_FILE_PARSER

#include "../ImageSettings.h"

#include <string>

#include "../ApiHeader.h"

namespace NIFileParser
{
    class RAYTRACINGAPI IFileParser
    {
    public:
        virtual NImageSettings::ImageSettings * parseFile(std::string filename) = 0;
        virtual ~IFileParser()
        {
        }
    };
}

#endif
