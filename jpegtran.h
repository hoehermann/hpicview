/**
 * This is the rotation functionality taken from libjpeg's jpegtran.c.
 */

#include <string>

class JPEGtran
{
    public:
        virtual ~JPEGtran();
        static std::string rotate_left(std::string input);
        static std::string rotate_right(std::string input);
    protected:
    private:
    JPEGtran();
};
