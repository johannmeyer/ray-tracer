#include "ImplicitShape.h"

Vec3 ImplicitShape::get_outward_normal(const Point3& p) const
{
    double delta = 1e-6;
    return unit_vector(Vec3( 
                this->get_distance(p + Vec3(delta, 0, 0)) - this->get_distance(p - Vec3(delta, 0, 0)), 
                this->get_distance(p + Vec3(0, delta, 0)) - this->get_distance(p - Vec3(0, delta, 0)), 
                this->get_distance(p + Vec3(0, 0, delta)) - this->get_distance(p - Vec3(0, 0, delta))));
}

bool ImplicitShape::hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const
{

    AABB aabb;
    this->bounding_box(aabb);

    if (!aabb.hit(ray, min_ray_length, max_ray_length))
        return false;

    double curr_ray_length = min_ray_length;
    
    while (curr_ray_length < 100)
    {
        Point3 curr_pos = ray.at(curr_ray_length);
        double dist_to_surface = this->get_distance(curr_pos);

        if (dist_to_surface < epsilon*curr_ray_length)
        {   
            hit_rec.ray_length = curr_ray_length;
            hit_rec.p = curr_pos;
            Vec3 outward_normal = this->get_outward_normal(hit_rec.p);
            hit_rec.set_face_normal(ray, outward_normal);
            hit_rec.mat_ptr = this->get_material();

            return true;
        }
        curr_ray_length += dist_to_surface;
    }
    return false;
}