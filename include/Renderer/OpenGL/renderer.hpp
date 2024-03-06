#pragma once
#include <vector>

#include "shader.hpp"

class GameObject;

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

	void Render(const std::vector<GameObject>& objects) const;

	void ToggleWireFrame();

	bool GetDrawWireFrame() const;

private:
	void GenerateBuffers();
	void CreateShaders();
	void LinkAttributes();
};
