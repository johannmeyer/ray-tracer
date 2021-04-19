#include <iostream>
#include "Image.h"
#include "Vec3.h"

int main()
{
    // Image

    const int image_cols = 512;
    const int image_rows = 256;
    Image image(image_rows, image_cols);
    

    for (int r = 0; r < image.get_rows(); r++)
    {
        for (int c = 0; c < image.get_cols(); c++)
        {
            Color pixel_color(double(c) / (image_rows-1),
                              double(r) / (image_cols-1),
                              0.25);

            image.set(r,c,pixel_color);
        }
    }

    image.save_image("ImageTest.ppm");
}
