#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include <string>
#include <fstream>

/** @file log.hpp
 * This file defines various functions and variables for logging.
 */

using namespace std;

namespace mp
{
    extern bool debug_mode;

    extern ofstream log_file;

    extern string level_severe;
    extern string level_error;
    extern string level_warning;
    extern string level_info;
    extern string level_config;

    /** Function for logging.
     *
     * \param filename name of the file and eventually the path.
     * \param level_name level name to use.
     * \param msg Text to log.
     * \param ... optionals parameters to use with format codes.
     *
     * You can format the text to log with :\n
     * %%i : display an integer.\n
     * %%f : display a decimal value.\n
     * Theses values are passed as optional parameters.
     */
    void log(const string &filename, const string &level_name, const string &msg, ...);
};

#endif // LOG_HPP_INCLUDED
