#pragma once
#include <string>

class IResource
{
protected:
	std::string ReadFile(const std::string& pPath);
};
