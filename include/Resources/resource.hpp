#pragma once
#include <string>

class IResource
{
protected:

	std::string resourcePath;

public:

	IResource(const std::string& pPath);
	virtual ~IResource();

	constexpr std::string GetPath() const;
	static std::string ReadFile(const std::string& pPath);
};

constexpr std::string IResource::GetPath() const
{
	return resourcePath;
}
