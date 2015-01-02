////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include <cstdarg>

#include "MiraiProject/util/log.hpp"
#include "MiraiProject/util/string_functions.hpp"

using namespace std;

bool mp::debugMode{ false };

ofstream mp::logFile;

string mp::levelSevere{ "SEVERE" };
string mp::levelError{ "ERROR" };
string mp::levelWarning{ "WARNING" };
string mp::levelInfo{ "INFO" };
string mp::levelConfig{ "CONFIG" };

void mp::log(const string &fileName, const string &levelName, const string &msg, ...)
{
    if (debugMode)
    {
        // current date/time based on current system
        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
		//This following line causes an error.
		tm tm = {0};
		gmtime_r(&tt, &tm);
        ostringstream text;
        va_list ap; // Argument pointer
        va_start(ap, msg);

        //Added the current time and level_name
        text << "[";
        text << setfill('0') << setw(2) << tm.tm_hour << ":";
        text << setfill('0') << setw(2) << tm.tm_min << ":";
        text << setfill('0') << setw(2) << tm.tm_sec << "] (" << upper(levelName) << ") >";

        //Parsing message
        for (unsigned int i{ 0 } ; i < msg.length() ; i++)
        {
            if (msg[i] == '%')
            {
                i++; // Using next letter.

                switch(msg[i])
                {
                    case 'i':
                        text << va_arg(ap, int);
                        break;
                    case 'f':
                        text << va_arg(ap, double);
                        break;
                    case '%': // %% = % in output.
                        text << '%';
                        break;
                    default:
                        break;
                }
            }
            else
                text << msg[i];
        }

        va_end(ap);

        cout << text.str() << endl;

        //write news entries in log file (append mode)
        logFile.open(fileName, ios::app);
        logFile << text.str() << endl;
        logFile.close();
    }
}
