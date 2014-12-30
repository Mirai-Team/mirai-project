#ifndef STRING_FUNCTIONS_TPP_INCLUDED
#define STRING_FUNCTIONS_TPP_INCLUDED

#include <sstream>

using namespace std;

namespace mp
{
    template<typename T>
    string to_string(const T &object)
    {
        ostringstream oss;
        oss << object;
        return oss.str();
    }
}

#endif // STRING_FUNCTIONS_TPP_INCLUDED
