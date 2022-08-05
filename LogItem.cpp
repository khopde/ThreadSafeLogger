#include <LogItem.h>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

LogItem::LogItem( const LogLevel& level, const std::string& message )
: time { std::chrono::system_clock::now() },
  level { level},
  message { message }
{}

std::chrono::system_clock::time_point LogItem::getTime(void) const
{
	return time;
}

LogLevel LogItem::getLevel(void) const
{
	return level;
}

std::ostream & operator<< (std::ostream &out, LogItem const &item)
{
	out << serializeTimePoint(item.time, "%T") << " [" << logLevelToString(item.level) << "] " << item.message;
	return out;
}


std::string logLevelToString(const LogLevel& level)
{
	switch(level)
	{
		case LogLevel::ERROR:
		return "ERROR";
		break;

		case LogLevel::WARN:
		return "WARN";
		break;

		case LogLevel::INFO:
		return "INFO";
		break;

		case LogLevel::DEBUG:
		return "DEBUG";
		break;
	}

	return "";
}

std::string serializeTimePoint( const std::chrono::system_clock::time_point& time, const std::string& format)
{
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    //std::tm tm = *std::gmtime(&tt); //GMT (UTC)
    std::tm tm = *std::localtime(&tt); //Locale time-zone, usually UTC by default.
    std::stringstream ss;
    ss << std::put_time( &tm, format.c_str() );
    return ss.str();
}