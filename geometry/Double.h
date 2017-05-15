#ifndef _DOUBLE
#define _DOUBLE

#include <cmath>
#include <iostream>

namespace NDouble
{
    class Double
    {
        double value;
    public:
        static const double EPS;

        Double (const double &value);

        Double ();

        Double operator - () const;
        
        Double& operator += (const Double &d);
        
        Double& operator -= (const Double &d);
        
        operator double () const;
    };
    
    inline Double operator * (const Double &a, const Double &b)
    {
        return Double(double(a) * double(b));
    }
    
    template<typename T>
    Double operator * (const Double &a, const T &b)
    {
        return Double(double(a) * double(b));
    }
    
    template<typename T>
    Double operator * (const T &a, const Double &b)
    {
        return Double(double(a) * double(b));
    }

    inline Double operator / (const Double &a, const Double &b)
    {
        return Double(double(a) / double(b));
    }
    
    template<typename T>
    Double operator / (const Double &a, const T &b)
    {
        return Double(double(a) / double(b));
    }
    
    template<typename T>
    Double operator / (const T &a, const Double &b)
    {
        return Double(double(a) / double(b));
    }

    Double operator + (const Double &a, const Double &b);

    Double operator - (const Double &a, const Double &b);

    bool operator == (const Double &a, const Double &b);

    bool operator < (const Double &a, const Double &b);
    
    template<typename T>
    bool operator < (const T &a, const Double &b)
    {
        return double(a) < double(b) - Double::EPS;
    }
    
    template<typename T>
    bool operator < (const Double &a, const T &b)
    {
        return double(a) < double(b) - Double::EPS;
    }

    bool operator > (const Double &a, const Double &b);

    bool operator > (const Double &a, const double &b);

    bool operator > (const double &a, const Double &b);

    std::istream& operator >> (std::istream &in, Double &d);
    
    std::ostream& operator << (std::ostream &out, const Double &d);
};

#endif
