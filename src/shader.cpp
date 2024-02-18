#include "shader.hpp"

Shader::Shader(const std::string& pPath)
{
	shaderTxt = ReadFile(pPath);
}

std::string Shader::GetSource() const
{
	return shaderTxt;
}
