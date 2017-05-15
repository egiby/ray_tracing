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
    inline Double operator * (const Double &a, const T &b)
    {
        return Double(double(a) * double(b));
    }
    
    template<typename T>
    inline Double operator * (const T &a, const Double &b)
    {
        return Double(double(a) * double(b));
    }

    inline Double operator / (const Double &a, const Double &b)
    {
        return Double(double(a) / double(b));
    }
    
    template<typename T>
    inline Double operator / (const Double &a, const T &b)
    {
        return Double(double(a) / double(b));
    }
    
    template<typename T>
    inline Double operator / (const T &a, const Double &b)
    {
        return Double(double(a) / double(b));
    }

    inline Double operator + (const Double &a, const Double &b)
    {
        return Double(double(a) + double(b));
    }

    inline Double operator - (const Double &a, const Double &b)
    {
        return Double(double(a) - double(b));
    }

    inline bool operator == (const Double &a, const Double &b)
    {
        return fabs(a - b) < Double::EPS;
    }

    inline bool operator < (const Double &a, const Double &b)
    {
        return double(a) < double(b) - Double::EPS;
    }
    
    template<typename T>
    inline bool operator < (const T &a, const Double &b)
    {
        return double(a) < double(b) - Double::EPS;
    }
    
    template<typename T>
    inline bool operator < (const Double &a, const T &b)
    {
        return double(a) < double(b) - Double::EPS;
    }

    inline bool operator > (const Double &a, const Double &b)
    {
        return double(a) > double(b) + Double::EPS;
    }

    inline bool operator > (const Double &a, const double &b)
    {
        return double(a) > double(b) + Double::EPS;
    }

    inline bool operator > (const double &a, const Double &b)
    {
        return double(a) > double(b) + Double::EPS;
    }

    inline std::istream& operator >> (std::istream &in, Double &d)
    {
        double _d;
        in >> _d;
        d = Double(_d);
        
        return in;
    }
    
    inline std::ostream& operator << (std::ostream &out, const Double &d)
    {
        out << double(d);
        return out;
    }
};

#endif
