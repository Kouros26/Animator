#pragma once
#include <iostream>
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

	template<typename T, typename... Args>
	inline static std::shared_ptr<T> Get(const std::string& pPath, Args... args);

	inline static std::unordered_map<std::string, std::weak_ptr<IResource>>& GetResources() { return resources; }

private:

	ThreadPool threadPool;
	inline static std::unordered_map<std::string, std::weak_ptr<IResource>> resources;

};

template <typename T, typename ... Args>
inline std::shared_ptr<T> ResourceManager::Get(const std::string& pPath, Args... args)
{
	if (const auto it = resources.find(pPath); it != resources.end())
	{
		return std::static_pointer_cast<T>(it->second.lock());
	}

	auto resource = std::make_shared<T>(pPath, std::forward<Args>(args)...);
	resources[pPath] = resource;

	return resource;
}
