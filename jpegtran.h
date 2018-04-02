/**
 * This is the rotation functionality taken from libjpeg's jpegtran.c.
 */

#include <string>

class JPEGtran
{
    public:
        JPEGtran();
        virtual ~JPEGtran();
        std::string rotate_left(std::string input);
        std::string rotate_right(std::string input);
    protected:
    private:
};
