#include "Rendering/OpenGL/shader.hpp"

#include <iostream>
#include <glad/glad.h>

Shader::Shader(const std::string& pPath, unsigned type)
	: IResource(pPath)
{
	switch (type)
	{
	case 0:
		Id = glCreateShader(GL_VERTEX_SHADER);
		break;

	case 1:
		Id = glCreateShader(GL_FRAGMENT_SHADER);
		break;

	case 2:
		Id = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	default: 
		std::cout << "Shader type invalid" << "\n";
		return;
	}

	const std::string shaderSourceString = ReadFile(pPath);
	const char* shaderSource = shaderSourceString.c_str();

	glShaderSource(Id, 1, &shaderSource, nullptr);
	glCompileShader(Id);

	int  success;
	char infoLog[512];
	glGetShaderiv(Id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(Id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::Use() const
{
	glUseProgram(Id);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(Id, name.c_str()), static_cast<int>(value));
}
void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
}
void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
}

int Shader::GetId() const
{
	return Id;
}
