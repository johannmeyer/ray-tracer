#include "Texture.h"

using namespace std;

Color CheckerTexture::get_value(double u, double v, const Point3& p) const
{
    double sines = sin(10*p.x()) * sin(10*p.y()) * sin(10*p.z());
    if (sines < 0)
        return odd->get_value(u, v, p);
    else
        return even->get_value(u, v, p);
}