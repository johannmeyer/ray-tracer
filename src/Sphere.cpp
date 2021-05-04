#include "Sphere.h"
#include "Utility.h"

#include <assert.h>

/*
    Ray-Sphere Intersection

    An ray intersection with a sphere occurs if x^2+y^2+z^2 <= R is true.
    Alternatively, (x,y,z) can be written as a
    ray(dist) = origin + dist*direction and solve for dist.
*/
bool Sphere::hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const
{
    // vector ray origin -> sphere center
    Vec3 oc = ray.origin() - this->center;
    
    // Code simplifies by changing b to b/2.
    double a = ray.direction().length_squared();
    double half_b = dot(oc, ray.direction());
    double c = oc.length_squared() - radius*radius;

    double discriminant = half_b*half_b - a*c;

    // Ray does not intersect with sphere
    if (discriminant < 0) return false;

    // Apply camera/ray clipping (solves shadow acne)
    double sqrt_d = std::sqrt(discriminant);
    double ray_length = (-half_b - sqrt_d)/a;
    if (ray_length < min_ray_length || ray_length > max_ray_length)
    {
        ray_length = (-half_b + sqrt_d)/a;
        if (ray_length < min_ray_length || ray_length > max_ray_length)
            return false;
    }
        
    
    hit_rec.ray_length = ray_length;
    hit_rec.p = ray.at(hit_rec.ray_length);
    Vec3 outward_normal = this->get_outward_normal(hit_rec.p);
    hit_rec.set_face_normal(ray, outward_normal);
    hit_rec.mat_ptr = mat_ptr;

    get_sphere_uv(outward_normal, hit_rec.u, hit_rec.v);

    return true;
}

Vec3 Sphere::get_outward_normal(const Point3& p) const
{
    return (p - center)/radius;
}

void Sphere::get_sphere_uv(const Point3& p, double& u, double &v)
{
    assert(approx_equals(p.length(), 1));

    double theta = std::acos(-p.y());
    double phi = std::atan2(-p.z(), p.x()) + PI;

    u = phi / (2*PI);
    v = theta / PI;
}