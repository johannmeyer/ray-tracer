#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <string>
#include <iostream>

class ProgressBar
{
    public:
        int max;
        std::string message;

        ProgressBar(int max) : ProgressBar(max, "Progress") {}
        ProgressBar(int max, std::string message) : max(max), message(message) {}

        void update(int value)
        {
            std::cerr << "\r" + message << ": " << (value*100)/max << "% complete";
            if (value == max)
                std::cerr << std::endl;
        }
};

#endif