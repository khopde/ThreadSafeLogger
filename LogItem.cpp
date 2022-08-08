#include <LogItem.h>
#include <Utils.h>
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
	out << usec_time_to_string(item.time) << " [" << logLevelToString(item.level) << "] " << item.message;
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