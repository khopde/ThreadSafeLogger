#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono>

std::string timestamp_to_string(time_t timestamp, const std::string& format)
{
	char buffer[256];
	buffer[0] = '0';
	std::strftime( buffer, sizeof(buffer), format.c_str(), std::localtime(&timestamp) );

	return buffer;
}

std::string timepoint_to_string
(
	const std::chrono::system_clock::time_point& timePoint,
	const std::string& format
)
{
	return timestamp_to_string(std::chrono::system_clock::to_time_t(timePoint), format);
}

std::string usec_time_to_string( const std::chrono::system_clock::time_point& timePoint )
{
	const auto timeMs = std::chrono::duration_cast<std::chrono::microseconds>(timePoint.time_since_epoch()) % 1000000;
	return ( timepoint_to_string(timePoint, "%T") + '.' + std::to_string(timeMs.count()) );
}

#endif