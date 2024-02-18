#pragma once
#include <vector>
#include <glad/glad.h>

#include "shader.hpp"

class Renderer
{
	std::vector<Shader> shaders;

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	unsigned int shaderProgram;

	void GenerateBuffers();
	void CreateShaders();
	void LinkAttributes();

public:
	Renderer();
	~Renderer();

	void Render() const;
};
