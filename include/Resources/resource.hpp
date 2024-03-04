#pragma once
#include <string>

class IResource
{
protected:

	std::string resourcePath;

	//IResource(const std::string& pPath);

public:

	static std::string ReadFile(const std::string& pPath);
};
