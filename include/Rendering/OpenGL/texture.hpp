#pragma once
#include "Resources/resource.hpp"

class Texture : public IResource
{
public:
	Texture(const std::string& pFilePath);
	~Texture();

	[[nodiscard]] constexpr std::string GetName() const;
	[[nodiscard]] constexpr unsigned GetId() const;
private:

	std::string name;

	unsigned int Id;

	bool valid = false;
};

constexpr std::string Texture::GetName() const
{
	return name;
}

constexpr unsigned Texture::GetId() const
{
	return Id;
}
