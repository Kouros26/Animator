#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "resource.hpp"
#include "task.hpp"
#include "threadpool.hpp"

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();

	void RunTasks();
	void SyncTasks();

	//static std::unordered_map<std::string, Task>& GetTasks() { return tasks; }
	//static std::unordered_map<std::string, Task>& GetCompletedTasks() { return completedTasks; }
	static std::unordered_map<std::string, std::shared_ptr<IResource>>& GetResources() { return resources; }

private:

	ThreadPool threadPool;

	//static std::unordered_map<std::string, Task> tasks;
	//static std::unordered_map<std::string, Task> completedTasks;

	static std::unordered_map<std::string, std::shared_ptr<IResource>> resources;
};
