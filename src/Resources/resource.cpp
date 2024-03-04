#include "Resources/resource.hpp"

#include <fstream>


//IResource::IResource(const std::string& pPath)
//{
//	resourcePath = pPath;
//}

std::string IResource::ReadFile(const std::string& pPath)
{
	std::string content{};
	std::ifstream file(PROJECT_PATH + pPath);

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			content.append(line + "\n");

		file.close();
	}
	return content;
}
