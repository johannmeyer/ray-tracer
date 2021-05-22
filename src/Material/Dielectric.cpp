#include "Material.h"

bool Dielectric::scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    attenuation = albedo;
    // assumes index of refraction of incident ray medium is air = 1.0
    double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

    Vec3 unit_incident_direction = unit_vector(incident.direction());
    double cos_theta = fmin(dot(-unit_incident_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

    const bool cannot_refract = refraction_ratio * sin_theta > 1.0;

    Vec3 direction;
    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
    {
        // reflect
        direction = unit_incident_direction.reflect(rec.normal);
    }
    else
    {
        // refract
        direction = unit_incident_direction.refract(rec.normal, refraction_ratio);
    }
    scattered = Ray(rec.p, direction);
    return true;
}

double Dielectric::reflectance(double cos_theta, double eta_t)
{
    // Use Schlick's approximation for reflectance.
    const double eta_i = 1.0;
    double r0 = (eta_i - eta_t)/(eta_i + eta_t);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cos_theta),5);
}