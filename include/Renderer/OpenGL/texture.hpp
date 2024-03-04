#pragma once
#include "Resources/resource.hpp"

class Texture : public IResource
{
public:
	Texture(const std::string& pFilePath);
	~Texture();

private:

	unsigned int Id;

	bool valid = false;
};
