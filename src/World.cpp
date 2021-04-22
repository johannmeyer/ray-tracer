#include "World.h"
#include "Utility.h"

void World::clear()
{
    objects.clear();
}

void World::add(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

/*
    Iterate through all objects in world scene and find closest object hit by a ray.
*/
bool World::hit(const Ray& ray, double min_ray_length, double max_ray_length, HitRecord& hit_rec) const
{
    HitRecord temp_hit_rec;
    bool hit_anything = false;

    double dist_closest_object = max_ray_length;

    for (const auto& object : objects)
    {
        if (object->hit(ray, min_ray_length, dist_closest_object, temp_hit_rec))
        {
            hit_anything = true;
            dist_closest_object = temp_hit_rec.ray_length;
            hit_rec = temp_hit_rec;
        }
    }

    return hit_anything;
}

/*
    Determines the color of a ray cast in the world.
*/
Color World::get_ray_color(const Ray& ray) const
{
    HitRecord rec;
    // Check if ray hits an object in the scene
    if (this->hit(ray, 0, INF, rec))
    {
        return 0.5 * (rec.normal + Color(1,1,1));
    }
    else
    {
        return get_background_color(ray);
    }

}

Color World::get_background_color(const Ray& ray) const
{
    Vec3 unit_direction = unit_vector(ray.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    // blend between white and light blue
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}