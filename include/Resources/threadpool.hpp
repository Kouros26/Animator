#pragma once
#include <thread>
#include <vector>

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void SetThreadCount(unsigned pCount);

	std::vector<std::thread>& GetThreads();
	unsigned GetThreadCount() const;

private:

	std::vector<std::thread> threads;

	unsigned threadCount;

};
