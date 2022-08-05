#ifndef LOGGER_H
#define LOGGER_H

#include <LogItem.h>
#include <queue>
#include <mutex>

class ThreadSafeLogger
{
	public:
		static ThreadSafeLogger& getInstance(void);
		~ThreadSafeLogger();
		void log(const LogLevel& level, const std::string& message);

	private:
		ThreadSafeLogger(void) = default;
		//~ThreadSafeLogger() = default;
		ThreadSafeLogger(ThreadSafeLogger const&) = delete;
		ThreadSafeLogger(ThreadSafeLogger&&) = delete;
		ThreadSafeLogger& operator=(ThreadSafeLogger const&) = delete;
		ThreadSafeLogger& operator=(ThreadSafeLogger &&) = delete;

		void writeToFile(void);
		
		unsigned long int flushCount = 5;
		std::queue<LogItem> items;
		mutable std::mutex itemsMutex;
};

#endif