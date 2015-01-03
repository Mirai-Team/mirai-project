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
#include <chrono>
#include <iomanip>

#include "MiraiProject/util/Logger.hpp"
#include "MiraiProject/util/LogStream.hpp"
#include "MiraiProject/util/string_functions.hpp"

using namespace std;

ostream& operator<< (ostream& stream, const tm* time)
{
    //We write values on two digits.
	return stream << 1900 + time->tm_year << '-' 
		<< setfill('0') << setw(2) << time->tm_mon + 1 << '-'
		<< setfill('0') << setw(2) << time->tm_mday << ' '
		<< setfill('0') << setw(2) << time->tm_hour << ':'
		<< setfill('0') << setw(2) << time->tm_min << ':'
		<< setfill('0') << setw(2) << time->tm_sec;
}

// 0 in time_ are for -Wmissing-field-initializers
mp::Logger::Logger(string filename) : mutex_ { }, file_ { }, time_ { 0,0,0,0,0,0,0,0,0,0,0 }
{
	if(mp::debugMode)
		file_.open(filename, fstream::app);
}

mp::Logger::~Logger()
{
	if(mp::debugMode)
		file_.flush();
		file_.close();
}

mp::Logstream mp::Logger::operator()()
{
	return mp::Logstream(*this, "INFO");
}

mp::Logstream mp::Logger::operator()(string priority)
{
	return mp::Logstream(*this, priority);
}

const tm* mp::Logger::getLocalTime()
{
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm *time;
    time = localtime(&tt);
	return time;
}

void mp::Logger::log(string priority, string msg)
{
	if(mp::debugMode)
	{
		mutex_.lock();
		file_ << '[' << getLocalTime() << ']'
			<< '[' << mp::upper(priority) << "]\t"
			<< msg << endl;
		mutex_.unlock();
	}
}
