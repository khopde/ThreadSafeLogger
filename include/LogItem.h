#ifndef LOGITEM_H
#define LOGITEM_H

#include <string>
#include <chrono>

enum class LogLevel
{
	ERROR,
	WARN,
	INFO,
	DEBUG
};

class LogItem
{
	public:
		LogItem( const LogLevel& level, const std::string& message );
		std::chrono::system_clock::time_point getTime(void) const;
		LogLevel getLevel(void) const;
		friend std::ostream & operator<< (std::ostream &out, LogItem const &item);

	private:
		LogLevel level;
		std::chrono::system_clock::time_point time;
		std::string message;
};

std::ostream & operator<< (std::ostream &out, LogItem const &item);
std::string logLevelToString(const LogLevel& level);
std::string serializeTimePoint( const std::chrono::system_clock::time_point& time, const std::string& format);
#endif