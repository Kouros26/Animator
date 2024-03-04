#pragma once
#include <vector>

#include "shader.hpp"

class Renderer
{
	std::vector<Shader> shaders;

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	unsigned int shaderProgram;

	bool drawWireFrame = false;

public:
	Renderer();
	~Renderer();

	void Clear() const;

	void Render() const;

	void ToggleWireFrame();

	bool GetDrawWireFrame() const;

private:
	void GenerateBuffers();
	void CreateShaders();
	void LinkAttributes();
};
