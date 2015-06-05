////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.fr)
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

#include "MiraiProject/parser/Parser.hpp"

using namespace std;

namespace mp
{
    template<>
    string Parser::fileParser<string>(string inputFile, string variableName, char separator, bool isEncrypted, string key)
    {
        string line;
        vector<string> words;
        string value;
        ifstream file;

        mp::Logger log("mirai_project.log");

        if(isEncrypted && key != "")
        {

            mp::Encryption EncryptMotor(key);
            stringstream filedata(EncryptMotor.encryptFile(inputFile));

            while(getline(filedata,line))
            {
                words = mp::StringUtilities::split(line, separator);
                if(words[0] == variableName)
                    value = words[1];
            }
        }
        else if(!isEncrypted)
        {
            file.open(inputFile, ios::in);
            if(file)
            {
                while(getline(file,line))
                {
                    words = mp::StringUtilities::split(line, separator);
                    if(words[0] == variableName)
                        value = words[1];
                }
            }
            else
                log(Logger::priorityWarning) << "The file doesn't exist";
        }
        else
            log(Logger::priorityError) << "File encrypted, and no key provided";

        return value;
    }

    template<>
    vector<string> mp::Parser::vFileParser<string>(string inputFile, string variableName,
                                                   char separator, char separatorValues,
                                                   bool isEncrypted, string key)
    {
        string line;
        vector<string> words;
        vector<string> values;
        ifstream file;

        mp::Logger log("mirai_project.log");

        if(isEncrypted && key != "")
        {
            mp::Encryption EncryptMotor(key);
            stringstream filedata(EncryptMotor.encryptFile(inputFile));

            while(getline(filedata,line))
            {
                words = mp::StringUtilities::split(line, separator);
                if(words[0] == variableName)
                {
                    vector<string> temp = mp::StringUtilities::split(words[1], separatorValues);
                    for(unsigned int i = 0; i < temp.size(); i++)
                    {
                        values.push_back(temp[i]);
                    }
                }
            }
        }
        else if(!isEncrypted)
        {
            file.open(inputFile, ios::in);
            if(file)
            {
                while(getline(file,line))
                {
                    words = mp::StringUtilities::split(line, separator);
                    if(words[0] == variableName)
                    {
                        vector<string> temp = mp::StringUtilities::split(words[1], separatorValues);
                        for(unsigned int i = 0; i < temp.size(); i++)
                        {
                            values.push_back(temp[i]);
                        }
                    }
                }
            }
            else
            {
                log(Logger::priorityWarning) << "The file doesn't exist";
            }
        }
        else
            log(Logger::priorityError) << "File encrypted, and no key provided";

        return values;

    }
}

string mp::Parser::put_time(const struct tm* tmb, const string &format)
{
    ostringstream formatedTime;

    string abbrDays[7] = { "Sun", "Mon", "Tues", "Wed", "Thu", "Fri", "Sat"  };
    string days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"  };
    string month[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    string abbrMonth[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };

    for(unsigned int i = 0; i < format.length(); i++)
    {
        if(format[i] == '%')
            i++;

        switch(format[i])
        {
            case 'a':
                formatedTime << abbrDays[tmb->tm_wday] << " ";
                break;
            case 'A':
                formatedTime << days[tmb->tm_wday] << " ";
                break;
            case 'b':
                formatedTime << abbrMonth[tmb->tm_mon] << " ";
                break;
            case 'B':
                formatedTime << month[tmb->tm_mon] << " ";
                break;
            case 'c':
                formatedTime << abbrDays[tmb->tm_wday] << " " << abbrMonth[tmb->tm_mon] << " " << setfill('0') << setw(2) << tmb->tm_mday << " " << setfill('0') << setw(2) << tmb->tm_hour << ":" << setfill('0') << setw(2) << tmb->tm_min << ":" << setfill('0') << setw(2) << tmb->tm_sec << " " << tmb->tm_year + 1900 << " ";
                break;
            case 'C':
                formatedTime << static_cast<int>(tmb->tm_year/100);
                break;
            case 'd':
                formatedTime << setfill('0') << setw(2) << tmb->tm_mday << " ";
                break;
            case 'D':
                formatedTime << setfill('0') << setw(2) << tmb->tm_mon + 1 << "/" << setfill('0') << setw(2) << tmb->tm_mday << "/" << tmb->tm_year%100 << " ";
                break;
            case 'e':
                formatedTime << tmb->tm_mday << " ";
                break;
            case 'F':
                formatedTime << tmb->tm_year +1900 << "-" << tmb->tm_mon + 1 << "-" << tmb->tm_mday << " ";
                break;
            case 'G':
                formatedTime << tmb->tm_year +1900 << " ";
                break;
            case 'h':
                formatedTime << abbrMonth[tmb->tm_mon] << " ";
                break;
            case 'm':
                formatedTime << setfill('0') << setw(2) << tmb->tm_mon << " ";
                break;
            case 'M':
                formatedTime << setfill('0') << setw(2) <<  tmb->tm_min << " ";
                break;
            case 'n':
                formatedTime << endl;
                break;
            case 'R':
                formatedTime << setfill('0') << setw(2) << tmb->tm_hour << ":" << setfill('0') << setw(2) << tmb->tm_min << " ";
                break;
            case 'S':
                formatedTime << tmb->tm_sec << " ";
                break;
            case 't':
                formatedTime << "\t";
                break;
            case 'T':
                formatedTime << setfill('0') << setw(2) << tmb->tm_hour << ":" << setfill('0') << setw(2) << tmb->tm_min << ":" << setfill('0') << setw(2) << tmb->tm_sec << " ";
                break;
            case 'w':
                formatedTime << tmb->tm_wday << " ";
                break;
            case 'y':
                formatedTime << tmb->tm_year%100 << " ";
                break;
            case 'Y':
                formatedTime << tmb->tm_year +1900 << " ";
                break;
            default:
                break;
        }
    }

    return formatedTime.str();
}
