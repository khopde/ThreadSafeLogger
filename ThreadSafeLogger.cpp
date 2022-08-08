#include <ThreadSafeLogger.h>
#include <iostream>
#include <thread>


ThreadSafeLogger& ThreadSafeLogger::getInstance(void)
{
	static ThreadSafeLogger instance;
	return instance;
}

ThreadSafeLogger::ThreadSafeLogger(void)
 : monitorThread(nullptr)
 {}

void ThreadSafeLogger::init(const LogLevel& level, const unsigned long int& flushCount)
{
	if(!monitorThread)
	{
		this->flushCount = flushCount;
		this->logLevel = level;
		monitorThread = std::unique_ptr<std::thread>( new std::thread( &ThreadSafeLogger::monitor, this ) );
	}
}

void ThreadSafeLogger::shutDown(void)
{
	if(!monitorThread)
	{
		return;
	}
	
	//Scope for unique lock
	{
		std::unique_lock<std::mutex> lock(itemsMutex);
		writeToFile();
	}

	monitorThread->join();
	monitorThread = nullptr;
}

ThreadSafeLogger::~ThreadSafeLogger()
{
	std::unique_lock<std::mutex> lock(itemsMutex);
	writeToFile();
}

void ThreadSafeLogger::log(const LogLevel& level, const std::string& message)
{
	if(level > logLevel)
	{
		return;
	}
	else
	{
		std::unique_lock<std::mutex> lock(itemsMutex);
		items.push( LogItem{ level, message } );
		flushCondition.notify_one();
	}
}

void ThreadSafeLogger::monitor(void)
{
	while(1)
	{
		//Scope for unique_lock
		{
			std::unique_lock<std::mutex> lock(itemsMutex);
			while( items.size() < flushCount )
			{
				flushCondition.wait(lock);
			}

			if( items.size() < flushCount )
			{
				continue;
			}

			writeToFile();
		}
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