#ifndef STRING_FUNCTIONS_HPP_INCLUDED
#define STRING_FUNCTIONS_HPP_INCLUDED

#include <string>
#include <vector>

#include "util/string_functions.tpp"

/** @file string_functions.hpp
 * This file defines various functions to manipulate std::string.
 */

using namespace std;

namespace mp
{
    /** Remove the given letter from the given string. */
    void strip_letter(string &str, const char &letter);

    /** Return the given string all switched to capslock. */
    string upper(string text);

    /** Split the given string using the given separator (a single letter).
     * The limit specifies the number of separator until the function stop splitting.
     * If limit = 0, there is no limit
     * All part of the given string are returned in a vector<string>.
     */
    vector<string> split(const string &text, const char &separator, unsigned int limit=0);

    /** Replace occurrences by a given string in the given text. */
    string replace(string &text, string to_replace, string replace_with);

    /** Return the given value converted into string. */
    template<typename T> string to_string(const T &value);
}

#endif // STRING_FUNCTIONS_HPP_INCLUDED
