#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "Utility.h"

// Class prototype
class Vec3;

// Function prototypes for special functions
inline double dot(const Vec3& u, const Vec3& v);
inline Vec3 cross(const Vec3& u, const Vec3& v);
inline Vec3 unit_vector(const Vec3& v);

class Vec3
{
    public:
        double data[3];

        Vec3(): data{0,0,0} {}
        Vec3(double d0, double d1, double d2): data{d0,d1,d2} {}

        double x() const { return data[0]; }
        double y() const { return data[1]; }
        double z() const { return data[2]; }

        Vec3 operator-() const { return Vec3(-data[0], -data[1], -data[2]); }
        double operator[](int i) const { return data[i]; }
        double& operator[](int i) { return data[i]; }
        
        Vec3& operator+= (const Vec3& v)
        {
            data[0] += v.data[0];
            data[1] += v.data[1];
            data[2] += v.data[2];
            return *this;
        }

        Vec3& operator-= (const Vec3& v)
        {
            data[0] -= v.data[0];
            data[1] -= v.data[1];
            data[2] -= v.data[2];
            return *this;
        }

        Vec3& operator*= (double s)
        {
            data[0] *= s;
            data[1] *= s;
            data[2] *= s;
            return *this;
        }

        Vec3& operator/=(double t) {
            return *this *= 1/t;
        }

        double length() const
        {
            return std::sqrt(length_squared());
        }

        double length_squared() const
        {
            return dot(*this, *this);
        }

        inline static Vec3 random()
        {
            return Vec3(random_double(), random_double(), random_double());
        }

        inline static Vec3 random(double min, double max)
        {
            return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        /*
            Rejection-based algorithm for finding a random point within a unit sphere.
        */
        static Vec3 random_in_unit_sphere()
        {
            while (true)
            {
                Vec3 p = Vec3::random(-1,1);
                if (p.length_squared() >= 1) continue;
                return p;
            }
        }

        static Vec3 random_unit_vector()
        {
            return unit_vector(random_in_unit_sphere());
        }

        static Vec3 random_in_hemisphere(rec.normal)
        {
            Vec3 in_unit_sphere == random_in_unit_sphere();
            if dot(in_unit_sphere, normal) > 0)
                return in_unit_sphere;
            else
                return -in_unit_sphere;
        }

};

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.data[0] << ' ' 
               << v.data[1] << ' '
               << v.data[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.data[0] + v.data[0],
                u.data[1] + v.data[1],
                u.data[2] + v.data[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.data[0] - v.data[0],
                u.data[1] - v.data[1],
                u.data[2] - v.data[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.data[0] * v.data[0],
                u.data[1] * v.data[1],
                u.data[2] * v.data[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
    return Vec3(t*v.data[0], t*v.data[1], t*v.data[2]);
}

inline Vec3 operator*(const Vec3& v, double t) {
    return t * v;
}

inline Vec3 operator/(const Vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const Vec3& u, const Vec3& v)
{
    return u.data[0]*v.data[0]
         + u.data[1]*v.data[1]
         + u.data[2]*v.data[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.data[1]*v.data[2] - u.data[2]*v.data[1],
                u.data[2]*v.data[0] - u.data[0]*v.data[2],
                u.data[0]*v.data[1] - u.data[1]*v.data[0]);
}

inline Vec3 unit_vector(const Vec3& v)
{
    // This can cause numerical issues. A simple alternative is
    // to always add 1e-6
    // if (length < 1e-6)
    // {
    //     std::cerr << "Warning (unit_vector): v.length < 1e-6" << std::endl;
    //     return v/(length + 1e-6);
    // }
    return v/v.length();
}

// Type aliases for Vec3
using Point3 = Vec3;   // 3D point
using Color = Vec3;    // RGB color

#endif