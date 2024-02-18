#pragma once
#include "resource.hpp"

class Shader : public IResource
{
	std::string shaderTxt{};

public:
	Shader(const std::string& pPath);

	std::string GetSource() const;
};
