#include <ThreadSafeLogger.h>
#include <thread>

//Logging macros
#define LOG(level, msg) ThreadSafeLogger::getInstance().log(level, msg)
#define LOG_ERROR(msg) LOG(LogLevel::ERROR, msg)
#define LOG_WARN(msg) LOG(LogLevel::WARN, msg)
#define LOG_INFO(msg) LOG(LogLevel::INFO, msg)
#define LOG_DEBUG(msg) LOG(LogLevel::DEBUG, msg)

void printTable(int num)
{
	for(size_t i=1; i<=100; ++i)
	{
		LOG_DEBUG( std::to_string(num) + " x " + std::to_string(i) + " = " + std::to_string( num*i ) );
	}
}

int main()
{
	std::thread t1(
		[](){ printTable(3); }
	);

	LOG_DEBUG("Hello logger 2");
	LOG_DEBUG("Hello logger 3");
	LOG_INFO("Hello logger 4");

	std::thread t2(
		[](){ printTable(5); }
	);

	LOG_ERROR("Hello logger 5");
	LOG_WARN("Hello logger 6");

	LOG_WARN("Hello logger 7");

	t1.join();
	t2.join();

	LOG_WARN("Hello logger 8");
	return 0;
}