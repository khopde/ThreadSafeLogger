#ifndef LOGGER_H
#define LOGGER_H

#include <LogItem.h>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

class ThreadSafeLogger
{
	public:
		static ThreadSafeLogger& getInstance(void);
		~ThreadSafeLogger();

		void init(const LogLevel& level, const unsigned long int& flushCount);
		void shutDown(void);
		void log(const LogLevel& level, const std::string& message);

	private:
		ThreadSafeLogger(void);
		ThreadSafeLogger(ThreadSafeLogger const&) = delete;
		ThreadSafeLogger(ThreadSafeLogger&&) = delete;
		ThreadSafeLogger& operator=(ThreadSafeLogger const&) = delete;
		ThreadSafeLogger& operator=(ThreadSafeLogger &&) = delete;

		void monitor(void);
		void writeToFile(void);
		
		unsigned long int flushCount = 5;
		LogLevel logLevel = LogLevel::ERROR;

		std::queue<LogItem> items;
		mutable std::mutex itemsMutex;
		std::condition_variable flushCondition;
		std::unique_ptr<std::thread> monitorThread;
};

#endif