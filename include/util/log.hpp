#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include <string>
#include <fstream>

/** @file log.hpp
 * This file defines various functions and variables for logging.
 */

namespace mp
{
    extern bool debug_mode;

    extern std::ofstream log_file;

    extern std::string level_severe;
    extern std::string level_error;
    extern std::string level_warning;
    extern std::string level_info;
    extern std::string level_config;

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
    void log(const std::string &filename, const std::string &level_name, const std::string &msg, ...);
};

#endif // LOG_HPP_INCLUDED
