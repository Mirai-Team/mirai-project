#ifndef STRING_FUNCTIONS_HPP_INCLUDED
#define STRING_FUNCTIONS_HPP_INCLUDED

#include <string>
#include <vector>

#include "MiraiProject/util/string_functions.tpp"

/** @file string_functions.hpp
 * \brief This file define various functions to manipulate std::string.
 */

namespace mp
{
    /** \brief Remove the given letter from the given string. 
	 *
	 * \param str : the string to modify by reference.
	 * \param letter : the letter to remove.
	 */
    void stripLetter(std::string &str, const char &letter);

    /** \brief Get a uppercase version from a string. 
	 * 
	 * \param text : the string to convert.
	 * \return the given string but with each character in uppercase. 
	 */
    std::string upper(std::string text);

    /** \brief Split the given string using the given separator (a single letter).
	 *
	 * \param text : the text to explode.
	 * \param separator : the character to use as separator.
     * \param limit : specifies the number of separator until the function stop splitting. If limit = 0, there is no limit
	 *
     * \return All part of the given string in a vector<string>.
     */
    std::vector<std::string> split(const std::string &text, const char &separator, unsigned int limit=0);

    /** \brief Replace all chosen occurrences by a given string in the given text. 
	 *
	 * \param text : the text where replace operation should be operated.
	 * \param toReplace : occurrence to replace.
	 * \param replaceWith : string which will replace the occurrences.
	 * 
	 * \return the string with all occurrences replaced.
	 */
    std::string replace(std::string &text, std::string toReplace, std::string replaceWith);

    /** \brief Convert the given object into string if possible by using an ostringstream object.
	 *
	 * \param object : the object to convert.
	 * \return the given object converted into string.
	 */
    template<typename T> std::string toString(const T &object);
}

#endif // STRING_FUNCTIONS_HPP_INCLUDED
