#include "Image.h"
#include <iostream>
#include <fstream>
#include <cstring>

#include "Ascii.h"

// Helper function for indices
#define ind(r,c) (r*cols + c)


// Constructor
Image::Image(int rows, int cols) : 
                rows(rows),
                cols(cols),
                data(cols*rows, Vec3(0,0,0)){}


int Image::get_rows() const
{
    return rows;
}

int Image::get_cols() const
{
    return cols;
}

int Image::save_image(const std::string& filename) const
{
    std::ofstream file;

    file.open(filename);
    if (file.fail())
    {
        std::cerr << std::strerror(errno) << std::endl;
        return -1;
    }

    file << "P3\n" << std::endl 
         << cols << ' ' << rows << std::endl
         << "255" << std::endl;

    file << this->to_string();

    file.close();
    if (file.fail())
    {
        std::cerr << std::strerror(errno) << std::endl;
        return -1;
    }

    return 0;   
}

std::string Image::to_string() const
{
    std::string output;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            Color pixel_color = this->get(r,c);
            double r = pixel_color.x();
            double g = pixel_color.y();
            double b = pixel_color.z();

            // Gamma correct (gamma = 2)
            r = std::sqrt(r);
            g = std::sqrt(g);
            b = std::sqrt(b);

            output += std::to_string(static_cast<int>(clamp(r,0,1)*255)) + ' ';
            output += std::to_string(static_cast<int>(clamp(g,0,1)*255)) + ' ';  
            output += std::to_string(static_cast<int>(clamp(b,0,1)*255)) + '\n'; 
        }
    }
    return output;
}

Vec3 Image::get(int r, int c) const
{
    return data[ind(r,c)];
}

void Image::set(int r, int c, const Vec3& v)
{
    data[ind(r,c)] = v;
}

/*
    Converts the image to a grayscale ASCII representation of the image.
*/
Image Image::to_ascii_image()
{
    const int new_rows = rows - (rows % ASCII_HEIGHT);
    const int num_ascii_per_col = rows/ASCII_HEIGHT;
    const int new_cols = cols - (cols % ASCII_WIDTH);
    const int num_ascii_per_row = cols/ASCII_WIDTH;

    Image ascii_image(new_rows, new_cols);
    for (int r = 0; r < num_ascii_per_col; r++)
    {
        for (int c = 0; c < num_ascii_per_row; c++)
        {
            const Color old_color = this->get(r*ASCII_HEIGHT+ASCII_HEIGHT/2, c*ASCII_WIDTH+ASCII_WIDTH/2);
            const int brightness = (old_color.x() + old_color.y() + old_color.z())*(ASCII_TABLE_LENGTH-1)/3.0;
            const bool *character = ASCII_TABLE[brightness];
            
            // This loop can be executed in parallel and enables resuse of the above data.
            // Additionally, better cache locality, since neighbouring threads access the same character.
            for (int i = 0; i < ASCII_LENGTH; i++)
            {
                Color pixel_color(character[i],character[i], character[i]);
                ascii_image.set(r*ASCII_HEIGHT + i/ASCII_WIDTH,c*ASCII_WIDTH + i%ASCII_WIDTH, pixel_color);
            }
        }
    }
    return ascii_image;
}

std::ostream &operator<<(std::ostream& ostream, Image& image)
{
    return ostream << image.to_string();
}