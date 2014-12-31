#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include <string>
#include <fstream>

/** @file log.hpp
 * \brief This file defines various functions and variables for logging.
 */

namespace mp
{
    extern bool debugMode;

    extern std::ofstream logFile;

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
     * \param ... optional parameters to use along with format codes.
     *
     * You can format the text to log with :\n
     * %%i : display an integer.\n
     * %%f : display a decimal value.\n
	 * %% : display a % character\n
     * Integer and decimal values are passed as optional parameters.
     */
    void log(const std::string &fileName, const std::string &levelName, const std::string &msg, ...);
}

#endif // LOG_HPP_INCLUDED
