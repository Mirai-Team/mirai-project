#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
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
        time_t now(time(0));
        struct tm *timeinfo(localtime(&now));
        int hour{ timeinfo->tm_hour }, minute{ timeinfo->tm_min }, second{ timeinfo->tm_sec };
        ostringstream text;
        va_list ap; // Argument pointer
        va_start(ap, msg);

        //Added the current time and level_name
        text << "[";
        text << setfill('0') << setw(2) << hour << ":";
        text << setfill('0') << setw(2) << minute << ":";
        text << setfill('0') << setw(2) << second << "] (" << upper(levelName) << ") >";

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
