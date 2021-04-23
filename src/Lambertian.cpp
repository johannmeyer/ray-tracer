#include "Material.h"

bool Lambertian::scatter(const Ray& /*incident*/, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    // scatter_direction is independent of incident ray's direction
    Vec3 scatter_direction = rec.normal + Vec3::random_unit_vector();
    // Catch degenerate scatter direction
    if (scatter_direction.approx_equals(Vec3(0,0,0)))
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}