#include "Material.h"

bool Metal::scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = unit_vector(incident.direction()).reflect(rec.normal);

    scattered = Ray(rec.p, reflected + roughness*Vec3::random_in_unit_sphere());
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
}