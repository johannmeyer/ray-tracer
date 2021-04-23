#include "Material.h"

#include <iostream>

bool Metal::scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = unit_vector(incident.direction()).reflect(rec.normal);

    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    if (!(dot(scattered.direction(), rec.normal) > 0))
        std::cout << "Metal scatter is negative" << std::endl;
    return (dot(scattered.direction(), rec.normal) > 0);
}