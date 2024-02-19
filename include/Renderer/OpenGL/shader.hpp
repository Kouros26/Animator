#pragma once
#include "resource.hpp"

class Shader : public IResource
{
	unsigned int Id;

public:
	Shader(const std::string& pPath, unsigned type);

	void Use() const;

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	[[nodiscard]] int GetId() const;
};
