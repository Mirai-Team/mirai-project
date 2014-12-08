#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdarg>

#include "General/log.hpp"
#include "General/string_functions.hpp"

using namespace std;

bool mp::debug_mode{ false };

ofstream mp::log_file;

string mp::level_severe{ "SEVERE" };
string mp::level_warning{ "WARNING" };
string mp::level_info{ "INFO" };
string mp::level_config{ "CONFIG" };

void mp::log(const string &filename, const string &level_name, const string &msg, ...)
{
    if (debug_mode)
    {
        // current date/time based on current system
        time_t now(time(0));
        struct tm *timeinfo(localtime(&now));
        int hour{ timeinfo->tm_hour }, minute{ timeinfo->tm_min }, second{ timeinfo->tm_sec };
        ostringstream text;
        va_list ap; // Extra parameters.
        va_start(ap, msg);

        text << "[";
        if (hour < 10)
            text << "0";
        text << hour << ":";
        if (minute < 10)
            text << "0";
        text << minute << ":";
        if (second < 10)
            text << "0";

        //Maybe add a separator between second and level_name ?
        text << second << " " << upper(level_name) << "] ";

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
                }
            }
            else
                text << msg[i];
        }

        va_end(ap);

        cout << text.str() << endl;

        log_file.open(filename, ios::app);
        log_file << text.str() << endl;
        log_file.close();
    }
}
