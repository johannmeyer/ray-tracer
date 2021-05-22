#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <cassert>

#include "Utility.h"

// Class prototype
class Vec3;

// Type aliases for Vec3
using Point3 = Vec3;   // 3D point
using Color = Vec3;    // RGB color

// Function prototypes for free functions
std::ostream& operator<<(std::ostream& out, const Vec3& v);
std::istream& operator>>(std::istream& in, Vec3& v);
Vec3 operator+(const Vec3& u, const Vec3& v);
Vec3 operator-(const Vec3& u, const Vec3& v);
Vec3 operator*(const Vec3& u, const Vec3& v);
Vec3 operator*(double t, const Vec3& v);
Vec3 operator*(const Vec3& v, double t);
Vec3 operator/(const Vec3& v, double t);
double dot(const Vec3& u, const Vec3& v);
Vec3 cross(const Vec3& u, const Vec3& v);
Vec3 unit_vector(const Vec3& v);
bool approx_equals(const Vec3& u, const Vec3& v);

class Vec3
{
    public:
        double data[3];

        Vec3(): Vec3(0) {}
        Vec3(double s) : data{s,s,s} {}
        Vec3(double d0, double d1, double d2): data{d0,d1,d2} {}

        double x() const { return data[0]; }
        double y() const { return data[1]; }
        double z() const { return data[2]; }

        // Aliases of the member functions for when it is used as a Color
        inline double r() const { return x(); }
        inline double g() const { return y(); }
        inline double b() const { return z(); }

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

        bool approx_equals(const Vec3& v) const
        {
            // not overriding operator= to be explicit
            // about approximation.
            return std::fabs(data[0] - v.data[0]) < epsilon
                && std::fabs(data[1] - v.data[1]) < epsilon
                && std::fabs(data[2] - v.data[2]) < epsilon;
        }

        Vec3 reflect(const Vec3& normal) const
        {
            return *this - 2*dot(*this, normal)*normal;
        }

        Vec3 refract(const Vec3& normal, double etai_over_etat) const
        {
            // eta_incident over eta_transmitted
            // fmin protects against NaNs
            // This function assumes both normal and the incident vector (*this)
            // is normalised.
            // assert(::approx_equals(normal.length_squared(), 1.0));
            // assert(::approx_equals(this->length_squared(), 1.0));

            double cos_theta = std::fmin(dot(-*this, normal), 1.0);
            Vec3 ray_out_perp = etai_over_etat * (*this + cos_theta*normal);
            Vec3 ray_out_parallel = - std::sqrt(std::fabs(1.0 - ray_out_perp.length_squared()))*normal;
            return ray_out_perp + ray_out_parallel;
        }

        Vec3 rotate(const Vec3& axis, const double angle) const
        {
            return cos(angle)*(*this) + sin(angle)*cross(axis, *this) + (1 - cos(angle))*dot(axis, *this)*axis;
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

        static Vec3 random_in_hemisphere(Vec3 normal)
        {
            Vec3 in_unit_sphere = random_in_unit_sphere();
            if (dot(in_unit_sphere, normal) > 0)
                return in_unit_sphere;
            else
                return -in_unit_sphere;
        }

        /*
            Rejection-based algorithm for finding a random point within a unit circle.
        */
        static Vec3 random_in_unit_circle()
        {
            while (true)
            {
                Vec3 p(random_double(-1,1), random_double(-1,1), 0);
                if (p.length_squared() >= 1) continue;
                return p;
            }
        }

};

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.data[0] << ' ' 
               << v.data[1] << ' '
               << v.data[2];
}

inline std::istream& operator>>(std::istream& in, Vec3& v)
{
    return in >> v.data[0] 
              >> v.data[1]
              >> v.data[2];
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

inline Vec3 operator-(const Vec3& u, double s)
{
    return Vec3(u.data[0] - s,
                u.data[1] - s,
                u.data[2] - s);
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

inline Vec3 abs(const Vec3& v)
{
    return Vec3(std::abs(v.x()), std::abs(v.y()), std::abs(v.z()));
}

inline double max_element(const Vec3& v)
{
    return std::max(v.x(), std::max(v.y(), v.z()));
}

inline double min_element(const Vec3& v)
{
    return std::min(v.x(), std::min(v.y(), v.z()));
}

inline Vec3 max(const Vec3& v, double s)
{
    return Vec3(std::max(v.x(), s), std::max(v.y(), s), std::max(v.z(), s));
}

inline Vec3 min(const Vec3& v, double s)
{
    return Vec3(std::min(v.x(), s), std::min(v.y(), s), std::min(v.z(), s));
}

inline Vec3 max(const Vec3& v, const Vec3& u)
{
    return Vec3(std::max(v.x(), u.x()), std::max(v.y(), u.y()), std::max(v.z(), u.z()));
}

inline Vec3 min(const Vec3& v, const Vec3& u)
{
    return Vec3(std::min(v.x(), u.x()), std::min(v.y(), u.y()), std::min(v.z(), u.z()));
}

#endif