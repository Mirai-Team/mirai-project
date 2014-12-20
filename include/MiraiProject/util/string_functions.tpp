#ifndef STRING_FUNCTIONS_TPP_INCLUDED
#define STRING_FUNCTIONS_TPP_INCLUDED

#include <sstream>

using namespace std;

namespace mp
{
    template<typename T>
    string to_string(const T &value)
    {
        ostringstream oss;
        oss << value;
        return oss.str();
    }
}

#endif // STRING_FUNCTIONS_TPP_INCLUDED
