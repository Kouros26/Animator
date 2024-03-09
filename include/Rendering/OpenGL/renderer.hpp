#pragma once
#include <memory>
#include <vector>

#include "camera.hpp"
#include "shader.hpp"

class GameObject;

class Renderer
{
	std::vector<std::shared_ptr<Shader>> shaders;

	unsigned int shaderProgram;

	bool drawWireFrame = false;

public:
	Renderer(const Camera& camera);
	~Renderer();

	void Clear() const;

	void Render(std::vector<GameObject>& objects, Camera& camera) const;

	void ToggleWireFrame();

	bool GetDrawWireFrame() const;

private:
	void CreateShaders();
	void LinkAttributes();
	void SetupCamera(const Camera& camera) const;
};
