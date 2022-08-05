#include <ThreadSafeLogger.h>
#include <iostream>


ThreadSafeLogger& ThreadSafeLogger::getInstance(void)
{
	static ThreadSafeLogger instance;
	return instance;
}

void ThreadSafeLogger::log(const LogLevel& level, const std::string& message)
{
	std::lock_guard<std::mutex> lock(itemsMutex);
	
	items.push( LogItem{ level, message } );
	if(items.size() >= flushCount)
	{
		writeToFile();
	}
}

void ThreadSafeLogger::writeToFile(void)
{
	while( items.size() )
	{
		std::cout << items.front() << std::endl;
		items.pop();
	}
}