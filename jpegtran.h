/**
 * This provides the rotation functionality taken from libjpeg's jpegtran.c.
 */

#pragma once

#include <string>

class JPEGtran
{
    public:
        static std::string rotate_left(std::string input);
        static std::string rotate_right(std::string input);
    protected:
    private:
};
