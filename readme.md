Build:
	g++ -std=c++14 -g3 -o3 -I./include LogItem.cpp ThreadSafeLogger.cpp log_test.cpp -lpthread -o build/logtest

Run
	./build/logtest