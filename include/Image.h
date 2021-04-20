#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <iostream>

#include "Vec3.h"

class Image
{
    private:
        const int rows, cols;
        std::vector<Vec3> data;

    public:
        Image(int rows, int cols);

        int get_rows() const;
        int get_cols() const;
        int get_size() const;

        std::string to_string() const;

        Vec3 get(int row, int col) const;

        void set(int row, int col, const Vec3& value);

        int save_image(const std::string& filename) const;
};

std::ostream &operator<<(std::ostream& ostream, Image& image);

#endif