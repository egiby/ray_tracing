#ifndef _IPAINTER
#define _IPAINTER

#include <vector>

#include "../objects/GeometricObject.h"

class IPainter
{
public:
    virtual std::vector<std::vector<NGeometricObjects::Color> > getImage() const = 0;
    virtual void paint(std::string result_file) const = 0;
    virtual ~IPainter() {}
};
#endif
