#include "Resources/threadpool.hpp"

#include <thread>

ThreadPool::ThreadPool()
{
	threadCount = std::thread::hardware_concurrency() - 1;
	threads.reserve(threadCount);
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::SetThreadCount(unsigned pCount)
{
	threadCount = pCount;
}

std::vector<std::thread>& ThreadPool::GetThreads()
{
	return threads;
}

unsigned ThreadPool::GetThreadCount() const
{
	return threadCount;
}
